#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "State.h"
#include <memory>
#include <stack>

namespace Sonar
{
    typedef std::unique_ptr<State> StateRef;

    class StateMachine {
        public:     
            StateMachine( ) { }
            ~StateMachine( ) { }

            void AddState( StateRef newState, bool isReplacing = true );
            void RemoveState( );

            void ProcessingStateChanges( );

            StateRef &GetActiveState( );

        private:
            std::stack<StateRef> _states;
            StateRef _newState;

            bool _isRemoving;
            bool _isAdding;
            bool _isReplacing;

    };
}




#endif