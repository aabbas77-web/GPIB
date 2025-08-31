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
#include "UOP7907.h"
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
const float PI=3.1415926535897932384626433832795;
//---------------------------------------------------------------------------
class TFormInterface : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer1;
        TTimer *Timer2;
        TActionList *ActionList1;
        TAction *AFile;
        TAction *ASin;
        TAction *AClose;
        TMainMenu *MainMenu1;
        TMenuItem *Measure1;
        TMenuItem *NewMeasure1;
        TMenuItem *N1;
        TMenuItem *Close1;
        TSaveDialog *SaveDialog1;
        TImageList *ImageList1;
        TStatusBar *StatusBar1;
        TPanel *Panel6;
        TPanel *Panel3;
        TPanel *Panel4;
        TCGauge *CGauge1;
        TPanel *Panel5;
        TPanel *Panel2;
        TPanel *Panel7;
        TGroupBox *GroupBox4;
        TBitBtn *BitBtn3;
        TPanel *Panel8;
        TPanel *Panel9;
        TCheckBox *CheckBox1;
        TPanel *Panel12;
        TDBChart *DBChart1;
        TLineSeries *Series1;
        TCSpinEdit *CSpinEdit5;
        TLabel *Label7;
        TPanel *Panel10;
        TEdit *Edit2;
        TEdit *Edit3;
        TButton *Button1;
        TButton *Button2;
        TNotebook *Notebook1;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TEdit *Edit1;
        TLabel *Label2;
        TEdit *Edit4;
        TLabel *Label3;
        TEdit *Edit5;
        TBitBtn *BitBtn4;
        TBitBtn *BitBtn1;
        TAction *ASegments;
        TMenuItem *Segments1;
        TGroupBox *GroupBox5;
        TPanel *Panel1;
        TImage *Image1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn5;
        TPanel *Panel11;
        TOpenDialog *OpenDialog1;
        TPanel *Panel13;
        TGroupBox *GroupBox3;
        TCSpinEdit *CSpinEdit1;
        TGroupBox *GroupBox2;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TCSpinEdit *CSpinEdit2;
        TCSpinEdit *CSpinEdit3;
        TCSpinEdit *CSpinEdit4;
        TGroupBox *GroupBox6;
        TDateTimePicker *DateTimePicker1;
        TDateTimePicker *DateTimePicker2;
        TGroupBox *GroupBox7;
        TCSpinEdit *CSpinEdit6;
        TBitBtn *BitBtn6;
        TEdit *Edit6;
        TLabel *Label8;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
        void __fastcall AFileExecute(TObject *Sender);
        void __fastcall ASinExecute(TObject *Sender);
        void __fastcall ACloseExecute(TObject *Sender);
        void __fastcall CSpinEdit5Change(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Image1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall ASegmentsExecute(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall BitBtn5Click(TObject *Sender);
        void __fastcall BitBtn6Click(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall BitBtn4Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall CSpinEdit6Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormInterface(TComponent* Owner);
        void __fastcall Plot(float AX,float AY);
        void __fastcall Divide(TPoint P1,TPoint P2,float Step,TStringList *List);
	void __fastcall Stop();
        void __fastcall DivideSin(float A,float B,float C,float Step,TStringList *List);

        // DLL Definitions
        TUOP7907 UOP7907;
        TAParams *InParams;
        TAParams *OutParams;
	TMeasures *Measures;

        // Interface Definitions
        int PointCount;

        TDateTime StartTime,SysTime;
        float StartT,StartM,EndT;

        float A,B,X,Y,TStart,TEnd;
        bool IsFirst;

        TPoint P1,P2;
        bool Clicked,FirstClick;
        int NY,RepeatCount;
        float TimeStep;
        TStringList *List,*ListOpen;

        float VoltScale;
        int PointNo;

        float VoltLimit;
        float Y0;
        float time;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormInterface *FormInterface;
//---------------------------------------------------------------------------
#endif
