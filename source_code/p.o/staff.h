#ifndef STAFF_H
#define STAFF_H
#include "handle.h"
#include "singlestaff.h"
#include "singleboss.h"
template <class T,class P>
class Staff:public SingleStaff<T,P>
{
    //friend class Boss;
    bool Active_Accessorial;
public:
    virtual void Accessorial(T,P){CloseAccessorial();}
    Staff():Active_Accessorial(true){}
    bool IsActiveAccessorial(){return Active_Accessorial;}
    void CloseAccessorial(){Active_Accessorial=false;}
    void OpenAccessorial(){Active_Accessorial=true;}
};
#endif // STAFF_H
