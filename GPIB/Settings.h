//---------------------------------------------------------------------------

#ifndef SettingsH
#define SettingsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormSettings : public TForm
{
__published:	// IDE-managed Components
        TRichEdit *RichEdit1;
        TPanel *Panel1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
private:	// User declarations
public:		// User declarations
        __fastcall TFormSettings(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSettings *FormSettings;
//---------------------------------------------------------------------------
#endif
