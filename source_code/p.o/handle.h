#ifndef DIY_HANDLE_H
#define DIY_HANDLE_H
#include <stdio.h>
class HandleSeed
{
    public:
    bool Exist;
    unsigned int Life;
    unsigned int Using;
    virtual ~HandleSeed(){}
    virtual bool CheckExist(){return Exist;}
    virtual void Destory(){Exist=false;}
    //virtual void Use()=0;
    HandleSeed():Exist(true),Using(0),Life(0){}
};


template <class T>
class Handle
{
    public:
        bool Used;
        T* Data;
        unsigned int Life;
        void operator =(T* L);
        bool operator ==(Handle&);
        void operator =(Handle&);
        bool operator<(Handle<T>& H){return Data<H.Data;}
        template <class G>
                void operator =(Handle<G>&);
        template <class G>
                bool operator ==(G*);
        template <class G>
                bool operator !=(G*);
        template <class G>
                bool operator !=(Handle<G>&);
        void Rebirth();
        void Follow(){if(Used) Life=Data->HandleSeed::Life;}
        void Unused();
        operator bool();
        bool Exist();
        operator T*(void){return Data;}
        T* operator->(){return Data;}
        template <class G>
                bool operator ==(Handle<G>&);
        template <class P>
                operator Handle<P>();
        Handle():Used(false),Data(0){}
        Handle(const Handle& H);
        Handle(T*);
        virtual ~Handle();
};

class HandleArraySize:public HandleSeed
{
public:
    int Size;
    HandleArraySize():Size(0){}
    ~HandleArraySize(){}
};



template<class T>
class HandleArray
{
    class HandleList:public HandleSeed
    {
    public:
        Handle<T> This;
        Handle<HandleList> Last;
        Handle<HandleList> Next;
        HandleList(Handle<T> P):This(P){}
    };
    Handle<HandleList> Begin;
    Handle<HandleList> TheEnd;
    int Size;
    Handle<HandleArraySize> Using;
public:
        Handle<T> Front();
        Handle<T> End();
        bool Empty(){if(Size<=0)return true;return false;}
        bool Add(Handle<T> c){AddFront(c);}
        void Unused();
        void AddEnd(Handle<T>);
        void AddFront(Handle<T>);
        void operator =(HandleArray<T>&);
        HandleArray():Size(0){Using=new HandleArraySize();Using->Size+=1;}
        HandleArray(HandleArray&);
        virtual ~HandleArray();
        operator bool(){return Using;}
};

template <class T>
        void HandleArray<T>::Unused()
{
    if(Using)
    {
        if(Using->Size<=1)
        {
            Handle<HandleList> Tem;
            for(Tem=Begin;Tem;)
            {
                Tem->This.Unused();
                Tem=Tem->Next;
            }
        }else{
            Using->Size-=1;
        }
    }
    Using.Unused();
    Begin.Unused();
    TheEnd.Unused();
}

template <class T>
        void HandleArray<T>::operator=(HandleArray<T>& H)
{
    Unused();
    if(H)
    {
        Using=H.Using;
        if(Using)
        {
            Using->Size+=1;
        }
        Begin=H.Begin;
        TheEnd=H.TheEnd;
        Size=H.Size;
    }
}

template <class T>
        Handle<T> HandleArray<T>::Front()
{
    Handle<T> Tem;
    if(Begin)
    {
        Tem=Begin->This;
        Begin=Begin->Next;
        Size-=1;
    }else{
        if(TheEnd)
        {
            Size-=1;
            Tem=TheEnd->This;
            TheEnd.Unused();
            Using.Unused();
        }
    }
    return Tem;
}

template <class T>
        Handle<T> HandleArray<T>::End()
{
    Handle<T> Tem;
    if(TheEnd)
    {
        Tem=TheEnd->This;
        TheEnd=TheEnd->Last;
        Size-=1;
    }else{
        if(Begin)
        {
            Size-=1;
            Tem=Begin->This;
            Begin.Unused();
            Using.Unused();
        }
    }
    return Tem;
}

template <class T>
        void HandleArray<T>::AddEnd(Handle<T> C)
{
    Handle<HandleList> Tem=new HandleList(C);
    Size+=1;
    if(Begin)
    {
        if(TheEnd)
        {
            TheEnd->Next=Tem;
            Tem->Last=TheEnd;
            TheEnd=Tem;
        }else{
            TheEnd=Tem;
        }
    }else{
        AddFront(C);
    }
}

template <class T>
        void HandleArray<T>::AddFront(Handle<T> C)
{
    Handle<HandleList> Tem=new HandleList(C);
    Size+=1;
    if(Begin)
    {
        Begin->Last=Tem;
        Tem->Next=Begin;
        Begin=Tem;
    }else{
        Begin=Tem;
    }
}


template <class T>
        HandleArray<T>::HandleArray(HandleArray &H)
{
    if(H)
    {
        Using=H.Using;
        if(Using)
        {
            Using->Size+=1;
        }
        Begin=H.Begin;
        TheEnd=H.TheEnd;
        Size=H.Size;
    }
}

template <class T>
        HandleArray<T>::~HandleArray()
{
    if(Using)
    {
        if(Using->Size==1)
        {
            Handle<HandleList> Tem;
            for(Tem=Begin;Tem;)
            {
                Tem=Tem->Next;
            }
        }else{
            Using->Size-=1;
        }
    }
    Using.Unused();
    Begin.Unused();
    TheEnd.Unused();
}

template <class T>
        template <class G>
        bool Handle<T>::operator !=(G* C)
{
    if(*this)
    {
        T* Tem=dynamic_cast<T*>(C);
        if(Data!=Tem)
            return true;
    }
    return false;
}
template <class T>
        template <class G>
        bool Handle<T>::operator !=(Handle<G>& C)
{
    if(*this)
    {
        if(C)
        {
            T* Tem=dynamic_cast<T*>(C.Data);
            if(Data!=Tem)
                return true;
        }
    }
    return false;
}
template <class T>
        template<class G>
bool Handle<T>::operator ==(G *C)
{
    if(Used)
    {
        if(Data==dynamic_cast<T*>(C))
            return true;
    }
}

template <class P>
        bool Handle<P>::operator == (Handle<P>& F)
{
    if(*this)
    {
        if(F)
        {
            if(Data==F.Data)
                return true;
        }
    }
    return false;
}
template <class T>
        template <class G>
        void Handle<T>::operator =(Handle<G>& D)
                                  {
    this->Unused();
    if(D)
    {
        T* P=dynamic_cast<T*>(D.Data);
        if(P)
        {
            *this=P;
        }
    }
}
template <class T>
        template <class G>
        Handle<T>::operator Handle<G>()
{
    Handle<G> Tem;
    if(*this)
    {
        G* P=dynamic_cast<G*>(Data);
        if(P)
        {
            Tem=P;
        }
    }
    return Tem;
}
template<class T>
void Handle<T>::operator =(T* L)
{
    Unused();
    if(L)
    {
        Used=true;
        Life=L->HandleSeed::Life;
        L->HandleSeed::Using+=1;
        Data=L;
    }
}
template<class T>
void Handle<T>::operator =(Handle<T>& H)
                          {
    if(this!=&H)
    {
        if(Used)
        {
            Data->HandleSeed::Using-=1;
            if(Data->HandleSeed::Using==0)
            {
                //error<<"É¾³ý¾ä±ú"<<endl;
                delete Data;
                //error<<"Íê³ÉÉ¾³ý"<<endl;
            }
            Used=false;
        }
        if(H)
        {
            Used=H.Used;
            Data=H.Data;
            Life=H.Life;
            if(H.Used)
            {
                Data->HandleSeed::Using+=1;
            }
        }
    }
}
template<class T>
Handle<T>::Handle(const Handle &H)
{
    Used=H.Used;
    Data=H.Data;
    Life=H.Life;
    if(H.Used)
    {
        H.Data->HandleSeed::Using+=1;
    }
}
template<class T>
Handle<T>::~Handle()
{
    if(Used)
    {
        Data->HandleSeed::Using-=1;
        if(Data->HandleSeed::Using==0)
        {
            delete Data;
        }
    }
}
template<class T>
Handle<T>::Handle(T *L)
{
    Life=L->HandleSeed::Life;
    L->HandleSeed::Using+=1;
    Data=L;
    Used=true;
}
template<class T>
bool Handle<T>::Exist()
{
    if(!Used)
    {
        return false;
    }else{
        if(Life!=Data->HandleSeed::Life) return false;
        else return Data->CheckExist();
    }
}
template<class T>
Handle<T>::operator bool()
{
    return Exist();
}
template<class T>
void Handle<T>::Rebirth()
{
    if(Exist())
    {
        Data->HandleSeed::Life+=1;
        Life=Data->HandleSeed::Life;
    }
}
template <class T>
        template <class G>
        bool Handle<T>::operator ==(Handle<G>& P)
{
    if(*this)
    {
        if(P)
        {
            if(Data==dynamic_cast<T*>(P.Data))
            {
                return true;
            }
        }
    }
    return false;
}
template <class T>
        void Handle<T>::Unused()
{
    if(Used)
    {
        Data->HandleSeed::Using-=1;
        if(Data->HandleSeed::Using==0)
        {
            delete Data;
        }
        Used=false;
    }
}
#endif // HANDLE_H
