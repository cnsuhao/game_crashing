//最后修改于2月28，修改了初始化方式，优化了读取显示函数 
//最后修改于2013-1-15，重整了排版，优化了读取函数，绘图函数由深度测试改为混合（在函数外对字体使用的所有混合将失效） 
#ifndef  DIY_SGPRINT_H 
#define  DIY_SGPRINT_H 
#include <string>
#include <fstream>
#include "language.h"
#include "baseclass.h"
#include "information.h"
#include "sdlttfinit.h"
class Sentence
{
    protected:
        unsigned int Point;
        std::string Data;
        int W;
        int H;
        //static bool PReadyToUse;
    public:
        void Add(std::string, TTF_Font * =PO_FONT::SDL_TTF_FONT);
        XYF Show( float X ,float Y , float R=1.0,float G=1.0,float B=1.0,float Size=0.2);
        inline XYF Show( XYF Tem,float R=1.0,float G=1.0,float B=1.0,float Size=0.2);
        inline XYF ShowXMiddle(float X,float Y,float R=1.0,float G=1.0,float B=1.0,float Size=0.2);
        inline XYF ShowXMiddle(XYF Tem,float R=1.0,float G=1.0,float B=1.0,float Size=0.2);
        long Size(){return Data.size();}
        //TTF_Font* Font(){return font;}
        void Delete();
        Sentence(const Sentence& Tem);
        Sentence();
        ~Sentence();
};
class Sentence3D:public Sentence
{
    public:
        XYZF Show( const XYZF Local , 
                 const XYZF Target2 ,
                   const  XYZF Face ,
                         float R,
                         float G,
                         float B,
                    float Size);//Target是指向下 ;
};
//bool Sentence::PReadyToUse=false;
//TTF_Font* Sentence::font=NULL;

XYF Sentence::ShowXMiddle(float X, float Y, float R, float G, float B, float Size)
{
    //error<<static_cast<float>(Data.size())*0.<<endl;
    return Show(X-Data.size()*0.2*Size,Y,R,G,B,Size);
}

XYF Sentence::ShowXMiddle(XYF T, float R, float G, float B, float Size)
{
    return ShowXMiddle(T.X,T.Y,R,G,B,Size);
}
void Sentence::Add(std::string data , TTF_Font* Font)
{
    if(Data!=data)
    {
        if(Font==PO_FONT::SDL_TTF_FONT)
        {
            if(!PO_FONT::FontReady)
                throw RunInitError("The default Font is not ready! Please use \"PO_FONT::Set(FileAddress)\" To Init. ");
        }
        Data=data;
        if(Point!=0)
            Delete();
        SDL_Surface *Texture;
        Texture = TTF_RenderUTF8_Blended(Font,Translate(Data).c_str(),(SDL_Color){255,255,255} );
        //error<<"字符个数"<<Translate(Data).size()<<endl;
        //if(Texture==NULL)
            //throw RunInitError("Your sentence:  "+data+"  can't not open.\n"+"Or may be you can get something from here: "+SDL_GetError());
        W = Texture->w;
        H = Texture->h;
        glGenTextures(1,&Point);
        //error<<"字体:"<<Point<<"  "<<Data<<endl;
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,Point);
        gluBuild2DMipmaps(GL_TEXTURE_2D,4,Texture->w,Texture->h,GL_BGRA,GL_UNSIGNED_BYTE,Texture->pixels);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glDisable(GL_TEXTURE_2D);
        SDL_FreeSurface(Texture);
    }
}
XYF Sentence::Show( float X ,float Y , float R,float G,float B,float Size)
{
    bool Shendu=glIsEnabled(GL_BLEND);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,Point);
    glColor4f(R,G,B,1.0);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0,1.0);        glVertex2f(X+Data.size()*Size*0.4,Y-Size);
        glTexCoord2f(1.0,0.0);      glVertex2f(X+Data.size()*Size*0.4,Y);
        glTexCoord2f(0.0,0.0);     glVertex2f(X,Y);
        glTexCoord2f(0.0,1.0);       glVertex2f(X,Y-Size);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    if(!Shendu)
        glDisable(GL_BLEND);
    return XYF(X+Data.size()*Size*0.4,Y);
    return XYF(0.0,0.0);
}
XYF Sentence::Show( XYF Tem,float R,float G,float B,float Size)
{
    return Show(Tem.X,Tem.Y,R,G,B,Size);
}
void Sentence::Delete()
{
    if(Point!=0)
    {
        //error<<"删除而已"<<Data<<endl;
        glDeleteTextures(1,&Point);
        Point=0;
    }
}
Sentence::Sentence(const Sentence& Tem)
{
    Add(Tem.Data);
}
Sentence::Sentence():Point(0)
{
}
Sentence::~Sentence()
{
    if(Point!=0)
    {
        //error<<"释放字体"<<Point<<" "<<Data<<endl;
        glDeleteTextures(1,&Point);
    }
}
XYZF Sentence3D::Show( const XYZF Local , const XYZF Target2 ,const  XYZF Face ,float R=1.0,float G=1.0,float B=1.0,float Size=0.02)//Target是指向下
{
    bool Shendu=glIsEnabled(GL_ALPHA_TEST);
    XYZF Target=Target2;
    XYZF Crosswise=Face&Target;
    Crosswise=Crosswise.Uint(Size*0.4);
    Target=Target.Uint(Size);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GEQUAL, 0.5f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,Point);
    glColor4f(R,G,B,1.0);
    glBegin(GL_QUADS);
        glNormal(Face);
        glTexCoord2f(1.0,1.0);        glVertex(Local+Crosswise*Data.size()+Target);
        glTexCoord2f(1.0,0.0);      glVertex(Local+Crosswise*Data.size());
        glTexCoord2f(0.0,0.0);    glVertex(Local);
        glTexCoord2f(0.0,1.0);      glVertex(Local+Target);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    if(!Shendu)
       glDisable(GL_ALPHA_TEST);
    return XYZF(Local+Crosswise*Data.size());
}
#endif
