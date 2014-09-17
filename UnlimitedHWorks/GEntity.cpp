/*  Class Name  : GEntity, GEntityCollide
    Description : Fully handles Entities: movements, speed, actions, collisions, status, flags, ...
    Author      : Aleqh
*/

#include "GEntity.h"

std::vector<GEntity*> 	GEntity::EntityList;

/******************************************************************************************/
// Initialize Entity
GEntity::GEntity()
{
	EntitySurface = NULL;

	X = 0;
	Y = 0;

	Width 	= 0;
	Height 	= 0;

	MoveLeft  = false;
	lastMoveLeft = false;

	MoveRight = false;
    lastMoveRight = true;

    CanJump = false;
    CanAttack = false;

    firstAttack = true;

	Type = 	ENTITY_TYPE_GENERIC;

	Dead = false;
	Flags = ENTITY_FLAG_GRAVITY;

	SpeedX = 0;
	SpeedY = 0;

	AccelX = 0;
	AccelY = 0;

	MaxSpeedX = 15;
	MaxSpeedY = 20;

	CurrentFrameCol = 0;
	CurrentFrameRow = 0;

	Col_X = 0;
	Col_Y = 0;

	Col_Width  = 0;
	Col_Height = 0;
}

/******************************************************************************************/
GEntity::~GEntity()
{}

/******************************************************************************************/
// Loads the Entity's Spritesheet from a file.
bool GEntity::OnLoad(const char* File, int Width, int Height, int MaxFrames)
{
	if((EntitySurface = GSurface::OnLoad(File)) == NULL)
	{
		return false;
	}

    // Applies transparency on the Entity's Surface
	GSurface::Transparent(EntitySurface, 255, 0, 255);

	this->Width = Width;
	this->Height = Height;

	Anim_Control.MaxFrames = MaxFrames;

    return true;
}

/******************************************************************************************/
void GEntity::OnLoop()
{
	//We're not Moving
	if(MoveLeft == false && MoveRight == false)
	{
		StopMove();
	}

    // Indicates whether we are moving Left or Right. Acceleration comes in the opposite direction so we come to a gradual stop.
	if(MoveLeft)
	{
		AccelX = -1.5;
	}
	else if(MoveRight)
	{
		AccelX = 1.5;
	}

    // Checks if Gravity is turned ON for the Entity ( The bigger the number, the faster the fall)
	if(Flags & ENTITY_FLAG_GRAVITY)
	{
		AccelY = 1.50f;
	}

    // Increase the Speed of Entity over time in correlation with the calculated SpeedFactor.
	SpeedX += AccelX * GFPS::FPSControl.GetSpeedFactor();
	SpeedY += AccelY * GFPS::FPSControl.GetSpeedFactor();

	// We check against MaxSpeed to make sure we only go to a certain speed.
	// LEFT/RIGHT
	if(SpeedX > MaxSpeedX)
        SpeedX =  MaxSpeedX;
	if(SpeedX < -MaxSpeedX)
        SpeedX = -MaxSpeedX;
    // UP/DOWN
	if(SpeedY > MaxSpeedY)
        SpeedY =  MaxSpeedY;
	if(SpeedY < -MaxSpeedY)
        SpeedY = -MaxSpeedY;

    // Animate the Entity.
	OnAnimate();

	// Move the Entity
	OnMove(SpeedX, SpeedY);
}

/******************************************************************************************/
void GEntity::OnRender(SDL_Surface* TheSurface)
{
    if(EntitySurface == NULL || TheSurface == NULL)
        return;

    GSurface::OnDraw(TheSurface, EntitySurface,                                                 // Draws EntitySurface on the destination surface TheSurface
                     X - GCamera::CameraControl.GetX(), Y - GCamera::CameraControl.GetY(),      // Renders in connection to where the Camera is. Entity moves respecting the Camera.
                               (CurrentFrameCol + Anim_Control.GetCurrentFrame()) * Width,
                                                                 CurrentFrameRow * Height,      // Draws different set of animations while performing a action or staying Idle.
                                                                           Width, Height);      // Height and Width of each Sprite.
}

/******************************************************************************************/
// Nothing new.
void GEntity::OnCleanup()
{
    if(EntitySurface)
    {
        SDL_FreeSurface(EntitySurface);
    }

    EntitySurface = NULL;
}

/******************************************************************************************/
// This is straight forward. Animate according to the CurrentFrame Column or Row.
void GEntity::OnAnimate()
{
    Anim_Control.OnAnimate();
}


/******************************************************************************************/
/*
 * This method is called whenever two Entities collide with each others.
 * To OVERRIDE in derivated classes (GPlayer, GEnemy, ..) to perform specific actions.
 *
 * eg. A Player won't react the same way when colliding with an Enemy as when he is colliding with a Gold coin for example.
 */
bool GEntity::OnCollision(GEntity* Entity)
{
    return false;
}


/******************************************************************************************/
void GEntity::OnMove(float MoveX, float MoveY)
{
    // Per default the Player isn't JUMPING.
    CanJump = false;

    // Checks if the Player is actually MOVING
	if(MoveX == 0 && MoveY == 0)
        return;

    // Desired Target position
	float NewX = 0;
	float NewY = 0;

    // Retrieves the correct movement per second.
	MoveX *= GFPS::FPSControl.GetSpeedFactor();
	MoveY *= GFPS::FPSControl.GetSpeedFactor();

    // Set NewX to our desired target position depending on the SpeedFactor
	if(MoveX != 0)
	{
		if(MoveX >= 0)
		 	NewX =  GFPS::FPSControl.GetSpeedFactor();
		else
            NewX = -GFPS::FPSControl.GetSpeedFactor();
	}

    // Set NewY to our desired target position depending on the SpeedFactor
	if(MoveY != 0)
	{
		if(MoveY >= 0)
		 	NewY =  GFPS::FPSControl.GetSpeedFactor();
		else
            NewY = -GFPS::FPSControl.GetSpeedFactor();
	}

	while(true)
	{
	    // Checks if the Entity is a GHOST: collisions will be ignored
		if(Flags & ENTITY_FLAG_GHOST)
		{
		    //We don't care about collisions, but we need to send events to other entities
			PosValid((int)(X + NewX), (int)(Y + NewY));

            // Increase X and Y coordinate regardless of the desired target position
			X += NewX;
			Y += NewY;
		}
		/* Otherwise we do normal collisions: we check X and Y separately.
		 * eg. We may be able to move up but not forward.
		 */
		else
		{
			if(PosValid((int)(X + NewX), (int)(Y)))
			{
				X += NewX;
			}
			else
			{
			    // Running through a wall makes the Speed drop to 0 instantly.
			    if(MoveX > 0)
                    SpeedX = 0;
			}

			if(PosValid((int)(X), (int)(Y + NewY)))
			{
				Y += NewY;
			}
			else
			{
			    /* Checks if the Entity isn't in Mid Air. If so, the Entity can Jump
			     * ie. Entity can Jump IF AND ONLY IF it's on the ground.
			     */
			    if(MoveY > 0)
			    {
			        CanJump = true;
			    }

                // Hitting a wall makes the Speed drop to 0 instantly.
				SpeedY = 0;
			}
		}
        // Slowly decrease the distance between the current position to the target position.
		MoveX += -NewX;
		MoveY += -NewY;

        // When arrived at the desired position we drop the speed to 0.
		if(NewX > 0 && MoveX <= 0) NewX = 0;
		if(NewX < 0 && MoveX >= 0) NewX = 0;

		if(NewY > 0 && MoveY <= 0) NewY = 0;
		if(NewY < 0 && MoveY >= 0) NewY = 0;

		if(MoveX == 0) NewX = 0;
		if(MoveY == 0) NewY = 0;

        // The following statments check if MoveX and MoveY have reached 0
        // When reaching the desired position, we break out of the loop.
		if(MoveX == 0 && MoveY 	== 0) break;
		if(NewX  == 0 && NewY 	== 0) break;
	}
}

/******************************************************************************************/
// Stops Movement.
// Depending on the Speed we set the Acceleration in the reverse direction.
void GEntity::StopMove()
{
	if(SpeedX > 0)
	{
		AccelX = -2;
	}

	if(SpeedX < 0)
	{
		AccelX =  2;
	}

    // How slow the Entity will be going until it stops.
	if(SpeedX < 4.0f && SpeedX > -4.0f)
	{
		AccelX = 0;
		SpeedX = 0;
	}
}

/******************************************************************************************/
// A generic Jump for all Entities
bool GEntity::Jump()
{
    // If the Entity can Jump, make it JUMP according a specific Speed.
    // PS: Gravity is taken into account.
    if(CanJump == false)
        return false;
    else
        SpeedY =  -(MaxSpeedY * 6.5f);

    return true;
}

/******************************************************************************************/
// A generic Attack for all Entities
bool GEntity::Attack()
{
    // Checks if the Entity is allowed to attack.
    if(CanAttack == false)
       return false;

    // Slightly move forward when attacking.
    if(lastMoveLeft == false)
        SpeedX = (MaxSpeedX * 0.4f);
    else
        SpeedX = - (MaxSpeedX * 0.4f);

    return true;
}

/******************************************************************************************/
// Collision of two boxes.
// Borrowed from Marius Andra's Cone3D tutorials with some tweaking with jnrdev as a reference.
bool GEntity::Collides(int oX, int oY, int oW, int oH)
{
    // Edges of Box #1
    int left1, right1, top1, bottom1;
    // Edges of Box #2
    int left2, right2, top2, bottom2;

    /* The TOP and LEFT are the X and Y of the object.
     * The RIGHT and BOTTOM are the (X + Width -1) and (Y + Height - 1)
     * We Substract one in order to get the true coordinate of the side.
     *
     * Col_ variables are used to offset the size of the Entity.
     */
	int tX = (int)X + Col_X;
	int tY = (int)Y + Col_Y;

    left1 = tX;
    left2 = oX;

    right1 = left1 + Width - 1 - Col_Width;
    right2 = oX + oW;

    top1 = tY;
    top2 = oY;

    bottom1 = top1 + Height - 1 - Col_Height;
    bottom2 = oY + oH - 1;

    // If one of the four sides of the first object are out of range of the second object, there is no collision.
    // If all check fails, we have a collision.
    if (bottom1 < top2)
        return false;
    if (top1 > bottom2)
        return false;

    if (right1 < left2)
        return false;
    if (left1 > right2)
        return false;

    return true;
}

/******************************************************************************************/
// Determines ifthe position we are moving to is a valid position.
bool GEntity::PosValid(int NewX, int NewY)
{
	bool isPosValid = true;

    /** Map to Entity collision **/
	int StartX 	= ((NewX + Col_X))  / TILE_SIZE;   // Adjust LEFT side
	int StartY 	= (NewY + Col_Y) / TILE_SIZE;      // Adjust TOP  side

	int EndX	= ((NewX + Col_X) + Width - Col_Width - 1)/ TILE_SIZE;    // Adjust RIGHT side
	int EndY	= ((NewY + Col_Y) + Height - Col_Height - 1)	/ TILE_SIZE;    // Ground collision OK.
    // Added and substracted 20 pixels from both Left and Right side. In order to fix a collision bug due to my shitty graphic assets.

    // We have start and end tiles, we loop through them:
	for(int iY = StartY; iY <= EndY; iY++)
	{
		for(int iX = StartX; iX <= EndX; iX++)
		{
		    // We grab the suggested tile, then...
			GTile* Tile = GArea::AreaControl.GetTile(iX * TILE_SIZE, iY * TILE_SIZE);
            // .. check is this a valid Tile to move the Entity to?
			if(PosValidTile(Tile) == false)
			{
				isPosValid = false;
			}
		}
	}

    /** Entity to Entity collision **/
	if(Flags & ENTITY_FLAG_MAPONLY)
	{
        // We won't worry about Entity to Entity collisions, as the Flag means we are dealing with Map to Entity collisions ONLY!
	}
	else
	{
	    // Pass each Entity to the specific method who revises Entity to Entity valid positions.
		for(unsigned int i = 0;i < EntityList.size();i++)
		{
			if(PosValidEntity(EntityList[i], NewX, NewY) == false)
			{
				isPosValid = false;
			}
		}
	}

	return isPosValid;
}

/******************************************************************************************/
// Map to Entity collision detection
bool GEntity::PosValidTile(GTile* Tile)
{
    // Yes, we can walk on this tile.
	if(Tile == NULL)
	{
		return true;
	}

    // No, this tile is a block.
	if(Tile->TypeID == TILE_TYPE_BLOCK)
	{
		return false;
	}

	return true;
}

/******************************************************************************************/
// Entity to Entity collision detection
bool GEntity::PosValidEntity(GEntity* Entity, int NewX, int NewY)
{
    // Checks if..
	if(
        this    != Entity                   &&      // ..this Entity is not the same than the one we are moving.
        Entity  != NULL                     &&      // ..this Entity exists.
        Entity->Dead == false               &&      // ..this Entity isn't DEAD.
		Entity->Flags ^ ENTITY_FLAG_MAPONLY &&      // ..this Entity doesn't have a FLAG "MAP_ONLY" set ON
		Entity->Collides(NewX + Col_X, NewY + Col_Y, Width - Col_Width - 1, Height - Col_Height - 1) == true
    ){
        // Creates a Entity to Entity collision.
		GEntityCollide EntityCol;

		EntityCol.EntityA = this;
		EntityCol.EntityB = Entity;

        // Adds the collision to Queue.
		GEntityCollide::EntityColList.push_back(EntityCol);

		return false;
	}

	return true;
}
