//---------------------------------------------------------------------------

#ifndef GraphH
#define GraphH
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
#include <Menus.hpp>
#include <Series.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
//---------------------------------------------------------------------------
class TFormGraph : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TSplitter *Splitter1;
	TPanel *Panel3;
	TPanel *Panel4;
	TSplitter *Splitter2;
	TPanel *Panel5;
	TPanel *Panel6;
	TSplitter *Splitter3;
	TPanel *Panel7;
	TDBChart *DBChart1;
	TDBChart *DBChart2;
	TDBChart *DBChart3;
	TDBChart *DBChart4;
	TPopupMenu *PopupMenu1;
	TMenuItem *Edit1;
        TLineSeries *Series1;
        TLineSeries *Series2;
        TTable *Table1;
        TTable *Table2;
        TTable *Table3;
        TTable *Table4;
        TPopupMenu *PopupMenu2;
        TPopupMenu *PopupMenu3;
        TPopupMenu *PopupMenu4;
        TMenuItem *Edit2;
        TMenuItem *Edit3;
        TMenuItem *Edit4;
        TLineSeries *Series3;
        TLineSeries *Series4;
        void __fastcall Edit1Click(TObject *Sender);
        void __fastcall Edit2Click(TObject *Sender);
        void __fastcall Edit3Click(TObject *Sender);
        void __fastcall Edit4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormGraph(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormGraph *FormGraph;
//---------------------------------------------------------------------------
#endif
