/*  Class Name  : GCamera
    Description : Camera Settings Class

    Author      : Aleqh
*/

#include "GCamera.h"


GCamera GCamera::CameraControl;

/******************************************************************************************/
GCamera::GCamera()
{
	X = 0;
	Y = 0;

	TargetX = TargetY = NULL;

	TargetMode = TARGET_MODE_NORMAL;
}

/******************************************************************************************/
// Increase the X and Y of the camera by MoveX and MoveY
void GCamera::OnMove(int MoveX, int MoveY)
{
	X += MoveX;
	Y += MoveY;
}

/******************************************************************************************/
int GCamera::GetX()
{
    // Checks if we have a valid Target at X coordinate
	if(TargetX != NULL)
	{
	    // For MODE CENTER we take half the screen's WIDTH and substract it from the Target's coordinates.
		if(TargetMode == TARGET_MODE_CENTER)
		{
		    // LOCK Camera to fit target at the LEFT
            if(*TargetX <= WWIDTH/2)
                return 0;
            // LOCK Camera to fit target at the RIGHT
            else if(*TargetX >= (MAP_WIDTH * TILE_SIZE) - WWIDTH/2)
                return (MAP_WIDTH * TILE_SIZE) - WWIDTH;
            // LOCK Camera to follow target
            else
                return static_cast<int> (*TargetX - (WWIDTH / 2));
		}

		return static_cast<int> (*TargetX);
	}

    // Returns the Target's X coordinate as the Camera's X coordinate
	return X;
}

/******************************************************************************************/
int GCamera::GetY()
{
    // Checks if we have a valid Target at Y coordinate
	if(TargetY != NULL)
	{
        // For MODE CENTER we take half the screen's HEIGHT and substract it from the Target's coordinates.
		if(TargetMode == TARGET_MODE_CENTER)
		{
                return static_cast<int> (*TargetY - (WHEIGHT * 0.4));
		}

        // Returns the Target's Y coordinate as the Camera's Y coordinate
		return static_cast<int> (*TargetY);
	}

	return Y;
}

/******************************************************************************************/
void GCamera::SetPos(int X, int Y)
{
	this->X = X;
	this->Y = Y;
}

/******************************************************************************************/
void GCamera::SetTarget(float* X, float* Y)
{
	TargetX = X;
	TargetY = Y;
}


