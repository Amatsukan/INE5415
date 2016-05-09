#ifndef AUTOMA_H
#define AUTOMA_H

//--------------------------//---------------------------------------------------------------//
#include <unordered_map>   // std::unordered_map                                            //
#include "exception.hpp"  // Exceptions                                                    //
#include "state.hpp"     // std::string and std::vector and std::queue and Machine::State //
//______________________//_______________________________________________________________//


typedef std::string state_name;

//GRAPH
template <typename Symbol_type>
class Automata{
private:

    //std::string => stateName, Machine::State<Symbol_type> => state
    std::unordered_map < std::string, Machine::State<Symbol_type> > states;
    std::unordered_map < std::string, Machine::State<Symbol_type> > final_states;
    std::string InitialStateName;

public:
    Automata(std::string s0){ addState(s0); }

    void addState(std::string name, std::string obs){
        if(existState(name))
            throw ExistStateException();

        auto state = Machine::State<Symbol_type>(name, obs);

        states.emplace(name,state);

        if(states.size() == 1){
           toggle_initial(name);
        }

    }

    void addState(std::string name){
        addState(name, "");
    }

    Machine::State<Symbol_type> get_state_by_name(std::string state_name){
        return states.at(state_name);
    }

    void addTransition(Symbol_type condition, std::string from, std::string to){

        if( !(existState(from) and existState(to)) ) throw MissingStateException();

        states.at(from).connect(&(states.at(to)), condition);
    }

    void addEpsilonTransition(std::string from, std::string to){

        if( !(existState(from) and existState(to)) ) throw MissingStateException();

        states.at(from).epsilonConnect(&(states.at(to)));
    }

    bool existState(state_name key){
        return states.count(key);
    }

    bool existFinal(state_name key){
        return final_states.count(key);
    }

    bool existFinal(){
        return final_states.size();
    }

    void toggle_final(state_name s){
        if(!existState(s)) throw MissingStateException();

        if(existFinal(s)){
            final_states.erase(s);
        }else{
            final_states.emplace(s,Machine::State<Symbol_type>(s));
        }

    }

    void toggle_initial(state_name s){
        if(!existState(s)) throw MissingStateException();

        InitialStateName = s;
    }

    bool validateWord(std::queue<Symbol_type> word){

        auto initialState =  get_state_by_name(InitialStateName);

        auto stop_states = initialState.make_transitions(word);

        for(auto state : stop_states){
            if(existFinal(state->getName())){
                return true;
            }
        }

        return false;
    }

};

#endif
