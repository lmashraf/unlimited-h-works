/*  Class Name  : GAnimation
    Description : Events are extra, a mean for the user (ie. Player) to manipulate data as well.
                  Events are not required but needed in cases.
    Author      : Aleqh
*/
#include "GAnimation.h"

/******************************************************************************************/
// Init Animation variables.
GAnimation::GAnimation()
{
    CurrentFrame    = 0;
    MaxFrames       = 0;
    FrameInc        = 1;

    FrameRate       = 100; //Milliseconds
    OldTime         = 0;

    Oscillate       = false;
}

/******************************************************************************************/
void GAnimation::OnAnimate()
{
    /*
     * By taking the Old Time in milliseconds plus the desired frame rate, we can check it
     * against how long the SDL has been running.
     */
    if((unsigned) OldTime + FrameRate > SDL_GetTicks())
    {
        return;
    }

    OldTime = SDL_GetTicks();

    CurrentFrame += FrameInc;

    // The oscilation considers increasing then decreasing the frames: 12345678 9 8765432 1 23..
    if(Oscillate)
    {
        if(FrameInc > 0)
        {
            // If the CurrentFrame is at edge, revert the Frames counter.
            if(CurrentFrame >= MaxFrames)
            {
                FrameInc = -FrameInc;
            }
        }   // And below that, we increase it to the next Frame.
        else
        {
            if(CurrentFrame <= 0)
            {
                FrameInc = -FrameInc;
            }
        }
    }   // If the CurrentFrame exceeds the Max Frame resets it back to 0 (NO OSCILLATION INVOLVED).
    else
    {
        if(CurrentFrame >= MaxFrames)
        {
            CurrentFrame = 0;
        }
    }
}

/******************************************************************************************/
void GAnimation::SetFrameRate(int Rate)
{
    FrameRate = Rate;
}

/******************************************************************************************/
void GAnimation::SetCurrentFrame(int Frame)
{
    if(Frame < 0 || Frame >= MaxFrames) return;

    CurrentFrame = Frame;
}

/******************************************************************************************/
int GAnimation::GetCurrentFrame()
{
    return CurrentFrame;
}
