#ifndef AUTOMA_H
#define AUTOMA_H

//--------------------------//---------------------------------------------------------------//
#include <unordered_map>   // std::unordered_map
#include "exception.hpp"  // Exceptions                                                    //
#include "transition.hpp"// Machine::Transition
#include "state.hpp"    // std::string and std::vector and std::queue and Machine::State
//_____________________//_______________________________________________________________//


typedef std::string state_name;

//GRAPH
template <typename Symbol_type>
class Automata{
private:

    //std::string => stateName, Machine::State<Symbol_type> => state
    std::unordered_map < std::string, Machine::State<Symbol_type> > states;
    std::unordered_map < std::string, Machine::State<Symbol_type> > final_states;
    Machine::State<Symbol_type> *initial_stt_prt = NULL;

public:
    Automata(std::string s0){ addState(s0); }

    void addState(std::string name, std::string obs){
        if(existState(name))
            throw ExistStateException();

        auto state = Machine::State<Symbol_type>(name, obs);

        if(states.empty()){
           initial_stt_prt = &state;
           initial_stt_prt->set_unset_intial();
        }

        states.emplace(name,state);
    }

    void addState(std::string name){
        addState(name, "");
    }

    Machine::State<Symbol_type> get_state_by_name(std::string state_name){
            return states[state_name];
    }

    void addTransition(Symbol_type condition, std::string from, std::string to){

        if( !(existState(from) and existState(to)) ) throw MissingStateException();

        states.at(from).connect(states.at(to), condition);

    }


    bool existState(std::string state_name){
        return states.count(state_name);
    }

    bool existFinal(std::string state_name){
        if( std::find(final_states.begin(), final_states.end(), state_name) != final_states.end() )//FIXIT
            return true;
        return false;
    }

    void set_unset_final(state_name s){
        if(!existState(s)) throw MissingStateException();

        auto state = get_state_by_name(s);

        state.set_unset_final();

        if(existFinal(s)){
            final_states.erase(std::remove(final_states.begin(), final_states.end(), s), final_states.end());
        }else{
            final_states.push_back(state);
        }
    }

    void set_unset_intial(state_name s){
        if(!existState(s)) throw MissingStateException();

        // auto state = get_state_by_name(s);

        // state.set_unset_intial();

        // if(state == *initial_stt_prt){
        //     //initial_stt_prt = states[0]; // pq precisa de um inicial =/
        // } else{
        //     initial_stt_prt->set_unset_intial();
        //     initial_stt_prt = &state;
        // }
    }

    bool allReject(){

    }

    bool validateWord(std::queue<Symbol_type> word){

        auto stop_state = initial_stt_prt.make_transitions(word);

    }

};

#endif
