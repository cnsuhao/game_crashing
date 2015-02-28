#ifndef DIY_ERROR_H
#define DIY_ERROR_H
#include <string>
class PreRunError
{
public:
    std::string Data;
    PreRunError(std::string S):Data(S){}
    void operator =(std::string S){Data=S;}
    void operator =(char* C){std::string Tem(C);Data=Tem;}
    std::string operator+(std::string S){return Data+S;}
};

class RunInitError
{
public:
    std::string Data;
    RunInitError(std::string S):Data(S){}
    void operator =(std::string S){Data=S;}
    void operator =(char* C){std::string Tem(C);Data=Tem;}
    std::string operator+(std::string S){return Data+S;}
};

class RunError
{
public:
    std::string Data;
    RunError(std::string S):Data(S){}
    void operator =(std::string S){Data=S;}
    void operator =(char* C){std::string Tem(C);Data=Tem;}
    std::string operator+(std::string S){return Data+S;}
};

#endif // ERROR_H
