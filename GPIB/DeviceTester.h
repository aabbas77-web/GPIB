//---------------------------------------------------------------------------

#ifndef DeviceTesterH
#define DeviceTesterH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include "Device.h"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------
class TFormDeviceTester : public TForm
{
__published:	// IDE-managed Components
        TOpenDialog *OpenDialog1;
        TRichEdit *RichEdit1;
        TSaveDialog *SaveDialog1;
        TPanel *Panel1;
        TToolBar *ToolBar1;
        TToolButton *ToolButton1;
        TToolButton *ToolButton2;
        TToolButton *ToolButton3;
        TToolButton *ToolButton4;
        TToolButton *ToolButton5;
        void __fastcall ToolButton1Click(TObject *Sender);
        void __fastcall ToolButton2Click(TObject *Sender);
        void __fastcall ToolButton3Click(TObject *Sender);
        void __fastcall ToolButton4Click(TObject *Sender);
        void __fastcall ToolButton5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormDeviceTester(TComponent* Owner);
        AnsiString FileName;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDeviceTester *FormDeviceTester;
//---------------------------------------------------------------------------
#endif
 