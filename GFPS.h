/*  Class Name  : GFPS
    Description : The idea is simple: figure out the frame rate of the machine,
                  and base our movements off of the frame rate. I call this a "SpeedFactor"
    Author      : Aleqh
*/
#ifndef _GFPS_H_
    #define _GFPS_H_

#include <SDL.h>


class GFPS
{
	public:
        // By using this object we are allowed to single-handedly control the FPS from any other class.
		static GFPS FPSControl;

	private:
        // Calculate the Frames per second
		int     OldTime;

		// Calculate the Speed Factor
		int     LastTime;

        // Current Speed Factor of the game
		float 	SpeedFactor;

        // Game's current FPS
		int		NumFrames;

		// Frame count when calculating frames per second
		int     Frames;

	public:
		GFPS();

		void    OnLoop();

	public:
		int     GetFPS();
		float   GetSpeedFactor();
};


#endif
