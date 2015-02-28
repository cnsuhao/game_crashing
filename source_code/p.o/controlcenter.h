/*作者：吞薯条 */
/*
 *2013年4月15日增加了一些异常处理（主要是运行时的初始化错误），将退出的过程抽象为一个函数，但必须在RUN函数中使用。 
*/
/*
 *增加随机数的功能。。。。。。。。。。。。这个应该不需要专门记录下来吧！？
 */
/*
 *最后修改日期于2013年2月27日
 *修正了3D显示模式下伪2D变换函数。如果需要在2D绘画中呈现3D效果，需要调用ControlCenter 中的SetView(3)，然后再调用SetView(1)恢复。
 *增加了判断窗口活动的函数，这样在窗口非活动的情况下对鼠标的控制将失效。(由于找不到该项的宏定义，所以通过实验找出了其真值，所以SDL版本改变的时候可能需要改变
 *      其位置位于ControlCenter.cpp 中的Run函数中对SDL_ACTIVEEVENT消息的响应)。
 *优化了SDL扩展库的初始化方式。
 */
/*
*最后修改与2013年1月16日 
*更改了加载插件的方式，ready()函数删除 
*现在可随时调用REGEIDT（）来加载插件，并能确保在使用前初始化 
*/
/*
*最后修改与2013年1月13日 
*添加注释 
*加入两个时间变量，INTERVALTIMESHOW INTERVALTIMEANALYZE用来表示每次循环的间隔时间。 
*/
/*
*最后修改与2012年12月2日 
*添加注释 
*加入通过鼠标在屏幕的坐标获得当前鼠标所指向像素的3D坐标GET3DMOUSE，未完成 
*/
/* 
 *最后修改于： 2012年4月12日 
 *关于用法，请阅读位于末尾的详细说明书。
 * 删除了固定时间响应函数 
 */ 
/*   2012年4月20日
     修改了刷新间隔时间的智能判断
     增加了固定时间响应函数。 
*/
/*      2012年11月7日
        增加了3D透视模式下的伪2D显示函数
 */
#ifndef  DIY_CONTROLCENTER_H 
#define  DIY_CONTROLCENTER_H 
#include <ctime>
#include <cstdlib>
#include <vector> 
#include <list>
#include <map>
#include <string>
#include "information.h"//消息传递类  
#include "plugin_base.h"//插件类
#include "boss.h"
class ControlCenterJustForFirstInit
{
    public:
    ControlCenterJustForFirstInit();
}JustForInitAndDoNotUseThis;

class ControlCenter
{
    friend int Thread_1_Function(void* Data);//第二线程函数 
    SDL_Event Event;//SDL的事件体 
    SDL_Thread* Thread1;//线程2 Analyze 
    SDL_Thread* Thread2;//线程3 备用 
    SDL_Surface* Screen;//SDL的窗口 
    Boss<ControlCenter*,long> AllList;
    PublicValue<std::list< Handle<Information> > > MainLibrary; //主函数的消息列表
    PublicValue<std::list< Handle<Information> > > DeliverLibrary;   //各插件和主函数所需传递的信息列表
    int ViewMode;//主函数的视觉模型    1为2D，2为3D正交，3为3D透视 
    unsigned int Aspect;//插件共用，用于插件间快速交流 
    bool InitFinish;//标记是否已初始化 
    int TimeForShow,TimeForAnalyze;//Show函数 和Analyze函数所需停留时间 （ms） 
    int DelayForShow,DelayForAnalyze;//停滞时间， 保证不同插件个数停留时间大致相等（MS） 
    int RegeditID;//该类专属的ID 
    int WindowW,WindowH;//窗口的高度宽度（像素） 
    int Calculate;//显示循环次数计数 
    int StarTime;//除初始化外的正式运行时间 
    bool MouseLock;//标记鼠标是否固定在屏幕中心 
    bool MouseLockMode;//标记鼠标是否隐藏 
    bool ThreadReady;//第二线程运行状况标记 
    bool ExitImi;//标记是否在点掉窗口的右上角就退出 
    bool AnalyzeReadyToExit;//第二线程退出准备完成 
    bool Get3DMouse(float X,float Y,XYZF& Location); //鼠标3D位置获得函数 
    public:
        bool Active;//当为true时表示该窗口当前有效
        long IntervalTimeShow;//间隔时间
        long IntervalTimeAnalyze;//间隔时间
        bool Running;//标记程序是否退出 
        float FarSize,Angle,NearSize;//如果是3D视觉模型，则表示视景体最远距离，Y-Z平面视觉角度，视景体最近距离 
        float Far,Near,FX,FY,NX,NY;//3D-2D伪变换用 
        bool SetView(int Mode); //改变视觉模型 
        unsigned int Asp(void);//返回当前ASPECT 
        int WindowX(){return WindowW;}//=。= 
        int WindowY(){return WindowH;}//=。= 
        bool Time(int X1,int X2);//判断是否在此段时间之内 
        bool Init(int Mode,int W,int H);//初始化 
        void Finish(void);//每播放完一次的收尾工作 
        void Run(int number);//主函数 
        void Regedit(Handle<Plugin_Base > Temporary);//加载插件
        ControlCenter();
        bool ChangeIntoFlat(XYZF&,XYF&);//3D坐标转2D坐标，如果该2D坐标在视景体内，返回TRUE 
        int Time(int Number);//当前运行时间与NUMBER之差 
        void Exit(void);
        void FlatShow(Handle<Plugin_Base >);
        void BlendShow(Handle<Plugin_Base>);
        void GetInformation(Handle<Plugin_Base >);
        void ShootInformation(Handle<Plugin_Base>);
        Boss_StaffActive<ControlCenter*,long>* StaffActive(){return AllList.StaffActive();}
        //static void InitFunction(void (*)(void));
};
//void ControlCenter::InitFunction(void (*)(void)=NULL){}//用以在某种情况下对全局都有影响的初始化
int Thread_1_Function(void* Data); //消息传递 
//int Oclock(void *param);
#include "controlcenter.cpp"
#endif
