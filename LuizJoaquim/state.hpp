#ifndef STAT_H
#define STAT_H

       /**///******************************************************///
      /**///------------------------//----------------------------///
          #include "config.hpp"    // ConfigReader                //
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

        std::vector<std::string> get_epsilon_close(){
            std::vector<std::string> ret;
            ret.push_back(getName());
            for(auto state : epsilonTransitions){
                ret.push_back(state->getName());
            }

            return ret;
        }

        std::set<State<Symbol_type>*> get_hit_by(Symbol_type symbol){
            std::set< State<Symbol_type>* > reached_states;

            if(transitions.count(symbol) > 0){
                auto its = transitions.equal_range(symbol);
                for (auto it=its.first; it!=its.second; ++it){
                    reached_states.insert((*it).second);;
                }
            }else{
                reached_states.insert(getLimboState());
            }

            return reached_states;
        }

        std::string get_hit_by_epsilon_str(){
            std::string reached_states = "";

            if(epsilonTransitions.size() == 1){

                reached_states+=(*(epsilonTransitions.begin()))->getName();

            }else if(epsilonTransitions.size() > 1){
                reached_states+="{";

                auto first = epsilonTransitions.begin(), last = epsilonTransitions.end();
                for (auto it=first; it!=last; ++it){
                    reached_states+=(*it)->getName();
                    auto it_cpy = it;
                    if( it_cpy++ != last )
                        reached_states+=",";
                }
                reached_states[reached_states.size()-1] = '}';

            }else{
                reached_states =  getLimboState()->getName();
            }

            return reached_states;
        }

        std::string get_hit_by_str(Symbol_type symbol){
            std::string reached_states = "";

            if(transitions.count(symbol) == 1){

                auto its = transitions.equal_range(symbol);

                reached_states+=(*(its.first)).second->getName();

            }else if(transitions.count(symbol) > 1){
                reached_states+="{";
                auto its = transitions.equal_range(symbol);
                for (auto it=its.first; it!=its.second; ++it){
                    reached_states+=(*it).second->getName();
                    auto it_cpy = it;
                    if( it_cpy++ != its.second )
                        reached_states+=",";
                }
                reached_states[reached_states.size()-1] = '}';

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

        std::set< State<Symbol_type>* > make_transitions(std::queue<Symbol_type> word){
            std::set< State<Symbol_type>* > reached_states;

            if(epsilonTransitions.size() > 0){
                for (auto it=epsilonTransitions.begin(); it!=epsilonTransitions.end(); ++it){
                        std::set< State<Symbol_type>* > results = (*it)->make_transitions(word);
                        reached_states.insert( results.begin(), results.end() );
                    }
            }

            if(word.empty()){
                reached_states.insert(this);
                return reached_states;
            }else{

                Symbol_type token =  word.front();
                word.pop();

                if(transitions.size() > 0){
                    if(transitions.count(token) > 0){
                        auto its = transitions.equal_range(token);
                        for (auto it=its.first; it!=its.second; ++it){
                            std::set< State<Symbol_type>* > results = (*it).second->make_transitions(word);
                            reached_states.insert( results.begin(), results.end() );
                        }
                    }else{
                        reached_states.insert(getLimboState());
                    }
                }
                else{
                    reached_states.insert(getLimboState());
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
