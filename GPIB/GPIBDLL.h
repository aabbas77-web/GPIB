//---------------------------------------------------------------------------
#ifndef GPIBDLLH
#define GPIBDLLH
//---------------------------------------------------------------------------
typedef int *(*F_Pibsta)();
typedef long *(*F_Pibcntl)();
//---------------------------------------------------------------------------
class TGPIB
{
private:
        F_Pibsta FPibsta;
        F_Pibsta FPiberr;
        F_Pibcntl FPibcntl;

        bool FLoaded;
        AnsiString FDeviceDLL;
public:
       TGPIB();
       ~TGPIB();

       void Error(AnsiString Function);
       void Load(AnsiString FileName);

       int *Pibsta();
       int *Piberr();
       long *Pibcntl();

       __property bool Loaded={read=FLoaded};
};
//---------------------------------------------------------------------------
#endif
