/*  Class Name  : GAnimation
    Definition  : Handles animation.
    Author      : Aleqh
*/

#ifndef _GAnimation_H_
    #define _GAnimation_H_

#include <SDL.h>

class GAnimation
{
	private:
		int	    CurrentFrame;
		int     FrameInc;

    public:
        int     FrameRate;      // Milliseconds
		long    OldTime;

	public:
        int	    MaxFrames;
		bool	Oscillate;

	public:
		GAnimation();
		void OnAnimate();

	public:
        void SetFrameRate(int Rate);
		void SetCurrentFrame(int Frame);

		int GetCurrentFrame();
};

#endif
