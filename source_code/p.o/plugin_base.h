/*���ߣ������� 
  ����ڣ�2012��4��20�� 
*/
/*
2012��12��2���޸� 
*/ 

#ifndef DIY_PLUGIN_BASE_H
#define DIY_PLUGIN_BASE_H
#include <string>
#include <list>
#include <map>
#include <vector>
#include <set>
#include "information.h"
#include "error.h"
#include "handle.h"
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <GL/glu.h>
#include "glsimplify.h"
#include "staff.h"
class Plugin_Base;
class ControlCenter;
std::map<std::string , int > NaTarSI;//�ַ������ʶID��ת�� 
std::map<int , Handle<Plugin_Base> > NaTarIP;//��ʶID����ָ���ת�� 
std::map<int , std::string > NaTarIS;
inline int Call(std::string Tem)
{
    if(NaTarSI.count(Tem))
        return NaTarSI[Tem];
    else
        return INFNOTAR;
}
inline Handle<Plugin_Base> Call(int Tem)
{
    if(NaTarIP.count(Tem))
        return NaTarIP[Tem];
    else{
        Handle<Plugin_Base> Ty;
        return Ty;
    }
}
int Thread_1_Function(void* Data);
class Plugin_Base:virtual public Staff<ControlCenter*,long>//�������
{
    std::list< Handle<Information> > OutLibrary;//�����Ϣ���������Զ��ŵ����ʵĵط�
    std::list< Handle<Information> > Library;//�����յ��ĺ���
    protected:
    friend class ControlCenter;
    friend int Thread_1_Function(void* Data);
    int NomberOfInformation;//��Ϣ�ļ��� 
    friend int Oclock(void *param);//���� 
    int RegeditID;//��ʶID 
    const std::string Name;//��ʾ�ַ����� 

    void virtual Destory(ControlCenter* Data);//α�������� 
    void virtual Main(ControlCenter* Data,long L){}//SHOW�����������й�SDL��OPENGL�ĺ�����Ӧ�÷���������Բ�����
    void virtual Accessorial(ControlCenter* Data,long L){}//ANALYZE���������ݵĴ����滭�����޷���Ӧ ���Բ�����
    void virtual FlatShow(ControlCenter* Data){}//3D-2D������3DͶӰģ��ʱ���ã�����ֻ֧��glVertex2f()��glVertex(XYF)��������ʾЧ������
    void virtual BlendShow(ControlCenter* Data){}
    bool RefuseINFALL;//��CONTROLCENTER������������Ϣ����շ�
    void GetLib(Handle<Information>& Temp);//��������Ϣ�б��е���Ϣѹ�������Ϣ�б� 
    bool PushOutLibrary(Handle<Information> &K);
    void Destory(){HandleSeed::Destory();}
    int InformationSize;
    public: 
        bool ReceiveInformation(){return true;}
        bool ReceiceEventInformation(){return RefuseINFALL;}
        Plugin_Base(std::string name);
        Plugin_Base(std::string name,bool choice);//�ڶ���������ѡ���Ƿ����CONTROLCENTER��������Ϣ�� 
        void Useless(void);//�����ʹ����Ϣ�࣬����ã�����������;�������� 
        void ToAspect(unsigned int Te);//�ı�CONTROLCENTER�е�ASPECT 
        void Orthogonality(void);//�ĳ�2ά�Ӿ�ģ�� 
        void Perspective(void);//�ĳ�3DͶӰ�Ӿ�ģ�� 
        void UnableExit(void);//���� 
        void Killmyself(void);//��ɱ���� 
        void Out(Handle<Information>& Tem);//����Ϣѹ����Ϣ�����б� 
        void Exit(void);//�����˳��ź� 
        void LockMouse(void);//�̶���� 
        void UnlockMouse(void);//�Ӵ��̶� 
        bool InformationEmpty(){return Library.empty();}
        Handle<Information> NewInformation(int Target,int Category1,int Category2,int Category3,int Category4);//��������Ϣ 
        Handle<Information> GetInformation(void);//�õ��б�ĵ�һ������������б�Ϊ����Ϊ����Ϣ 
        ~Plugin_Base();

}; 


#include "plugin_base.cpp"
#endif
