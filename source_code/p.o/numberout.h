#ifndef DIY_NUMBEROUT_H
#define DIY_NUMBEROUT_H
#include <stdio.h>
#include <sstream>
#include <string>
#include <list>
#include <map>
#include "../p.o/sgprint.h"
#include "stdio.h"
#include "../p.o/picture.h"
class NumberOut
{
    Sentence3D Perfix;
    std::string St;
    static std::map<char,unsigned int> NumberModel;
    static unsigned int ModelPoint[12];
    static int PointNumber;
    public:
        bool Inable;
        void Set(const std::string& rr);
        void Off(void);
        void In(void);
        template<class T>
        XYZF Show(T nu,float X,float Y,float Size);
        NumberOut();
        ~NumberOut()
        {
            PointNumber-=1;
            if(PointNumber==0)
            {
                NumberModel.clear();
                for(int i=0;i<12;++i)
                {
                    glDeleteTextures(1,&(ModelPoint[i]));
                    ModelPoint[i]=0;
                }
            }
        }
};
void NumberOut::Set(const std::string& rr)
{
    Perfix.Add(rr);
}
std::map<char,unsigned int> NumberOut::NumberModel;
unsigned int NumberOut::ModelPoint[12];
int NumberOut::PointNumber=0;

void NumberOut::Off(void)
{
    Inable=false;
}
void NumberOut::In(void)
{
    Inable=true;
}
template <class Txxx>
XYZF NumberOut::Show(Txxx num,const float X,const float Y,const float Size2=1.0)
{
    if(NumberModel.empty())
    {
        //error<<"初始化~"<<endl;
        char Txt[]={'0','1','2','3','4','5','6','7','8','9','-','.'};
        for(int i=0;i<12;++i)
        {
            SDL_Surface *Texture;
            SDL_Surface *Back;
            int w;
            int h;
            float W;
            float H;
            unsigned int Point;
            std::string Tu;
            Tu=Tu+Txt[i];
            Texture = TTF_RenderUTF8_Blended( Perfix.Font() , Tu.c_str() , (SDL_Color){255,255,255} );
            w = static_cast<int>(pow(2,ceil(log(Texture->w)/log(2)))+0.5 );
            h = static_cast<int>(pow(2,ceil(log(Texture->h)/log(2)))+0.5 );
            W=static_cast<float>(Texture->w)/w;
            H=static_cast<float>(Texture->h)/h;
            Back=SDL_CreateRGBSurface(0,w,h,32,0x00ff0000,0x0000ff00,0x000000ff,0xff000000);
            SDL_BlitSurface(Texture,0,Back,0);
            void* PointForTexture= operator new[](sizeof(unsigned long*) * w*h*4);
            unsigned char* Poi= static_cast<unsigned char*> (PointForTexture);
            unsigned char* Poi2=static_cast<unsigned char*> (Back->pixels);
            for(int hh=0;hh< static_cast<int>(H*h*4);++hh)
            {
                for(int ww=0;ww< static_cast<int>(W*w);++ww)
                {
                    Poi[hh*w+ww*4]=Poi2[hh*w+ww*4];
                    Poi[hh*w+ww*4+1]=Poi2[hh*w+ww*4+1];
                    Poi[hh*w+ww*4+2]=Poi2[hh*w+ww*4+2];
                    if(Poi[hh*w+ww*4]!=0&&Poi[hh*w+ww*4+1]!=0&&Poi[hh*w+ww*4+2]!=0)
                    {
                        Poi[hh*w+ww*4+3]=255;
                    }else{
                        Poi[hh*w+ww*4+3]=0;
                    }
                }
            } 
            glGenTextures(1,&Point);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,Point);
            glTexImage2D(GL_TEXTURE_2D,0,4,w,h,0,GL_BGRA,GL_UNSIGNED_BYTE,PointForTexture);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glDisable(GL_TEXTURE_2D);
            SDL_FreeSurface(Texture);
            SDL_FreeSurface(Back);
            operator delete[] (PointForTexture);
            
            ModelPoint[i]=glGenLists(1);
            glNewList(ModelPoint[i],GL_COMPILE);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,Point);
            glColor4f(1.0,1.0,1.0,1.0);
            glBegin(GL_QUADS);
                glTexCoord2f(W,H);        glVertex2f(0.4,-1.0);  
                glTexCoord2f(W,0.0);      glVertex2f(0.4,0.0);                  
                glTexCoord2f(0.0,0.0);     glVertex2f(0.0,0.0);
                glTexCoord2f(0.0,H);       glVertex2f(0.0,-1.0);
            glEnd();
            glDisable(GL_TEXTURE_2D);
            glEndList();
            NumberModel.insert(std::make_pair(Txt[i],ModelPoint[i]));
        }
    }
    if(Inable)
    {
        //error<<"我来对了~"<<endl;
        int I=0;
        XYZF T=Perfix.Show(XYZF(X,Y,0.0),XYZF(0.0,-1.0,0.0),XYZF(0.0,0.0,1.0),1.0f,1.0f,1.0f,Size2);
        glPushMatrix();
        glTranslatef(T.X,T.Y,0.0);
        glColor4f(1.0,1.0,1.0,1.0);
        bool Shendu=glIsEnabled(GL_ALPHA_TEST);
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GEQUAL, 0.9f);
        glScalef(Size2,Size2,1.0);
        std::stringstream ST;
        //ST.clear();
        ST<<num;
        ST>>St;
        //error<<St<<endl;
        for(std::string::iterator Po=St.begin();Po!=St.end();++Po)
        {
            if(NumberModel.count(*Po)>0)
            {
                glCallList(NumberModel[*Po]);
                glTranslatef(0.4,0.0,0.0);
            }
            ++I;
        }
        if(!Shendu) glDisable(GL_ALPHA_TEST);
        glPopMatrix();
        return T+XYZF(I*Size2,0.0,0.0);
                                                                                                                                                      
    }
    return XYZF(0.0,0.0,0.0);
}
NumberOut::NumberOut()
{
    Inable=true;
    PointNumber+=1;
}


#endif
