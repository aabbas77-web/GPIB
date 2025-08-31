//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Axis.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormAxis *FormAxis;
//---------------------------------------------------------------------------
__fastcall TFormAxis::TFormAxis(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormAxis::FormActivate(TObject *Sender)
{
 ComboBox1->Clear();
 ComboBox2->Clear();

 ComboBox3->Clear();
 ComboBox4->Clear();

 for(int j=0;j<FormMain->Session->Count;j++)
  {
   FormMain->Session->Devices[j]->GetMeasures();
   for(int i=0;i<FormMain->Session->Devices[j]->Measures->Count;i++)
    {
     AnsiString Title=FormMain->Session->Devices[j]->Measures->Measures[i]->Title;
     ComboBox3->Items->Add(Title);
     ComboBox4->Items->Add(Title);
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormAxis::ComboBox3Change(TObject *Sender)
{
 ComboBox1->Clear();
 for(int i=0;i<FormMain->Session->Devices[FormMain->Session->DeviceNo]->Measures->Measures[ComboBox3->ItemIndex]->Params->Count;i++)
  {
   AnsiString Title=FormMain->Session->Devices[FormMain->Session->DeviceNo]->Measures->Measures[ComboBox3->ItemIndex]->Params->Strings[i];
   ComboBox1->Items->Add(Title);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormAxis::ComboBox4Change(TObject *Sender)
{
 ComboBox2->Clear();
 for(int i=0;i<FormMain->Session->Devices[FormMain->Session->DeviceNo]->Measures->Measures[ComboBox4->ItemIndex]->Params->Count;i++)
  {
   AnsiString Title=FormMain->Session->Devices[FormMain->Session->DeviceNo]->Measures->Measures[ComboBox4->ItemIndex]->Params->Strings[i];
   ComboBox2->Items->Add(Title);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormAxis::BitBtn1Click(TObject *Sender)
{
 if(ComboBox3->ItemIndex<=-1)
  return;
 if(ComboBox4->ItemIndex<=-1)
  return;

 XName=ComboBox1->Text;
 XTitle=ComboBox3->Text;        

 YName=ComboBox2->Text;
 YTitle=ComboBox4->Text;

 TTable *TableX=new TTable(this);
 TTable *TableY=new TTable(this);

 AnsiString XTable=FormMain->Session->Devices[FormMain->Session->DeviceNo]->Measures->Measures[ComboBox3->ItemIndex]->FileName;
 TableX->Active=false;
 TableX->DatabaseName=ExtractFilePath(XTable);
 TableX->TableName=ExtractFileName(XTable);
 TableX->Active=true;

 AnsiString YTable=FormMain->Session->Devices[FormMain->Session->DeviceNo]->Measures->Measures[ComboBox4->ItemIndex]->FileName;
 TableY->Active=false;
 TableY->DatabaseName=ExtractFilePath(YTable);
 TableY->TableName=ExtractFileName(YTable);
 TableY->Active=true;

 AnsiString Path=ExtractFilePath(Application->ExeName);
 CreateTable(Path+FormMain->Session->ResultsDir,TableName);

 Table->Active=false;
 Table->DatabaseName=Path+FormMain->Session->ResultsDir;
 Table->TableName=TableName;
 Table->Active=true;

 int Count=min(TableX->RecordCount,TableY->RecordCount);
 for(int i=0;i<Count;i++)
  {
   Table->Append();
   Table->FieldByName("XValues")->Value=TableX->FieldByName(XName)->Value;
   Table->FieldByName("YValues")->Value=TableY->FieldByName(YName)->Value;
   Table->Post();

   TableX->Next();
   TableY->Next();
  }
 Table->Active=false;
 Table->IndexName="XValuesIndex";
 Table->Active=true;
 float OldF=0.0,F;
 while(!Table->Eof)
  {
   F=Table->FieldByName("XValues")->AsFloat;
   if(F==OldF)
    {
     Table->Prior();
     Table->Delete();
     OldF=0.0;
    }
   else
    {
     Table->Next();
     OldF=F;
    }
  }
 Table->Active=false;
 Table->IndexName="XValuesIndex";
 Table->Active=true;

 if(TableX)
  delete TableX;
 if(TableY)
  delete TableY;
}
//---------------------------------------------------------------------------

void __fastcall TFormAxis::BitBtn2Click(TObject *Sender)
{
 Close();        
}
//---------------------------------------------------------------------------
void __fastcall TFormAxis::CreateTable(AnsiString Path,AnsiString TableName)
{
 TTable *Table=new TTable(this);

// if(FileExists(Path+TableName))
//  DeleteFile(Path+TableName);

 // Deactivate the table before changing its database name
 Table->Active=false;
 Table->DatabaseName=Path;

 // Determine table type
 Table->TableType=ttParadox;
 Table->TableName=TableName;

 // Define Fields
 Table->FieldDefs->Clear();
 TFieldDef *pNewDef;

 pNewDef=Table->FieldDefs->AddFieldDef();
 pNewDef->Name="No";
 pNewDef->DataType=ftAutoInc;

 pNewDef=Table->FieldDefs->AddFieldDef();
 pNewDef->Name="XValues";
 pNewDef->DataType=ftFloat;

 pNewDef=Table->FieldDefs->AddFieldDef();
 pNewDef->Name="YValues";
 pNewDef->DataType=ftFloat;

 // Define Indexs
 Table->IndexDefs->Clear();
 // The first index needn`t to determine its name because it is primary index
 Table->IndexDefs->Add("","No",TIndexOptions()<<ixPrimary<<ixUnique);
 Table->IndexDefs->Add("XValuesIndex","XValues",TIndexOptions()<<ixCaseInsensitive);

 // Create the table
 Table->CreateTable();

 if(Table)
  delete Table;
} 
//---------------------------------------------------------------------------

void __fastcall TFormAxis::FormCreate(TObject *Sender)
{
 Table=new TTable(this);        
}
//---------------------------------------------------------------------------

void __fastcall TFormAxis::FormDestroy(TObject *Sender)
{
 if(Table)
  delete Table;        
}
//---------------------------------------------------------------------------

