#ifndef SINGLESTAFF_H
#define SINGLESTAFF_H
#include "handle.h"
#include "publicvalue.h"
template <class T,class P>
class SingleStaff:virtual public HandleSeed
{
    bool Peacefull;
    bool P_StaffInitFinish;
    bool Active_Main;
public:
    bool IsActiveMain(){return Active_Main;}
    void CloseMain(){Active_Main=false;}
    void OpenMain(){Active_Main=true;}
    virtual void Main(T,P){CloseMain();}
    virtual void Init(T,P){P_StaffInitFinish=true;}
    bool IsInitReady(){return P_StaffInitFinish;}
    bool Peace(){return Peacefull;}
    virtual int Contribution(T,P){return -999999;}
            virtual void ChangeBoss(T,P){}
    void Unemploy();
    SingleStaff():Peacefull(false),P_StaffInitFinish(false),Active_Main(true){}
    virtual ~SingleStaff(){}
};

template <class T,class P>
        void SingleStaff<T,P>::Unemploy()
{
    Destory();
}
#endif // SINGLESTAFF_H
