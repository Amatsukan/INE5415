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

    std::ifstream inputs;
    std::ofstream outputs;

    int lc(){
        CloseInputFile();
        OpenInputFile();
        std::string filler;
        int i;
        for (i = 0; std::getline(inputs, filler); ++i);
        CloseInputFile();
        OpenInputFile();
        return i;
    }

    void OpenInputFile(){
        inputs.open ("test.in");
    }

    void CloseInputFile(){
        inputs.close();
    }

    void OpenOutputFile(){
        outputs.open ("test.out", std::ios::trunc | std::ios::out);
    }

    void CloseOutputFile(){
        outputs.close();
    }

    std::vector< std::queue<char> > getWords(){
        OpenInputFile();
        std::string tok;

        auto ret = std::vector< std::queue<char> >();

        if(lc() < 1){
            std::cout<<"There is no inputs in input.in file... Skipping test"<<std::endl;
            return ret;
        }

        std::cout<<"Testing for "<<lc()<<" inputs..."<<std::endl;

        while(getline(inputs,tok)){

            std::queue<char> actualWord;

            for(char c : tok){
                if(c == '\n' and c == '\r' and c == '\0' and c == ' ') continue;
                actualWord.push(c);
            }

            ret.push_back(actualWord);
        }

        CloseInputFile();

        return ret;
    }

    std::string toString(std::queue<char> word){
        std::string ret;
        for(int i = 0; i<=word.size(); i++){
            ret+=(char)word.front();
            word.pop();
        }

        return ret;
    }

public:

    void test(Automata<char> a){

        auto words = getWords();

        OpenOutputFile();
        for(auto word : words){
            outputs<<toString(word)<<" -- "<<(a.validateWord(word) ? "OK" : "NOT OK")<<std::endl;
        }
        CloseOutputFile();

        std::cout<<"Test end!"<<std::endl;

    }

};


#endif
