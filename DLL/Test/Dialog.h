//---------------------------------------------------------------------------

#ifndef DialogH
#define DialogH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFormDialog : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TEdit *Edit1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
private:	// User declarations
public:		// User declarations
        __fastcall TFormDialog(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDialog *FormDialog;
//---------------------------------------------------------------------------
#endif
