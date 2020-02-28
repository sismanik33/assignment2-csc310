#include "myException.h"

using namespace std;


/**************************** PUBLIC: Constructor ****************************/
MyException::MyException(void){
    this->errString = "Program failed to execute properly.";
    this->errCode = SYSTEM_FAILURE;
        }

/**************************** PUBLIC: Constructor ****************************/
MyException::MyException(const string &errorString, e_CODES errorCode){
    this->errString = errorString;
    this->errCode = errorCode;
}

/**************************** PUBLIC: Constructor ****************************/
MyException::MyException(const char *errorString, e_CODES errorCode){
    this->errString = errorString;
    this->errCode = errorCode;
}

/**************************** PUBLIC: retrieveError ****************************/
string MyException::retrieveError(void){
    if (this->errCode == INFORMATIONAL){
        this->errString = GREY + string("INFO: ") + this->errString + CLOSE;
    } else if(this->errCode == WARNING){
        this->errString = YELLOW + string("WARNING: ") + this->errString + CLOSE;
    } else if(this->errCode == ERROR){
        this->errString = MAGENTA + string("ERROR: ") + this->errString + CLOSE;
    } else if(this->errCode == SYSTEM_FAILURE){
        this->errString = REDCOLOR + string("SYSTEM FAILURE: ") + this->errString + CLOSE;
    }

    return this->errString;
}