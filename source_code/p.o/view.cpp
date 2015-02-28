#ifndef DIY_VIEW_H
#define DIY_VIEW_H
#include "plugin_base.h"
#include "baseclass.h"
#define VIEWLOCATION 125
#define VIEWANGLE 458
#define VIEWUP 789
#define MOVESPEED 0.1
#define MOVESPEEDANGLE 0.01
class View:public Plugin_Base,public Coordinate
{
    float AngleUp;
    float AngleRight;
    std::map<unsigned char , bool > Key;
    public:
        bool OwnKey;//this bool will determine if the section of its own key work.
        void Init(ControlCenter* CC)
        {
            Key.insert(std::make_pair('w',false));
            Key.insert(std::make_pair('s',false));
            Key.insert(std::make_pair('a',false));
            Key.insert(std::make_pair('d',false));
            Key.insert(std::make_pair('q',false));
            Key.insert(std::make_pair('e',false));
            Key.insert(std::make_pair('r',false));
            Key.insert(std::make_pair('f',false));
        }
        void Show(ControlCenter* Data)
        {
            //Z+=0.01;
            glLoadIdentity();
            gluLookAt(Location.X,Location.Y,Location.Z,Front.X+Location.X,Front.Y+Location.Y,Front.Z+Location.Z,Up.X,Up.Y,Up.Z);
            /*glBegin(GL_LINES);
            glColor3f(1.0,0.0,0.0);
            glVertex3f(0.0,0.0,-20.0);
            glVertex3f(0.0,0.0,20.0);
            
            
            glColor3f(0.0,1.0,0.0);
            glVertex3f(-20.0,0.0,0.0);
            glVertex3f(20.0,0.0,0.0);
            
            glColor3f(0.0,0.0,1.0);
            glVertex3f(0.0,-20.0,0.0);
            glVertex3f(0.0,20.0,0.0);
            
            glEnd();*/
        }
        View(bool Right=false):Plugin_Base("View"),OwnKey(Right){}
        void Analyze(ControlCenter* Data)
        {
            while(!Library.empty())
            {
                Handle<Information> Tem=GetInformation();
                bool Reflesh=false;
                if(Tem->Target==RegeditID)
                {
                    switch(Tem->Category1)
                    {
                        case VIEWLOCATION:
                            Location.X=Tem->Data1.f;
                            Location.Y=Tem->Data2.f;
                            Location.Z=Tem->Data3.f;
                            Reflesh=true;
                            break;
                        case VIEWANGLE:
                            AngleUp=Tem->Data1;
                            AngleRight=Tem->Data2;
                            Front.Set(cos(AngleUp)*sin(AngleRight),sin(AngleUp),-cos(AngleUp)*cos(AngleRight));
                            Up.Set(-sin(AngleUp)*sin(AngleRight),cos(AngleUp),sin(AngleUp)*cos(AngleRight));
                            Reflesh=true;
                            break;
                    }
                    if(Reflesh)
                    {
                        Handle<Information> Tey=new Information;
                        Tey->Target=Tem->Resource;
                        Tey->Resource=Tem->Target;
                        Out(Tey);
                    }
                }
                if(OwnKey)
                {
                    if(Tem->Target==INFALL&&Tem->Category1==INFEVENT)
                    {
                        if(Tem->Category2==INFKEY)
                        {
                            if(Tem->Category3==INFKEYDOWN)
                            {
                                if(Key.count(Tem->Data1)>0)
                                {
                                    Key[Tem->Data1]=true;
                                }
                            }else if(Tem->Category3==INFKEYUP)
                            {
                                if(Key.count(Tem->Data1)>0)
                                {
                                    Key[Tem->Data1]=false;
                                }
                            }
                        }
                    }
                }
            }
            if(Key['w'])
            {
                Location=Location+Front.Uint(MOVESPEED);
            }
            if(Key['s'])
            {
                Location=Location-Front.Uint(MOVESPEED);
            }
            if(Key['a'])
            {
                AngleRight-=MOVESPEEDANGLE;
                Front.Set(cos(AngleUp)*sin(AngleRight),sin(AngleUp),-cos(AngleUp)*cos(AngleRight));
            }
            if(Key['d'])
            {
                AngleRight+=MOVESPEEDANGLE;
                Front.Set(cos(AngleUp)*sin(AngleRight),sin(AngleUp),-cos(AngleUp)*cos(AngleRight));
            }
            if(Key['q'])
            {
                Location=Location+(Up&Front).Uint(MOVESPEED);
            }
            if(Key['e'])
            {
                Location=Location-(Up&Front).Uint(MOVESPEED);
            }
            if(Key['r'])
            {
                Location=Location+Up.Uint(MOVESPEED);
            }
            if(Key['f'])
            {
                Location=Location-Up.Uint(MOVESPEED);
            }
        }
        const XYZF* LocationPoint() const {  return &Location;  }
        const float* AngleRightPoint() const {  return &AngleRight;  }
        const float* AngleUpPoint() const { return &AngleUp; }
};
#endif
