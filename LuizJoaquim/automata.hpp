#ifndef AUTOMA_H
#define AUTOMA_H

//--------------------------//---------------------------------------------------------------//
#include <unordered_map>   // std::unordered_map                                            //
#include "exception.hpp"  // Exceptions                                                    //
#include "state.hpp"     // std::string and std::vector and std::queue and Machine::State //
#include "config.hpp"   // ConfigReader                                                  //
//_____________________//_______________________________________________________________//

typedef std::string state_name;

//GRAPH
template <typename Symbol_type>
class Automata{
private:

    //(std::string -> stateName) => (Machine::State<Symbol_type> -> state)
    std::unordered_map < std::string, Machine::State<Symbol_type>* > states;
    std::set< state_name > final_states;
    std::vector< char > Alphabet;
    std::string InitialStateName;
    bool isAFN;

public:

    Automata(std::vector< char > Alp) : Alphabet(Alp), isAFN(false){}

    void addState(std::string name, std::string obs){
        if(name.length() < 1)
            throw InvalidStateNameException();

        if(existState(name))
            throw ExistStateException();

        auto state = new Machine::State<Symbol_type>(name, obs);

        states.emplace(name,state);

        if(states.size() == 1){
           toggle_initial(name);
        }

    }

    void addState(std::string name){
        addState(name, "");
    }

    Machine::State<Symbol_type> get_state_by_name(std::string state_name){
        return *(states.at(state_name));
    }

    void addTransition(Symbol_type condition, std::string from, std::string to){

        if( !(existState(from) and existState(to)) ) throw MissingStateException();

        states.at(from)->connect(states.at(to), condition);
    }

    void addEpsilonTransition(std::string from, std::string to){

        if( !(existState(from) and existState(to)) ) throw MissingStateException();

        if(!isAFN){
            isAFN = true;
        }

        states.at(from)->epsilonConnect(states.at(to));
    }

    bool existState(state_name key){
        return states.count(key);
    }

    bool isFinal(state_name key){
        return final_states.count(key);
    }

    bool isNonDeterministic(){
        return isAFN;
    }

    bool containsFinal(std::vector<std::string> stateSet){
        for(auto state : stateSet){
            if(isFinal(state)) return true;
        }

        return false;
    }

    bool isInitial(state_name key){
        return (key == InitialStateName);
    }

    bool existFinal(){
        return final_states.size();
    }

    void toggle_final(state_name s){
        if(!existState(s)) throw MissingStateException();

        if(isFinal(s)){
            final_states.erase(s);
        }else{
            final_states.insert(s);
        }

    }

    std::unordered_map < std::string, Machine::State<Symbol_type>* > getStates(){
        return states;
    }


    std::string getInitial_str(){
        return InitialStateName;
    }

    std::string getFinals_str(){
        std::string ret;
        for(auto state : final_states){
            ret+=state;
            ret+=" ";
        }

        return ret;
    }

    std::string getStates_str(){
        std::string ret;
        for(auto state : states){
            ret+=state.second->getName();
            ret+=" ";
        }

        return ret;
    }

    std::string getAlphabet(){
        std::string ret;
        for(auto c : Alphabet){
            if(c == ConfigReader::getNullSlot() or c == ConfigReader::getEpsilon()) continue;
            ret+=c;
            ret+=" ";
        }

        return ret;
    }

    std::vector<char> getAlphabet_vector(){
        std::vector<char> ret;
        for(auto c : Alphabet){
            if(c == ConfigReader::getNullSlot() or c == ConfigReader::getEpsilon()) continue;
            ret.push_back(c);
        }

        return ret;
    }

    std::string getStateTransitions_str(state_name s){
       std::string stateT = "";

       for(char c:Alphabet){
            if(c == ConfigReader::getNullSlot() or c == ConfigReader::getEpsilon()) continue;
            std::string hitByC = get_state_by_name(s).get_hit_by_str(c);
            stateT += ConfigReader::spaces(hitByC);
       }

       return stateT;
   }

    void toggle_initial(state_name s){
        if(!existState(s)) throw MissingStateException();

        InitialStateName = s;
    }

    bool validateWord(std::queue<Symbol_type> word){

        auto initialState =  get_state_by_name(InitialStateName);

        auto stop_states = initialState.make_transitions(word);

        for(auto state : stop_states){
            if(isFinal(state->getName())){
                return true;
            }
        }

        return false;
    }

};

#endif
