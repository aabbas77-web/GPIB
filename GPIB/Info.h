//---------------------------------------------------------------------------

#ifndef InfoH
#define InfoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
#include "Main.h"
#include <ComCtrls.hpp>
#include <ActnList.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFormInfo : public TForm
{
__published:	// IDE-managed Components
        TActionList *ActionList1;
        TMainMenu *MainMenu1;
        TAction *AInformation;
        TAction *ASave;
        TAction *AClose;
        TMenuItem *AInformation1;
        TMenuItem *Save1;
        TMenuItem *Close1;
        TMenuItem *N1;
        TPanel *Panel1;
        TRichEdit *RichEdit1;
        TSaveDialog *SaveDialog1;
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall AInformationExecute(TObject *Sender);
        void __fastcall ASaveExecute(TObject *Sender);
        void __fastcall ACloseExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormInfo(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormInfo *FormInfo;
//---------------------------------------------------------------------------
#endif
