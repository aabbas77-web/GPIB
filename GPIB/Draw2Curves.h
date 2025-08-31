//---------------------------------------------------------------------------

#ifndef Draw2CurvesH
#define Draw2CurvesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <DBChart.hpp>
#include <ExtCtrls.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Series.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFormDraw2Curves : public TForm
{
__published:	// IDE-managed Components
        TTable *Table1;
        TPopupMenu *PopupMenu1;
        TMenuItem *Curve11;
        TMenuItem *Curve21;
        TTable *Table2;
        TMenuItem *N1;
        TMenuItem *ShowCurve11;
        TMenuItem *ShowCurve21;
        TDBChart *DBChart1;
        TLineSeries *Series1;
        TLineSeries *Series2;
        void __fastcall Curve11Click(TObject *Sender);
        void __fastcall Curve21Click(TObject *Sender);
        void __fastcall ShowCurve11Click(TObject *Sender);
        void __fastcall ShowCurve21Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormDraw2Curves(TComponent* Owner);
        AnsiString X1Title,X2Title,Y1Title,Y2Title;
        AnsiString X11Title,X21Title,Y11Title,Y21Title;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDraw2Curves *FormDraw2Curves;
//---------------------------------------------------------------------------
#endif
