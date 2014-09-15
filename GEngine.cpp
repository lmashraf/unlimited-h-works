/*  Class Name  : GEngine
    Description : Contains the Entry Point to the program and the overall skeleton:
                                .--------------------.
                                |    initialize();   |
                                |    whil(running)   |
                                |    {               |
                                |        events();   |
                                |        loop();     |
                                |        render();   |
                                |    }               |
                                |    cleanup();      |
                                \____________________/
                This skeleton runs the game processes smoothely along the of the Game States. (NIY!!)

    Author      : Aleqh
*/

#include "GEngine.h"

/******************************************************************************************/
GEngine::GEngine()
{
    statusRunning = true;

    // Main Surface
    TheSurface = NULL;

    // Foregrounds
    // TBD: add at least 2 more foregrounds
}

/******************************************************************************************/
int GEngine::OnExecute()
{
    // Handles the loading of all data whether be textures, maps, NPCs, or whatever.
    if(OnInit() == false)
    {
        return -1;
    }

    SDL_Event Event;

    /*Main Loop
     *
     * A game is one gigantic loop. Within the loop we find events, update data, and render pictures.
     * Each iteration of the loop we do something with data then render accordingly.
     */
    while(statusRunning)
    {
        // Checks on Events and pass them one at a time to OnEvent.
        while(SDL_PollEvent(&Event))
        {
            OnEvent(&Event);
        }

        // Handles all the data updates, such as NPCs moving across the screen, decreasing your health bar, or whatever.
        OnLoop();

        // Handles all the rendering of anything that shows up on the screen.
        // !!!! THIS SHOULD NOT HANDLE DATA MANIPULATION !!!!
        OnRender();
    }

    // Cleans any loaded resources.
    OnCleanup();

    return 0;
}

/******************************************************************************************/
int main(int argc, char* argv[])
{
    GEngine theApp;

    return theApp.OnExecute();
}
