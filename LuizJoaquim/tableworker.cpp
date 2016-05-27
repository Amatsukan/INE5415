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

void TableWorker::setOutputMachine(Automata<char> a){
    OpenOutputFile();

    std::string alphabetLine = ConfigReader::spaces(std::to_string((char)ConfigReader::getNullSlot()));
    
    for(char c : a.getAlphabet_vector()){
           alphabetLine = ConfigReader::spaces(std::to_string(c));
    }
    
    outputFile << alphabetLine << std::endl;

    auto states = a.getStates();

    for(auto s:states){
        std::string sName = s.second.getName();
        std::string estado_str = "";
        
        short op = ConfigReader::NONE;
      
        if(a.isInitial(sName)){
            estado_str += ConfigReader::getInitialStateString();
            op += ConfigReader::INITIAL_STATE;
        }
        if(a.isFinal(sName)){
            estado_str += ConfigReader::getFinalStateChar();
            op += ConfigReader::FINAL_STATE;
        }
      
        estado_str += ConfigReader::spaces(sName, op);
        estado_str += a.getStateTransitions_str(sName);
        outputFile << estado_str << std::endl;
    }

    CloseFiles();
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
                if( s!= ConfigReader::getNotTransition() ){
                    if(!a.existState(s)){
                        a.addState(s);
                    }
                    if(alphabet[i] == ConfigReader::getEpsilon())
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
        if((*stateName)[i] == ConfigReader::getFinalStateChar()){
            (*stateName).erase(std::remove((*stateName).begin(), (*stateName).end(), ConfigReader::getFinalStateChar()), (*stateName).end());
            return true;
        }

    return false;
}

bool TableWorker::isInitial(std::string *stateName){

    if ((*stateName).find(ConfigReader::getInitialStateString()) != std::string::npos){
        for(auto c : ConfigReader::getInitialStateString()){
            (*stateName).erase(std::remove((*stateName).begin(), (*stateName).end(), c), (*stateName).end());
        }
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
