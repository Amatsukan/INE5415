#ifndef TRANS_H
#define TRANS_H

//--------------------//-----------------------------//
#include <utility>   // std::make_pair and std::pair//
#include "state.hpp"// Machine::State              //
//_________________//_____________________________//

namespace Machine{

    //EDGE
    template <typename Symbol_type>
    class Transition{
    private:
        Symbol_type condition;
        std::pair< State<Symbol_type>, State<Symbol_type> > states;

    public:
        Transition(Symbol_type symbol, State<Symbol_type> from, State<Symbol_type> to) : condition(symbol){
            states = std::make_pair(from, to);
        }

        bool matchCondition(Symbol_type symbol){
            return symbol == condition;
        }

        State<Symbol_type> get_next(){
            return states.second;
        }

        State<Symbol_type> get_actual(){
            return states.first;
        }
    };
};

#endif
