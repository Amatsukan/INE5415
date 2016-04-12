#ifndef AUTOMA_H
#define AUTOMA_H

//------------------------//---------------------------------------------------------------//
#include "transition.hpp"// std::make_pair and std::pair and Machine::Transition          //
#include "state.hpp"    // std::string and std::vector and std::queue and Machine::State //
//_____________________//_______________________________________________________________//


typedef std::string state_name;

//GRAPH
template <typename Symbol_type>
class Automata{
private:

    //TODO trocar VECTOR por UNORDERED_SET
    std::vector < Machine::State<Symbol_type> > states;
    std::vector < Machine::State<Symbol_type> > final_states;
    Machine::State<Symbol_type> initial_state;

public:
    Automata(){}

    void addState(state_name name){
        addState(name, "");
    }

    void addState(state_name name, std::string obs){
        if(existState(name))
            throw /*some exception*/0;

        auto state = Machine::State<Symbol_type>(name, obs);

        if(states.empty()){
            initial_state = state;
            initial_state.set_unset_intial();
        }

        states.push_back(state);
    }

    void addTransition(Symbol_type condition, state_name from, state_name to){

        auto s1 = find_state_by_name(from);
        if(s1 == states.end()) throw /*some exception*/0;

        auto s2 = find_state_by_name(to);
        if(s2 == states.end()) throw /*some exception*/0;

        s1.connect(s2, condition);

    }

    Machine::State<Symbol_type> find_state_by_name(std::string state_name){
        return std::find(states.begin(), states.end(), state_name);
    }

    bool existState(std::string state_name){
        if( std::find(states.begin(), states.end(), state_name) != states.end() ) //FIXIT
            return true;
        return false;
    }

    bool existFinal(std::string state_name){
        if( std::find(final_states.begin(), final_states.end(), state_name) != final_states.end() )//FIXIT
            return true;
        return false;
    }

    void set_unset_final(state_name s){
        if(!existState(s)) throw /*some exception*/0;

        auto state = find_state_by_name(s);

        state.set_unset_final();

        if(existFinal(s)){
            final_states.erase(std::remove(final_states.begin(), final_states.end(), s), final_states.end());
        }else{
            final_states.push_back(state);
        }
    }

    void set_unset_intial(state_name s){
        if(!existState(s)) throw /*some exception*/0;

        auto state = find_state_by_name(s);

        state.set_unset_intial();

        if(state == initial_state){
            initial_state = states[0]; // pq precisa de um inicial =/
        } else{
            initial_state.set_unset_intial();
            initial_state = state;
        }
    }

    bool validateWord(std::queue<Symbol_type> word){

        try{
            auto stop_state = initial_state.make_transitions(word);
            return existFinal(stop_state);
        }catch(...){//catch limbo, TODO: improve to AFND
            return false;
        }
    }

};

#endif
