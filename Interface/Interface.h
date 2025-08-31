//---------------------------------------------------------------------------

#ifndef InterfaceH
#define InterfaceH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
#include "PM3000.h"
#include "decl-32.h"
#include "Params.h"
//---------------------------------------------------------------------------
#include <Grids.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "CSPIN.h"
#include "CGAUGES.h"
#include <ActnList.hpp>
#include <Menus.hpp>
#include "PERFGRAP.h"
//---------------------------------------------------------------------------
class TFormInterface : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer1;
        TTimer *Timer2;
        TStatusBar *StatusBar1;
        TActionList *ActionList1;
        TAction *AMeasure;
        TAction *ANewMeasure;
        TMainMenu *MainMenu1;
        TMenuItem *Measure1;
        TMenuItem *NewMeasure1;
        TPanel *Panel6;
        TPanel *Panel3;
        TPanel *Panel4;
        TCGauge *CGauge1;
        TPanel *Panel5;
        TPanel *Panel2;
        TPanel *Panel7;
        TGroupBox *GroupBox4;
        TComboBox *ComboBox1;
        TComboBox *ComboBox2;
        TComboBox *ComboBox3;
        TListBox *ListBox1;
        TBitBtn *BitBtn3;
        TPanel *Panel1;
        TGroupBox *GroupBox1;
        TDateTimePicker *DateTimePicker1;
        TDateTimePicker *DateTimePicker2;
        TGroupBox *GroupBox2;
        TDateTimePicker *DateTimePicker3;
        TDateTimePicker *DateTimePicker4;
        TGroupBox *GroupBox3;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TCSpinEdit *CSpinEdit1;
        TCSpinEdit *CSpinEdit2;
        TCSpinEdit *CSpinEdit3;
        TCSpinEdit *CSpinEdit4;
        TBitBtn *BitBtn4;
        TPanel *Panel8;
        TPanel *Panel9;
        TLabel *Label5;
        TComboBox *ComboBox4;
        TCheckBox *CheckBox1;
        TPanel *Panel10;
        TPerformanceGraph *PerformanceGraph1;
        TPanel *Panel11;
        TPanel *Panel12;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall BitBtn4Click(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
        void __fastcall AMeasureExecute(TObject *Sender);
        void __fastcall ANewMeasureExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormInterface(TComponent* Owner);
        void __fastcall Measure();
        TPM3000 PM3000;
        TAParams *InParams;
        TAParams *OutParams;
        TDateTime StartTime,EndTime,SysTime;
        DWORD ProgressCount,ProgressInterval;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormInterface *FormInterface;
//---------------------------------------------------------------------------
extern "C" __declspec(dllexport) void DeviceInit(int Address);
extern "C" __declspec(dllexport) void DeviceClose();
extern "C" __declspec(dllexport) bool ExecuteInterface();
extern "C" __declspec(dllexport) void SendParameters(TAParams *Params);
extern "C" __declspec(dllexport) void GetDeviceInParameters(TAParams *Params);
extern "C" __declspec(dllexport) void GetDeviceOutParameters(TAParams *Params);
extern "C" __declspec(dllexport) int  GetDeviceAddress();
extern "C" __declspec(dllexport) char * GetDeviceName();
extern "C" __declspec(dllexport) char * GetDeviceFilter();
extern "C" __declspec(dllexport) char * GetDeviceExtention();
//---------------------------------------------------------------------------
#endif
