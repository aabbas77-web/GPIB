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
#include "Measure.h"
//---------------------------------------------------------------------------
#include <Grids.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "CSPIN.h"
#include "CGAUGES.h"
#include <ActnList.hpp>
#include <Menus.hpp>
#include "PERFGRAP.h"
#include <Dialogs.hpp>
#include <ImgList.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <Chart.hpp>
#include <DBChart.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
//---------------------------------------------------------------------------
class TFormInterface : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer1;
        TTimer *Timer2;
        TActionList *ActionList1;
        TAction *AMeasure;
        TAction *ANewMeasure;
        TAction *AClose;
        TMainMenu *MainMenu1;
        TMenuItem *Measure1;
        TMenuItem *NewMeasure1;
        TMenuItem *N1;
        TMenuItem *Close1;
        TPopupMenu *PopupMenu1;
        TMenuItem *Delete1;
        TMenuItem *DeleteAll1;
        TSaveDialog *SaveDialog1;
        TImageList *ImageList1;
        TTable *Table1;
        TStatusBar *StatusBar1;
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
        TBitBtn *BitBtn1;
        TPanel *Panel8;
        TPanel *Panel9;
        TLabel *Label5;
        TComboBox *ComboBox4;
        TCheckBox *CheckBox1;
        TPanel *Panel12;
        TPanel *Panel11;
        TPanel *Panel13;
        TLabel *Label6;
        TEdit *Edit1;
        TGroupBox *GroupBox5;
        TRichEdit *RichEdit1;
        TDBChart *DBChart1;
        TLineSeries *Series1;
        TCSpinEdit *CSpinEdit5;
        TLabel *Label7;
        TComboBox *ComboBox5;
        TPanel *Panel10;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall BitBtn4Click(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
        void __fastcall AMeasureExecute(TObject *Sender);
        void __fastcall ANewMeasureExecute(TObject *Sender);
	void __fastcall Delete1Click(TObject *Sender);
	void __fastcall DeleteAll1Click(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall ACloseExecute(TObject *Sender);
        void __fastcall CSpinEdit5Change(TObject *Sender);
        void __fastcall ComboBox3Change(TObject *Sender);
        void __fastcall ComboBox5Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormInterface(TComponent* Owner);
        void __fastcall Init();
        void __fastcall Measure(TStringList *List);
	void __fastcall CreateTable(AnsiString Path,AnsiString TableName);
	void __fastcall Stop();
        void __fastcall Plot(float AX,float AY);
        void __fastcall ListBoxChanged();
        void __fastcall EnableControls(bool Etat);

        // DLL Definitions
        TPM3000 PM3000;
        TAParams *InParams;
        TAParams *OutParams;
	TMeasures *Measures;

        // Interface Definitions
        TDateTime StartTime,EndTime,SysTime;
        float StartT,StartM,EndT;
        AnsiString Path,TableName;
        bool IsFirst;
        int PointCount;
        bool IsSingle;

        float A,B,X,Y,TStart,TEnd;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormInterface *FormInterface;
//---------------------------------------------------------------------------
#endif
