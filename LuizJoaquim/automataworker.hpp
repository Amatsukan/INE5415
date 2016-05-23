#ifndef AW_H
#define AW_H

#include "automata.hpp"
#include "state.hpp"
#include <set>

template <typename Symbol_type>

class AutomataWorker
{
private:
    void adicionaProximosEstado(std::vector<Symbol_type> alphabet,std::string stateName, std::set<Machine::State<Symbol_type>*> states, Automata<Symbol_type> AFD );

    std::set<Machine::State<Symbol_type>*> getNextState(std::set<Machine::State<Symbol_type>*> states,Symbol_type c);

    std::string getNomeEstado(std::set<Machine::State<Symbol_type>*> states);

    std::string ordenaNomeState(std::set<Machine::State<Symbol_type>*> states);

public:
	Automata<Symbol_type> determiniza(Automata<Symbol_type>);

};

template <typename Symbol_type>
Automata<Symbol_type> AutomataWorker<Symbol_type>::determiniza(Automata<Symbol_type> AFN){

    std::vector<Symbol_type> alphabet = AFN.getAlphabet_vector();

    auto AFD = Automata<Symbol_type>(alphabet);

    auto novoStateI = AFN.get_state_by_name(AFN.getInitial_str()).get_epsilon_reach();


    std::string novoStateI_str = getNomeEstado(novoStateI);

    novoStateI_str = ordenaNomeState(novoStateI); //fazer

    AFD.addState(novoStateI_str);
    AFD.toggle_inicial(novoStateI_str);

    adicionaProximosEstado(alphabet, novoStateI_str, novoStateI, AFD);

    return AFD;
}

template <typename Symbol_type>
void AutomataWorker<Symbol_type>::adicionaProximosEstado(std::vector<Symbol_type> alphabet,std::string stateName, std::set<Machine::State<Symbol_type>*> states, Automata<Symbol_type> AFD ){
    std::set<Machine::State<Symbol_type>*> nextState;
    for(Symbol_type c:alphabet){
        nextState = getNextState(states, c);
        std::string nextState_str = getNomeEstado(nextState);
        nextState_str = ordenaNomeState(nextState_str);
        AFD.addTransition(c, stateName, nextState_str );

        if(!AFD.existState(nextState)){
            AFD.addState(nextState);
            adicionaProximosEstado(alphabet, nextState_str, nextState, AFD);
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
std::string AutomataWorker<Symbol_type>::getNomeEstado(std::set<Machine::State<Symbol_type>*> states){
    std::string nome = "";
    for(auto s:states){
        nome += s.getName() + " ";
    }
    return nome;
}

//É preciso para os estados terem o mesmo nome
template <typename Symbol_type>
std::string AutomataWorker<Symbol_type>::ordenaNomeState(std::set<Machine::State<Symbol_type>*> states){

    return std::string();
}



#endif
