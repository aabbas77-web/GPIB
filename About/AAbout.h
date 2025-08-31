//---------------------------------------------------------------------------

#ifndef AAboutH
#define AAboutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TFormAAbout : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TImage *Image1;
        void __fastcall Image1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormAAbout(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormAAbout *FormAAbout;
//---------------------------------------------------------------------------
#endif
