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
        bool initial_st = false;

                            //Condition, State relationship
        std::multimap< Symbol_type, State<Symbol_type> > transitions;

        State<Symbol_type> getLimboState(bool acept = false){
            State<Symbol_type> s("LIMBO","Limbo state: created automatically when consuming an unknown entry");
            if(acept){
                s.set_unset_final();
            }

            return s;
        }

    public:
        State(std::string name) : state_name(name){}
        State(std::string name, std::string obs) : state_name(name), obs(obs){}

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

        //TODO works only in AFD, improve to AFND
        std::vector< State<Symbol_type> > make_transitions(std::queue<Symbol_type> word){
            std::vector< State<Symbol_type> > reached_states;

            if(word.empty()){
                return reached_states.push_back(*this);
            }else{
                Symbol_type actual_token = word.pop();
                for(Transition<Symbol_type> t : transitions){
                    if(t.matchCondition(actual_token)){
                        reached_states.push_back(t.get_next().make_transitions(word));
                    }
                }

                if(reached_states.empty())
                    reached_states.push_back(getLimboState());

                return reached_states;
            }
        }

        void connect(State<Symbol_type> s, Symbol_type condition){
            transitions.insert({condition,s});
        }

    };

    template <typename Symbol_type>
    class LimboState : public State<Symbol_type>{
    public:
        LimboState(bool acept = false) : State<Symbol_type>("LIMBO","Limbo state: created automatically when consuming an unknown entry"){
            if(acept){
                this->set_unset_final();
            }
        }

    };

};

#endif
