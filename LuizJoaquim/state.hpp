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
            transitions = std::multimap< Symbol_type, State<Symbol_type> >();
        }
        State(std::string name, std::string obs) : state_name(name), obs(obs){
            transitions = std::multimap< Symbol_type, State<Symbol_type> >();
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

            std::cout<<"State:"<< state_name <<" symbol:" << word.front() <<" word size:"<<word.size()<<std::endl;

            if(word.empty()){

                std::cout<<"Reached: "<<state_name<<std::endl;

                reached_states.push_back(this);

            }else{

                Symbol_type token =  word.front();
                word.pop();

                if(transitions.count(token) > 0){

                    auto its = transitions.equal_range(token);
                    for (auto it=its.first; it!=its.second; ++it){
                        std::cout<<"["<< state_name <<", s= " << word.front()<<" goto-> "<<(*it).second.state_name<<"]"<<std::endl;
                        std::vector< State<Symbol_type>* > results = (*it).second.make_transitions(word);
                        reached_states.assign(results.begin(), results.end());
                    }

                }else{
                    std::cout<<"LIMBO"<<std::endl;
                    reached_states.push_back(getLimboState());
                 }
             }

            return reached_states;
        }

        void connect(State<Symbol_type> s, Symbol_type condition){
            transitions.insert(std::pair<Symbol_type,State<Symbol_type>>(condition,s));
        }

    };

};

#endif
