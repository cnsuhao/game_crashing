#ifndef DIY_ZHUANKUAI_H
#define DIY_ZHUANKUAI_H
#include "zhuankuaispace.h"
class ZhuanKuai:public Staff<ZhuanKuaiSpace*,long>
{
public:
    bool Move;
    bool Falling;
    XYF L;
    XYF D;
    float Speed;
    ZhuanKuai(XYF Y):Move(false),L(Y),Falling(false){Speed=((rand()%100)+50)/500.0;}
    void Main(ZhuanKuaiSpace*,long);
    void Accessorial(ZhuanKuaiSpace*,long);
};
void ZhuanKuai::Main(ZhuanKuaiSpace* S,long T)
{
    if(!Falling)
        glColor3f(1.0,1.0,1.0);
    else
        glColor3f(0.2,0.2,1.5);
    glBegin(GL_POINTS);
    glVertex(L);
    glEnd();
}
void ZhuanKuai::Accessorial(ZhuanKuaiSpace* S,long T)
{
    if(Move)
    {
        D=D.Uint();
        L=L+Speed*(float)T/1000.0*D;
            if(L.X<-1.0)
            {
                L.X=-1.0;
                if(D.X<0)
                    D.X=-D.X;
            }else if(L.X>1.0)
            {
                L.X=1.0;
                if(D.X>0)
                    D.X=-D.X;
            }
            if(L.Y<=-1.0)
                Destory();
                else if(L.Y>=1.0)
                D.Y=-D.Y;
        if(Falling)
        {
            if(S->B.Crash(D,L))
            {
                Falling=false;
                D.X=((rand()%100)-50)/100.0;
                D.Y=(rand()%100+10)/110.0;
                D=D.Uint();
            }
        }else{
            if(S->Translate(L))
            {
                Handle<ZhuanKuai> Tem=new ZhuanKuai(L);
                Tem->D.X=0.0;
                Tem->Move=true;
                Tem->Falling=true;
                Tem->D.Y=-1.0;
                S->Bo.Employ(Tem);
                D.Y=-D.Y;
            }
            S->B.Crash(D,L);
        }
    }
}
#endif
