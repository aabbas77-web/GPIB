//---------------------------------------------------------------------------

#ifndef EditorH
#define EditorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ActnList.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TFormEditor : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TDBGrid *DBGrid1;
	TDBNavigator *DBNavigator1;
	TMainMenu *MainMenu1;
	TActionList *ActionList1;
	TAction *ADatabse;
	TAction *AOpenDatabase;
	TMenuItem *ADatabse1;
	TMenuItem *OpenDatabase1;
	TOpenDialog *OpenDialog1;
	TAction *AClose;
	TMenuItem *N1;
	TMenuItem *Close1;
        TDataSource *DataSource1;
        TTable *Table1;
        TAction *AExport;
        TMenuItem *Export1;
        TMenuItem *N2;
        TImageList *ImageList1;
        TSaveDialog *SaveDialog1;
	void __fastcall ADatabseExecute(TObject *Sender);
	void __fastcall AOpenDatabaseExecute(TObject *Sender);
	void __fastcall ACloseExecute(TObject *Sender);
        void __fastcall AExportExecute(TObject *Sender);
        void __fastcall FormDeactivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormEditor(TComponent* Owner);
        AnsiString FileName;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormEditor *FormEditor;
//---------------------------------------------------------------------------
#endif
