//---------------------------------------------------------------------------

#ifndef EditH
#define EditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
#include "Main.h"
//---------------------------------------------------------------------------
class TFormEdit : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TPanel *Panel2;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TLabel *Label1;
        TComboBox *ComboBox1;
        TLabel *Label2;
        TComboBox *ComboBox2;
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormEdit(TComponent* Owner);
        void __fastcall GetValues(AnsiString FileName,AnsiString Param,TStrings *Values);
        void __fastcall GetHeaders(AnsiString FileName,TStrings *Headers);

        bool Changed;
        TStringList *List;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormEdit *FormEdit;
//---------------------------------------------------------------------------
#endif
