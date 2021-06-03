#pragma once 

#include <SFML/System/Time.hpp>

namespace Engine {
    
    class State 
    {
        private:
            /* data */
        public:
            State(){};
            virtual ~State(){};

            //Métodos virtuais puros(são obigados a serem redefinidos para cada estado.)
            virtual void Init() = 0;
            virtual void ProcessInput() = 0;
            virtual void Update(sf::Time deltaTime) = 0;
            virtual void Draw() = 0;

            //Métodos virtuais não-puros(apenas alguns estados irão utiliza-los);

            virtual void Pause(){};
            virtual void Start(){}; 
    };
}