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
 PM3000.pm3000_init(Address,0);
}
//---------------------------------------------------------------------------
void DeviceClose()
{
 PM3000.pm3000_close_instr(PM3000.instr_ID);
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
 PM3000.pm3000_conf_operation(PM3000.instr_ID,Params->Params[0]->Index, 0,
                              Params->Params[1]->Index, Params->Params[14]->Index,
                              Params->Params[15]->Index + 1, Params->Params[2]->Index,
                              Params->Params[3]->Index);

 PM3000.pm3000_conf_range_set(PM3000.instr_ID, Params->Params[16]->Index,
                              Params->Params[8]->Index,Params->Params[4]->Index,
                              Params->Params[5]->Index);

 PM3000.pm3000_conf_wiring(PM3000.instr_ID, Params->Params[6]->Index,
                           Params->Params[17]->Index);

 PM3000.pm3000_conf_meas_IEC555_mode(PM3000.instr_ID, Params->Params[12]->Index,
                                     Params->Params[8]->Index);

 PM3000.pm3000_conf_ballast_mode(PM3000.instr_ID, Params->Params[13]->Index);
}
//---------------------------------------------------------------------------
void GetDeviceInParameters(TAParams *Params)
{
 TAParam *Param;

 // Index 0
 Param=new TAParam();
 Param->Name="Frequency_Source";
 Param->Index=0;
 Param->Values->Add("VLT");
 Param->Values->Add("AMP");
 Param->Values->Add("EXT");
 Param->Values->Add("SLW");
 Params->Add(Param);

 // Index 1
 Param=new TAParam();
 Param->Name="VoltsAmps";
 Param->Index=1;
 Param->Values->Add("MEA");
 Param->Values->Add("TRU");
 Params->Add(Param);

 // Index 2
 Param=new TAParam();
 Param->Name="Coupling";
 Param->Index=1;
 Param->Values->Add("-DC");
 Param->Values->Add("+DC");
 Params->Add(Param);

 // Index 3
 Param=new TAParam();
 Param->Name="Internal_External";
 Param->Index=1;
 Param->Values->Add("EXT");
 Param->Values->Add("INT");
 Params->Add(Param);

 // Index 4
 Param=new TAParam();
 Param->Name="Volt Range";
 Param->Index=0;
 Param->Values->Add("AUT");
 Param->Values->Add("FIX 1");
 Param->Values->Add("FIX 2");
 Param->Values->Add("FIX 3");
 Param->Values->Add("FIX 4");
 Param->Values->Add("FIX 5");
 Param->Values->Add("FIX 6");
 Param->Values->Add("FIX 7");
 Param->Values->Add("FIX 8");
 Param->Values->Add("FIX 9");
 Param->Values->Add("FIX 10");
 Param->Values->Add("FIX 11");
 Param->Values->Add("FIX 12");
 Params->Add(Param);

 // Index 5
 Param=new TAParam();
 Param->Name="Current Range";
 Param->Index=0;
 Param->Values->Add("AUT");
 Param->Values->Add("FIX 1");
 Param->Values->Add("FIX 2");
 Param->Values->Add("FIX 3");
 Param->Values->Add("FIX 4");
 Param->Values->Add("FIX 5");
 Param->Values->Add("FIX 6");
 Param->Values->Add("FIX 7");
 Param->Values->Add("FIX 8");
 Param->Values->Add("FIX 9");
 Param->Values->Add("FIX 10");
 Param->Values->Add("FIX 11");
 Param->Values->Add("FIX 12");
 Params->Add(Param);

 // Index 6
 Param=new TAParam();
 Param->Name="Wiring";
 Param->Index=0;
 Param->Values->Add("1P2");
 Param->Values->Add("1P3");
 Param->Values->Add("3P3");
 Param->Values->Add("3P4");
 Param->Values->Add("CH2");
 Param->Values->Add("CH3");
 Param->Values->Add("MIX");
 Param->Values->Add("ALL");
 Params->Add(Param);

 // Index 7
 Param=new TAParam();
 Param->Name="Harmonic";
 Param->Index=0;
 Param->Values->Add("ODD");
 Param->Values->Add("ALL");
 Params->Add(Param);

// Index 8
 Param=new TAParam();
 Param->Name="Channel";
 Param->Index=1;
 Param->Values->Add("ALL");
 Param->Values->Add("CH1");
 Param->Values->Add("CH2");
 Param->Values->Add("CH3");
 Param->Values->Add("SUM");
 Param->Values->Add("CHN");
 Param->Values->Add("AUX");
 Params->Add(Param);

 // Index 9
 Param=new TAParam();
 Param->Name="Function_List";
 Param->Index=0;
 Param->Values->Add("WAT");
 Param->Values->Add("VAS");
 Param->Values->Add("VAR");
 Param->Values->Add("VLT");
 Param->Values->Add("AMP");
 Param->Values->Add("PWF");
 Param->Values->Add("VPK");
 Param->Values->Add("APK");
 Param->Values->Add("VCF");
 Param->Values->Add("ACF");
 Param->Values->Add("IMP");
 Param->Values->Add("VDF");
 Param->Values->Add("ADF");
 Param->Values->Add("FRQ");
 Param->Values->Add("VHM");
 Param->Values->Add("AHM");
 Param->Values->Add("VHA");
 Param->Values->Add("AHA");
 Param->Values->Add("EFF");
 Param->Values->Add("WHR");
 Param->Values->Add("VAH");
 Param->Values->Add("VRH");
 Param->Values->Add("AHR");
 Param->Values->Add("APF");
 Param->Values->Add("TIM");
 Param->Values->Add("VDC");
 Param->Values->Add("ADC");
 Params->Add(Param);

 // Index 10
 Param=new TAParam();
 Param->Name="Select_List";
 Param->Index=0;
 Param->Values->Add("CH1");
 Param->Values->Add("CH2");
 Param->Values->Add("CH3");
 Param->Values->Add("SUM");
 Param->Values->Add("CHN");
 Param->Values->Add("FUN");
 Param->Values->Add("WAT");
 Param->Values->Add("VAS");
 Param->Values->Add("VAR");
 Param->Values->Add("VLT");
 Param->Values->Add("AMP");
 Param->Values->Add("PWF");
 Param->Values->Add("VPK");
 Param->Values->Add("APK");
 Param->Values->Add("VCF");
 Param->Values->Add("ACF");
 Param->Values->Add("IMP");
 Param->Values->Add("VDF");
 Param->Values->Add("ADF");
 Param->Values->Add("FRQ");
 Param->Values->Add("VHM");
 Param->Values->Add("AHM");
 Params->Add(Param);

 // Index 11
 Param=new TAParam();
 Param->Name="Fundamental_List";
 Param->Index=0;
 Param->Values->Add("WAT");
 Param->Values->Add("VAS");
 Param->Values->Add("VAR");
 Param->Values->Add("VLT");
 Param->Values->Add("AMP");
 Param->Values->Add("PWF");
 Param->Values->Add("IMP");
 Param->Values->Add("VHM");
 Param->Values->Add("AHM");
 Param->Values->Add("VHA");
 Param->Values->Add("AHA");
 Param->Values->Add("EFF");
 Param->Values->Add("WHR");
 Param->Values->Add("VAH");
 Param->Values->Add("VRH");
 Param->Values->Add("AHR");
 Param->Values->Add("APF");
 Param->Values->Add("CVR");
 Params->Add(Param);

 // Index 12
 Param=new TAParam();
 Param->Name="IEC_Mode";
 Param->Index=0;
 Param->Values->Add("DIS");
 Param->Values->Add("FIX");
 Param->Values->Add("FLU");
 Param->Values->Add("FLI");
 Params->Add(Param);

 // Index 13
 Param=new TAParam();
 Param->Name="Ballast";
 Param->Index=0;
 Param->Values->Add("DIS");
 Param->Values->Add("50H");
 Param->Values->Add("60H");
 Params->Add(Param);

 // Index 14
 Param=new TAParam();
 Param->Name="Averaging";
 Param->Index=0;
 Param->Values->Add("Fixed");
 Param->Values->Add("Auto");
 Params->Add(Param);

 // Index 15
 Param=new TAParam();
 Param->Name="Average Depth";
 Param->Index=0;
 Param->Values->Add("Depth 1");
 Param->Values->Add("Depth 2");
 Param->Values->Add("Depth 3");
 Param->Values->Add("Depth 4");
 Param->Values->Add("Depth 5");
 Param->Values->Add("Depth 6");
 Param->Values->Add("Depth 7");
 Param->Values->Add("Depth 8");
 Param->Values->Add("Depth 9");
 Param->Values->Add("Depth 10");
 Param->Values->Add("Depth 11");
 Param->Values->Add("Depth 12");
 Param->Values->Add("Depth 13");
 Param->Values->Add("Depth 14");
 Param->Values->Add("Depth 15");
 Param->Values->Add("Depth 16");
 Param->Values->Add("Depth 17");
 Param->Values->Add("Depth 18");
 Param->Values->Add("Depth 19");
 Param->Values->Add("Depth 20");
 Param->Values->Add("Depth 21");
 Param->Values->Add("Depth 22");
 Param->Values->Add("Depth 23");
 Param->Values->Add("Depth 24");
 Param->Values->Add("Depth 25");
 Param->Values->Add("Depth 26");
 Param->Values->Add("Depth 27");
 Param->Values->Add("Depth 28");
 Param->Values->Add("Depth 29");
 Param->Values->Add("Depth 30");
 Param->Values->Add("Depth 31");
 Param->Values->Add("Depth 32");
 Param->Values->Add("Depth 33");
 Param->Values->Add("Depth 34");
 Param->Values->Add("Depth 35");
 Param->Values->Add("Depth 36");
 Param->Values->Add("Depth 37");
 Param->Values->Add("Depth 38");
 Param->Values->Add("Depth 39");
 Param->Values->Add("Depth 40");
 Param->Values->Add("Depth 41");
 Param->Values->Add("Depth 42");
 Param->Values->Add("Depth 43");
 Param->Values->Add("Depth 44");
 Param->Values->Add("Depth 45");
 Param->Values->Add("Depth 46");
 Param->Values->Add("Depth 47");
 Param->Values->Add("Depth 48");
 Param->Values->Add("Depth 49");
 Param->Values->Add("Depth 50");
 Param->Values->Add("Depth 51");
 Param->Values->Add("Depth 52");
 Param->Values->Add("Depth 53");
 Param->Values->Add("Depth 54");
 Param->Values->Add("Depth 55");
 Param->Values->Add("Depth 56");
 Param->Values->Add("Depth 57");
 Param->Values->Add("Depth 58");
 Param->Values->Add("Depth 59");
 Param->Values->Add("Depth 60");
 Param->Values->Add("Depth 61");
 Param->Values->Add("Depth 62");
 Param->Values->Add("Depth 63");
 Param->Values->Add("Depth 64");
 Params->Add(Param);

 // Index 16
 Param=new TAParam();
 Param->Name="Ranging Mode";
 Param->Index=0;
 Param->Values->Add("Locked");
 Param->Values->Add("Independent");
 Params->Add(Param);

 // Index 17
 Param=new TAParam();
 Param->Name="Phase_Neutral";
 Param->Index=0;
 Param->Values->Add("Phase to Neutral");
 Param->Values->Add("Phase to Phase");
 Params->Add(Param);
/*
 // Index 14
 Param=new TAParam();
 Param->Name="Log_Mode";
 Param->Index=0;
 Param->Values->Add("DIS");
 Param->Values->Add("TRG");
 Param->Values->Add("EXT");
 Params->Add(Param);
*/
}
//---------------------------------------------------------------------------
void GetDeviceOutParameters(TAParams *Params)
{
 TAParam *Param;
// First Group:
 Param=new TAParam();
 Param->Name="B_Fundamentals";
 Param->Index=0;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="B_Watts";
 Param->Index=1;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="B_VA";
 Param->Index=2;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="B_VAr";
 Param->Index=3;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="B_Vrms";
 Param->Index=4;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="B_Arms";
 Param->Index=5;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="B_Powerfactor";
 Param->Index=6;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="B_Vpk";
 Param->Index=7;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="B_Apk";
 Param->Index=8;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="B_Voltage Crestfactor";
 Param->Index=9;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="B_Current Crestfactor";
 Param->Index=10;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="B_Impedance";
 Param->Index=11;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="B_VTHD";
 Param->Index=12;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="B_ATHD";
 Param->Index=13;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="B_Frequency";
 Param->Index=14;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="B_Voltage Harmonics";
 Param->Index=15;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="B_Current Harmonics";
 Param->Index=16;
 Param->Group=0;
 Params->Add(Param);

 // Second Group:
 Param=new TAParam();
 Param->Name="F_Fundamentals";
 Param->Index=0;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="F_Watts";
 Param->Index=1;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="F_VA";
 Param->Index=2;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="F_VAr";
 Param->Index=3;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="F_Vrms";
 Param->Index=4;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="F_Arms";
 Param->Index=5;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="F_Powerfactor";
 Param->Index=6;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="F_Vpk";
 Param->Index=7;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="F_Apk";
 Param->Index=8;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="F_Voltage Crestfactor";
 Param->Index=9;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="F_Current Crestfactor";
 Param->Index=10;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="F_Impedance";
 Param->Index=11;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="F_VTHD";
 Param->Index=12;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="F_ATHD";
 Param->Index=13;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="F_Frequency";
 Param->Index=14;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="F_Voltage Harmonics";
 Param->Index=15;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="F_Current Harmonics";
 Param->Index=16;
 Param->Group=1;
 Params->Add(Param);

 // Third Group:
 Param=new TAParam();
 Param->Name="D_Watts";
 Param->Index=0;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="D_VA";
 Param->Index=1;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="D_VAr";
 Param->Index=2;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="D_Volts";
 Param->Index=3;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="D_Amps";
 Param->Index=4;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="D_PF";
 Param->Index=5;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="D_Impedance";
 Param->Index=6;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="D_Voltage Harmonic";
 Param->Index=7;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="D_Current Harmonic";
 Param->Index=8;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="D_Voltage Harmonic Angle";
 Param->Index=9;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="D_Current Harmonic Angle";
 Param->Index=10;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="D_Efficiency";
 Param->Index=11;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="D_Watt-Hrs";
 Param->Index=12;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="D_VA-Hrs";
 Param->Index=13;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="D_VAr-Hrs";
 Param->Index=14;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="D_A-Hrs";
 Param->Index=15;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="D_Average PF";
 Param->Index=16;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="D_Corr VAr";
 Param->Index=17;
 Param->Group=2;
 Params->Add(Param);

 // Forth Group:
 Param=new TAParam();
 Param->Name="S_Watts";
 Param->Index=0;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_VA";
 Param->Index=1;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_VAr";
 Param->Index=2;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_Vrms";
 Param->Index=3;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_Arms";
 Param->Index=4;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_Powerfactor";
 Param->Index=5;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_Vpk";
 Param->Index=6;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_Apk";
 Param->Index=7;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_VCF";
 Param->Index=8;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_ACF";
 Param->Index=9;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_Impedance";
 Param->Index=10;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_VTHD";
 Param->Index=11;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_ATHD";
 Param->Index=12;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_Frequency";
 Param->Index=13;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_Voltage Harmonic";
 Param->Index=14;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_Current Harmonic";
 Param->Index=15;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_Voltage Harmonic Angle";
 Param->Index=16;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_Current Harmonic Angle";
 Param->Index=17;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_Efficiency";
 Param->Index=18;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_Watt-Hrs";
 Param->Index=19;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_VA-Hrs";
 Param->Index=20;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_VAr-Hrs";
 Param->Index=21;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_A-Hrs";
 Param->Index=22;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_Average PF";
 Param->Index=23;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_Integrator Time";
 Param->Index=24;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_Volts DC";
 Param->Index=25;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="S_Amps DC";
 Param->Index=26;
 Param->Group=3;
 Params->Add(Param);
}
//---------------------------------------------------------------------------
int GetDeviceAddress()
{
 return PM3000.instr_addr;
}
//---------------------------------------------------------------------------
char * GetDeviceName()
{
 return "Universal Power Analyzer";
}
//---------------------------------------------------------------------------
char * GetDeviceFilter()
{
 return "PM3000 Files (*.3000)|*.3000";
}
//---------------------------------------------------------------------------
char * GetDeviceExtention()
{
 return ".3000";
}
//---------------------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
        return 1;
}
//---------------------------------------------------------------------------
