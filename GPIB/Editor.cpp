//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Editor.h"
#include "Format.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormEditor *FormEditor;
//---------------------------------------------------------------------------
__fastcall TFormEditor::TFormEditor(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormEditor::ADatabseExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormEditor::AOpenDatabaseExecute(TObject *Sender)
{
 OpenDialog1->Filter="Database Files (*.db)|*.db";
 OpenDialog1->DefaultExt="db";
 if(OpenDialog1->Execute())
  {
   FileName=OpenDialog1->FileName;
   Caption="Database Editor ["+FileName+"]";

   Table1->Active=false;
   Table1->DatabaseName=ExtractFilePath(FileName);
   Table1->TableName=ExtractFileName(FileName);
   Table1->Active=true;

   AExport->Enabled=true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormEditor::ACloseExecute(TObject *Sender)
{
 Close();	
}
//---------------------------------------------------------------------------

void __fastcall TFormEditor::AExportExecute(TObject *Sender)
{
 SaveDialog1->Filter="Text Files (*.txt)|*.txt";
 SaveDialog1->DefaultExt="txt";
 if(SaveDialog1->Execute())
  {
   if(FormFormat->ShowModal()==mrCancel)
    return;
   AnsiString Format=FormFormat->Edit1->Text;

   TStringList *List=new TStringList();

   // Titles
   AnsiString S="",Name="";
   for(int i=0;i<Table1->Fields->Count;i++)
    {
     Name=Table1->Fields->Fields[i]->DisplayName;
     int N=Format.Length()-Name.Length();
     if(N>0)
      {
       for(int i=0;i<N;i++)
        Name+=" ";
      }
     S+=Name+"     ";
    } 
   List->Add(S);

   AnsiString S1="";
   for(int i=0;i<S.Length();i++)
    S1+="-";
   List->Add(S1);

   Table1->First();
   while(!Table1->Eof)
    {
     S="";
     for(int i=0;i<Table1->Fields->Count;i++)
      S+=FormatFloat(Format,Table1->Fields->Fields[i]->AsFloat)+"     ";
     List->Add(S);
     Table1->Next();
    }
   List->Add(S1);
   List->SaveToFile(SaveDialog1->FileName);

   if(List)
    delete List;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormEditor::FormDeactivate(TObject *Sender)
{
 Table1->Active=false;        
}
//---------------------------------------------------------------------------

