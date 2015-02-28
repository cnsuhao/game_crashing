#ifndef DIY_ZHUANKUAISPACE_H
#define DIY_ZHUANKUAISPACE_H
#include "p.o/boss.h"
#include "p.o/plugin_base.h"
#define Hang 200
#define Lie 800
class Block
{
public:
    XYF L;
    
    float W;
    float H;
    Block(XYF K,float w,float h):L(K),W(w),H(h){}
    void Right(float K){L.X+=K;}
    void Left(float I){L.X-=I;}
    bool Crash(XYF& T,XYF& K);
    void Show();
};
class ZhuanKuaiSpace:public Plugin_Base
{
public:
    Block B;
    char* Tem;
    Boss<ZhuanKuaiSpace*,long> Bo;
    bool Translate(XYF& Temc)
    {
        int I=320-(int)(Temc.Y*320);
        int K=(int)(Temc.X*400)+400;
        if(I>=0&&I<Hang&&K>=0&&K<Lie)
        {
            if(Tem[I*800+K]==1)
            {
                Temc.X=(K-400)/400.0;
                Temc.Y=(320-I)/320.0;
                Tem[I*800+K]=0;
                return true;
            }
        }
        return false;
    }
    void Main(ControlCenter*,long T)
    {
        
        B.Show();
        glColor3f(1.0,0.0,1.0);
        glBegin(GL_POINTS);
        for(int i=0;i<Hang;++i)
        {
            for(int k=0;k<Lie;++k)
            {
                if(Tem[i*800+k]==1)
                {
                    glVertex2f((k-400)/400.0,(320-i)/320.0);    
                }
            }
        }
        glEnd();
        Bo.Main(this,T);
    }
    void Accessorial(ControlCenter*,long);
    ZhuanKuaiSpace():B(XYF(0.0,-0.9),0.2,0.1),Plugin_Base("ZHUANKUAI")
    {
        Tem=new char[Hang*Lie];
        for(int i=0;i<Hang*Lie;++i)
        {
            Tem[i]=1;
        }
    }
    Boss_StaffActive<ZhuanKuaiSpace*,long>* StaffActive(){return Bo.StaffActive();}
};
void ZhuanKuaiSpace::Accessorial(ControlCenter*,long T)
{
    Bo.Accessorial(this,T);
    
    while(Handle<Information> Ter=GetInformation())
    if(Ter->IsMouseMotion())
    {
        B.L.X=Ter->Data1.f;
    }
}
void Block::Show()
{
    glColor3f(1.0,0.5,0.8);
    glBegin(GL_QUADS);
    glVertex(L.X-W,L.Y);
    glVertex(L.X-W,L.Y-H);
    glVertex(L.X+W,L.Y-H);
    glVertex(L.X+W,L.Y);
    glEnd();
}
bool Block::Crash(XYF& T,XYF& K)
{
    if(K.X-L.X<W&&K.X-L.X>-W&&K.Y<L.Y)
    {
        K.Y=L.Y;
        T.Y=-T.Y;
        return true;
    }else{
        return false;
    }
}
#endif
