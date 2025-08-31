//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Interface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma link "CGAUGES"
#pragma link "PERFGRAP"
#pragma resource "*.dfm"
TFormInterface *FormInterface;
//---------------------------------------------------------------------------
__fastcall TFormInterface::TFormInterface(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//-----------------------Exported functions----------------------------------
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
bool ExecuteInterface()
{
 TFormInterface *FormInterface=new TFormInterface(Application);
 bool Result=true;
 FormInterface->ShowModal();
 if(FormInterface)
  delete FormInterface;
 return Result;
}
//---------------------------------------------------------------------------
void SendParameters(TAParams *Params)
{
 PM3000.pm3000_conf_operation(PM3000.instr_ID,Params->Params[0]->Index, 0,
                              Params->Params[1]->Index, Params->Params[14]->Index,
                              Params->Params[15]->Index, Params->Params[2]->Index,
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
 Param->Index=1;
 Param->Values->Add("Fixed");
 Param->Values->Add("Auto");
 Params->Add(Param);

 // Index 15
 Param=new TAParam();
 Param->Name="Average Depth";
 Param->Index=1;
 Param->Values->Add("Auto");
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
 Param->Name="Channel 1";
 Param->Index=0;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Channel 2";
 Param->Index=1;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Channel 3";
 Param->Index=2;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Summation Channel";
 Param->Index=3;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Neutral Channel";
 Param->Index=4;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Fundamentals";
 Param->Index=5;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Watts";
 Param->Index=6;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="VA";
 Param->Index=7;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="VAr";
 Param->Index=8;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Vrms";
 Param->Index=9;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Arms";
 Param->Index=10;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Powerfactor";
 Param->Index=11;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Vpk";
 Param->Index=12;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Apk";
 Param->Index=13;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Voltage Crestfactor";
 Param->Index=14;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Current Crestfactor";
 Param->Index=15;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Impedance";
 Param->Index=16;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="VTHD";
 Param->Index=17;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="ATHD";
 Param->Index=18;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Frequency";
 Param->Index=19;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Voltage Harmonics";
 Param->Index=20;
 Param->Group=0;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Current Harmonics";
 Param->Index=21;
 Param->Group=0;
 Params->Add(Param);

 // Second Group:
 Param=new TAParam();
 Param->Name="Channel 1";
 Param->Index=0;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Channel 2";
 Param->Index=1;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Channel 3";
 Param->Index=2;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Summation Channel";
 Param->Index=3;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Neutral Channel";
 Param->Index=4;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Fundamentals";
 Param->Index=5;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Watts";
 Param->Index=6;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="VA";
 Param->Index=7;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="VAr";
 Param->Index=8;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Vrms";
 Param->Index=9;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Arms";
 Param->Index=10;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Powerfactor";
 Param->Index=11;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Vpk";
 Param->Index=12;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Apk";
 Param->Index=13;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Voltage Crestfactor";
 Param->Index=14;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Current Crestfactor";
 Param->Index=15;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Impedance";
 Param->Index=16;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="VTHD";
 Param->Index=17;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="ATHD";
 Param->Index=18;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Frequency";
 Param->Index=19;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Voltage Harmonics";
 Param->Index=20;
 Param->Group=1;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Current Harmonics";
 Param->Index=21;
 Param->Group=1;
 Params->Add(Param);



 // Third Group:
 Param=new TAParam();
 Param->Name="Watts";
 Param->Index=0;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="VA";
 Param->Index=1;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="VAr";
 Param->Index=2;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Volts";
 Param->Index=3;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Amps";
 Param->Index=4;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="PF";
 Param->Index=5;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Impedance";
 Param->Index=6;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Voltage Harmonic";
 Param->Index=7;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Current Harmonic";
 Param->Index=8;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Voltage Harmonic Angle";
 Param->Index=9;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Current Harmonic Angle";
 Param->Index=10;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Efficiency";
 Param->Index=11;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Watt-Hrs";
 Param->Index=12;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="VA-Hrs";
 Param->Index=13;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="VAr-Hrs";
 Param->Index=14;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="A-Hrs";
 Param->Index=15;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Average PF";
 Param->Index=16;
 Param->Group=2;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Corr VAr";
 Param->Index=17;
 Param->Group=2;
 Params->Add(Param);

 // Forth Group:
 Param=new TAParam();
 Param->Name="Watts";
 Param->Index=0;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="VA";
 Param->Index=1;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="VAr";
 Param->Index=2;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Vrms";
 Param->Index=3;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Arms";
 Param->Index=4;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Powerfactor";
 Param->Index=5;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Vpk";
 Param->Index=6;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Apk";
 Param->Index=7;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="VCF";
 Param->Index=8;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="ACF";
 Param->Index=9;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Impedance";
 Param->Index=10;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="VTHD";
 Param->Index=11;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="ATHD";
 Param->Index=12;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Frequency";
 Param->Index=13;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Voltage Harmonic";
 Param->Index=14;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Current Harmonic";
 Param->Index=15;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Voltage Harmonic Angle";
 Param->Index=16;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Current Harmonic Angle";
 Param->Index=17;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Efficiency";
 Param->Index=18;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Watt-Hrs";
 Param->Index=19;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="VA-Hrs";
 Param->Index=20;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="VAr-Hrs";
 Param->Index=21;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="A-Hrs";
 Param->Index=22;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Average PF";
 Param->Index=23;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Integrator Time";
 Param->Index=24;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Volts DC";
 Param->Index=25;
 Param->Group=3;
 Params->Add(Param);

 Param=new TAParam();
 Param->Name="Amps DC";
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
//-------------------Interface methods---------------------------------------
//---------------------------------------------------------------------------

void __fastcall TFormInterface::FormCreate(TObject *Sender)
{
 OutParams=new TAParams();
 GetDeviceOutParameters(OutParams);
 for(int i=0;i<OutParams->Count;i++)
  {
   switch(OutParams->Params[i]->Group)
    {
     case 0:
      {
       ComboBox1->Items->Add(OutParams->Params[i]->Name);
       break;
      }
     case 1:
      {
       ComboBox2->Items->Add(OutParams->Params[i]->Name);
       break;
      }
     case 2:
      {
       ComboBox3->Items->Add(OutParams->Params[i]->Name);
       break;
      }
    }
  }

 InParams=new TAParams();
 GetDeviceInParameters(InParams);

 ANewMeasureExecute(this);
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::FormDestroy(TObject *Sender)
{
 if(OutParams)
  delete OutParams;
 if(InParams)
  delete InParams;
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::ComboBox1Change(TObject *Sender)
{
 TComboBox *pComboBox=(TComboBox *)Sender;
 if(pComboBox)
  {
   AnsiString S=pComboBox->Items->Strings[pComboBox->ItemIndex];
   if(ListBox1->Items->IndexOf(S)<=-1)
    {
     ListBox1->Items->Add(S);
     ComboBox4->Items->Add(S);
    }

   switch(pComboBox->Tag)
    {
     case 0:
      {
       PM3000.pm3000_conf_meas_select_list(PM3000.instr_ID,0,pComboBox->ItemIndex);
       break;
      }
     case 1:
      {
       break;
      }
     case 2:
      {
       break;
      }
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::Measure()
{
/*
 // First Group
 float Back_Data_Array[1024];
 int Back_Size;
 int Error=PM3000.pm3000_meas_read_back_data(PM3000.instr_ID,1,100,1,Back_Data_Array,Back_Size);
 if(Error!=0)
  PM3000.gpiberr("Error Read BackGround Data");

 // Storing in the database
 int k=0;
 double Back_Value;
 for(int i=0;i<ComboBox1->Items->Count;i++)
  {
   AnsiString Name=ComboBox1->Items->Strings[i];
   if(ListBox1->Items->IndexOf(Name)>=0)
    {
     // ListBox2->Items->Add(FloatToStr(Back_Data_Array[k]));
     if(ComboBox4->Text==Name)
      Back_Value=Back_Data_Array[k];
     k++;
    }
  }

 // Second Group
 float Fore_Data_Array[1024];
 int Fore_Size;
 Error=PM3000.pm3000_meas_read_fore_data (PM3000.instr_ID, 1, Fore_Data_Array, Fore_Size);
 if(Error!=0)
  PM3000.gpiberr("Error Read ForeGround Data");

 // Storing in the database
 k=0;
 double Fore_Value;
 for(i=0;i<ComboBox2->Items->Count;i++)
  {
   Name=ComboBox2->Items->Strings[i];
   if(ListBox1->Items->IndexOf(Name)>=0)
    {
     // ListBox2->Items->Add(FloatToStr(Fore_Data_Array[k]));
     if(ComboBox4->Text==Name)
      Fore_Value=Fore_Data_Array[k];
     k++;
    }
  }

 // Third Group
 float fun_value;//return just one value
 Error=PM3000.pm3000_meas_read_fund_data (PM3000.instr_ID, 1, 3, fun_value);
 //Here we choice chan=1: channel 1, fundamental function=3: Volt
 //fundamental function value must link with index of selected item in ComboBox3
 if(Error!=0)
  PM3000.gpiberr("Error Read Fundamental Function Data");
*/

 double Value=random(100);

 // Display performance graph
 if(CheckBox1->Checked)
  {
   PerformanceGraph1->DataPoint(clRed,Value);
   PerformanceGraph1->Update();
   Panel12->Caption=String(Value)+" %";
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInterface::BitBtn3Click(TObject *Sender)
{
 Measure();
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::Timer1Timer(TObject *Sender)
{
 SysTime=Time()+Date();

 if(SysTime>=StartTime)
  {
   StatusBar1->Panels->Items[0]->Text="Measuring ...";
   ProgressCount++;
   CGauge1->Progress=float(ProgressCount)*100.0/float(ProgressInterval);

   if(SysTime>=EndTime)
    {
     Timer1->Enabled=false;
     StatusBar1->Panels->Items[0]->Text="Measure time finished successfully ...";
     return;
    }
    
   // Read measure And Store in Database
   Measure();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::BitBtn4Click(TObject *Sender)
{
 DateTimePicker1->Date=0;
 DateTimePicker2->Time=0;
 StartTime=DateTimePicker1->Time+DateTimePicker2->Date;

 DateTimePicker3->Date=0;
 DateTimePicker4->Time=0;
 EndTime=DateTimePicker3->Time+DateTimePicker4->Date;

 if(EndTime<=StartTime)
  {
   MessageDlg("Start time must be less than end time ...!",mtError,TMsgDlgButtons()<<mbOK,0);
   return;
  }

 ProgressCount=0;
 TDateTime D=EndTime-StartTime;
 Word h,m,s,ms;
 D.DecodeTime(&h,&m,&s,&ms);
// MessageBox(0,(IntToStr(h)+':'+IntToStr(m)+':'+IntToStr(s)+':'+IntToStr(ms)).c_str(),"",0);
 DWORD I=1000*(h*60*60+m*60+s)+ms;
 DWORD TI=1000*(CSpinEdit1->Value*60*60+CSpinEdit2->Value*60+CSpinEdit3->Value)+CSpinEdit4->Value;
 ProgressInterval=float(I)/float(TI);

 Timer1->Interval=TI;
 Timer1->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::Timer2Timer(TObject *Sender)
{
 Panel2->Caption=Date().DateString()+"  "+Time().TimeString();        
}
//---------------------------------------------------------------------------



void __fastcall TFormInterface::AMeasureExecute(TObject *Sender)
{
//        
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::ANewMeasureExecute(TObject *Sender)
{
 ListBox1->Clear();
 ComboBox4->Clear();

 DateTimePicker1->Time=Time();
 DateTimePicker2->Date=Date();

 DateTimePicker3->Time=Time();
 DateTimePicker4->Date=Date();

 CGauge1->Progress=0;

 // Clear Select Lists
 PM3000.pm3000_conf_meas_select_list(PM3000.instr_ID,1,0);
}
//---------------------------------------------------------------------------

