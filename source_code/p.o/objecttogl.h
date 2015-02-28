#ifndef DIY_OBJECTTOGL_H
#define DIY_OBJECTTOGL_H
#include <fstream>
#include <string>
#include "../p.o/baseclass.h"
#include "../p.o/picture.h"
#include "../p.o/glsimplify.h"
#include <map>
class Object
{
    public:
    class Face
    {
        public:
            int v;
            int vn;
            int vt;
            Face(int a,int b,int c):v(a),vn(b),vt(c){}
            Face(){}
    };
    bool Ready;
    int NOV;
    int NOVN;
    int NOVT;
    XYZF* V;
    XYZF* Vn;
    XYF* Vt;
    unsigned int TextMode;
    std::map <std::string, Picture* > File;
    std::map <std::string, std::string> Mode;
    public:
        Object():NOV(0),NOVN(0),NOVT(0){}
        bool Load(std::string);
        void STF(std::string& S,Face* F)
        {
            //error<<"属猪大小"<<S.size()<<endl;
            std::string::iterator Po;
            int i=0;
            int Te=0;
            bool Another=false;
            for(Po=S.begin();Po!=S.end();++Po)
            {
                //error<<Po-S.begin()<<endl;
                if(*Po>='0'&&*Po<='9')
                {
                    Te=Te*10+*Po-48;
                    //error<<"sdsd"<<*Po<<"      "<<Te<<endl;
                }
                else if(*Po=='/')
                {
                    //error<<"赋值"<<endl;
                    Another=true;
                    if(i==0) F->v=Te;
                    if(i==1) F->vt=Te;
                    Te=0;
                    i+=1;
                }
            }
            if(Another)
            {
                if(i==2) F->vn=Te;
            }
        }
};


bool Object::Load(std::string S)
{
    std::ifstream DataFile;
    std::ifstream TextureFile;
    char TT[100];
    bool HaveTexture;
    DataFile.open(S.c_str(),std::ios::in);
    std::string Tem;
    if(!DataFile) return false;
    for(;!DataFile.eof();)
    {
        DataFile>>Tem;
        //error<<"asdasdas "<<Tem<<endl;
        if(!Tem.compare("#"))
        {
        }else if(!Tem.compare("v"))
        {
            NOV+=1;
        }else if(!Tem.compare("vt"))
        {
            NOVT+=1;
        }else if(!Tem.compare("vn"))
        {
            NOVN+=1;
        }else if(!Tem.compare("mtllib"))
        {
            //error<<"yes"<<endl;
            std::string Tem3;
            std::string Tem2(S);
            std::string Tem11,Tem12,Tem13;
            int sizebetween;
            bool In=false;
            HaveTexture=true;
            DataFile>>Tem3;
            std::string::iterator Po=Tem2.end();
            for(;Po!=Tem2.begin();)
            {
                --Po;
                //error<<*Po<<endl;
                if(*Po=='\\')
                {
                    //error<<"shi de shuo"<<*Po<<endl;
                    In=true;
                    sizebetween=Po-Tem2.begin();
                    break;
                }
            }
            if(In)
            {
                //error<<Po-Tem2.begin()<<endl;
                std::string Tem4(Tem2.begin(),Tem2.begin()+sizebetween+1);
                Tem2=Tem4;
                //error<<Tem4+Tem3<<endl;
                TextureFile.open((Tem4+Tem3).c_str(),std::ios::in);
                if(!TextureFile) return false;
            }else{
                //error<<Tem3<<endl;
                TextureFile.open(Tem3.c_str(),std::ios::in);
                if(!TextureFile) return false;
            }
            for(;!TextureFile.eof();)
            {
                //error<<"12345"<<endl;
                TextureFile>>Tem11;
                if(!Tem11.compare("newmtl"))
                {
                    TextureFile>>Tem11;
                    TextureFile>>Tem12;
                    TextureFile>>Tem13;
                    //error<<Tem11<<"  "<<Tem12<<"  "<<Tem13<<"  "<<endl;
                    if(In)
                    {
                        Picture* P=new Picture;
                        P->Load(Tem2+Tem13);
                        File.insert(std::make_pair(Tem11,P));
                        //error<<P->Point<<endl;
                    }else{
                        Picture* P=new Picture;
                        P->Load(Tem13);
                        //error<<P->Point<<endl;
                        File.insert(std::make_pair(Tem11,P));
                    }
                    Mode.insert(std::make_pair(Tem11,Tem12));
                }
            }
            TextureFile.close();
        }else{
            //error<<"使得"<<endl;
            continue;
        }
        //DataFile.getline(TT,100);//no use
    }
    //error<<"V的数量"<<NOV<<endl;
    //error<<"Vt的数量"<<NOVT<<endl;
    //error<<"Vn的数量"<<NOVN<<endl;
    DataFile.clear();
    DataFile.seekg(std::ios::beg);
    //DataFile.close();
    V=(XYZF*)operator new[](sizeof(XYZF)*(NOV));
    Vt=(XYF*)operator new[](sizeof(XYF)*(NOVT));
    Vn=(XYZF*)operator new[](sizeof(XYZF)*(NOVN));
    //DataFile.open(S.c_str(),std::ios::in);
    if(!DataFile) return false;
    NOV=0;
    NOVT=0;
    NOVN=0;
    float X,Y,Z;
    Picture* NP;
    bool TextureReady=false;
    TextMode=glGenLists(1);
    //error<<"asdasd"<<TextMode<<endl;
    glNewList(TextMode,GL_COMPILE);
    for(;!DataFile.eof();)
    {
        DataFile>>Tem;
        if(!Tem.compare("#")||!Tem.compare("mtllib"))
        {
            DataFile.getline(TT,100);//no use
        }else if(!Tem.compare("v"))
        {
            //error<<"asdaff"<<endl;
            DataFile>>X>>Y>>Z;
            //error<<X<<"  ,  "<<Y<<"  ,  "<<Z<<"    "<<NOV<<endl;
            V[NOV].Set(X,Y,Z);
            NOV+=1;
        }else if(!Tem.compare("vt"))
        {
            //error<<"papapapap"<<endl;
            DataFile>>X>>Y;
            //error<<"完成"<<endl;
            Vt[NOVT].Set(X,Y);
            NOVT+=1;
        }else if(!Tem.compare("vn"))
        {
            DataFile>>X>>Y>>Z;
            Vn[NOVN].Set(X,Y,Z);
            NOVN+=1;
        }else if(Mode.count(Tem)!=0)
        {   
            //error<<"youle~~~~~"<<endl;
            if(HaveTexture) 
            {
                //error<<"haha~~"<<endl;
                if(TextureReady)
                {
                    glDisable(GL_TEXTURE_2D);
                }
                TextureReady=true;
                NP=File[Tem];
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,NP->Point);
            }
        }else if(!Tem.compare("f"))
        {
            if(TextureReady)
            {
                //error<<"我就说吗111"<<endl;
                std::string Tem2,Tem3,Tem4;
                DataFile>>Tem2>>Tem3>>Tem4;
                Face F1,F2,F3;
                STF(Tem2,&F1);
                STF(Tem3,&F2);
                STF(Tem4,&F3);
                //error<<Tem2<<"    "<<F1.v<<"   "<<F1.vt<<"    " <<F1.vn<<endl;
                //error<<Tem3<<"    "<<F2.v<<"   "<<F2.vt<<"    " <<F2.vn<<endl;;
                //error<<Tem4<<"    "<<F3.v<<"   "<<F3.vt<<"    " <<F3.vn<<endl;;
                glColor4f(1.0,1.0,1.0,1.0);
                glBegin(GL_TRIANGLES);
                glTexCoord2f((Vt[F3.vt-1].X),(1.0-Vt[F3.vt-1].Y));    glNormal(Vn[F3.vn-1]);  glVertex(V[F3.v-1]);
                glTexCoord2f((Vt[F2.vt-1].X),(1.0-Vt[F2.vt-1].Y));    glNormal(Vn[F2.vn-1]);  glVertex(V[F2.v-1]);
                glTexCoord2f((Vt[F1.vt-1].X),(1.0-Vt[F1.vt-1].Y));    glNormal(Vn[F1.vn-1]);  glVertex(V[F1.v-1]);
                
                glEnd();
                //error<<"我就说吗222"<<endl;
            }
        }
        //error<<" "<<NOV<<"  "<<NOVT<<"   "<<NOVN<<endl;
    }
    if(TextureReady)
    {
        glDisable(GL_TEXTURE_2D);
    }
    glEndList();
    operator delete[](V);
    operator delete[](Vt);
    operator delete[](Vn);
    //error<<"wancheng"<<endl;
    return true;
}
    
#endif
