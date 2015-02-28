#ifndef BOSS_H
#define BOSS_H
#include <list>
//#include "controlcenter.h"
//#include <SDL/SDL_mutex.h>
#include "staff.h"
#include "singleboss.h"
#include "publicvalue.h"
#define BOSS
template <class T,class P>
class Boss_StaffActive
{
public:
    bool NeedToInit;
    //PublicValue<SingleBoss<T,P> > SBO;
    PublicValue<SingleBoss<T,P> > SBO;
    PublicValue<std::list<Handle<Staff<T,P> > > > InitList;
#define INSIDE
#define USINGSIZE 1
    #include "bosssomefunction.h"
#undef USINGSIZE
#define USINGSIZE 2
    #include "bosssomefunction.h"
#undef USINGSIZE
#define USINGSIZE 0
    #include "bosssomefunction.h"
#undef USINGSIZE
#define USINGSIZE 3
    #include "bosssomefunction.h"
#undef USINGSIZE
#define USINGSIZE 4
    #include "bosssomefunction.h"
#undef USINGSIZE
#define USINGSIZE 5
    #include "bosssomefunction.h"
#undef USINGSIZE
#define USINGSIZE 6
    #include "bosssomefunction.h"
#undef USINGSIZE
#define USINGSIZE 7
    #include "bosssomefunction.h"
#undef USINGSIZE
#define USINGSIZE 8
    #include "bosssomefunction.h"
#undef USINGSIZE
#define USINGSIZE 9
    #include "bosssomefunction.h"
#undef USINGSIZE
#undef INSIDE
    void Employ(Handle<Staff<T,P> >);
    Boss_StaffActive():NeedToInit(false){}
};


template <class T,class P>
        class Boss:public Boss_StaffActive<T,P>,public Staff<T,P>
{   
    PublicValue<std::list<Handle<Staff<T,P> > > > DList;
    bool NeedToDelete;
public:
    void Accessorial(T,P);
    void Main(T,P);
    void StaffTransfer(T t,P p);
    void JobHopping(Boss<T,P>*,T,P);
    void RunAccessorial(Handle<Staff<T,P> > K,T t,P p){if(K)K->Accessorial(t,p);}
#define OUTSIDE
#define USINGSIZE 1
    #include "bosssomefunction.h"
#undef USINGSIZE
#define USINGSIZE 2
    #include "bosssomefunction.h"
#undef USINGSIZE
#define USINGSIZE 0
    #include "bosssomefunction.h"
#undef USINGSIZE
#define USINGSIZE 3
    #include "bosssomefunction.h"
#undef USINGSIZE
#define USINGSIZE 4
    #include "bosssomefunction.h"
#undef USINGSIZE
#define USINGSIZE 5
    #include "bosssomefunction.h"
#undef USINGSIZE
#define USINGSIZE 6
    #include "bosssomefunction.h"
#undef USINGSIZE
#define USINGSIZE 7
    #include "bosssomefunction.h"
#undef USINGSIZE
#define USINGSIZE 8
    #include "bosssomefunction.h"
#undef USINGSIZE
#define USINGSIZE 9
    #include "bosssomefunction.h"
#undef USINGSIZE
#undef OUTSIDE
    Boss_StaffActive<T,P>* StaffActive(){return this;}
    void UnEmploy(Handle<Staff<T,P> >);
public:
    Boss():NeedToDelete(false)
    {
    }
    ~Boss(){}
};
template <class T,class P>
        void Boss<T,P>::UnEmploy(Handle<Staff<T,P> > H)
{
    if(H)
    {
        DList.Lock();
        DList.push_back(H);
        NeedToDelete=true;
        DList.UnLock();
    }
}

template <class T,class P>
        void Boss<T,P>::JobHopping(Boss<T, P> *B,T t,P p)
{
    Boss_StaffActive<T,P>::SBO.Lock();
    B->Boss_StaffActive<T,P>::SBO.Lock();
    Boss_StaffActive<T,P>::SBO.JobHopping(&B->SBO,t,p);
    B->Boss_StaffActive<T,P>::SBO.UnLock();
    Boss_StaffActive<T,P>::SBO.UnLock();
}

template <class T,class P>
        void Boss<T,P>::StaffTransfer(T t,P p)
{
    Boss_StaffActive<T,P>::SBO.Lock();
    Boss_StaffActive<T,P>::SBO.StaffTransfer(t,p);
    Boss_StaffActive<T,P>::SBO.UnLock();
}


template <class T,class P>
        void Boss_StaffActive<T,P>::Employ(Handle<Staff<T, P> > H)
{
    if(H)
    {
        InitList.Lock();
        InitList.push_back(H);
        InitList.UnLock();
        NeedToInit=true;
    }
}

template <class T,class P>
        void Boss<T,P>::Accessorial(T t, P p)
{
    Train(&Boss<T,P>::RunAccessorial,this,t,p);
}

template <class T,class P>
        void Boss<T,P>::Main(T t, P p)
{
    if(Boss_StaffActive<T,P>::NeedToInit)
    {
        Boss_StaffActive<T,P>::InitList.Lock();
        Boss_StaffActive<T,P>::SBO.Lock();
        for(typename std::list<Handle<Staff<T,P> > >::iterator Po=Boss_StaffActive<T,P>::InitList.begin();Po!=Boss_StaffActive<T,P>::InitList.end();++Po)
        {
            Handle<SingleStaff<T,P> > Pc=*Po;
            Boss_StaffActive<T,P>::SBO.Employ(Pc,t,p);
        }
        Boss_StaffActive<T,P>::InitList.clear();
        Boss_StaffActive<T,P>::SBO.UnLock();
        Boss_StaffActive<T,P>::InitList.UnLock();
        Boss_StaffActive<T,P>::NeedToInit=false;
    }
    if(NeedToDelete)
    {
        DList.Lock();
        Boss_StaffActive<T,P>::SBO.Lock();
        for(typename std::list<Handle<Staff<T,P> > >::iterator Po=DList.begin();Po!=DList.end();++Po)
        {
            Boss_StaffActive<T,P>::SBO.UnEmploy(*Po);
        }
        DList.clear();
        Boss_StaffActive<T,P>::SBO.UnLock();
        DList.UnLock();
    }
    Boss_StaffActive<T,P>::SBO.Lock();
    Boss_StaffActive<T,P>::SBO.Main(t,p);
    Boss_StaffActive<T,P>::SBO.UnLock();
}
#undef BOSS
#endif // BOSS_H
