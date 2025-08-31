//---------------------------------------------------------------------------
#ifndef ConfigH
#define ConfigH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
const AnsiString ConfigName="GPIB.ini";
//---------------------------------------------------------------------------
class TFormConfig : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TPanel *Panel2;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TEdit *EditSessions;
        TLabel *Label2;
        TEdit *EditSettings;
        TLabel *Label3;
        TEdit *EditResults;
        TLabel *Label4;
        TEdit *EditDLLs;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormConfig(TComponent* Owner);
        void __fastcall LoadConfig();
        void __fastcall SaveConfig();
        AnsiString AppPath;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormConfig *FormConfig;
//---------------------------------------------------------------------------
#endif
