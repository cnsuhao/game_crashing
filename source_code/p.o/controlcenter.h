/*���ߣ������� */
/*
 *2013��4��15��������һЩ�쳣������Ҫ������ʱ�ĳ�ʼ�����󣩣����˳��Ĺ��̳���Ϊһ����������������RUN������ʹ�á� 
*/
/*
 *����������Ĺ��ܡ��������������������������Ӧ�ò���Ҫר�ż�¼�����ɣ���
 */
/*
 *����޸�������2013��2��27��
 *������3D��ʾģʽ��α2D�任�����������Ҫ��2D�滭�г���3DЧ������Ҫ����ControlCenter �е�SetView(3)��Ȼ���ٵ���SetView(1)�ָ���
 *�������жϴ��ڻ�ĺ����������ڴ��ڷǻ������¶����Ŀ��ƽ�ʧЧ��(�����Ҳ�������ĺ궨�壬����ͨ��ʵ���ҳ�������ֵ������SDL�汾�ı��ʱ�������Ҫ�ı�
 *      ��λ��λ��ControlCenter.cpp �е�Run�����ж�SDL_ACTIVEEVENT��Ϣ����Ӧ)��
 *�Ż���SDL��չ��ĳ�ʼ����ʽ��
 */
/*
*����޸���2013��1��16�� 
*�����˼��ز���ķ�ʽ��ready()����ɾ�� 
*���ڿ���ʱ����REGEIDT���������ز��������ȷ����ʹ��ǰ��ʼ�� 
*/
/*
*����޸���2013��1��13�� 
*���ע�� 
*��������ʱ�������INTERVALTIMESHOW INTERVALTIMEANALYZE������ʾÿ��ѭ���ļ��ʱ�䡣 
*/
/*
*����޸���2012��12��2�� 
*���ע�� 
*����ͨ���������Ļ�������õ�ǰ�����ָ�����ص�3D����GET3DMOUSE��δ��� 
*/
/* 
 *����޸��ڣ� 2012��4��12�� 
 *�����÷������Ķ�λ��ĩβ����ϸ˵���顣
 * ɾ���˹̶�ʱ����Ӧ���� 
 */ 
/*   2012��4��20��
     �޸���ˢ�¼��ʱ��������ж�
     �����˹̶�ʱ����Ӧ������ 
*/
/*      2012��11��7��
        ������3D͸��ģʽ�µ�α2D��ʾ����
 */
#ifndef  DIY_CONTROLCENTER_H 
#define  DIY_CONTROLCENTER_H 
#include <ctime>
#include <cstdlib>
#include <vector> 
#include <list>
#include <map>
#include <string>
#include "information.h"//��Ϣ������  
#include "plugin_base.h"//�����
#include "boss.h"
class ControlCenterJustForFirstInit
{
    public:
    ControlCenterJustForFirstInit();
}JustForInitAndDoNotUseThis;

class ControlCenter
{
    friend int Thread_1_Function(void* Data);//�ڶ��̺߳��� 
    SDL_Event Event;//SDL���¼��� 
    SDL_Thread* Thread1;//�߳�2 Analyze 
    SDL_Thread* Thread2;//�߳�3 ���� 
    SDL_Surface* Screen;//SDL�Ĵ��� 
    Boss<ControlCenter*,long> AllList;
    PublicValue<std::list< Handle<Information> > > MainLibrary; //����������Ϣ�б�
    PublicValue<std::list< Handle<Information> > > DeliverLibrary;   //����������������贫�ݵ���Ϣ�б�
    int ViewMode;//���������Ӿ�ģ��    1Ϊ2D��2Ϊ3D������3Ϊ3D͸�� 
    unsigned int Aspect;//������ã����ڲ������ٽ��� 
    bool InitFinish;//����Ƿ��ѳ�ʼ�� 
    int TimeForShow,TimeForAnalyze;//Show���� ��Analyze��������ͣ��ʱ�� ��ms�� 
    int DelayForShow,DelayForAnalyze;//ͣ��ʱ�䣬 ��֤��ͬ�������ͣ��ʱ�������ȣ�MS�� 
    int RegeditID;//����ר����ID 
    int WindowW,WindowH;//���ڵĸ߶ȿ�ȣ����أ� 
    int Calculate;//��ʾѭ���������� 
    int StarTime;//����ʼ�������ʽ����ʱ�� 
    bool MouseLock;//�������Ƿ�̶�����Ļ���� 
    bool MouseLockMode;//�������Ƿ����� 
    bool ThreadReady;//�ڶ��߳�����״����� 
    bool ExitImi;//����Ƿ��ڵ�����ڵ����ϽǾ��˳� 
    bool AnalyzeReadyToExit;//�ڶ��߳��˳�׼����� 
    bool Get3DMouse(float X,float Y,XYZF& Location); //���3Dλ�û�ú��� 
    public:
        bool Active;//��Ϊtrueʱ��ʾ�ô��ڵ�ǰ��Ч
        long IntervalTimeShow;//���ʱ��
        long IntervalTimeAnalyze;//���ʱ��
        bool Running;//��ǳ����Ƿ��˳� 
        float FarSize,Angle,NearSize;//�����3D�Ӿ�ģ�ͣ����ʾ�Ӿ�����Զ���룬Y-Zƽ���Ӿ��Ƕȣ��Ӿ���������� 
        float Far,Near,FX,FY,NX,NY;//3D-2Dα�任�� 
        bool SetView(int Mode); //�ı��Ӿ�ģ�� 
        unsigned int Asp(void);//���ص�ǰASPECT 
        int WindowX(){return WindowW;}//=��= 
        int WindowY(){return WindowH;}//=��= 
        bool Time(int X1,int X2);//�ж��Ƿ��ڴ˶�ʱ��֮�� 
        bool Init(int Mode,int W,int H);//��ʼ�� 
        void Finish(void);//ÿ������һ�ε���β���� 
        void Run(int number);//������ 
        void Regedit(Handle<Plugin_Base > Temporary);//���ز��
        ControlCenter();
        bool ChangeIntoFlat(XYZF&,XYF&);//3D����ת2D���꣬�����2D�������Ӿ����ڣ�����TRUE 
        int Time(int Number);//��ǰ����ʱ����NUMBER֮�� 
        void Exit(void);
        void FlatShow(Handle<Plugin_Base >);
        void BlendShow(Handle<Plugin_Base>);
        void GetInformation(Handle<Plugin_Base >);
        void ShootInformation(Handle<Plugin_Base>);
        Boss_StaffActive<ControlCenter*,long>* StaffActive(){return AllList.StaffActive();}
        //static void InitFunction(void (*)(void));
};
//void ControlCenter::InitFunction(void (*)(void)=NULL){}//������ĳ������¶�ȫ�ֶ���Ӱ��ĳ�ʼ��
int Thread_1_Function(void* Data); //��Ϣ���� 
//int Oclock(void *param);
#include "controlcenter.cpp"
#endif
