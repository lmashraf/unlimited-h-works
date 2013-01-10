// Entity Class

#ifndef _CENTITY_H_
    #define _CENTITY_H_

#include <vector>

#include "CArea.h"
#include "CAnimation.h"
#include "CCamera.h"
#include "CFPS.h"
#include "CSurface.h"


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


class CEntity
{
	public:
		static std::vector<CEntity*>    EntityList;

	protected:
		CAnimation      Anim_Control;

		SDL_Surface*    Surf_Entity;

	public:
		float	X;
		float	Y;

		int		Width;
		int		Height;

		bool	MoveLeft;
		bool    lastMoveLeft;

		bool	MoveRight;
		bool    lastMoveRight;

		bool    CanJump;
		bool    CanAttack;

	public:
		int		Type;

		bool	Dead;
		int		Flags;

	protected:
		float	SpeedX;
		float	SpeedY;

		float	AccelX;
		float	AccelY;

	public:
		float	MaxSpeedX;
		float	MaxSpeedY;

	protected:
		int		CurrentFrameCol;
		int		CurrentFrameRow;

	protected:
		int		Col_X;
		int		Col_Y;
		int		Col_Width;
		int		Col_Height;

	public:
		CEntity();
		virtual ~CEntity();

	public:
		virtual bool OnLoad(char* File, int Width, int Height, int MaxFrames);

		virtual void OnLoop();

		virtual void OnRender(SDL_Surface* Surf_Display);

		virtual void OnCleanup();

		virtual void OnAnimate();

		virtual bool OnCollision(CEntity* Entity);

	public:
		void    OnMove(float MoveX, float MoveY);
		void 	StopMove();
		bool    Jump();
		bool    Attack();

	public:
		bool    Collides(int oX, int oY, int oW, int oH);

	private:
		bool 	PosValid(int NewX, int NewY);
		bool 	PosValidTile(CTile* Tile);
		bool 	PosValidEntity(CEntity* Entity, int NewX, int NewY);
};


class CEntityCol
{
	public:
		static std::vector<CEntityCol>	EntityColList;

	public:
		CEntity* EntityA;
		CEntity* EntityB;

    public:
		CEntityCol();
};

#endif
