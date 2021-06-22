#include "Game.hpp"
#include "State.hpp"
#include "SoundManager.hpp"

int main()
{
    Game game;
    SoundManager sound;
    sound.playSound(2);
    game.Run();
    
    return 0;
}
