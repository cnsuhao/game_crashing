#ifndef SINGLEBOSS_H
#define SINGLEBOSS_H
#include "singlestaff.h"
#define SINGLEBOSS
template <class T,class P>
class SingleBoss_StaffActive
{
protected:
    std::list<Handle<SingleStaff<T,P> > >  List;
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
    //template <class Z,class K,class X,class C>
    //Handle<SingleStaff<T,P> > Find(bool (Z::*)(Handle<K >,X,C),Z*,X,C);
    void Employ(Handle<SingleStaff<T,P> >,T,P);
    SingleBoss_StaffActive<T,P>* StaffActive(){return this;}
};

template <class T,class P>
        class SingleBoss:public SingleStaff<T,P>,public SingleBoss_StaffActive<T,P>
{
public:
    void Main(T t,P p);
    void StaffTransfer(T t,P p);
    void JobHopping(SingleBoss<T,P>*,T t,P p);
    void UnEmploy(Handle<SingleStaff<T,P> >);
    SingleBoss()
    {}
};
template <class T,class P>
        void SingleBoss<T,P>::UnEmploy(Handle<SingleStaff<T,P> > H)
{
    if(H)
    {
        for(typename std::list<Handle<SingleStaff<T,P> > >::iterator Po=SingleBoss_StaffActive<T,P>::List.begin();Po!=SingleBoss_StaffActive<T,P>::List.end();++Po)
        {
            if(*Po==H)
            {
                SingleBoss_StaffActive<T,P>::List.erase(Po);
                break;
            }
        }
    }
}

template <class T,class P>
        void SingleBoss<T,P>::JobHopping(SingleBoss<T, P> *B,T t,P p)
{
    for(typename std::list<Handle<SingleStaff<T,P> > >::iterator Po=SingleBoss_StaffActive<T,P>::List.begin();Po!=SingleBoss_StaffActive<T,P>::List.end();++Po)
    {
        if(*Po)
        {
            (*Po)->ChangeBoss(t,p);
            B->Employ((*Po),t,p);
        }
    }
    SingleBoss_StaffActive<T,P>::List.clear();
}

template <class T,class P>
        void SingleBoss<T,P>::StaffTransfer(T t,P p)
{
    std::map<int,std::list<Handle<SingleStaff<T,P> > > > Tem2;
    for(typename std::list<Handle<SingleStaff<T,P> > >::iterator Po=SingleBoss_StaffActive<T,P>::List.begin();Po!=SingleBoss_StaffActive<T,P>::List.end();++Po)
    {
        if(*Po)
        {
            int Tem3=(*Po)->Contribution(t,p);
            Tem2[Tem3].push_back(*Po);
        }else{
            Tem2[-9999999].push_back(*Po);
        }
    }
    SingleBoss_StaffActive<T,P>::List.clear();
    for(typename std::map<int,std::list<Handle<SingleStaff<T,P> > > >::reverse_iterator Po=Tem2.rbegin();Po!=Tem2.rend();++Po)
    {
        for(typename std::list<Handle<SingleStaff<T,P> > >::iterator Po2=Po->second.begin();Po2!=Po->second.end();++Po2)
        {
            SingleBoss_StaffActive<T,P>::List.push_back(*Po2);
        }
    }
}

/*template <class T,class P>
        template<class Z,class K>
Handle<SingleStaff<T,P> > SingleBoss_StaffActive<T,P>::Find(bool (Z::*PP)(Handle<K >),Z* z)
{
    Handle<SingleStaff<T,P> > Tem;
    for(typename std::list<Handle<SingleStaff<T,P> > >::iterator Po=SingleBoss_StaffActive<T,P>::List.begin();Po!=SingleBoss_StaffActive<T,P>::List.end();++Po)
    {
        if((z->*PP)(*Po))
        {
            Tem=*Po;
            break;
        }
    }
    return Tem;
}
template <class T,class P>
        template<class Z,class K,class X>
Handle<SingleStaff<T,P> > SingleBoss_StaffActive<T,P>::Find(bool (Z::*PP)(Handle<K >,X),Z* z,X p)
{
    Handle<SingleStaff<T,P> > Tem;
    for(typename std::list<Handle<SingleStaff<T,P> > >::iterator Po=SingleBoss_StaffActive<T,P>::List.begin();Po!=SingleBoss_StaffActive<T,P>::List.end();++Po)
    {
        if((z->*PP)(*Po,p))
        {
            Tem=*Po;
            break;
        }
    }
    return Tem;
}
template <class T,class P>
        template<class Z,class K,class X,class C>
Handle<SingleStaff<T,P> > SingleBoss_StaffActive<T,P>::Find(bool (Z::*PP)(Handle<K >,X,C),Z* z,X x,C c)
{
    Handle<SingleStaff<T,P> > Tem;
    for(typename std::list<Handle<SingleStaff<T,P> > >::iterator Po=SingleBoss_StaffActive<T,P>::List.begin();Po!=SingleBoss_StaffActive<T,P>::List.end();++Po)
    {
        if((z->*PP)(*Po,x,c))
        {
            Tem=*Po;
            break;
        }
    }
    return Tem;
}
        template <class T,class P>
                template<class Z,class K>
        void SingleBoss_StaffActive<T,P>::Train(void (Z::*PP)(Handle<K >),Z* z)
        {
            for(typename std::list<Handle<SingleStaff<T,P> > >::iterator Po=List.begin();Po!=List.end();++Po)
            {
                if(*Po)
                {
                        (z->*PP)(*Po);
                }
            }
        }
        template <class T,class P>
                template<class Z,class K,class X>
        void SingleBoss_StaffActive<T,P>::Train(void (Z::*PP)(Handle<K >,X),Z* z,X p)
        {
            for(typename std::list<Handle<SingleStaff<T,P> > >::iterator Po=List.begin();Po!=List.end();++Po)
            {
                if(*Po)
                {
                        (z->*PP)(*Po,p);
                }
            }
        }

        template <class T,class P>
                template<class Z,class K,class X,class U>
        void SingleBoss_StaffActive<T,P>::Train(bool (Z::*PP)(Handle<K >,X,U),Z* z,X p,U u)
        {
            for(typename std::list<Handle<SingleStaff<T,P> > >::iterator Po=List.begin();Po!=List.end();++Po)
            {
                if(*Po)
                {
                        (z->*PP)(*Po,p,u);
                }
            }
        }*/
template <class T,class P>
        void SingleBoss_StaffActive<T,P>::Employ(Handle<SingleStaff<T, P> > H,T t,P p)
{
    if(H)
    {
        if(!H->IsInitReady())
            H->Init(t,p);
        List.push_back(H);
    }
}

template <class T,class P>
        void SingleBoss<T,P>::Main(T t, P p)
{
    for(typename std::list<Handle<SingleStaff<T,P> > >::iterator Po=SingleBoss_StaffActive<T,P>::List.begin();Po!=SingleBoss_StaffActive<T,P>::List.end();++Po)
    {
        if(*Po)
        {
            if((*Po)->IsActiveMain())
                (*Po)->Main(t,p);
        }else{
            SingleBoss_StaffActive<T,P>::List.erase(Po--);
        }
    }
}
#undef SINGLEBOSS
#endif // SINGLESingleBoss_H
