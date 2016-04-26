// using standard exceptions
#include <exception>

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
