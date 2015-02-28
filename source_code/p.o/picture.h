#ifndef DIY_PICTURE_H
#define DIY_PICTURE_H
#include "baseclass.h"
#include "glsimplify.h"
#include <string>
#include "sdlimageinit.h"
/*2月28日更新，改变了初始化方式，删除扣色（如果需要扣色请使用专业软件），优化了读取函数。
 */
class Picture
{
    public:
    int W;
    int H; 
    //bool KillColor;
    std::string Name;
    public:
    unsigned int Point;
    void Load(std::string File , float TM);
    //void Load(std::string File ,unsigned char R, unsigned char G,unsigned char B,float TM);
    void Show(float XS,float YS,float XE,float YE,float R,float B,float G,float TM);
    void StartShow(int Style,float R=1.0,float G=1.0,float B=1.0,float TM=1.0);
    void EndShow();
    void SetPoint(XYF P1,XYF P2){SetPoint(P1.X,P1.Y,P2.X,P2.Y);}
    void SetPoint(float x1,float y1,float x2,float y2);
    inline void Show(XYF S,XYF E,float R=1.0,float B=1.0,float G=1.0,float TM=1.0){Show(S.X,S.Y,E.X,E.Y,R,B,G,TM);}
    void Delete();
    Picture();
    ~Picture();
};
class Picture3D:public Picture//起始坐标，竖直方向，水平方向 
{
    public:
        void Show(XYZF L,XYZF H,XYZF Z,float,float,float,float );//Te是空间起点坐标，Tr是水平平移量，yy是竖直
        void SetPoint(XYF P1,XYZF P2){SetPoint(P1.X,P1.Y,P2);}
        void SetPoint(float X1,float Y1,XYZF P2);
};

void Picture::StartShow(int Style,float R,float B,float G,float TM)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,Point);
    glColor4f(R,B,G,TM);
    glBegin(Style);
}

void Picture::SetPoint(float x1, float y1, float x2, float y2)
{
    glTexCoord2f(x1,y1);     glVertex2f(x2,y2);
}


void Picture::EndShow()
{
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void Picture::Load(std::string File , float TM=1.0)
{
    Name=File;
    if(Point!=0)
    {
        glDeleteTextures(1,&Point);
    }
    SDL_Surface* Picture = IMG_Load(File.c_str());
    if(Picture==NULL)
        throw RunInitError("Your Picture:  "+File+"  isn't exist!\n"+"Or may be you can get something from here: "+SDL_GetError());
    SDL_Surface* TT=SDL_DisplayFormatAlpha(Picture);
    W = Picture->w;
    H = Picture->h;
    glGenTextures(1,&Point);
    //error<<"载入图片"<<Point<<"  "<<File<<endl;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,Point);
    gluBuild2DMipmaps(GL_TEXTURE_2D,4,TT->w,TT->h,GL_BGRA,GL_UNSIGNED_BYTE,TT->pixels);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glDisable(GL_TEXTURE_2D);
    SDL_FreeSurface(Picture);
    SDL_FreeSurface(TT);
}
void Picture::Show(float XS,float YS,float XE,float YE,float R=1.0,float B=1.0,float G=1.0,float TM=1.0)
{
    bool Alpha=false;
    Alpha=glIsEnabled(GL_ALPHA_TEST);
    glAlphaFunc(GL_GEQUAL, 0.5f);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,Point);
    glColor4f(R,B,G,TM);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0,0.0);     glVertex2f(XS,YS);
        glTexCoord2f(0.0,1.0);       glVertex2f(XS,YE);
        glTexCoord2f(1.0,1.0);         glVertex2f(XE,YE);
        glTexCoord2f(1.0,0.0);       glVertex2f(XE,YS);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    if(!Alpha)
        glDisable(GL_ALPHA_TEST);
}
void Picture::Delete()
{
    if(Point!=0)
    {
        //error<<"删除而已"<<Name<<endl;
        glDeleteTextures(1,&Point);
        Point=0;
    }
}
Picture::Picture():Point(0){}
Picture::~Picture()
{
    if(Point!=0)
    {
        glDeleteTextures(1,&Point);
        //error<<"消亡图片"<<Point<<"  "<<Name<<endl;
    }
}

void Picture3D::SetPoint(float X1, float Y1, XYZF P2)
{
    glTexCoord2f(X1,Y1);    glVertex(P2);
}

void Picture3D::Show(XYZF Te,XYZF Tr,XYZF yy,float R=1.0,float B=1.0,float G=1.0,float A=1.0)//Te是空间起点坐标，Tr是水平平移量，yy是竖直 
{
    bool Alpha=false;
    Alpha=glIsEnabled(GL_ALPHA_TEST);
    glAlphaFunc(GL_GEQUAL, 0.5f);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,Point);
    glColor4f(R,B,G,A);
    glBegin(GL_QUADS);
        glNormal(yy&Tr);
        glTexCoord2f(0.0,0.0);     glVertex(Te);
        glTexCoord2f(0.0,1.0);     glVertex(Te+Tr);
        glTexCoord2f(1.0,1.0);     glVertex(Te+Tr+yy);
        glTexCoord2f(1.0,0.0);     glVertex(Te+yy);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    if(Alpha)
        glDisable(GL_ALPHA_TEST);
}
#endif
