#ifndef TW_H
#define TW_H

        /**///******************************************************///
       /**///------------------------//----------------------------///
             #include "config.hpp"  // ConfigReader                //
            #include <string>      // std::string                 //
           #include <fstream>     // std::multimap               //
          #include "automata.hpp"// Automaton                   //
         #include <algorithm>   // std::getLine                //
        #include <sstream>     // std::stringstream           //
  /**///______________________//____________________________///
 /**///****************************************************///

class TableWorker{
private:

    std::ifstream inputFile;
    std::ofstream outputFile;

    void OpenOutputFile(){
        outputFile.open ("teste1AfndAfd.out", std::ios::trunc | std::ios::out);
    }

    void OpenInputFile(){
        inputFile.open ("teste1AfndAfd.in");
    }

    void CloseFiles(){
        inputFile.close();
        outputFile.close();
    }

    bool isFinal(std::string *stateName);

    bool isInitial(std::string *stateName);

    void trimToSeparator(std::string *line, char separator = '|');

    template<typename T>
    void Insert(std::string tok, std::vector<T> *vector);

    template<typename type>
    std::vector<type> tokenize(std::string line, char separator = '|'){
        std::vector<type> internal;
        std::stringstream ss(line); // Turn the string into a stream.
        std::string tok;

        while(std::getline(ss, tok, separator)) {
            Insert<type>(tok, &internal);
        }

        return internal;
    }

    std::vector<std::string> getNEstates(std::string *field);

public:

    void setOutputMachine(Automata<char>);
    Automata<char> getInputMachine();
};

template<>
inline void TableWorker::Insert<std::string>(std::string tok, std::vector<std::string> *vector){
    vector->push_back(tok);
}

template<>
inline void TableWorker::Insert<char>(std::string tok, std::vector<char> *vector){
    char c = tok.at(0);
    vector->push_back(c);
}

#endif
