/*作者：吞薯条 
  完成于：2012年4月20日 
*/
/*
2012年12月2日修改 
*/ 

#ifndef DIY_PLUGIN_BASE_H
#define DIY_PLUGIN_BASE_H
#include <string>
#include <list>
#include <map>
#include <vector>
#include <set>
#include "information.h"
#include "error.h"
#include "handle.h"
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <GL/glu.h>
#include "glsimplify.h"
#include "staff.h"
class Plugin_Base;
class ControlCenter;
std::map<std::string , int > NaTarSI;//字符串与标识ID的转化 
std::map<int , Handle<Plugin_Base> > NaTarIP;//标识ID与插件指针的转化 
std::map<int , std::string > NaTarIS;
inline int Call(std::string Tem)
{
    if(NaTarSI.count(Tem))
        return NaTarSI[Tem];
    else
        return INFNOTAR;
}
inline Handle<Plugin_Base> Call(int Tem)
{
    if(NaTarIP.count(Tem))
        return NaTarIP[Tem];
    else{
        Handle<Plugin_Base> Ty;
        return Ty;
    }
}
int Thread_1_Function(void* Data);
class Plugin_Base:virtual public Staff<ControlCenter*,long>//插件基类
{
    std::list< Handle<Information> > OutLibrary;//输出信息函数，会自动放到合适的地方
    std::list< Handle<Information> > Library;//所接收到的函数
    protected:
    friend class ControlCenter;
    friend int Thread_1_Function(void* Data);
    int NomberOfInformation;//消息的计数 
    friend int Oclock(void *param);//无用 
    int RegeditID;//标识ID 
    const std::string Name;//表示字符串名 

    void virtual Destory(ControlCenter* Data);//伪析构函数 
    void virtual Main(ControlCenter* Data,long L){}//SHOW函数，所有有关SDL与OPENGL的函数都应该放在这里，可以不重载
    void virtual Accessorial(ControlCenter* Data,long L){}//ANALYZE函数，数据的处理，绘画函数无法响应 可以不重载
    void virtual FlatShow(ControlCenter* Data){}//3D-2D函数，3D投影模型时适用，并且只支持glVertex2f()和glVertex(XYF)，否则显示效果错乱
    void virtual BlendShow(ControlCenter* Data){}
    bool RefuseINFALL;//从CONTROLCENTER函数传来的消息类接收否？
    void GetLib(Handle<Information>& Temp);//将传递消息列表中的消息压入接收信息列表 
    bool PushOutLibrary(Handle<Information> &K);
    void Destory(){HandleSeed::Destory();}
    int InformationSize;
    public: 
        bool ReceiveInformation(){return true;}
        bool ReceiceEventInformation(){return RefuseINFALL;}
        Plugin_Base(std::string name);
        Plugin_Base(std::string name,bool choice);//第二个参数是选择是否接收CONTROLCENTER发来的消息类 
        void Useless(void);//如果不使用消息类，请调用，否则运行中途会死机！ 
        void ToAspect(unsigned int Te);//改变CONTROLCENTER中的ASPECT 
        void Orthogonality(void);//改成2维视觉模型 
        void Perspective(void);//改成3D投影视觉模型 
        void UnableExit(void);//无用 
        void Killmyself(void);//自杀函数 
        void Out(Handle<Information>& Tem);//将消息压入消息传递列表 
        void Exit(void);//发出退出信号 
        void LockMouse(void);//固定鼠标 
        void UnlockMouse(void);//接触固定 
        bool InformationEmpty(){return Library.empty();}
        Handle<Information> NewInformation(int Target,int Category1,int Category2,int Category3,int Category4);//产生新消息 
        Handle<Information> GetInformation(void);//得到列表的第一个函数，如果列表为空则为空消息 
        ~Plugin_Base();

}; 


#include "plugin_base.cpp"
#endif
