#ifndef DIALOG_H
#define DIALOG_H
#include "sgprint.h"
class Dialog
{
    bool Dia_Empty;
    int NumberOfLine2;
public:
    std::string AllData;
    Dialog():Empty(true),NumberOfLine{}
    bool Empty(){return Dia_Empty;}
    void Set(int L);
    void Add("")
    {

    }
};

#endif // DIALOG_H
