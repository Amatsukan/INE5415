#ifndef AW_H
#define AW_H

#include "automata.hpp"
#include "state.hpp"
#include <set>
#include <vector>
#include <algorithm>

template <typename Symbol_type>

class AutomataWorker
{
private:
    void addNextState(std::string stateName, std::vector<std::string> states);

    std::vector<std::string> getNextState(std::vector<std::string> states,Symbol_type c);

    std::string getStateName(std::set<Machine::State<Symbol_type>*> states);

    std::string NameStateInOrder(std::vector<std::string> states);

    std::vector<std::string> getNameStatesVector(std::set<Machine::State<Symbol_type>*> states){

        std::vector<std::string> ret;

        for (auto state : states)
        {
            ret.push_back(state->getName());
        }

        return ret;
    }

	Automata<Symbol_type> AFN;
	Automata<Symbol_type> AFD;
public:

	AutomataWorker(Automata<Symbol_type> a) : AFN(a), AFD(a.getAlphabet_vector()){};

	Automata<Symbol_type> determinize();
};

template <typename Symbol_type>
Automata<Symbol_type> AutomataWorker<Symbol_type>::determinize(){

    auto newStateI = AFN.get_state_by_name(AFN.getInitial_str()).get_epsilon_close();


    std::string newStateI_str = NameStateInOrder(newStateI);

    AFD.addState(newStateI_str);
    AFD.toggle_initial(newStateI_str);
		if(AFN.containsFinal(newStateI)){
			AFD.toggle_final(newStateI_str);
		}

    addNextState(newStateI_str, newStateI);

    return AFD;
}

template <typename Symbol_type>
void AutomataWorker<Symbol_type>::addNextState(std::string stateName, std::vector<std::string> states){
    std::vector<std::string> nextState;
 	auto alphabet = AFD.getAlphabet_vector();
    for(Symbol_type c:alphabet){
//          nextState = getNextState(states, c);

// 		 \\\\\\\\

	auto contains = [nextState] (std::string nome){
		for(auto s : nextState)
			if(s == nome)
				return true;
		return false;
	};
    for(auto s: states){

        for(auto newS: AFN.get_state_by_name(s).get_hit_by(c)){
			if(newS->getName() == ConfigReader::getNotTransition())
				continue;
			std::cout<<"Statas size: "<< newS->getName() <<std::endl;
            if(contains(newS->getName())){
				nextState.push_back(newS->getName());
				std::cout<<"ESTADO ATINGIDO:" << newS->getName() <<std::endl;
			}
		}
    }

// 		 \\\\\\\\\\





       	std::string nextState_str = NameStateInOrder(nextState);

        if(!AFD.existState(nextState_str)){
            AFD.addState(nextState_str);
            addNextState(nextState_str, nextState);
        }

		AFD.addTransition(c, stateName, nextState_str);
     }
}

template <typename Symbol_type>
std::vector<std::string> AutomataWorker<Symbol_type>::getNextState(std::vector<std::string> states,Symbol_type c){
    std::vector<std::string> newState;
	auto contains =[newState] (std::string nome){
		for(auto s : newState)
			if(s == nome)
				return true;
		return false;
	};
    for(auto s: states){

		std::cout<<"Statas size: "<<c<<std::endl;
        for(auto newS: AFN.get_state_by_name(s).get_hit_by(c)){
            if(contains(newS->getName())){
				newState.push_back(newS->getName());
				std::cout<<"ESTADO ATINGIDO:" << newS->getName() <<std::endl;
			}
		}
    }
    return newState;
}

template <typename Symbol_type>
std::string AutomataWorker<Symbol_type>::NameStateInOrder(std::vector<std::string> vector){

    std::string ret = "";
	if(vector.size() > 2){
 		ret+="{";
    }


	std::sort(
        vector.begin(),
        vector.end(),
        [](const std::string & a, const std::string & b) -> bool
        {
            return a < b;
        }
    );

    for (auto state : vector)
    {
        ret+=std::string(state);
        if(state != vector.at(vector.size()-1)){
            ret+=',';
        }
    }

    if(vector.size() > 2){
 		 ret+='}';
    }

    std::cout<<ret<<std::endl;

    return ret;
}



#endif
