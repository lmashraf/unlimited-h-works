/*  Class Name  : GPlayer
    Definition  : Defines the Player entity. Overrides Entity class.
    Author      : Aleqh
*/
#include "GPlayer.h"

/******************************************************************************************/
GPlayer::GPlayer()
{}

/******************************************************************************************/
bool GPlayer::OnLoad(const char* File, int Width, int Height, int MaxFrames)
{
    if(GEntity::OnLoad(File, Width, Height, MaxFrames) == false)
    {
        return false;
    }

    return true;
}

/******************************************************************************************/
void GPlayer::OnLoop()
{
	GEntity::OnLoop();
}

/******************************************************************************************/
void GPlayer::OnRender(SDL_Surface* TheSurface)
{
	GEntity::OnRender(TheSurface);
}

/******************************************************************************************/
void GPlayer::OnCleanup()
{
	GEntity::OnCleanup();
}

/******************************************************************************************/
void GPlayer::OnAnimate()
{
    if(MoveLeft)
    {
        CurrentFrameRow = 2;
    }
    else if(MoveRight)
    {
        CurrentFrameRow = 3;
    }
    else if(CanAttack)
    {
        // Make sure to be facing the correct side when attacking
        if(lastMoveLeft)
	    {
            CurrentFrameRow = 5;
	    }
	    else
	    {
            CurrentFrameRow = 4;
	    }
    }
    else if(CanJump)
    {
        // Make sure to jump and land on the correct side.
        if(lastMoveLeft)
	    {
            CurrentFrameRow = 1;
	    }
	    else
	    {
            CurrentFrameRow = 0;
	    }
    }

	GEntity::OnAnimate();
}

/******************************************************************************************/
bool GPlayer::OnCollision(GEntity* Entity)
{
    return false;
}

/******************************************************************************************/
bool GPlayer::PosValid(int NewX, int NewY)
{
    // Hitbox adjustment because of shitty GFX resources.
    int adjustTop   = 50;
    int adjustBot   = 40;
    int adjustRight = 70;
    int adjustLeft  = 60;

    //
	bool isPosValid = true;

    /** Map to Entity collision **/
	int StartX 	= ((NewX + adjustLeft + Col_X))  / TILE_SIZE;   // Adjust LEFT side
	int StartY 	= (NewY + adjustTop + Col_Y) / TILE_SIZE;      // Adjust TOP  side

	int EndX	= ((NewX + Col_X) + Width - Col_Width - adjustRight - 1)/ TILE_SIZE;    // Adjust RIGHT side
	int EndY	= ((NewY + Col_Y) + Height - Col_Height - adjustBot - 1)	/ TILE_SIZE;    // Ground collision OK.
    // Added and substracted 20 pixels from both Left and Right side. In order to fix a collision bug due to my bad graphic assets.

    // We have start and end tiles, we loop through them:
	for(int iY = StartY; iY <= EndY; iY++)
	{
		for(int iX = StartX; iX <= EndX; iX++)
		{
		    // We grab the suggested tile, then...
			GTile* Tile = GArea::AreaControl.GetTile(iX * TILE_SIZE, iY * TILE_SIZE);
            // .. check is this a valid Tile to move the Entity to?
			if(GEntity::PosValidTile(Tile) == false)
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
			if(GEntity::PosValidEntity(EntityList[i], NewX, NewY) == false)
			{
				isPosValid = false;
			}
		}
	}

	return isPosValid;
}


/******************************************************************************************/
void GPlayer::OnMove(float MoveX, float MoveY)
{
    // Per default the Player isn't JUMPING.
    CanJump = false;

    // Checks if the Player is actually MOVING
	if(MoveX == 0 && MoveY == 0)
        return;

    // Desired Target position
	double NewX = 0;
	double NewY = 0;

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
			GPlayer::PosValid((int)(X + NewX), (int)(Y + NewY));

            // Increase X and Y coordinate regardless of the desired target position
			X += NewX;
			Y += NewY;
		}
		/* Otherwise we do normal collisions: we check X and Y separately.
		 * eg. We may be able to move up but not forward.
		 */
		else
		{
			if(GPlayer::PosValid((int)(X + NewX), (int)(Y)))
			{
				X += NewX;
			}
			else
			{
			    // Running through a wall makes the Speed drop to 0 instantly.
			    if(MoveX > 0)
                    SpeedX = 0;
			}

			if(GPlayer::PosValid((int)(X), (int)(Y + NewY)))
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
