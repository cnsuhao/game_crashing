#ifndef DIY_CONTROLCENTER_CPP
#define DIY_CONTROLCENTER_CPP
#include "controlcenter.h"
void ControlCenter::ShootInformation(Handle<Plugin_Base> H)
{
    if(H)
    {
        //error<<"1"<<endl;
        if(H->ReceiveInformation())
        {
            //error<<"2"<<endl;
            for(std::list<Handle<Information> >::iterator Po=DeliverLibrary.begin();Po!=DeliverLibrary.end();++Po)
            {
                //error<<"3"<<endl;
                if((*Po)->Target==INFALL)
                {
                    H->GetLib(*Po);
                    //error<<"4"<<endl;
                }else if(H->RegeditID==(*Po)->Target)
                {
                    H->GetLib(*Po);
                    DeliverLibrary.erase(Po--);
                }
            }
        }
    }
}


void ControlCenter::GetInformation(Handle<Plugin_Base> Temc)
{
    if(Temc)
    {
        Handle<Information> Tem;
        while(Temc->PushOutLibrary(Tem))
            DeliverLibrary.push_back(Tem);
    }
}

bool ControlCenter::Get3DMouse(float X,float Y,XYZF& Location)
{
    float M[16];
    float P[16];
    glGetFloatv(GL_PROJECTION_MATRIX,P);
    glGetFloatv(GL_MODELVIEW_MATRIX,M); 
    //未完成 
}

void ControlCenter::Exit(void)
{
    Running=false;
    SDL_WaitThread(Thread1,NULL);
    //while((!AnalyzeReadyToExit)){SDL_Delay(1);}
    //SDL_KillThread(Thread1);
    exit(0);
}
bool ControlCenter::ChangeIntoFlat(XYZF& T1,XYF& T2)
{
        T2.X=-Near*T1.X/T1.Z/NX;
        T2.Y=-Near*T1.Y/T1.Z/NY;
        if(T1.Z<=-Near)
            if((T2.X>=-1.0&&T2.X<=1.0)&&(T2.Y>=-1.0&&T2.Y<=1.0))
                return true;
    return false;
}
bool ControlCenter::SetView(int Mode)
{
    switch(Mode)
    {
        case 1:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D(-1.0,1.0,-1.0,1.0);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            return true;
            break;
        case 2:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-1,1,-1,1,1,-1);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            return true;
            break;
        case 3:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(Angle,static_cast<float>(WindowW)/WindowH,NearSize,FarSize);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            return true;
            break;
    }
    return false;
}
unsigned int ControlCenter::Asp(void)
{
    return Aspect;
}

bool ControlCenter::Init(int Mode=1,int W=640,int H=480)
{
    WindowW=W;
    WindowH=H;
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );//设定GL的初始属性，想使用GL的话必须用这个，其中参数自己百度
    Screen = SDL_SetVideoMode( WindowW, WindowH, 32, SDL_OPENGL); // 同上，设定属性的另一函数，必要。其参数自己百度
    Far=FarSize;
    Near=NearSize;
    NY=Near*tan(Angle*0.0087);
    FY=Far*tan(Angle*0.0087);
    NX=NY*(float)WindowW/WindowH;
    FX=FY*(float)WindowW/WindowH;
    StarTime=SDL_GetTicks();
    bool SomeErrorAndNeedToExit=false;
    if(SomeErrorAndNeedToExit)
    {
        exit(0);
    }
    Thread1=SDL_CreateThread(Thread_1_Function,(void*) this);
    if(!SetView(Mode))
    {
        SetView(1);
    }else ViewMode=Mode;
    atexit(SDL_Quit);
    InitFinish=true;
}





void ControlCenter::Finish(void)
{
    SDL_Delay( DelayForShow );//暂停~~~~
    Calculate+=1;
    if(Calculate>=2000001)
        Calculate=0;
    int Time=SDL_GetTicks()-TimeForShow;
    if(Time>=0&&Time<DelayForShow)
    {
        SDL_Delay(DelayForShow-Time);
        IntervalTimeShow=DelayForShow;
    }else{
        IntervalTimeShow=Time;
    }
}
void ControlCenter::FlatShow(Handle<Plugin_Base> Tem)
{
    if(Tem)
    {
        Tem->FlatShow(this);
    }
}

void ControlCenter::BlendShow(Handle<Plugin_Base> Tem)
{
    if(Tem)
    {
        Tem->BlendShow(this);
    }
}


void ControlCenter::Run(int number=0)
{
    if(Running)
    {
        TimeForShow=SDL_GetTicks();
        MainLibrary.Wait();
        MainLibrary.Lock();
        while(!MainLibrary.empty())
        {
            Handle<Information> Tempp=*MainLibrary.begin();
            MainLibrary.pop_front();
            if(Tempp)
            {
                switch(Tempp->Category1)
                {
                    case INFCONZJ:
                        SetView(2);
                        ViewMode=2;
                        break;
                    case INFCONTS:
                        SetView(3);
                        ViewMode=3;
                        break;
                    case INFUNABLEEXITIMI:
                        ExitImi=false;
                        break;
                    case INFDESTORY:
                        if(NaTarIP.count(Tempp->Resource)>0)
                        {
                            Handle<Plugin_Base> Tem=Call(Tempp->Resource);
                            if(Tem)
                            {
                                AllList.UnEmploy(Tem);
                            }
                        }
                        break;
                    case INFEVENT:
                        if(Tempp->Resource!=INFCONID)
                        {
                            if(Tempp->Category2==INFEXIT)
                            {
                                //error<<"发现"<<endl;
                                Exit();
                            }
                        }
                        break;
                }
            }       
        }
        MainLibrary.UnLock();
        while( SDL_PollEvent( &Event) )
        {
            Handle<Information> Temporary=new Information;
            Temporary->Resource=INFCONID;
            Temporary->Target=INFALL;
            Temporary->Category1=INFEVENT;
            float Temporary2[1];
            switch(Event.type)
            {
                case SDL_QUIT:
                    Temporary->Category2=INFEXIT;
                    if(ExitImi)
                    {
                        //error<<"退出"<<endl;
                        Exit();
                    }
                    break;
                case SDL_KEYDOWN:
                    Temporary->Category2=INFKEY;
                    Temporary->Category3=INFKEYDOWN;
                    Temporary->Data1.uc=Event.key.keysym.sym;
                    //er<<Event.key.keysym.sym<<endl;
                    break;
                case SDL_KEYUP:
                    Temporary->Category2=INFKEY;
                    Temporary->Category3=INFKEYUP;
                    Temporary->Data1.uc=Event.key.keysym.sym;
                    break;
                case SDL_MOUSEMOTION:
                    Temporary->Category2=INFMOUSE;
                    Temporary->Category3=MOUSEMOTION;
                    Temporary->Data1.f=(float)(2*Event.motion.x-(WindowW))/(float)(WindowW);
                    Temporary->Data2.f=-(float)(2*Event.motion.y-(WindowH))/(float)(WindowH);
                    //glReadPixels(Event.motion.x,WindowH-Event.motion.y,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,Temporary2);
                    //Temporary.Data3.f=Temporary2[0];
                    //Temporary.Data3.i=Event.motion.x;
                    //Temporary.Data4.i=Event.motion.y;
                    Temporary->Data3.i=Event.motion.xrel;
                    Temporary->Data4.i=Event.motion.yrel;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    Temporary->Category2=INFMOUSE;
                    Temporary->Category3=MOUSEBUTTONDOWN;
                    Temporary->Category4=Event.button.button;
                    Temporary->Data1.f=(float)(2*Event.button.x-(WindowW))/(float)(WindowW);
                    Temporary->Data2.f=-(float)(2*Event.button.y-(WindowH))/(float)(WindowH);
                    //glReadPixels(Event.button.x,WindowH-Event.button.y,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,Temporary2);
                    //Temporary.Data3.f=Temporary2[0];
                    //Temporary.Data4.i=Event.button.x;
                    //Temporary.Data5.i=Event.button.y;
                    //kk<<"试试"<<Temporary.Data3.f<<endl;
                    //kk<<"鼠标"<<Event.button.x<<" "<<Event.button.y<<endl; 
                    break;
                case SDL_MOUSEBUTTONUP:
                    Temporary->Category2=INFMOUSE;
                    Temporary->Category3=MOUSEBUTTONUP;
                    Temporary->Data1.f=(float)(2*Event.button.x-(WindowW))/(float)(WindowW);
                    Temporary->Data2.f=-(float)(2*Event.button.y-(WindowH))/(float)(WindowH);
                    Temporary->Category4=Event.button.button;
                    //glReadPixels(Event.button.x,WindowH-Event.button.y,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,Temporary2);
                    //Temporary.Data3.f=Temporary2[0];
                    //Temporary.Data4.i=Event.button.x;
                    //Temporary.Data5.i=Event.button.y;
                    break;
                 case SDL_ACTIVEEVENT:
                    if(Event.active.state==2)
                        Active=false;
                    else if(Event.active.state==6)
                        Active=true;
                    //error<<"额外的"<<(int)Event.active.state<<endl;
                 default :
                    //error<<"额外的："<<(int)Event.type<<endl;
                    break;
            }
            DeliverLibrary.Wait();
            DeliverLibrary.Lock();
            DeliverLibrary.push_back(Temporary);
            DeliverLibrary.UnLock();
            //check("  主函数事件",Temporary);
                    
        }
        std::list<Handle<Plugin_Base> >::iterator Poi;
        SDL_GL_SwapBuffers();//强制输出，刷屏。
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        if(Active)
        {
            if(MouseLock)
            {
                SDL_WarpMouse(WindowW/2,WindowH/2);
            }
        }
        try
        {
            AllList.Main(this,this->IntervalTimeShow);
        }catch(RunInitError K)
        {
            std::ofstream Px("allerror.txt");
            Px<<K.Data<<endl;
        }

        bool IsBland=glIsEnabled(GL_BLEND);
        glEnable(GL_BLEND);
        glDepthMask(GL_FALSE);
        AllList.Train(&ControlCenter::BlendShow,this);
        glDepthMask(GL_TRUE);
        if(!IsBland)
            glDisable(GL_BLEND);
            if(ViewMode==3||ViewMode==2)
            {
                /*glPushMatrix();//伪2D偏转，其中Z坐标因为0；
                glLoadIdentity();
                glTranslatef(0.0,0.0,-1.0000001*Near);
                glScalef(NX,NY,1.0);*/
                SetView(1);
                AllList.Train(&ControlCenter::FlatShow,this);
                //glPopMatrix();
                SetView(3);
            }
        //error<<"Show"<<endl;
                //check("  主函数分析",Tem);
    }
}
void ControlCenter::Regedit(Handle<Plugin_Base> Temporary)
{
    if(Temporary)
    {
        if(NaTarSI.count(Temporary->Name)==0)
        {
            RegeditID+=1;
            Temporary->RegeditID=RegeditID;
            NaTarIP.insert(std::make_pair(RegeditID , Temporary));
            NaTarSI.insert(std::make_pair(Temporary->Name , RegeditID));
            NaTarIS.insert(std::make_pair(RegeditID,Temporary->Name  ));
            AllList.Employ(Temporary);
        }
    }
}
ControlCenter::ControlCenter():ThreadReady(false),Running(true),InitFinish(false),ExitImi(true)
{
    RegeditID=INFCONID;
    Aspect=1;
    Active=true;
    DelayForShow=17;
    DelayForAnalyze=5;
    Calculate=0;
    WindowW=1200;
    WindowH=800;
    Angle=60;
    FarSize=5000;
    NearSize=0.01;
    AnalyzeReadyToExit=false;
}
int ControlCenter::Time(int Number)
{
    return SDL_GetTicks()-StarTime-Number;
}
bool ControlCenter::Time(int X1,int X2)
{
    int Time=SDL_GetTicks()-StarTime;
    if((Time>=X1&&Time<=X2)||(Time>=X2&&Time<=X1))    return true;
    else    return false;
}
int Thread_1_Function(void* Data) //对数据的分析 
{
    //error<<"SBSBSBSB"<<endl; 
    ControlCenter* CC = static_cast< ControlCenter* > (Data);
    std::list<Handle<Plugin_Base> >::iterator FunPoi;
    Handle<Information> Tem;
    while(!CC->InitFinish){SDL_Delay(4);}
    if(CC->InitFinish)
    {
        srand(time(NULL));
        while(CC->Running)
        {
            CC->TimeForAnalyze=SDL_GetTicks();
            CC->DeliverLibrary.Wait();
            CC->DeliverLibrary.Lock();
            CC->AllList.Train(&ControlCenter::GetInformation,CC);
            CC->AllList.Train(&ControlCenter::ShootInformation,CC);
            for(std::list<Handle<Information> >::iterator Po=CC->DeliverLibrary.begin();Po!=CC->DeliverLibrary.end();++Po)
            {
                if(*Po)
                {
                    if((*Po)->Resource!=INFCONID&&((*Po)->Target==INFALL||(*Po)->Target==INFCONID))
                    {
                        if((*Po)->Target == INFCONID)
                        {
                            switch((*Po)->Category1)
                            {
                                case INFEVENT:
                                    if((*Po)->Category2==INFEXIT)
                                    {
                                        CC->MainLibrary.Wait();
                                        CC->MainLibrary.Lock();
                                        CC->MainLibrary.push_back((*Po));
                                        CC->MainLibrary.UnLock();
                                    }
                                    break;
                                case INFCONTS:
                                case INFCONZJ:
                                    CC->MainLibrary.Wait();
                                    CC->MainLibrary.Lock();
                                    CC->MainLibrary.push_back((*Po));
                                    CC->MainLibrary.UnLock();
                                    break;
                                case INFMOUSELOCK:
                                    CC->MouseLock=true;
                                    break;
                                case INFMOUSEUNLOCK:
                                    CC->MouseLock=false;
                                    break;
                                case INFDESTORY:
                                    //error<<"调用删除"<<endl;
                                    CC->AllList.UnEmploy(Call((*Po)->Resource));
                                    //error<<"删除完毕"<<endl;
                                    break;
                            }
                        }
                    }
                }
            }
            CC->DeliverLibrary.clear();
            CC->DeliverLibrary.UnLock();
            CC->AllList.Accessorial(CC,CC->IntervalTimeAnalyze);
            SDL_Delay( CC->DelayForAnalyze );
            int Time=SDL_GetTicks()-CC->TimeForAnalyze;
            if(Time>=0&&Time<CC->DelayForAnalyze)
            {
                SDL_Delay(CC->DelayForAnalyze-Time);
                CC->IntervalTimeAnalyze=CC->DelayForAnalyze;
            }else{
                CC->IntervalTimeAnalyze=Time;
            }
        }
    }
    CC->AnalyzeReadyToExit=true;
    return 0;
}
ControlCenterJustForFirstInit::ControlCenterJustForFirstInit()
{
    std::fstream Error("allerror.txt",std::ios::out);
    SDL_ClearError();
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) //SDL初始化失败
    {
        Error<<"This is something wrong!! The SDL can not Init as your wish. Please Check your Developmental Environment ^.^"<<std::endl;
        Error<<"Or may be you can get something from here:"<<std::endl<<SDL_GetError()<<std::endl;
        Error.close();
    }
    Error.close();
    atexit(SDL_Quit);//注册退出函数
    srand(time(NULL));
}

#endif
