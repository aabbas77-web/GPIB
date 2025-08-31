//---------------------------------------------------------------------------

#ifndef SingleH
#define SingleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormSingle : public TForm
{
__published:	// IDE-managed Components
        TRichEdit *RichEdit1;
        TPanel *Panel1;
        TBitBtn *BitBtn1;
private:	// User declarations
public:		// User declarations
        __fastcall TFormSingle(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSingle *FormSingle;
//---------------------------------------------------------------------------
#endif
