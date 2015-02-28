#ifdef USINGSIZE
#ifndef BOSSSOMEFUNCTION_H
#define BOSSSOMEFUNCTION_H
#define CLASS(P,B) class P##B
#define VALUE(P,B) P##B v##P##B
#define SINGLEVALUE(P,B) v##P##B



#define TEMPLATENUMBER_0
#define TEMPLATENUMBER_1 TEMPLATENUMBER_0,CLASS(P,1)
#define TEMPLATENUMBER_2 TEMPLATENUMBER_1,CLASS(P,2)
#define TEMPLATENUMBER_3 TEMPLATENUMBER_2,CLASS(P,3)
#define TEMPLATENUMBER_4 TEMPLATENUMBER_3,CLASS(P,4)
#define TEMPLATENUMBER_5 TEMPLATENUMBER_4,CLASS(P,5)
#define TEMPLATENUMBER_6 TEMPLATENUMBER_5,CLASS(P,6)
#define TEMPLATENUMBER_7 TEMPLATENUMBER_6,CLASS(P,7)
#define TEMPLATENUMBER_8 TEMPLATENUMBER_7,CLASS(P,8)
#define TEMPLATENUMBER_9 TEMPLATENUMBER_8,CLASS(P,9)

#define VALUENUMBER_0
#define VALUENUMBER_1 VALUENUMBER_0,VALUE(P,1)
#define VALUENUMBER_2 VALUENUMBER_1,VALUE(P,2)
#define VALUENUMBER_3 VALUENUMBER_2,VALUE(P,3)
#define VALUENUMBER_4 VALUENUMBER_3,VALUE(P,4)
#define VALUENUMBER_5 VALUENUMBER_4,VALUE(P,5)
#define VALUENUMBER_6 VALUENUMBER_5,VALUE(P,6)
#define VALUENUMBER_7 VALUENUMBER_6,VALUE(P,7)
#define VALUENUMBER_8 VALUENUMBER_7,VALUE(P,8)
#define VALUENUMBER_9 VALUENUMBER_8,VALUE(P,9)

#define SINGLEVALUENUMBER_0
#define SINGLEVALUENUMBER_1 SINGLEVALUENUMBER_0,SINGLEVALUE(P,1)
#define SINGLEVALUENUMBER_2 SINGLEVALUENUMBER_1,SINGLEVALUE(P,2)
#define SINGLEVALUENUMBER_3 SINGLEVALUENUMBER_2,SINGLEVALUE(P,3)
#define SINGLEVALUENUMBER_4 SINGLEVALUENUMBER_3,SINGLEVALUE(P,4)
#define SINGLEVALUENUMBER_5 SINGLEVALUENUMBER_4,SINGLEVALUE(P,5)
#define SINGLEVALUENUMBER_6 SINGLEVALUENUMBER_5,SINGLEVALUE(P,6)
#define SINGLEVALUENUMBER_7 SINGLEVALUENUMBER_6,SINGLEVALUE(P,7)
#define SINGLEVALUENUMBER_8 SINGLEVALUENUMBER_7,SINGLEVALUE(P,8)
#define SINGLEVALUENUMBER_9 SINGLEVALUENUMBER_8,SINGLEVALUE(P,9)

#define BOSSFUNCTIONCONNECT(a,b) a##b

#define TEMPLATE(A) BOSSFUNCTIONCONNECT(TEMPLATENUMBER_,A)
#define USINGCLASS(A) BOSSFUNCTIONCONNECT(VALUENUMBER_,A)
#define USINGVALUE(A) BOSSFUNCTIONCONNECT(SINGLEVALUENUMBER_,A)

#endif





    #ifdef SINGLEBOSS
        #ifdef INSIDE
        template <class Z,class K TEMPLATE(USINGSIZE)>
            void Train(void (Z::*PP)(Handle<K > USINGCLASS(USINGSIZE) ),Z *z USINGCLASS(USINGSIZE))
        {
            for(typename std::list<Handle<SingleStaff<T,P> > >::iterator Po=List.begin();Po!=List.end();++Po)
            {
                if(*Po)
                {
                    (z->*PP)(*Po USINGVALUE(USINGSIZE));
                }
            }
        }
        template <class Z,class K,class Q TEMPLATE(USINGSIZE)>
        bool Find(Handle<Q>& R,bool (Z::*PP)(Handle<K > USINGCLASS(USINGSIZE)),Z* z USINGCLASS(USINGSIZE))
        {
            bool HaveFind=false;
            for(typename std::list<Handle<SingleStaff<T,P> > >::iterator Po=List.begin();Po!=List.end();++Po)
            {
                if((z->*PP)(*Po USINGVALUE(USINGSIZE)))
                {
                    R=*Po;
                    HaveFind=true;
                    break;
                }
            }
            return HaveFind;
        }
        #endif
    #endif
    #ifdef BOSS
        #ifdef INSIDE
        template <class Z,class K TEMPLATE(USINGSIZE)>
        void Train(void (Z::*P)(Handle<K> USINGCLASS(USINGSIZE)) ,Z *z USINGCLASS(USINGSIZE))
        {
            SBO.Train(P,z USINGVALUE(USINGSIZE));
        }
        template <class Z,class K,class Q TEMPLATE(USINGSIZE)>
                bool Find(Handle<Q>& R,bool (Z::*p)(Handle<K > USINGCLASS(USINGSIZE)),Z* z USINGCLASS(USINGSIZE))
        {
            bool HaveFind=false;
            HaveFind=SBO.Find(R,p,z USINGVALUE(USINGSIZE));
            return HaveFind;
        }
        #endif
        #ifdef OUTSIDE
        template <class Z,class K TEMPLATE(USINGSIZE)>
        void Train(void (Z::*PP)(Handle<K > USINGCLASS(USINGSIZE)),Z *z USINGCLASS(USINGSIZE))
        {
            Boss_StaffActive<T,P>::SBO.Lock();
            Boss_StaffActive<T,P>::SBO.Train(PP,z USINGVALUE(USINGSIZE));
            Boss_StaffActive<T,P>::SBO.UnLock();
        }
        template <class Z,class K,class Q TEMPLATE(USINGSIZE)>
                bool Find(Handle<Q>& R,bool (Z::*PP)(Handle<K > USINGCLASS(USINGSIZE)),Z* z USINGCLASS(USINGSIZE))
        {
            bool HaveFind=false;
            Boss_StaffActive<T,P>::SBO.Lock();
            HaveFind=Boss_StaffActive<T,P>::SBO.Find(R,PP,z USINGVALUE(USINGSIZE));
            Boss_StaffActive<T,P>::SBO.UnLock();
            return HaveFind;
        }
        #endif
    #endif
    #ifdef UNEQUALBOSS
        #ifdef INSIDE
        template <class Z,class V TEMPLATE(USINGSIZE)>
                void Train(K k,void (Z::*PP)(Handle<V> USINGCLASS(USINGSIZE)),Z* z,UnequalStaff<T,P,K> *Po USINGCLASS(USINGSIZE))
        {
            RWL.Read();
            if(AllMap.count(k)>0)
            {
                    if(Po->Style()==k)
                    {
                        AllMap[k].Boss_StaffActive<T,P>::Train(PP,z USINGVALUE(USINGSIZE));
                    }else{
                        AllMap[k].Train(PP,z USINGVALUE(USINGSIZE));
                    }
            }
            RWL.ReadingFinish();
        }
        template <class Z,class V TEMPLATE(USINGSIZE)>
        void Train(void (Z::*PP)(Handle<V> USINGCLASS(USINGSIZE)),Z * z,UnequalStaff<T,P,K> *Poi USINGCLASS(USINGSIZE))
        {
            RWL.Read();
            for(typename std::map<K,Boss<T,P> >::iterator Po=UnequalBoss_StaffActive<T,P,K>::AllMap.begin();Po!=UnequalBoss_StaffActive<T,P,K>::AllMap.end();++Po)
            {
                if(Poi->Style()==Po->frist)
                    Po->second.Boss_StaffActive<T,P>::Train(PP,z USINGVALUE(USINGSIZE));
                else
                    Po->second.Train(PP,z USINGVALUE(USINGSIZE));
            }
            RWL.ReadingFinish();
        }
        template <class Z,class D,class Q TEMPLATE(USINGSIZE)>
                bool Find(Handle<Q>& R,K k,bool (Z::*PP)(Handle<D> USINGCLASS(USINGSIZE)),Z * z,UnequalStaff<T,P,K> *Poi USINGCLASS(USINGSIZE))
        {
            bool HaveFind=false;
            RWL.Read();
            if(AllMap.count(k)>0)
            {
                    if(Poi->Style()==k)
                        HaveFind=AllMap[k].Boss_StaffActive<T,P>::Find(R,PP,z USINGVALUE(USINGSIZE));
                    else
                        HaveFind=AllMap[k].Find(R,PP,z USINGVALUE(USINGSIZE));
            }
            RWL.ReadingFinish();
            return HaveFind;
        }
        #endif
        #ifdef OUTSIDE
        template <class Z,class V TEMPLATE(USINGSIZE)>
                void UnequalBoss<T,P,K>::Train(K k,void (Z::*PP)(Handle<V> USINGCLASS(USINGSIZE)),Z *z USINGCLASS(USINGSIZE))
        {
            UnequalBoss_StaffActive<T,P,K>::RWL.Read();
            if(UnequalBoss_StaffActive<T,P,K>::AllMap.count(k)==1)
            {
                UnequalBoss_StaffActive<T,P,K>::AllMap[k].Train(PP,z USINGVALUE(USINGSIZE));
            }
            UnequalBoss_StaffActive<T,P,K>::RWL.ReadingFinish();
        }
        template <class Z,class V TEMPLATE(USINGSIZE)>
                void UnequalBoss<T,P,K>::Train(void (Z::*PP)(Handle<V> USINGCLASS(USINGSIZE)),Z *z USINGCLASS(USINGSIZE))
        {
            UnequalBoss_StaffActive<T,P,K>::RWL.Read();
            for(typename std::map<K,Boss<T,P> >::iterator Po=UnequalBoss_StaffActive<T,P,K>::AllMap.begin();Po!=UnequalBoss_StaffActive<T,P,K>::AllMap.end();++Po)
            {
                Po->second.Train(PP,z USINGVALUE(USINGSIZE));
            }
            UnequalBoss_StaffActive<T,P,K>::RWL.ReadingFinish();
        }
        template <class Z,class D,class Q TEMPLATE(USINGSIZE)>
                bool Find(Handle<Q>& R,K k,bool (Z::*PP)(Handle<D> USINGCLASS(USINGSIZE)),Z* z USINGCLASS(USINGSIZE))
        {
            bool HaveFind=false;
            UnequalBoss_StaffActive<T,P,K>::RWL.Read();
            if(UnequalBoss_StaffActive<T,P,K>::AllMap.count(k)>0)
            {
                HaveFind=UnequalBoss_StaffActive<T,P,K>::AllMap[k].Find(R,PP,z USINGVALUE(USINGSIZE));
            }
            UnequalBoss_StaffActive<T,P,K>::RWL.ReadingFinish();
            return HaveFind;
        }
        #endif
    #endif
#endif// BOSSSOMEFUNCTION_H
