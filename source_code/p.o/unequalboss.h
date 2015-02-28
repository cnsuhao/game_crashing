#ifndef UNEQUALBOSS_H
#define UNEQUALBOSS_H
#include <map>
#include <list>
#include "unequalstaff.h"
#include "boss.h"
#define UNEQUALBOSS
template <class T,class P,class K>
class UnequalBoss_StaffActive
{
protected:
    ReadWriteLock RWL;
    PublicValue<std::list<Handle<UnequalStaff<T,P,K> > > > Init;
    PublicBaseValue<bool> NeedToInit;
    std::map<K,Boss<T,P> >  AllMap;
public:
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
    UnequalBoss_StaffActive<T,P,K>* StaffActive(){return this;}
    UnequalBoss_StaffActive<T,P,K>(){NeedToInit=false;}
    void Employ(Handle<UnequalStaff<T,P,K> >);
};
template <class T,class P,class K>
        class UnequalBoss:public UnequalBoss_StaffActive<T,P,K>
{
public:
    UnequalBoss(){}
    void UnequalBoss<T,P,K>::StaffTransfer(T t,P p,K k);
    void UnequalBoss<T,P,K>::StaffTransfer(T t,P p);
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
    void Accessorial(T t, P p);
    void Main(T t, P p);
    void JobHopping(UnequalBoss<T,P,K>*,T,P);
    void JobHopping(UnequalBoss<T,P,K>*,K,T,P);
};



template <class T,class P,class K>
        void UnequalBoss_StaffActive<T,P,K>::Employ(Handle<UnequalStaff<T, P, K> > C)
{
    if(C)
    {
        RWL.Read();
        if(AllMap.count(C->Style())>0)
            AllMap[C->Style()].Employ(C);
        else{
            Init.Lock();
            Init.push_back(C);
            Init.UnLock();
            NeedToInit=true;
        }
        RWL.ReadingFinish();
    }
}




template <class T,class P,class K>
        void UnequalBoss<T,P,K>::JobHopping(UnequalBoss<T,P,K>* UB,K k,T t,P p)
{
    UnequalBoss_StaffActive<T,P,K>::RWL.Read();
    if(UnequalBoss_StaffActive<T,P,K>::AllMap.count(k)==1)
    {
        UnequalBoss_StaffActive<T,P,K>::AllMap[k].JobHopping(&UB->AllMap[k],t,p);
    }
    UnequalBoss_StaffActive<T,P,K>::RWL.ReadingFinish();
}

template <class T,class P,class K>
        void UnequalBoss<T,P,K>::JobHopping(UnequalBoss<T,P,K>* UB,T t,P p)
{
    UnequalBoss_StaffActive<T,P,K>::RWL.Read();
    for(typename std::map<K,Boss<T,P> >::iterator Po=UnequalBoss_StaffActive<T,P,K>::AllMap.begin();Po!=UnequalBoss_StaffActive<T,P,K>::AllMap.end();++Po)
    {
        Po->second.JobHopping((*UB)[Po->frist],t,p);
    }
    UnequalBoss_StaffActive<T,P,K>::RWL.ReadingFinish();
}

template <class T,class P,class K>
        void UnequalBoss<T,P,K>::StaffTransfer(T t,P p,K k)
{
    UnequalBoss_StaffActive<T,P,K>::RWL.Read();
    if(UnequalBoss_StaffActive<T,P,K>::AllMap.count(k)==1)
    {
        UnequalBoss_StaffActive<T,P,K>::AllMap[k].StaffTransfer(t,p);
    }
    UnequalBoss_StaffActive<T,P,K>::RWL.ReadingFinish();
}
template <class T,class P,class K>
        void UnequalBoss<T,P,K>::StaffTransfer(T t,P p)
{
    UnequalBoss_StaffActive<T,P,K>::RWL.Read();
    for(typename std::map<K,Boss<T,P> >::iterator Po=UnequalBoss_StaffActive<T,P,K>::AllMap.begin();Po!=UnequalBoss_StaffActive<T,P,K>::AllMap.end();++Po)
        Po->second.StaffTransfer(t,p);
    UnequalBoss_StaffActive<T,P,K>::RWL.ReadingFinish();
}
template <class T,class P,class K>
        void UnequalBoss<T,P,K>::Accessorial(T t, P p)
{
    UnequalBoss_StaffActive<T,P,K>::RWL.Read();
    for(typename std::map<K,Boss<T,P> >::iterator Po=UnequalBoss_StaffActive<T,P,K>::AllMap.begin();Po!=UnequalBoss_StaffActive<T,P,K>::AllMap.end();++Po)
        Po->second.Accessorial(t,p);
    UnequalBoss_StaffActive<T,P,K>::RWL.ReadingFinish();
}

template <class T,class P,class K>
        void UnequalBoss<T,P,K>::Main(T t, P p)
{
    if(UnequalBoss<T,P,K>::NeedToInit)
    {
        UnequalBoss_StaffActive<T,P,K>::RWL.Write();
        UnequalBoss_StaffActive<T,P,K>::Init.Lock();
        for(typename std::list<Handle<UnequalStaff<T,P,K> > >::iterator Po=UnequalBoss_StaffActive<T,P,K>::Init.begin();Po!=UnequalBoss_StaffActive<T,P,K>::Init.end();++Po)
        {
            if(*Po)
            {
                UnequalBoss_StaffActive<T,P,K>::AllMap[(*Po)->Style()].Employ(*Po);
            }
        }
        UnequalBoss_StaffActive<T,P,K>::Init.clear();
        UnequalBoss_StaffActive<T,P,K>::Init.UnLock();
        UnequalBoss_StaffActive<T,P,K>::RWL.WriteFinish();
        UnequalBoss<T,P,K>::NeedToInit=false;
    }
    UnequalBoss_StaffActive<T,P,K>::RWL.Read();
    for(typename std::map<K,Boss<T,P> >::iterator Po=UnequalBoss_StaffActive<T,P,K>::AllMap.begin();Po!=UnequalBoss_StaffActive<T,P,K>::AllMap.end();++Po)
    {
        Po->second.Main(t,p);
    }
    UnequalBoss_StaffActive<T,P,K>::RWL.ReadingFinish();
}
#undef UNEQUALBOSS
#endif
