#ifndef Tester_H
#define Tester_H

        /**///*****************************************************///
       /**///-----------------------//----------------------------///
            #include <string>      // std::string                 //
           #include <fstream>     // std::multimap               //
          #include "automata.hpp"// Automaton                   //
         #include <algorithm>   // std::getLine                //
        #include <sstream>     // std::stringstream           //
  /**///______________________//____________________________///
 /**///****************************************************///

class Tester{
private:

    std::fstream inputs;
    std::ofstream outputs;

    void OpenInputFile(){
        inputs.open ("inputs");
    }

    void CloseInputFile(){
        inputs.close();
    }

    void OpenOutputFile(){
        inputs.open ("testOutput", std::ios::trunc);
    }

    void CloseOutputFile(){
        inputs.close();
    }

    std::vector< std::queue<char> > getWords(){
        OpenInputFile();
        std::string tok;

        auto ret = std::vector< std::queue<char> >();

        while(std::getline(inputs,tok)){

            std::queue<char> actualWord;

            for(char c : tok){
                actualWord.push(c);
            }

            ret.push_back(actualWord);
        }

        CloseInputFile();

        return ret;
    }

    std::string toString(std::queue<char> word){
        std::string ret;
        for(int i = 0; i<word.size(); i++){
            ret+=word.front();
            word.pop();
        }
        ret+='\0';

        return ret;
    }

public:

    void test(Automata<char> a){
        CloseOutputFile();

        for(auto word : getWords()){
            outputs<<toString(word);
            outputs<<" -- ";
            outputs<<(a.validateWord(word) ? "OK" : "NOT OK")<<std::endl;
        }

        CloseOutputFile();
    }

};


#endif
