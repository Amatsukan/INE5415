#ifndef STAT_H
#define STAT_H

#include <iostream>
#include "config.hpp"

       /**///*****************************************************///
      /**///-----------------------//----------------------------///
         #include <string>        // std::string                 //
        #include <map>           // std::multimap               //
       #include <set>           // std::set                    //
      #include <queue>         // std::queue                  //
  /**///______________________//____________________________///

namespace Machine{

    //NODE
    template <typename Symbol_type>
    class State{
    private:
        std::string state_name;
        std::string obs = " ";


                    //   Condition, State relationship
        std::multimap< Symbol_type, State<Symbol_type>* > transitions;
        std::set<State<Symbol_type>*> epsilonTransitions;

        State<Symbol_type>* getLimboState(){
            static State<Symbol_type>* s = new State<Symbol_type>(ConfigReader::getNotTransition() ,"Limbo state: created automatically when consuming an unknown entry");
            return s;
        }

    public:
        State(std::string name) : state_name(name){}

        State(std::string name, std::string obs) : state_name(name), obs(obs){}

        std::string getObs(){
            return obs;
        }

        std::string getName(){
            return state_name;
        }
      
        std::string getLimboName(){
            return getLimboState ->getName();
        }

        bool operator=(Machine::State<Symbol_type> s){
            return state_name == s.state_name;
        }

        std::set<State<Symbol_type>*> get_epsilon_reach(){
            return epsilonTransitions;
        }

        std::set<State<Symbol_type>*> get_hit_by(Symbol_type symbol){
            std::vector< State<Symbol_type>* > reached_states;

            if(transitions.count(symbol) > 0){
                auto its = transitions.equal_range(symbol);
                for (auto it=its.first; it!=its.second; ++it){
                    reached_states.push_back((*it).second);;
                }
            }else{
                reached_states.push_back(getLimboState());
            }

            return reached_states;
        }

        std::string get_hit_by_str(Symbol_type symbol){
            std::string reached_states = "";

            if(transitions.count(symbol) > 0){
                auto its = transitions.equal_range(symbol);
                for (auto it=its.first; it!=its.second; ++it){
                    reached_states+=(*it).second->getName();
                    reached_states+="\t";
                }
            }else{
                reached_states =  getLimboState()->getName();
            }

            return reached_states;
        }

        std::string get_epsilon_reach_str(){
            std::string reached_states = "";

            for (auto state :  epsilonTransitions)
            {
                reached_states+=state->getName();
                reached_states+=" ";
            }

            return reached_states;
        }

        std::vector< State<Symbol_type>* > make_transitions(std::queue<Symbol_type> word){
            std::vector< State<Symbol_type>* > reached_states;


            if(epsilonTransitions.size() > 0){
                for (auto it=epsilonTransitions.begin(); it!=epsilonTransitions.end(); ++it){
                        std::vector< State<Symbol_type>* > results = (*it)->make_transitions(word);
                        reached_states.insert( reached_states.end(), results.begin(), results.end() );
                    }
            }



            if(word.empty()){
                reached_states.push_back(this);
                return reached_states;

            }else{

                Symbol_type token =  word.front();
                word.pop();

                if(transitions.count(token) > 0){
                    auto its = transitions.equal_range(token);
                    for (auto it=its.first; it!=its.second; ++it){
                        std::vector< State<Symbol_type>* > results = (*it).second->make_transitions(word);
                        reached_states.insert( reached_states.end(), results.begin(), results.end() );
                    }
                }else{
                    reached_states.push_back(getLimboState());
                }
             }


            return reached_states;
        }

        void connect(State<Symbol_type>* s, Symbol_type condition){
            transitions.insert(std::pair<Symbol_type, State<Symbol_type>* >(condition,s));
        }
        void epsilonConnect(State<Symbol_type>* s){
            epsilonTransitions.insert(s);
        }

    };

};

#endif
