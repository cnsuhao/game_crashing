#ifndef DIY_PLUGIN_BASE_APP_CPP
#define DIY_PLUGIN_BASE_APP_CPP
#include "plugin_base.h"
void Plugin_Base::Destory(ControlCenter* Data){}
bool Plugin_Base::PushOutLibrary(Handle<Information> &K)
{
    K.Unused();
    if(OutLibrary.empty())
    {
        return false;
    }else{
        K=*OutLibrary.begin();
        OutLibrary.pop_front();
        return true;
    }
}

/*void Plugin_Base::Init(ControlCenter* Data,long*)
{
    try
    {
        Init(Data);
    }catch(RunInitError C)
    {
        throw RunInitError(C+"\n    ---This Error Locations at the Son Class Of The \"Plugin_Base\" "+Name);
    }
}*/

/*bool Plugin_Base::ShootLib(Handle<Information>& Temp)
{
    if(Temp)
    {
        if(NaTarIP.count(Temp->Target))
        {
            if((NaTarIP[Temp->Target])->ReceiveInformation())
                (NaTarIP[Temp->Target])->Library.push_back(Temp);
            return true;
        }
    }
    return false;
}*/
Plugin_Base::~Plugin_Base()
{
    //error<<"Plugin"<<" "<<Name<<endl;
}
Plugin_Base::Plugin_Base(std::string name):Name(name),RefuseINFALL(false),InformationSize(0)
{
    RegeditID=INFNOID;
}

Plugin_Base::Plugin_Base(std::string name,bool choice):Name(name),RefuseINFALL(choice),InformationSize(0)
{
    RegeditID=INFNOID;
}

void Plugin_Base::GetLib(Handle<Information>& Temp)
{
    if(InformationSize>50)
    {
        //error<<Library.size();
        //error<<"超过数量"<<endl;
        Library.pop_front();
        Library.push_back(Temp);
    }else{
        InformationSize+=1;
        Library.push_back(Temp);
    }
}

void Plugin_Base::Orthogonality(void)
{
    Handle<Information> Tem=new Information;
    Tem->Resource=RegeditID;
    Tem->Target=INFCONID;
    Tem->Category1=INFCONZJ;
    OutLibrary.push_back(Tem);
}

void Plugin_Base::UnableExit(void)
{
    Handle<Information> Tem=new Information;
    Tem->Resource=RegeditID;
    Tem->Target=INFCONID;
    Tem->Category1=INFUNABLEEXITIMI;
    OutLibrary.push_back(Tem);
}

void Plugin_Base::Perspective(void)
{
    Handle<Information> Tem=new Information;
    Tem->Resource=RegeditID;
    Tem->Target=INFCONID;
    Tem->Category1=INFCONTS;
    OutLibrary.push_back(Tem);
}

void Plugin_Base::Out(Handle<Information>& Tem)
{
    OutLibrary.push_back(Tem);
}
void Plugin_Base::Killmyself(void)
{
    Handle<Information> Tem=new Information;
    Tem->Target=INFCONID;
    Tem->Resource=RegeditID;
    Tem->Category1=INFDESTORY;
    Out(Tem);
    //error<<"want to kill my seflf"<<endl;
}
/*void Plugin_Base::Init(ControlCenter* Data)
{
}*/
Handle<Information> Plugin_Base::NewInformation(int Target,int Category1=INFNULL,int Category2=INFNULL,int Category3=INFNULL,int Category4=INFNULL)
{
    Handle<Information> Tem=new Information;
    Tem->Resource=RegeditID;
    Tem->Target=Target;
    Tem->Category1=Category1;
    Tem->Category2=Category2;
    Tem->Category3=Category3;
    Tem->Category4=Category4;
    return Tem;
}
            
Handle<Information> Plugin_Base::GetInformation(void)
{
    Handle<Information> Tem;
    if(Library.empty())
    {
        return Tem;
    }else{

        Tem=*Library.begin();
        Library.pop_front();
        InformationSize-=1;
        return Tem;
    }
}
void Plugin_Base::Useless(void)
{
    Library.clear();
    InformationSize=0;
}
void Plugin_Base::Exit(void)
{
    //error<<"发出"<<endl;
    Handle<Information> Tem=NewInformation(INFCONID,INFEVENT,INFEXIT);
    Out(Tem);
}
void Plugin_Base::LockMouse(void)
{
    Handle<Information> Tem=NewInformation(INFCONID,INFMOUSELOCK);
    Out(Tem);
}
void Plugin_Base::UnlockMouse(void)
{
    Handle<Information> Tem=NewInformation(INFCONID,INFMOUSEUNLOCK);
    Out(Tem);
}
#endif

