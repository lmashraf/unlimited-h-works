/*  Class Name  : GEngine
    Description : Events are extra, a mean for the user (ie. Player) to manipulate data as well.
                  Events are not required but needed in cases.
    Author      : Aleqh
*/

#include "GEngine.h"


/******************************************************************************************/
void GEngine::OnEvent(SDL_Event* Event)
{
    /* We pass the Event structure into our GEvent class, so it can take care of the correct function calls.
     * When we want to check for an event, we override the function.
     * eg. SDL_QUIT overwritten.
     */
    GEvent::OnEvent(Event);

    GStateManager::OnEvent(Event);

}

/******************************************************************************************/
void GEngine::OnExit()
{
	statusRunning = false;
}
