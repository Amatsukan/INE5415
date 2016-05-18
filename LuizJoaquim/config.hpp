#ifndef cfg_H
#define cfg_H

#include <iostream>
#include <algorithm>
#include <sstream>
     /**///*****************************************************///
    /**///-----------------------//----------------------------///
         #include <string>      // std::string                 //
        #include <fstream>     // std::multimap               //
       #include "automata.hpp"// Automaton                   //
  /**///_____________________//____________________________///
 /**///***************************************************///

    typedef struct {
        bool initialized = false;
        char epsilonChar;
        char finalStateChar;
        std::string initialString;
        char NullSlotTable;
        std::string NotTransition;
    }Config;

class ConfigReader{
private:


    Config c;

    ConfigReader(){}

    std::ifstream configFile;

    void OpenConfigFile(){
        configFile.open ("Config");
    }

    void CloseConfigFile(){
        configFile.close();
    }

    template<typename T>
    void assing(T *to, std::string from);

    template<typename T>
    T getValue(std::string line){
        T internal;
        std::stringstream ss(line); // Turn the string into a stream.
        std::string tok;

        while(std::getline(ss, tok, ':')) {
            assing<T>(&internal, tok);
        }

        return internal;
    }

    void readConfigurations(){
        OpenConfigFile();

        std::string line;

        while(std::getline(configFile, line)){
            if(line[0] == '#') continue;

            if (line.find("EpsilonIdentifier") != std::string::npos) {
                c.epsilonChar = getValue<char>(line);
            }else if (line.find("FinalStateIdentifier") != std::string::npos) {
                c.finalStateChar = getValue<char>(line);
            }else if (line.find("InitialStateIdentifier") != std::string::npos) {
                c.initialString = getValue<std::string>(line);
            }else if (line.find("FirstTableNullSlotId") != std::string::npos) {
                c.NullSlotTable= getValue<char>(line);
            }else if (line.find("NotTransitionIdentifier") != std::string::npos) {
                c.NotTransition= getValue<std::string>(line);
            }
        }
        c.initialized = true;

        CloseConfigFile();
    }

    // static ConfigReader *me;
public:

    // static ConfigReader *Instance(){
    //     if(ConfigReader::me == nullptr){
    //         ConfigReader::me = new ConfigReader();
    //         ConfigReader::me->readConfigurations();
    //     }

    //     return me;
    // }

    static ConfigReader& Instance()
    {
        static ConfigReader instance; // Guaranteed to be destroyed.
                          // Instantiated on first use.
        instance.readConfigurations();
        return instance;
    }

    static char getEpsilon(){
        return Instance().c.epsilonChar;
    }
    static char getFinalStateChar(){
        return Instance().c.finalStateChar;
    }
    static std::string getInitialStateString(){
        return Instance().c.initialString;
    }
    static char getNullSlot(){
        return Instance().c.NullSlotTable;
    }
    static std::string getNotTransition(){
        return Instance().c.NotTransition;
    }

};

template<>
inline void ConfigReader::assing<char>(char *to, std::string from){
    *to = from[0];
}

template<>
inline void ConfigReader::assing<std::string>(std::string *to, std::string from){
    *to = from;
}

#endif
