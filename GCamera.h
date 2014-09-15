/*  Class Name  : GCamera
    Description : Camera Settings Class

    Author      : Aleqh
*/

#ifndef _GCamera_H_
    #define _GCamera_H_

#include <SDL.h>

#include "GConfig.h"


// Defines the Camera's target
enum
{
	TARGET_MODE_NORMAL = 0,
	TARGET_MODE_CENTER,
	TARGET_MODE_EDGE
};


class GCamera
{
	public:
        // By using this object we are allowed to manipulate a Camera from any other class.
		static GCamera CameraControl;

	private:
		int X;
		int Y;

		float* TargetX;
		float* TargetY;

	public:
		int TargetMode;

	public:
		GCamera();

	public:
		void OnMove(int MoveX, int MoveY);

	public:
		int GetX();
		int GetY();

	public:
		void SetPos(int X, int Y);
		void SetTarget(float* X, float* Y);
};

#endif
