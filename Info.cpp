//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Info.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormInfo *FormInfo;
//---------------------------------------------------------------------------
__fastcall TFormInfo::TFormInfo(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormInfo::FormActivate(TObject *Sender)
{
 for(int j=0;j<FormMain->Session->Count;j++)
  FormMain->Session->Devices[j]->GetMeasures();

 RichEdit1->Visible=false;
 RichEdit1->Clear();

 RichEdit1->Lines->Add(" ");
 RichEdit1->Paragraph->Numbering=nsNone;
 RichEdit1->Paragraph->Alignment=taCenter;
 RichEdit1->DefAttributes->Color=clNavy;
 RichEdit1->DefAttributes->Size=20;
 RichEdit1->DefAttributes->Style.Clear();
 RichEdit1->DefAttributes->Style=TFontStyles()<<fsBold<<fsUnderline;
 RichEdit1->Lines->Add("Session Informations");
 RichEdit1->Paragraph->Numbering=nsNone;

 RichEdit1->Lines->Add(" ");
 RichEdit1->Paragraph->Numbering=nsNone;
 RichEdit1->Paragraph->Alignment=taLeftJustify;
 RichEdit1->DefAttributes->Color=clRed;
 RichEdit1->DefAttributes->Size=18;
 RichEdit1->DefAttributes->Style.Clear();
 RichEdit1->DefAttributes->Style=TFontStyles()<<fsBold<<fsUnderline;
 RichEdit1->Lines->Add("Devices: ");
 RichEdit1->Paragraph->Numbering=nsNone;

 // [Device 1..n]
 for(int i=0;i<FormMain->Session->Count;i++)
  {
   AnsiString DeviceName=FormMain->Session->Devices[i]->DeviceName;

   RichEdit1->Paragraph->Numbering=nsNone;
   RichEdit1->Paragraph->Alignment=taLeftJustify;
   RichEdit1->DefAttributes->Color=clGreen;
   RichEdit1->DefAttributes->Size=18;
   RichEdit1->DefAttributes->Style.Clear();
   RichEdit1->DefAttributes->Style=TFontStyles()<<fsBold<<fsUnderline;
   RichEdit1->Lines->Add(DeviceName);

   RichEdit1->Paragraph->Numbering=nsNone;
   RichEdit1->Paragraph->Alignment=taLeftJustify;
   RichEdit1->DefAttributes->Color=clBlack;
   RichEdit1->DefAttributes->Size=14;
   RichEdit1->DefAttributes->Style.Clear();
   RichEdit1->DefAttributes->Style=TFontStyles()>>fsBold>>fsUnderline;
   RichEdit1->Lines->Add("Device Name: "+DeviceName);
   RichEdit1->Lines->Add("Device Address: "+IntToStr(FormMain->Session->Devices[i]->DeviceAddress));
   RichEdit1->Lines->Add("Device Extension: "+FormMain->Session->Devices[i]->DeviceExtention);
   RichEdit1->Lines->Add("Device Filter: "+FormMain->Session->Devices[i]->DeviceFilter);
   RichEdit1->Lines->Add("DLL Name: "+FormMain->Session->Devices[i]->DeviceDLL);
   RichEdit1->Lines->Add("Setting File: "+FormMain->Session->Devices[i]->InParams->FileName);

   // Save measure informations
   RichEdit1->Lines->Add(" ");
   RichEdit1->Paragraph->Numbering=nsNone;
   RichEdit1->Paragraph->Alignment=taLeftJustify;
   RichEdit1->DefAttributes->Color=clBlue;
   RichEdit1->DefAttributes->Size=16;
   RichEdit1->DefAttributes->Style.Clear();
   RichEdit1->DefAttributes->Style=TFontStyles()<<fsBold<<fsUnderline;
   RichEdit1->Lines->Add("Measures: ");
   RichEdit1->Paragraph->Numbering=nsNone;

   for(int j=0;j<FormMain->Session->Devices[i]->Measures->Count;j++)
    {
     AnsiString Title=FormMain->Session->Devices[i]->Measures->Measures[j]->Title;

     RichEdit1->Paragraph->Numbering=nsNone;
     RichEdit1->Paragraph->Alignment=taLeftJustify;
     RichEdit1->DefAttributes->Color=clMaroon;
     RichEdit1->DefAttributes->Size=16;
     RichEdit1->DefAttributes->Style.Clear();
     RichEdit1->DefAttributes->Style=TFontStyles()<<fsBold<<fsUnderline;
     RichEdit1->Lines->Add(Title);

     RichEdit1->Paragraph->Numbering=nsNone;
     RichEdit1->Paragraph->Alignment=taLeftJustify;
     RichEdit1->DefAttributes->Color=clBlack;
     RichEdit1->DefAttributes->Size=14;
     RichEdit1->DefAttributes->Style.Clear();
     RichEdit1->DefAttributes->Style=TFontStyles()>>fsBold>>fsUnderline;
     RichEdit1->Lines->Add("Measure Title: "+Title);
     RichEdit1->Lines->Add("Measure FileName: "+FormMain->Session->Devices[i]->Measures->Measures[j]->FileName);
     RichEdit1->Lines->Add("Measure Start Time: "+TimeToStr(FormMain->Session->Devices[i]->Measures->Measures[j]->StartTime));
     RichEdit1->Lines->Add("Measure End Time: "+TimeToStr(FormMain->Session->Devices[i]->Measures->Measures[j]->EndTime));

     AnsiString SInterval="";
     SInterval+=IntToStr(FormMain->Session->Devices[i]->Measures->Measures[j]->Interval.wHour)+":"+
                IntToStr(FormMain->Session->Devices[i]->Measures->Measures[j]->Interval.wMinute)+":"+
                IntToStr(FormMain->Session->Devices[i]->Measures->Measures[j]->Interval.wSecond)+":"+
                IntToStr(FormMain->Session->Devices[i]->Measures->Measures[j]->Interval.wMilliseconds);
     RichEdit1->Lines->Add("Measure Interval: "+SInterval);


     RichEdit1->Lines->Add(" ");
     RichEdit1->Paragraph->Numbering=nsNone;
     RichEdit1->Paragraph->Alignment=taLeftJustify;
     RichEdit1->DefAttributes->Color=clTeal;
     RichEdit1->DefAttributes->Size=14;
     RichEdit1->DefAttributes->Style.Clear();
     RichEdit1->DefAttributes->Style=TFontStyles()<<fsBold<<fsUnderline;
     RichEdit1->Lines->Add("Parameters: ");
     RichEdit1->Paragraph->Numbering=nsNone;

     RichEdit1->Paragraph->Numbering=nsNone;
     RichEdit1->Paragraph->Alignment=taLeftJustify;
     RichEdit1->DefAttributes->Color=clBlack;
     RichEdit1->DefAttributes->Size=14;
     RichEdit1->DefAttributes->Style.Clear();
     RichEdit1->DefAttributes->Style=TFontStyles()>>fsBold>>fsUnderline;
     for(int k=0;k<FormMain->Session->Devices[i]->Measures->Measures[j]->Params->Count;k++)
      RichEdit1->Lines->Add(FormMain->Session->Devices[i]->Measures->Measures[j]->Params->Strings[k]);

     RichEdit1->Lines->Add(" ");
     RichEdit1->Paragraph->Numbering=nsNone;
     RichEdit1->Paragraph->Alignment=taLeftJustify;
     RichEdit1->DefAttributes->Color=clTeal;
     RichEdit1->DefAttributes->Size=14;
     RichEdit1->DefAttributes->Style.Clear();
     RichEdit1->DefAttributes->Style=TFontStyles()<<fsBold<<fsUnderline;
     RichEdit1->Lines->Add("Comments: ");
     RichEdit1->Paragraph->Numbering=nsNone;

     RichEdit1->Paragraph->Numbering=nsNone;
     RichEdit1->Paragraph->Alignment=taLeftJustify;
     RichEdit1->DefAttributes->Color=clBlack;
     RichEdit1->DefAttributes->Size=14;
     RichEdit1->DefAttributes->Style.Clear();
     RichEdit1->DefAttributes->Style=TFontStyles()>>fsBold>>fsUnderline;
     for(int k=0;k<FormMain->Session->Devices[i]->Measures->Measures[j]->Comments->Count;k++)
      RichEdit1->Lines->Add(FormMain->Session->Devices[i]->Measures->Measures[j]->Comments->Strings[k]);
    }
  }

 RichEdit1->Paragraph->Numbering=nsNone;
 RichEdit1->Paragraph->Alignment=taCenter;
 RichEdit1->DefAttributes->Color=clNavy;
 RichEdit1->DefAttributes->Size=20;
 RichEdit1->DefAttributes->Style.Clear();
 RichEdit1->DefAttributes->Style=TFontStyles()<<fsBold;
 RichEdit1->Lines->Add("------------------------------------");

 RichEdit1->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TFormInfo::AInformationExecute(TObject *Sender)
{
//        
}
//---------------------------------------------------------------------------

void __fastcall TFormInfo::ASaveExecute(TObject *Sender)
{
 if(SaveDialog1->Execute())
  {
   RichEdit1->Lines->SaveToFile(SaveDialog1->FileName);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormInfo::ACloseExecute(TObject *Sender)
{
 Close();        
}
//---------------------------------------------------------------------------

