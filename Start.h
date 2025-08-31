//---------------------------------------------------------------------------

#ifndef StartH
#define StartH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TFormStart : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TImage *Image1;
private:	// User declarations
public:		// User declarations
        __fastcall TFormStart(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormStart *FormStart;
//---------------------------------------------------------------------------
#endif
