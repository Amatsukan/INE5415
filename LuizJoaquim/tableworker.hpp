     /**///*****************************************************///
    /**///-----------------------//----------------------------///
         #include <string>      // std::string                 //
        #include <fstream>     // std::multimap               //
       #include "automata.hpp"// Automaton                   //
  /**///_____________________//____________________________///
 /**///***************************************************///

class TableWorker{
private:
    const std::string epsilon = "&";
    std::ofstream inputFile, outputFile;

    void OpenOutputFile(){
        outputFile.open ("teste1AfndAfd.out");
    }

    void OpenInputFile(){
        inputFile.open ("teste1AfndAfd.in");
    }

    void CloseFiles(){
        inputFile.close();
        outputFile.close();
    }
    
    std::vector<std::string> tokenize(std::string line, std::string separator = "|"){
        std::vector<std::string> tokens;
        std::istringstream f(line.c_str());
        std::string s;
        while (getline(f, s, separator)) {
            tokens.push_back(s);
        }
        
        return tokens;
    }
    
    std::vector<std::string> getNEstates(std::string field){
        std::vector<std::string> ret;
        
        if(field.at(0)=='{'){
            return tokenize(field, ",");
        }
        
        ret.push_back(field);
        return ret;
    }
    
public:    
    Automata<std::string> getInputMachine(){
        OpenInputFile();
        
        Automata<std::string> a();
        
        std::string alphabetLine;
        std::getline(inputFile, alphabetLine);
        
        std::vector<std::string> alphabet = tokenize(alphabetLine);
        
        std::string line;
        
        while(std::getline(inputFile, line){
            std::vector<std::string> stateAndTransitions = tokenize(line);
            auto actualState = stateAndTransitions[0];
            bool isFinal = false;
            if(actualState[0] == "*"){
                isFinal ^= 1;
                actualState = actualState.erase(std::remove(actualState.begin(), actualState.end(), '*'), actualState.end());
            }
            if(!a.ExistState(actualState)){
                 a.addState(actualState);
                 if(isFinal)
                    a.toggle_final(actualState);
            }
            for(int i = 1; i< alphabet.size(); i++){
                for(auto s : getNEstates(stateAndTransitions[i]))
                    if(s!="-"){
                        if(!a.ExistState(s)){
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
    
    


};
