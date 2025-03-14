#include "MyException.h"
namespace GTU{    
    MyException::MyException():MyException("There is no information!"){}
    MyException::MyException(string text):message(text){}
    string MyException::getExceptionDetails() const{
        return message;
    }

}