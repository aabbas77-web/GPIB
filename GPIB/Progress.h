//---------------------------------------------------------------------------

#ifndef ProgressH
#define ProgressH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormProgress : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TProgressBar *ProgressBar1;
        TLabel *Label1;
private:	// User declarations
public:		// User declarations
        __fastcall TFormProgress(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormProgress *FormProgress;
//---------------------------------------------------------------------------
#endif
