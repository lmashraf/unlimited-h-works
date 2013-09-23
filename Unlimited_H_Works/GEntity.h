/*  Class Name  : GAnimation
    Definition  : Rather than clumpsing them together with everything, here we will be encapsulating the basic components of the game:
                  Excluding OnEvent(), we will have OnLoad(), OnRender(), OnLoop() and and OnCleanUp(). This will allow us to handle Entities
                  within the game much more easily.
    Author      : Aleqh
*/

#ifndef _GEntity_H_
    #define _GEntity_H_

#include <vector>

#include "GArea.h"
#include "GAnimation.h"
#include "GCamera.h"
#include "GFPS.h"
#include "GSurface.h"

/*************************/
/**   ENUMERATIONS       */
/*************************/

// Entity types: Player, Generic, Enemy, ...
enum
{
	ENTITY_TYPE_GENERIC = 0,

	ENTITY_TYPE_PLAYER,
	ENTITY_TYPE_ENEMY
};

// Entity flags
enum
{
	ENTITY_FLAG_NONE 	= 0,

	ENTITY_FLAG_GRAVITY	= 0x00000001,
	ENTITY_FLAG_GHOST	= 0x00000002,
	ENTITY_FLAG_MAPONLY	= 0x00000004
};

/*************************/
/**       ENTITY         */
/*************************/

class GEntity
{
	public:
        // Holds all of our Entities in a static manner to make it easily accessible.
		static std::vector<GEntity*>    EntityList;

	protected:
        // Entity Animation controller
		GAnimation      Anim_Control;

        // Entity Surface image
		SDL_Surface*    EntitySurface;

	public:
        // Entity Coordinates
		float	X;
		float	Y;

        // Entity Dimensions
		int		Width;
		int		Height;

        // Entity Movements
		bool	MoveLeft;
		bool    lastMoveLeft;

		bool	MoveRight;
		bool    lastMoveRight;

        // Entity Actions
		bool    CanJump;
		bool    CanAttack;
		bool    firstAttack;

	public:
	    int		Type;
		bool	Dead;
		int		Flags;

	protected:
        // Entity Speed and Acceleration
		float	SpeedX;
		float	SpeedY;

		float	AccelX;
		float	AccelY;

	public:
		float	MaxSpeedX;
		float	MaxSpeedY;

	protected:
        // Entity Animation attributes
		int		CurrentFrameCol;
		int		CurrentFrameRow;

	protected:
	    // Offsets a collision for an Entity
		int		Col_X;
		int		Col_Y;
		int		Col_Width;
		int		Col_Height;

	public:
		GEntity();
		virtual ~GEntity();

	public:
        // Takes a filename to load the Entity corresponding Sprite image
		virtual bool OnLoad(const char* File, int Width, int Height, int MaxFrames);

		// Handles basic calculation, practically Animation in this case.
		virtual void OnLoop();

		// Instead of rendering to Display only, we can render Entity to a specific Surface.
		virtual void OnRender(SDL_Surface* TheSurface);

        // Restores memory and all that stuff.
		virtual void OnCleanup();

        // Select the right animation of the Entity
		virtual void OnAnimate();

        // Called whenever an EntityA collides with EntityB
		virtual bool OnCollision(GEntity* Entity);

	public:
		virtual void    OnMove(float MoveX, float MoveY);
		void 	        StopMove();
		bool            Jump();
		bool            Attack();

	public:
	    // Determines the actual collision.
		bool    Collides(int oX, int oY, int oW, int oH);

	protected:
		virtual bool 	PosValid(int NewX, int NewY);
		bool 	        PosValidTile(GTile* Tile);
		bool 	        PosValidEntity(GEntity* Entity, int NewX, int NewY);
};


class GEntityCollide
{
	public:
	    // A Queue that stores any collision that have happened when all the Entities have moved.
	    // Once all movement has taken place, that is when we will notify all the Entities of collisions
	    // Then call OnCollision()
		static std::vector<GEntityCollide>	EntityColList;

	public:
	    // Colliding Entities
		GEntity* EntityA;
		GEntity* EntityB;

    public:
		GEntityCollide();
};

#endif
