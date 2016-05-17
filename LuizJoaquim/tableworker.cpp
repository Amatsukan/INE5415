#include "tableworker.hpp"
#include <sstream>

std::vector<std::string> TableWorker::getNEstates(std::string *field){
    std::vector<std::string> ret;

    if((*field).at(0)=='{'){
        (*field).erase(std::remove((*field).begin(), (*field).end(), '{'), (*field).end());
        (*field).erase(std::remove((*field).begin(), (*field).end(), '}'), (*field).end());
        return tokenize<std::string>((*field), ',');
    }

    ret.push_back(*field);
    return ret;
}

Automata<char> TableWorker::getInputMachine(){
    OpenInputFile();


    std::string alphabetLine;
    std::getline(inputFile, alphabetLine);

    trimToSeparator(&alphabetLine);

    std::vector<char> alphabet = tokenize<char>(alphabetLine);

    Automata<char> a = Automata<char>(alphabet);

    std::string line;

    while(std::getline(inputFile, line)){

        trimToSeparator(&line);

        if(line.size() == 0) continue;

        std::vector<std::string> stateAndTransitions = tokenize<std::string>(line);

        auto actualState = stateAndTransitions[0];
        bool is_final = isFinal(&actualState);
        bool is_initial = isInitial(&actualState);

        if(! a.existState(actualState) ){
            a.addState(actualState);
            if(is_final)
                a.toggle_final(actualState);
            if(is_initial)
                a.toggle_initial(actualState);
        }
        for(int i = 1; i< alphabet.size(); i++){
            for(auto s : getNEstates( &(stateAndTransitions[i]) ))
                if(s!="-"){
                    if(!a.existState(s)){
                        a.addState(s);
                    }
                    if(alphabet[i] == epsilon)
                        a.addEpsilonTransition(actualState, s);
                    else
                        a.addTransition(alphabet[i], actualState, s);
                }
        }
    }

    CloseFiles();
    return a;
}

bool TableWorker::isFinal(std::string *stateName){

    for (int i = 0; i < stateName->size(); ++i)
        if((*stateName)[i] == '*'){
            (*stateName).erase(std::remove((*stateName).begin(), (*stateName).end(), '*'), (*stateName).end());
            return true;
        }

    return false;
}

bool TableWorker::isInitial(std::string *stateName){

        for (int i = 0; i < stateName->size()-1; ++i)
        if((*stateName)[i] == '-' and (*stateName)[i+1] =='>'){
            (*stateName).erase(std::remove((*stateName).begin(), (*stateName).end(), '-'), (*stateName).end());
            (*stateName).erase(std::remove((*stateName).begin(), (*stateName).end(), '>'), (*stateName).end());
            return true;
        }

    return false;
}

void TableWorker::trimToSeparator(std::string *line, char separator){
    char actualChar = (*line)[0], nextChar= (*line)[0], space = ' ';
    std::string ret;

    for (int i = 0; i < line->size(); ++i)
    {
        actualChar = (*line)[i];

        if(i+1 < line->size()){
            nextChar = (*line)[i+1];
        }

        if(actualChar == '\0' or actualChar == '\n') continue;

        if(actualChar == space ){
            if(nextChar != space){
                ret+=separator;
            }
        }else{
            ret+=actualChar;
        }
    }
    ret+="\0";

    *line = ret;
}
