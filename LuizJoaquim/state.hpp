#ifndef STAT_H
#define STAT_H


      /**///*****************************************************///
     /**///-----------------------//----------------------------///
        #include <string>        // std::string                 //
       #include <map>           // std::multimap               //
      #include <queue>         // std::queue                  //
     #include "transition.hpp"// Machine::Transition         //
/**///_______________________//____________________________///

namespace Machine{

    //foward declaration//
    template <typename Symbol_type>
    class Transition;


    //NODE
    template <typename Symbol_type>
    class State{
    private:
        std::string state_name;
        std::string obs = " ";
        bool final_st = false;

                            //Condition, State relationship
        std::multimap< Symbol_type, State<Symbol_type> > transitions;

        State<Symbol_type>* getLimboState(bool acept = false){
            State<Symbol_type>* s = new State<Symbol_type>("LIMBO","Limbo state: created automatically when consuming an unknown entry");
            if(acept){
                s->set_unset_final();
            }

            return s;
        }

    public:
        State(std::string name) : state_name(name){
            std::aligned_storage< sizeof(transitions), std::alignment_of<transitions>::value>::type storage;
        }
        State(std::string name, std::string obs) : state_name(name), obs(obs){
            std::aligned_storage< sizeof(transitions), std::alignment_of<transitions>::value>::type storage;
        }

        void set_unset_final(){
            final_st = !final_st;
        }

        bool isFinal(){
            return final_st;
        }

        std::string getObs(){
            return obs;
        }

        bool operator=(Machine::State<Symbol_type> s){
            return state_name == s.state_name;
        }


        std::vector< State<Symbol_type>* > make_transitions(std::queue<Symbol_type> word){
            std::vector< State<Symbol_type>* > reached_states;

            if(word.empty()){

                reached_states.push_back(this);

            }else{

                Symbol_type token =  word.front();
                // word.pop();

                std::cout<< transitions.size() <<std::endl;
                // if(transitions.count(token) > 0){

                    // for (auto it=its->first; it!=its->second; ++it){
                    //     std::vector< State<Symbol_type>* > results = (*it).second.make_transitions(word);
                    //     reached_states.assign(results.begin(), results.end());
                    // }

                // }else{
                // //     reached_states.push_back(getLimboState());
                // }
             }

            return reached_states;
        }

        void connect(State<Symbol_type> s, Symbol_type condition){
            transitions.insert(std::pair<Symbol_type,State<Symbol_type>>(condition,s));
        }

    };

};

#endif
