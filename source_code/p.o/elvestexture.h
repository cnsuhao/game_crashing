#ifndef DIY_ELVESTEXTURE_H
#define DIY_ELVESTEXTURE_H
#include "picture.h"
class ElveTexture:public Picture
{
public:
    int Ha;
    int Li;
    void Show(float X,float Y,int H,int L,float SizeX=0.1,float SizeY=0.15);
    void Show(XYF Tem, int H, int L,float SizeX=0.1,float SizeY=0.15){return Show(Tem.X,Tem.Y,H,L,SizeX,SizeY);}
    inline void ShowXMiddle(float X,float Y,int H,int L,float SizeX=0.1,float SizeY=0.15){Show(X-SizeX*0.5,Y,H,L,SizeX,SizeY);}
    inline void ShowXMiddle(XYF Tem, int H, int L,float SizeX=0.1,float SizeY=0.15){return ShowXMiddle(Tem.X,Tem.Y,H,L,SizeX,SizeY);}
    inline void ShowMiddle(float X,float Y,int H,int L,float SizeX=0.1,float SizeY=0.15){Show(X-SizeX/2.0,Y+SizeY/2.0,H,L,SizeX,SizeY);}
    inline void ShowMiddle(XYF Tem, int H, int L,float SizeX=0.1,float SizeY=0.15){return ShowMiddle(Tem.X,Tem.Y,H,L,SizeX,SizeY);}
    void Load(std::string,int,int,float);
};

void ElveTexture::Load(std::string File, int h, int l,float TM=1.0)
{
    Picture::Load(File,TM);
    Ha=h;
    Li=l;
    //error<<Ha<<" "<<Li<<endl;
}

void ElveTexture::Show(float X, float Y, int h, int l, float SizeX,float SizeY)
{
    bool Alpha=false;
    Alpha=glIsEnabled(GL_ALPHA_TEST);
    glAlphaFunc(GL_GEQUAL, 0.5f);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,Point);
    glColor4f(1.0,1.0,1.0,1.0);
    //error<<h<<" "<<l<<endl;
    glBegin(GL_QUADS);
        glTexCoord2f(static_cast<float>(l-1)/Li,static_cast<float>(h-1)/Ha);     glVertex2f(X,Y);
        glTexCoord2f(static_cast<float>(l-1)/Li,static_cast<float>(h)/Ha);       glVertex2f(X,Y-SizeY);
        glTexCoord2f(static_cast<float>(l)/Li,static_cast<float>(h)/Ha);         glVertex2f(X+SizeX,Y-SizeY);
        glTexCoord2f(static_cast<float>(l)/Li,static_cast<float>(h-1)/Ha);       glVertex2f(X+SizeX,Y);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    if(!Alpha)
        glDisable(GL_ALPHA_TEST);
}

#endif // ELVESTEXTURE_H
