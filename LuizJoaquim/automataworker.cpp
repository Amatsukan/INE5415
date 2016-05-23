#include "automataworker.hpp"
#include "state.hpp"
#include <string>

template <typename Symbol_type>


Automata<Symbol_type> AutomataWorker::determiniza(Automata<Symbol_type> AFN){

	std::vector<char> alphabet = AFN.getAlphabet_vector();

	auto AFD = Automata<char>(alphabet);

	std::set<State<Symbol_type>*> novoStateI = AFN.get_state_by_name(AFN.getInitial_str()).get_epsilon_reach();


	std::string novoStateI_str = getNomeEstado(novoStateI);

	novoStateI_str = ordenaNomeState(novoStateI); //fazer

	AFD.addState(novoStateI_str);
	AFD.toggle_inicial(novoStateI_str);

	adicionaProximosEstado(alphabet, novoStateI_str, novoStateI, AFD);

	return AFD;
}

void AutomataWorker::adicionaProximosEstado(std::vector<char> alphabet,std::string stateName, set<State<Symbol_type>*> states, Automata<char> AFD ){
	set<State<Symbol_type>*> nextState;
	for(char c:alphabet){
		nextState = getNextState(states, c);
		std::string nextState_str = getNomeEstado(nextState);
		nextState_str = ordenaNomeState(nextState_str); 
		AFD.addTransition(c, stateName, nextState_str )	

		if(!AFD.existState(nextState)){
			AFD.addState(nextState);
			adicionaProximosEstado(alphabet, nextState_str, nextState, AFD);
		}
	}
}

//REFAZER!!
std::set<State<Symbol_type>*> AutomataWorker::getNextState(set<State<Symbol_type>*> states,char c){
	std::set<State<Symbol_type>*> newEstate;
	for(State s: states){
		for(State newS: s.get_hit_by(c))
			if(newEstate.count(newS))
				newEstate.push_back(newS);
	}
	return newEstate;
}

std::string AutomataWorker::getNomeEstado(set<State<Symbol_type>*> states){
	std::string nome = "";
	for(State s:states){
		nome += s.getName() + " ";
	}
	return nome;
}

//É preciso para os estados terem o mesmo nome
std::string AutomataWorker::ordenaNomeState(set<State<Symbol_type>*> states){


}

}