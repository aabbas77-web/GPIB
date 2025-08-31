//---------------------------------------------------------------------------

#ifndef AxisH
#define AxisH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFormAxis : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TGroupBox *GroupBox1;
        TComboBox *ComboBox1;
        TComboBox *ComboBox3;
        TLabel *Label1;
        TLabel *Label3;
        TGroupBox *GroupBox2;
        TLabel *Label2;
        TLabel *Label4;
        TComboBox *ComboBox2;
        TComboBox *ComboBox4;
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall ComboBox3Change(TObject *Sender);
        void __fastcall ComboBox4Change(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormAxis(TComponent* Owner);
        void __fastcall CreateTable(AnsiString Path,AnsiString TableName);
        AnsiString XName,XTitle,YName,YTitle;
        TTable *Table;
        AnsiString TableName;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormAxis *FormAxis;
//---------------------------------------------------------------------------
#endif
