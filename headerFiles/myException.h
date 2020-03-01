//*********************INCLUDE GUARD*********************
#ifndef __MY_EXCEPTION_H__
#define __MY_EXCEPTION_H__
//*********************INCLUDE GUARD*********************

//*********************REQUIRED INCLUDES*********************
#include <exception>
#include <string>
//*********************REQUIRED INCLUDES*********************

using namespace std;

typedef enum CODES{
    INFORMATIONAL,
    WARNING,
    ERROR,
    SYSTEM_FAILURE
}e_CODES;

    #define     REDCOLOR    "\033[1;31m"
    #define     MAGENTA     "\033[1;35m"
    #define     YELLOW      "\033[1;33m"
    #define     GREY        "\033[1;37m"
    #define     CLOSE       "\033[0m"

//*********************START CLASS MyException DEFINITION*********************
class MyException : public exception {
    public:
        MyException(void);
        MyException(const char*, e_CODES=INFORMATIONAL);
        MyException(const string&, e_CODES=INFORMATIONAL);
        virtual const string what(){
            return this->retrieveError();
        }
        const e_CODES getCode(){
            return this->errCode;
        }
    private:
        string errString;
        e_CODES errCode;

        string retrieveError(void);
        
};
//*********************END CLASS MyException DEFINITION*********************

#endif