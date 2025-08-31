//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DeviceTester.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormDeviceTester *FormDeviceTester;
//---------------------------------------------------------------------------
__fastcall TFormDeviceTester::TFormDeviceTester(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormDeviceTester::ToolButton1Click(TObject *Sender)
{
 if(OpenDialog1->Execute())
  {
   FileName=OpenDialog1->FileName;
   TDevice *Device=new TDevice();
   Device->Load(FileName,false);
   if(!Device->Loaded)
    return;

   RichEdit1->Visible=false;
   RichEdit1->Lines->Clear();

   RichEdit1->Lines->Add(" ");
   RichEdit1->Paragraph->Alignment=taCenter;
   RichEdit1->DefAttributes->Color=clNavy;
   RichEdit1->DefAttributes->Size=20;
   RichEdit1->DefAttributes->Style.Clear();
   RichEdit1->DefAttributes->Style=TFontStyles()<<fsBold<<fsUnderline;
   RichEdit1->Lines->Add("Device Information:");

   RichEdit1->Lines->Add(" ");
   RichEdit1->Paragraph->Alignment=taLeftJustify;
   RichEdit1->DefAttributes->Color=clBlack;
   RichEdit1->DefAttributes->Size=14;
   RichEdit1->DefAttributes->Style.Clear();
   RichEdit1->DefAttributes->Style=TFontStyles()>>fsBold>>fsUnderline;
   RichEdit1->Lines->Add("Device Address = "+IntToStr(Device->DeviceAddress));
   RichEdit1->Lines->Add("Device Name = "+Device->DeviceName);
   RichEdit1->Lines->Add("Device Filter = "+Device->DeviceFilter);
   RichEdit1->Lines->Add("Device Extention = "+Device->DeviceExtention);
   RichEdit1->Lines->Add(" ");
   RichEdit1->Lines->Add(" ");
   RichEdit1->Paragraph->Alignment=taCenter;
   RichEdit1->DefAttributes->Color=clRed;
   RichEdit1->DefAttributes->Size=18;
   RichEdit1->DefAttributes->Style.Clear();
   RichEdit1->DefAttributes->Style=TFontStyles()<<fsBold<<fsUnderline;
   RichEdit1->Lines->Add("Device In Parameters:");
   RichEdit1->Lines->Add(" ");
   RichEdit1->Paragraph->Alignment=taLeftJustify;
   RichEdit1->DefAttributes->Color=clBlack;
   RichEdit1->DefAttributes->Size=14;
   RichEdit1->DefAttributes->Style.Clear();
   RichEdit1->DefAttributes->Style=TFontStyles()>>fsBold>>fsUnderline;
   for(int i=0;i<Device->InParams->Count;i++)
    {
     RichEdit1->Lines->Add("Parameter "+IntToStr(i+1)+" = "+Device->InParams->Params[i]->Name);
     for(int j=0;j<Device->InParams->Params[i]->Values->Count;j++)
      RichEdit1->Lines->Add("Value "+IntToStr(j+1)+" = "+Device->InParams->Params[i]->Values->Strings[j]);
     RichEdit1->Lines->Add("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }

   RichEdit1->Lines->Add(" ");
   RichEdit1->Paragraph->Alignment=taCenter;
   RichEdit1->DefAttributes->Color=clGreen;
   RichEdit1->DefAttributes->Size=18;
   RichEdit1->DefAttributes->Style.Clear();
   RichEdit1->DefAttributes->Style=TFontStyles()<<fsBold<<fsUnderline;
   RichEdit1->Lines->Add("Device Out Parameters:");
   RichEdit1->Lines->Add(" ");
   RichEdit1->Paragraph->Alignment=taLeftJustify;
   RichEdit1->DefAttributes->Color=clBlack;
   RichEdit1->DefAttributes->Size=14;
   RichEdit1->DefAttributes->Style.Clear();
   RichEdit1->DefAttributes->Style=TFontStyles()>>fsBold>>fsUnderline;
   for(int i=0;i<Device->OutParams->Count;i++)
    {
     RichEdit1->Lines->Add("Parameter "+IntToStr(i+1)+" = "+Device->OutParams->Params[i]->Name);
     for(int j=0;j<Device->OutParams->Params[i]->Values->Count;j++)
      RichEdit1->Lines->Add("Value "+IntToStr(j+1)+" = "+Device->OutParams->Params[i]->Values->Strings[j]);
    }
   RichEdit1->Lines->Add(" ");
   RichEdit1->Paragraph->Alignment=taCenter;
   RichEdit1->DefAttributes->Color=clBlue;
   RichEdit1->DefAttributes->Size=18;
   RichEdit1->DefAttributes->Style.Clear();
   RichEdit1->DefAttributes->Style=TFontStyles()<<fsBold;
   RichEdit1->Lines->Add("----------------------------------------------");
   if(Device)
    delete Device;
   RichEdit1->Visible=true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormDeviceTester::ToolButton2Click(TObject *Sender)
{
 if(!FileExists(FileName))
  {
   MessageDlg(("File not found ["+FileName+"]").c_str(),mtError,TMsgDlgButtons()<<mbOK,0);
   return;
  }
 TDevice *Device=new TDevice();
 Device->Load(FileName,false);
 if(!Device->Loaded)
  return;
 AnsiString Res="9";
 if(InputQuery("Init","Enter Device Address:",Res))
  Device->DeviceInit(StrToInt(Res));
 if(Device)
  delete Device;
}
//---------------------------------------------------------------------------

void __fastcall TFormDeviceTester::ToolButton3Click(TObject *Sender)
{
 if(!FileExists(FileName))
  {
   MessageDlg(("File not found ["+FileName+"]").c_str(),mtError,TMsgDlgButtons()<<mbOK,0);
   return;
  }
 TDevice *Device=new TDevice();
 Device->Load(FileName,false);
 if(!Device->Loaded)
  return;
 Device->DeviceClose();
 if(Device)
  delete Device;
}
//---------------------------------------------------------------------------

void __fastcall TFormDeviceTester::ToolButton4Click(TObject *Sender)
{
 if(!FileExists(FileName))
  {
   MessageDlg(("File not found ["+FileName+"]").c_str(),mtError,TMsgDlgButtons()<<mbOK,0);
   return;
  }
 TDevice *Device=new TDevice();
 Device->Load(FileName,false);
 Device->CreateInterface();
 if(!Device->Loaded)
  return;
 Device->ShowModalInterface();
 Device->DestroyInterface();
 if(Device)
  delete Device;
}
//---------------------------------------------------------------------------

void __fastcall TFormDeviceTester::ToolButton5Click(TObject *Sender)
{
 if(RichEdit1->Lines->Count==0)
  return;
 if(SaveDialog1->Execute())
  {
   RichEdit1->Lines->SaveToFile(SaveDialog1->FileName);
  }
}
//---------------------------------------------------------------------------

