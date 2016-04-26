#ifndef TRANS_H
#define TRANS_H

    /**///*****************************************************///
   /**///-----------------------//----------------------------///
  /**/#include <map>           // std::map                    //
 /**/#include "state.hpp"     // Machine::State              //
/**///_______________________//____________________________///

namespace Machine{

    typedef enum{
        FROM, TO
    } Edge;

    //EDGE
    template <typename Symbol_type>
    class Transition{
    private:
        std::map< Edge,State<Symbol_type> > states;

    public:
        Transition(State<Symbol_type> from, State<Symbol_type> to){
            states[FROM] = from;
            states[TO] = to;
        }

        State<Symbol_type> get_next(){
            return states[TO];
        }

        State<Symbol_type> get_actual(){
            return states[FROM];
        }


    };
};

#endif
