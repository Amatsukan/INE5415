#ifndef STAT_H
#define STAT_H

//---------------------------//--------------//
#include <string>           // std::string  //
#include <vector>          // std::vector  //
#include <queue>          // std::queue   //
#include "transition.hpp"//              //
//______________________//______________//

namespace Machine{

    //foward declaration//
    template <typename Symbol_type>
    class Transition;

    //NODE
    template <typename Symbol_type>
    class State{
    private:
        std::string name;
        std::string obs = " ";
        bool final_st = false;
        bool initial_st = false;

        std::vector < Transition<Symbol_type> > transitions;

    public:
        State(){}
        State(std::string name) : name(name){}
        State(std::string name, std::string obs) : name(name), obs(obs){}

        void set_unset_intial(){
            initial_st = !initial_st;
        }

        void set_unset_final(){
            final_st = !final_st;
        }

        bool isFinal(){
            return final_st;
        }

        bool isInitial(){
            return initial_st;
        }

        std::string getObs(){
            return obs;
        }

        std::string getName(){
            return name;
        }

        //TODO works only in AFD, improve to AFND
        State<Symbol_type> make_transitions(std::queue<Symbol_type> word){
            if(word.empty()){
                return &this;
            }else{
                Symbol_type actual_token = word.pop();
                for(Transition<Symbol_type> t : transitions){
                    if(t.matchCondition(actual_token)){
                        return t.get_next().make_transitions(word);
                    }
                }

                throw /*LIMBO*/0;
            }
        }

        void connect(State<Symbol_type> s, Symbol_type condition){
            transitions.push_back(Transition<Symbol_type>(condition, &this, s));
        }

        bool operator==(std::string s){
            return name == s;
        }

        bool operator==(State& s){
            return name == s.getName();
        }

    };

};

#endif
