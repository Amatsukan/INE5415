      // using standard exceptions
   /**///*****************************************************///
  /**///-----------------------//----------------------------///
        #include <exception>  // std::exception              //
 /**///----------------------//----------------------------///
/**///****************************************************///
class ExistStateException : public std::exception{
    virtual const char* what() const throw()
    {
        return "State already exists in automaton";
    }
};

class MissingStateException : public std::exception{
    virtual const char* what() const throw()
    {
        return "State does not belong to the automaton";
    }
};

class InvalidStateNameException : public std::exception{
    virtual const char* what() const throw()
    {
        return "StateName must contain at least one character";
    }
};

//SAMPLE
// int main ()
// {
//     ExistStateException myex;

//     try
//     {
//         throw myex;
//     }catch (exception& e)
//     {
//         cout << e.what() << endl;
//     }

//     return 0;
// }
