#ifndef AW_H
#define AW_H

#include "automata.hpp"
#include "state.hpp"
#include <set>
#include <vector>

template <typename Symbol_type>

class AutomataWorker
{
private:
    void addNextState(std::vector<Symbol_type> alphabet,std::string stateName, std::set<Machine::State<Symbol_type>*> states, Automata<Symbol_type> AFD );

    std::set<Machine::State<Symbol_type>*> getNextState(std::set<Machine::State<Symbol_type>*> states,Symbol_type c);

    std::string getStateName(std::set<Machine::State<Symbol_type>*> states);

    std::string NameStateInOrder(std::set<Machine::State<Symbol_type>*> states);

    std::vector<std::string> getStatesVector(std::set<Machine::State<Symbol_type>*> states){

        std::vector<std::string> ret;

        for (auto state_pair : states)
        {
            ret+=state_pair.seccond->getName();
        }

        return ret;
    }

public:
	Automata<Symbol_type> determinize(Automata<Symbol_type>);

};

template <typename Symbol_type>
Automata<Symbol_type> AutomataWorker<Symbol_type>::determinize(Automata<Symbol_type> AFN){

    std::vector<Symbol_type> alphabet = AFN.getAlphabet_vector();

    auto AFD = Automata<Symbol_type>(alphabet);

    auto novoStateI = AFN.get_state_by_name(AFN.getInitial_str()).get_epsilon_reach();


    std::string novoStateI_str = NameStateInOrder(novoStateI);

    AFD.addState(novoStateI_str);
    AFD.toggle_inicial(novoStateI_str);

    addNextState(alphabet, novoStateI_str, novoStateI, AFD);

    return AFD;
}

template <typename Symbol_type>
void AutomataWorker<Symbol_type>::addNextState(std::vector<Symbol_type> alphabet,std::string stateName, std::set<Machine::State<Symbol_type>*> states, Automata<Symbol_type> AFD ){
    std::set<Machine::State<Symbol_type>*> nextState;
    for(Symbol_type c:alphabet){
        nextState = getNextState(states, c);
        std::string nextState_str = NameStateInOrder(nextState_str);
        AFD.addTransition(c, stateName, nextState_str );

        if(!AFD.existState(nextState)){
            AFD.addState(nextState);
            addNextState(alphabet, nextState_str, nextState, AFD);
        }
    }
}

//REFAZER!!
template <typename Symbol_type>
std::set<Machine::State<Symbol_type>*> AutomataWorker<Symbol_type>::getNextState(std::set<Machine::State<Symbol_type>*> states,Symbol_type c){
    std::set<Machine::State<Symbol_type>*> newEstate;
    for(auto s: states){
        for(auto newS: s.get_hit_by(c))
            if(newEstate.count(newS))
                newEstate.push_back(newS);
    }
    return newEstate;
}

template <typename Symbol_type>
std::string AutomataWorker<Symbol_type>::getStateName(std::set<Machine::State<Symbol_type>*> states){
    std::string nome = "";
    for(auto s:states){
        nome += s.getName() + " ";
    }
    return nome;
}

//É preciso para os estados terem o mesmo nome
template <typename Symbol_type>
std::string AutomataWorker<Symbol_type>::ordenaNomeState(std::set<Machine::State<Symbol_type>*> states){
    std::string ret('{');

    std::vector<std::string> aux, vector = getStatesVector(states);

    for(int i = 0;i<vector.size();i++){
        if(vector[i].compare(vector[i+1]) >0 ){
            aux = vector[i];
            vector[i] = vector[i+1];
            vector[i+1] = aux;
        }
    }

    for (auto state : aux)
    {
        ret+=state;
        if(state != *(aux.end())){
            ret+=',';
        }
    }

    ret+='}';

    return ret;
}



#endif
