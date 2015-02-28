#include <fstream>
using namespace std;
fstream error("erro.txt",ios::out);
#include "p.o/controlcenter.h"
//#include <function>
//#include <bind>
//#include "p.o/unequalboss.h"
//#include "p.o/unequalstaff.h"
ControlCenter CC;
#include "zhuankuai.h" 
//#include "base/welcomeaspect.h"
//#include "base/viewer.cpp"
//Handle<Plugin_Base> ST=new Start();
//Handle<Plugin_Base> Vi=new Viewer();

int main(int argc, char* argv[])
{
    Handle<ZhuanKuaiSpace> KK=new ZhuanKuaiSpace();
    CC.Regedit(KK);
    CC.Init(1);
    Handle<ZhuanKuai> Cc=new ZhuanKuai(XYF(0.0,0.0));
    Cc->Move=true;
    Cc->Falling=false;
    Cc->D=XYF(-0.5,0.5);
    KK->Bo.Employ(Cc);
    while(CC.Running)
    {
        CC.Run();
        CC.Finish();
    }
}
