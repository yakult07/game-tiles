#include <iostream>
#include "Game.h"

int main()
{   
    //iniciar srand
    srand(static_cast<unsigned>(time(NULL))); // gerador de numero aleatorio

    Game game ;
    // game.loop
    while(game.running() && !game.getEndGame())
    {   

        //update
        game.update();
        // render
        game.render();
    }


    // end application
   return 0;


}   