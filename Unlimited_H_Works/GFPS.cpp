/*  Class Name  : GFPS
    Description : The idea is simple: figure out the frame rate of the machine,
                  and base our movements off of the frame rate. I call this a "SpeedFactor"
    Author      : Aleqh
*/
#include "GFPS.h"

// static object
GFPS GFPS::FPSControl;

/******************************************************************************************/
GFPS::GFPS()
{
	OldTime     = 0;
	LastTime    = 0;

	SpeedFactor	= 0;

	Frames      = 0;
	NumFrames   = 0;
}

/******************************************************************************************/
void GFPS::OnLoop()
{
   /*
    * Calculate the Frames per Second of the game.
    *
    * SDL_GetTicks returns the number of milliseconds that have passed since we called SDL_Init (1000 ms = 1s)
    */
	if((unsigned) OldTime + 1000 < SDL_GetTicks())
	{
		OldTime = SDL_GetTicks();

		NumFrames = Frames;

		Frames = 0;
	}

   /* Calculate the SpeedFactor
    *
    * The SpeedFactor determines how fast to move objects.
    * For example, say we are on a really slow computer that gets 1 Frame per Second.
    * We have set the base movement rate at 32, so ideally any computer will move objects 32 pixels per second.
    * In other words, this 1 FPS computer will move the object 32 pixels every second.
    * Whilst on a 10 FPS computer, we will still want to move 32 pixels per second. That's 1/10 of 32.
    * So for each calculation we'll have moved 3.2 pixels, and after one second we'll have moved 32 pixels..
    */
	SpeedFactor = ((SDL_GetTicks() - LastTime) / 1000.0f) * 32.0f;

    // Holds the time it took for the last loop in the game.
	LastTime = SDL_GetTicks();

	Frames++;
}

/******************************************************************************************/
int GFPS::GetFPS()
{
    return NumFrames;
}

/******************************************************************************************/
float GFPS::GetSpeedFactor()
{
    return SpeedFactor;
}
