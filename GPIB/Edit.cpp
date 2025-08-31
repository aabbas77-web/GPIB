//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Edit.h"
#include "Settings.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormEdit *FormEdit;
//---------------------------------------------------------------------------
__fastcall TFormEdit::TFormEdit(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormEdit::ComboBox1Change(TObject *Sender)
{
 ComboBox2->Items->Clear();
 for(int i=0;i<FormMain->Session->Devices[FormMain->Session->DeviceNo]->InParams->Params[ComboBox1->ItemIndex]->Values->Count;i++)
  ComboBox2->Items->Add(FormMain->Session->Devices[FormMain->Session->DeviceNo]->InParams->Params[ComboBox1->ItemIndex]->Values->Strings[i]);
 ComboBox2->ItemIndex=0;
}
//---------------------------------------------------------------------------

void __fastcall TFormEdit::BitBtn2Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormEdit::FormActivate(TObject *Sender)
{
 Changed=false;
 List->Clear();

 ComboBox1->Items->Clear();
 for(int i=0;i<FormMain->Session->Devices[FormMain->Session->DeviceNo]->InParams->Count;i++)
  ComboBox1->Items->Add(FormMain->Session->Devices[FormMain->Session->DeviceNo]->InParams->Params[i]->Name);

 ComboBox1->ItemIndex=0;
 ComboBox2->ItemIndex=FormMain->Session->Devices[FormMain->Session->DeviceNo]->InParams->Params[ComboBox1->ItemIndex]->Index;
 ComboBox1Change(this);
 ComboBox1->ItemIndex=0;
 ComboBox2->ItemIndex=FormMain->Session->Devices[FormMain->Session->DeviceNo]->InParams->Params[ComboBox1->ItemIndex]->Index;
}
//---------------------------------------------------------------------------

void __fastcall TFormEdit::BitBtn1Click(TObject *Sender)
{
 if(ComboBox2->ItemIndex>=0)
  {
   FormMain->Session->Devices[FormMain->Session->DeviceNo]->InParams->Params[ComboBox1->ItemIndex]->Index=ComboBox2->ItemIndex;
   Changed=true;

   for(int i=0;i<List->Count;i++)
    {
     if(List->Strings[i].Pos(ComboBox1->Text)>=1)
      {
       List->Delete(i);
       break;
      }
    }
   List->Add(ComboBox1->Text+" : "+ComboBox2->Text);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormEdit::FormClose(TObject *Sender, TCloseAction &Action)
{
 if(Changed)
  {
   FormSettings->RichEdit1->Clear();
   FormSettings->RichEdit1->Lines->Add("Modified Parameters:");
   FormSettings->RichEdit1->Lines->Add("-------------------------------------");
   for(int i=0;i<List->Count;i++)
    FormSettings->RichEdit1->Lines->Add(IntToStr(i+1)+"- "+List->Strings[i]);
   FormSettings->RichEdit1->Lines->Add("-------------------------------------");

   if(FormSettings->ShowModal()==mrOk)
    {
     Action=caHide;
    }
   else
    {
     Action=caNone;
     int I=FormSettings->RichEdit1->Lines->Count;
     FormSettings->RichEdit1->Lines->Delete(I-1);
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormEdit::FormCreate(TObject *Sender)
{
 List=new TStringList();
}
//---------------------------------------------------------------------------


