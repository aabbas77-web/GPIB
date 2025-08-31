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
 UOP7907.uop7907_init(Address,1);
}
//---------------------------------------------------------------------------
void DeviceClose()
{
 UOP7907.uop7907_close_instr(UOP7907.instr_ID);
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
 UOP7907.uop7907_set_voltage_resulation(UOP7907.instr_ID, Params->Params[0]->Index);
 UOP7907.uop7907_set_trigger_mode(UOP7907.instr_ID, Params->Params[1]->Index);
 UOP7907.uop7907_set_force_mode(UOP7907.instr_ID, Params->Params[2]->Index);
 UOP7907.uop7907_set_analog_input_mode(UOP7907.instr_ID, Params->Params[3]->Index);
}
//---------------------------------------------------------------------------
void GetDeviceInParameters(TAParams *Params)
{
 TAParam *Param;

 // Index 0
 Param=new TAParam();
 Param->Name="Voltage Resulation";
 Param->Index=0;
 Param->Values->Add("R0");
 Param->Values->Add("R1");
 Param->Values->Add("R2");
 Params->Add(Param);

 // Index 1
 Param=new TAParam();
 Param->Name="Trigger Mode";
 Param->Index=0;
 Param->Values->Add("T0");
 Param->Values->Add("T1");
 Params->Add(Param);

 // Index 2
 Param=new TAParam();
 Param->Name="Force Mode";
 Param->Index=0;
 Param->Values->Add("S0");
 Param->Values->Add("S1");
 Params->Add(Param);

 // Index 3
 Param=new TAParam();
 Param->Name="Input Mode";
 Param->Index=0;
 Param->Values->Add("A0");
 Param->Values->Add("A1");
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

/*
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

*/
 // Second Group: for MIN_MAX!!!!
}
//---------------------------------------------------------------------------
int GetDeviceAddress()
{
 return UOP7907.instr_addr;
}
//---------------------------------------------------------------------------
char * GetDeviceName()
{
 return "Unipolar Operational Power Supply";
}
//---------------------------------------------------------------------------
char * GetDeviceFilter()
{
 return "UOP7907 Files (*.7907)|*.7907";
}
//---------------------------------------------------------------------------
char * GetDeviceExtention()
{
 return ".7907";
}
//---------------------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
        return 1;
}
//---------------------------------------------------------------------------
