//---------------------------------------------------------------------------

#ifndef AddressH
#define AddressH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormAddress : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TPanel *Panel2;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TLabel *Label1;
        TComboBox *ComboBox1;
private:	// User declarations
public:		// User declarations
        __fastcall TFormAddress(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormAddress *FormAddress;
//---------------------------------------------------------------------------
#endif
