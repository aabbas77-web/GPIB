//---------------------------------------------------------------------------
#include <windows.h>
//---------------------------------------------------------------------------
#pragma argsused
//---------------------------------------------------------------------------
#include "Interface.h"
//---------------------------------------------------------------------------
extern "C" __declspec(dllexport) void DeviceInit(int Address);
extern "C" __declspec(dllexport) void DeviceClose();
extern "C" __declspec(dllexport) bool ExecuteInterface(TMeasures *AMeasures);
extern "C" __declspec(dllexport) void SendParameters(TAParams *Params);
extern "C" __declspec(dllexport) void GetDeviceInParameters(TAParams *Params);
extern "C" __declspec(dllexport) void GetDeviceOutParameters(TAParams *Params);
extern "C" __declspec(dllexport) int  GetDeviceAddress();
extern "C" __declspec(dllexport) char *GetDeviceName();
extern "C" __declspec(dllexport) char *GetDeviceFilter();
extern "C" __declspec(dllexport) char *GetDeviceExtention();

extern "C" __declspec(dllexport) void CreateInterface();
extern "C" __declspec(dllexport) void DestroyInterface();
extern "C" __declspec(dllexport) void ShowInterface();
extern "C" __declspec(dllexport) void ShowModalInterface();
extern "C" __declspec(dllexport) void CloseInterface();
extern "C" __declspec(dllexport) void GetMeasures(TMeasures *AMeasures);
//---------------------------------------------------------------------------
//-----------------------Exported functions----------------------------------
//---------------------------------------------------------------------------
TFormInterface *FormInterface;
//---------------------------------------------------------------------------
void CreateInterface()
{
 FormInterface=new TFormInterface(Application);
 GetDeviceOutParameters(FormInterface->OutParams);
 GetDeviceInParameters(FormInterface->InParams);
 FormInterface->Init();
}
//---------------------------------------------------------------------------
void DestroyInterface()
{
 if(FormInterface)
  delete FormInterface;
}
//---------------------------------------------------------------------------
void DeviceInit(int Address)
{
 PM2535.pm2535_init(Address,1);
}
//---------------------------------------------------------------------------
void DeviceClose()
{
 PM2535.pm2535_close_instr(PM2535.instr_ID);
}
//---------------------------------------------------------------------------
void ShowInterface()
{
 FormInterface->Show();
}
//---------------------------------------------------------------------------
void ShowModalInterface()
{
 FormInterface->ShowModal();
}
//---------------------------------------------------------------------------
void CloseInterface()
{
 FormInterface->Close();
}
//---------------------------------------------------------------------------
void GetMeasures(TMeasures *AMeasures)
{
 for(int i=0;i<FormInterface->Measures->Count;i++)
  AMeasures->Add(FormInterface->Measures->Measures[i]);
}
//---------------------------------------------------------------------------
bool ExecuteInterface(TMeasures *AMeasures)
{
 TFormInterface *FormInterface=new TFormInterface(Application);
 bool Result=true;
 FormInterface->ShowModal();
 for(int i=0;i<FormInterface->Measures->Count;i++)
  AMeasures->Add(FormInterface->Measures->Measures[i]);
 if(FormInterface)
  delete FormInterface;
 return Result;
}
//---------------------------------------------------------------------------
void SendParameters(TAParams *Params)
{
 PM2535.pm2535_set_function(PM2535.instr_ID, Params->Params[0]->Index);
 PM2535.pm2535_set_trig_source(PM2535.instr_ID, Params->Params[1]->Index);
 PM2535.pm2535_set_speed(PM2535.instr_ID, Params->Params[2]->Index+1);
 PM2535.pm2535_set_resolution(PM2535.instr_ID, Params->Params[3]->Index+4);
 PM2535.pm2535_set_settling_time(PM2535.instr_ID, Params->Params[4]->Index);
 PM2535.pm2535_set_filter(PM2535.instr_ID, Params->Params[5]->Index);
 PM2535.pm2535_set_range (PM2535.instr_ID,0.0); //Autoranging
 PM2535.pm2535_reset_min_max (PM2535.instr_ID);
}
//---------------------------------------------------------------------------
void GetDeviceInParameters(TAParams *Params)
{
 TAParam *Param;

 // Index 0
 Param=new TAParam();
 Param->Name="Function";
 Param->Index=0;
 Param->Values->Add("Volt DC");
 Param->Values->Add("Volt AC");
 Param->Values->Add("Current DC");
 Param->Values->Add("Current AC");
 Param->Values->Add("Resistan 2W");
 Param->Values->Add("Resistan 4W");
 Param->Values->Add("Temperature");
 Params->Add(Param);

// Index 1
 Param=new TAParam();
 Param->Name="Source";
 Param->Index=0;
 Param->Values->Add("Internal");
 Param->Values->Add("External");
 Param->Values->Add("Bus");
 Param->Values->Add("Manual");
 Params->Add(Param);

// Index 2
 Param=new TAParam();
 Param->Name="Speed";
 Param->Index=3;
 Param->Values->Add("Low");
 Param->Values->Add("Normal");
 Param->Values->Add("Medium");
 Param->Values->Add("High");
 Params->Add(Param);

// Index 3
 Param=new TAParam();
 Param->Name="Resolution";
 Param->Index=0;
 Param->Values->Add("4 Digits");
 Param->Values->Add("5 Digits");
 Param->Values->Add("6 Digits");
 Param->Values->Add("7 Digits");
 Params->Add(Param);

 // Index 4
 Param=new TAParam();
 Param->Name="Settling Time";
 Param->Index=1;
 Param->Values->Add("OFF");
 Param->Values->Add("ON");
 Params->Add(Param);

 // Index 5
 Param=new TAParam();
 Param->Name="Filter";
 Param->Index=1;
 Param->Values->Add("OFF");
 Param->Values->Add("ON");
 Params->Add(Param);
}
//---------------------------------------------------------------------------
void GetDeviceOutParameters(TAParams *Params)
{
 TAParam *Param;
 // First Group:
 Param=new TAParam();
 Param->Name="Volt DC";
 Param->Index=0;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Volt AC";
 Param->Index=1;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Current DC";
 Param->Index=2;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Current AC";
 Param->Index=3;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Resistan 2W";
 Param->Index=4;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Resistan 4W";
 Param->Index=5;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Temperature";
 Param->Index=6;
 Param->Group=0;
 Params->Add(Param);

 // Second Group: for MIN_MAX!!!!
}
//---------------------------------------------------------------------------
int GetDeviceAddress()
{
 return PM2535.instr_addr;
}
//---------------------------------------------------------------------------
char * GetDeviceName()
{
 return "Philips PM2535 Digital Multimeter";
}
//---------------------------------------------------------------------------
char * GetDeviceFilter()
{
 return "PM2535 Files (*.2535)|*.2535";
}
//---------------------------------------------------------------------------
char * GetDeviceExtention()
{
 return ".2535";
}
//---------------------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
        return 1;
}
//---------------------------------------------------------------------------
