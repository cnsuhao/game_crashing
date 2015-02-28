#ifndef DIY_INITER_H
#define DIY_INITER_H
#include <list>
#include <set>
#include <map>
#include <string>
#include "error.h"
#define Ini_All 0x11
#define Ini_Sho 0x10
#define Ini_Ana 0x01
#define Ini_Nul 0x00
class InitFunctionFactor
{
public:
    void (*InitFunction)(void);
    int UsingSize;
    void (*UnInitFunction)(void);
    bool Using(){if(UsingSize<=0)return true;else return false;}
    void Increase(){UsingSize+=1;}
    void Decrease(){UsingSize-=1;}
    void Init(){if(Using()){(*InitFunction)();}Increase();}
    void UnInit(){Decrease();if(!Using())(*UnInitFunction)();}
    InitFunctionFactor(void (*I)(void),void (*U)(void)):InitFunction(I),UnInitFunction(U){}
}; 


namespace IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit
{
    std::map<int,void (*)(void)> InitList_S;
    std::map<std::string,int> MakeItFasterWhenFinding;
    std::map<int,std::string> ToCallItsTureName;
    std::map<int,int> UsingTime; 
    std::set<int> Finish_S;
    std::set<std::string> All;
    std::set<int> NeedTo_S;
    std::map<int,void (*)(void)> InitList_A;
    std::set<int> Finish_A;
    std::set<int> NeedTo_A;
    int StarID=1;
}

class InitNote
{
public:
    int Style;
    int ID;
    std::list<int> Follow;
    InitNote(int S,std::string N,void (*Fun)(void));
    InitNote(std::string N,void (*Fun1)(void),void (*Fun2)(void));
    InitNote(int S, std::string N, void (*Fun)(void), std::string *Pc,int Style){}
    InitNote(std::string N,void (*Fun1)(void),void (*Fun2)(void),std::string *Pc,int Style){}
};

class IniterSeed
{
    public:
        int Style;
        int ID;
        bool CheckInit();
        operator int(){return ID;}
        IniterSeed():Style(Ini_Nul){}
        IniterSeed(InitNote& I):Style(I.Style),ID(I.ID){}
};

class Initer
{
std::set<int> IDList;
public:
    void Init();
    //Initer(int* A,int L){};
    Initer(){};
    void Get(int);
    void Get(std::string);
    void InitForShow();
    void InitForAnalyze();
};

void Initer::Get(std::string N)
{
    if(IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::MakeItFasterWhenFinding.count(N)==1)
    {
        int Tem=IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::MakeItFasterWhenFinding[N];
        if(IDList.count(Tem)==0)
            IDList.insert(Tem);
    }
}

bool IniterSeed::CheckInit()
{
    if(Style==Ini_All)
    {
        if(IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::Finish_A.count(ID)==1&&IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::Finish_S.count(ID)==1)
            return true;
    }else if(Style==Ini_Sho){
        if(IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::Finish_S.count(ID)==1)
            return true;
    }else if(Style==Ini_Ana){
        if(IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::Finish_A.count(ID)==1)
            return true;
    }
    return false;
}

void Initer::Get(int T)
{
    if(IDList.count(T)==0)
    {
        IDList.insert(T);
    }
}

void Initer::InitForAnalyze()
{
    for(std::set<int>::iterator Po=IDList.begin();Po!=IDList.end();++Po)
    {
        if(IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::NeedTo_A.count(*Po)!=0)
        {
            IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::UsingTime[*Po]+=1;
            (*(IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::InitList_A[*Po]))();
            IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::NeedTo_A.erase(*Po);
            IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::Finish_A.insert(*Po);
        }
    }
}

void Initer::InitForShow()
{
    //error<<"尝试开始画"<<endl;
    for(std::set<int>::iterator Po=IDList.begin();Po!=IDList.end();++Po)
    {
        if(IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::NeedTo_S.count(*Po)==1)
        {
            //error<<"有个东西"<<endl;
            IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::UsingTime[*Po]+=1;
            (*(IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::InitList_S[*Po]))();
            IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::NeedTo_S.erase(*Po);
            IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::Finish_S.insert(*Po);
        }
    }
}

InitNote::InitNote(int S, std::string N, void (*Fun)(void))
{
    ID=IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::StarID;
    IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::StarID+=1;
    Style=S;
    if(IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::All.count(N)==0)
    {
        if(Style==Ini_Sho)
        {
            IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::InitList_S.insert(std::make_pair(ID,Fun));
            IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::NeedTo_S.insert(ID);
        }else if(Style==Ini_Ana){
            IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::InitList_A.insert(std::make_pair(ID,Fun));
            IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::NeedTo_A.insert(ID);
        }else{
            //throw PreRun(std::string("Init Style Wrong, The Id of The IniterSeed is: ")+N);
        }
        IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::All.insert(N);
        IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::MakeItFasterWhenFinding.insert(make_pair(N,ID));
    }else{
       // throw PreRun(std::string("The ID:")+N+std::string("Haved Allready Exist!"));
    }
}

InitNote::InitNote(std::string N, void (*Fun1)(void), void (*Fun2)(void))
{
    ID=IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::StarID;
    IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::StarID+=1;
    Style=Ini_All;
    if(IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::All.count(N)==0)
    {
        IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::InitList_S.insert(std::make_pair(ID,Fun1));
        IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::NeedTo_S.insert(ID);
        IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::InitList_A.insert(std::make_pair(ID,Fun2));
        IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::NeedTo_A.insert(ID);
        IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::All.insert(N);
        IJustWandToSetItSoLongThatMakeTheUserCannotRememberItForInit::MakeItFasterWhenFinding.insert(make_pair(N,ID));
    }else{
        //throw PreRun(std::string("The ID:")+N+std::string("Haved Allready Exist!"));
    }
}

#endif // INITER_H
