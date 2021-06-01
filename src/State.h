#ifndef STATE_H
#define STATE_H


namespace Sonar
{
    class State
    {
        public:
            virtual void Init() = 0;

            virtual void HandleInput( ) = 0;
            virtual void Update( ) = 0;
            virtual void Draw( float dt ) = 0;

            virtual void Pause() { }
            virtual void Resume() { }
    };
}

#endif