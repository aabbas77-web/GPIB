//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Main.h"
#include "Edit.h"
#include "Address.h"
#include "Progress.h"
#include "Editor.h"
#include "Graph.h"
#include "Config.h"
#include "Draw2Curves.h"
#include "Info.h"
#include "DeviceTester.h"
//---------------------------------------------------------------------------
#include <IniFiles.hpp>
#include <FileCtrl.hpp>
#include <mmSystem.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Delay(int MS)
{
 int time1,time2;
 time1=timeGetTime();
 time2=time1;
 while(time2<time1+MS)
  time2=timeGetTime();
}
//---------------------------------------------------------------------------
AnsiString __fastcall TFormMain::Remove(AnsiString Text,char C)
{
 AnsiString S=Text;
 int Index=S.Pos(C);
 if(Index>0)
  S.Delete(Index,1);
 return S;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FindFiles(AnsiString Path,TStringList *Files)
{
 TSearchRec SR;
 int iAttributes=0;
 iAttributes |= faArchive | faAnyFile;
 if(FindFirst(Path,iAttributes,SR)==0)
  {
   do
    {
     if((SR.Attr & iAttributes) == SR.Attr)
      Files->Add(AppPath+Session->DLLsDir+SR.Name);
    } while(FindNext(SR) == 0);
   FindClose(SR);
  }
}    
//---------------------------------------------------------------------------

void __fastcall TFormMain::NewSession()
{
//
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AFinishDevicesExecute(TObject *Sender)
{
 if(Network1->Count<=0)
  {
   MessageDlg("You must select a device ...",mtError,TMsgDlgButtons()<<mbOK,0);
   return;
  }

 for(int i=0;i<Network1->Count;i++)
  Network1->Items[i]->Enabled=true;
 FinishNo=0;
 
 ADevices->Enabled=false;
 ANetwork->Enabled=true;
 ASettings->Enabled=false;
 EnableSettings(ASettings->Enabled);
 AOperations->Enabled=false;
 AAnalysing->Enabled=false;
 EnableSettings1(AAnalysing->Enabled);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormCreate(TObject *Sender)
{
 AppPath=ExtractFilePath(Application->ExeName);
 Session=new TDeviceSession();
 AInfoSession->Enabled=false;
 Files=new TStringList();
 FinishNo=0;
 IsNew=true;
 DeviceFinishCount=0;

 ADevices->Enabled=false;
 ANetwork->Enabled=false;
 ASettings->Enabled=false;
 EnableSettings(ASettings->Enabled);
 AOperations->Enabled=false;
 AAnalysing->Enabled=false;
 EnableSettings1(AAnalysing->Enabled);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditExecute(TObject *Sender)
{
 FormEdit->Caption=Session->Devices[Session->DeviceNo]->DeviceName;
 FormEdit->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASettingsExecute(TObject *Sender)
{
//        
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AFinishSettingsExecute(TObject *Sender)
{
 ASettings->Enabled=false;
 EnableSettings(ASettings->Enabled);
 ANetwork->Enabled=true;
 Network1->Items[FinishNo]->Enabled=false;
 FinishNo++;

 // Save edited settings
 AnsiString Name=ChangeFileExt(ExtractFileName(Session->FileName),Session->Devices[Session->DeviceNo]->DeviceExtention);
 AnsiString SettingFile=AppPath+Session->SettingsDir+Name;
 Session->Devices[Session->DeviceNo]->InParams->SaveToFile(SettingFile,false);
 // Send edited settings
 Session->Devices[Session->DeviceNo]->SendParameters();
 if(FinishNo>=Network1->Count)
  {
   ANetwork->Enabled=false;
   AOperations->Enabled=true;
   AAnalysing->Enabled=true;
   EnableSettings1(AAnalysing->Enabled);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASessionExecute(TObject *Sender)
{
//        
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ANewSessionExecute(TObject *Sender)
{
 if(Session->Modified)
  {
   int Res=MessageDlg("Save changes to ["+Session->FileName+"]",mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo<<mbCancel,0);
   if(Res==mrYes)
    {
     ASaveAsSessionExecute(this);
    }
   else
   if(Res==mrCancel)
    {
     return;
    }
  }
 AInfoSession->Enabled=true;
 Session->New();
 Caption="GPIB V1.0 ["+Session->FileName+"]";
 IsNew=true;
 DeviceFinishCount=0;

 // Rebuildig Devices Address
 FormAddress->ComboBox1->Items->Clear();
 for(int i=1;i<=30;i++)
  FormAddress->ComboBox1->Items->Add(IntToStr(i));

 Files->Clear(); 
 FindFiles(AppPath+Session->DLLsDir+"*.DLL",Files);
 int Index=Files->IndexOf("GPIB-32.DLL");
 if(Index!=-1)
  Files->Delete(Index);
 if(Files->Count<=0)
  {
   MessageDlg("Devices not found in the DLLs directory ...!",mtError,TMsgDlgButtons()<<mbOK,0);
   return;
  }

 // Rebuilding Devices Items
 FormProgress->ProgressBar1->Max=Files->Count; 
 FormProgress->ProgressBar1->Position=0;
 FormProgress->Caption="Loading Devices"; 
 FormProgress->Label1->Caption="Loading ..."; 
 FormProgress->Show();
 FormProgress->Update(); 

 Devices1->Clear();
 AnsiString DeviceName;
 for(int i=0;i<Files->Count;i++)
  {
   TDevice *Device=new TDevice();
   DeviceName=Device->GetDeviceName(AppPath+Session->DLLsDir+ExtractFileName(Files->Strings[i]));
   if(Device)
    delete Device;

   if(DeviceName!="")
    {
     TMenuItem *pItem=new TMenuItem(this);
     pItem->Caption=DeviceName;
     pItem->OnClick=ADeviceClickExecute;
     pItem->Tag=i;
     Devices1->Add(pItem);

     FormProgress->ProgressBar1->StepIt();
     FormProgress->Update();
    }
   else
    {
     Files->Delete(i);
     i--;
    }
  }
 FormProgress->Close();

 TMenuItem *pItem=new TMenuItem(this);
 pItem->Caption="-";
 Devices1->Add(pItem);

 pItem=new TMenuItem(this);
 pItem->Caption=AFinishDevices->Caption;
 pItem->OnClick=AFinishDevices->OnExecute;
 Devices1->Add(pItem);

 Network1->Clear();
 Operations1->Clear();
 for(int i=0;i<Devices1->Count;i++)
  Devices1->Items[i]->Checked=false;

 ADevices->Enabled=true;
 ANetwork->Enabled=false;
 ASettings->Enabled=false;
 EnableSettings(ASettings->Enabled);
 AOperations->Enabled=false;
 AAnalysing->Enabled=false;
 EnableSettings1(AAnalysing->Enabled);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AOpenSessionExecute(TObject *Sender)
{
 if(Session->Modified)
  {
   int Res=MessageDlg("Save changes to ["+Session->FileName+"]",mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo<<mbCancel,0);
   if(Res==mrYes)
    {
     ASaveAsSessionExecute(this);
    }
   else
   if(Res==mrCancel)
    {
     return;
    }
  }
 AInfoSession->Enabled=true;
 OpenDialog1->InitialDir=AppPath+Session->SessionsDir;
 OpenDialog1->Filter="Device Session Files (*.ses)|*.ses";
 OpenDialog1->DefaultExt="ses";
 if(!ExtractFileName(Session->FileName).IsEmpty())
  OpenDialog1->FileName=Session->FileName;
 if(OpenDialog1->Execute())
  {
   Session->LoadFromFile(OpenDialog1->FileName);
   Caption="GPIB V1.0 ["+Session->FileName+"]";
   IsNew=false;
   DeviceFinishCount=0;
         
   // Rebuildig Devices Address
   FormAddress->ComboBox1->Items->Clear();
   for(int i=1;i<=30;i++)
    FormAddress->ComboBox1->Items->Add(IntToStr(i));

   // Rebuilding Devices Items
   FormProgress->ProgressBar1->Max=Session->Count;
   FormProgress->ProgressBar1->Position=0;
   FormProgress->Caption="Loading Devices";
   FormProgress->Label1->Caption="Loading ...";
   FormProgress->Show();
   FormProgress->Update(); 

   Devices1->Clear();
   AnsiString DeviceName;
   Files->Clear();
   for(int i=0;i<Session->Count;i++)
    {
     TDevice *Device=Session->Devices[i];
     DeviceName=Device->DeviceName;
     Files->Add(Device->DeviceDLL);

     TMenuItem *pItem=new TMenuItem(this);
     pItem->Caption=DeviceName;
     pItem->OnClick=ADeviceClickExecute;
     pItem->Tag=i;
     Devices1->Add(pItem);

     FormProgress->ProgressBar1->StepIt();
     FormProgress->Update();
    }
   FormProgress->Close();

   if(Files->Count<=0)
    {
     MessageDlg("Devices not found in this session ...!",mtError,TMsgDlgButtons()<<mbOK,0);
     return;
    }

   TMenuItem *pItem=new TMenuItem(this);
   pItem->Caption="-";
   Devices1->Add(pItem);

   pItem=new TMenuItem(this);
   pItem->Caption=AFinishDevices->Caption;
   pItem->OnClick=AFinishDevices->OnExecute;
   Devices1->Add(pItem);

   Network1->Clear();
   Operations1->Clear();
   for(int i=0;i<Devices1->Count;i++)
    Devices1->Items[i]->Checked=false;

   ADevices->Enabled=true;
   ANetwork->Enabled=false;
   ASettings->Enabled=false;
   EnableSettings(ASettings->Enabled);
   AOperations->Enabled=false;
   AAnalysing->Enabled=false;
   EnableSettings1(AAnalysing->Enabled);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASaveSessionExecute(TObject *Sender)
{
 if(Session->FileName.Pos(Session->UntitledName)>=0)
  ASaveAsSessionExecute(this);
 else
  Session->SaveToFile(Session->FileName);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASaveAsSessionExecute(TObject *Sender)
{
 SaveDialog1->InitialDir=AppPath+Session->SessionsDir;
 SaveDialog1->Filter="Device Session Files (*.ses)|*.ses";
 SaveDialog1->DefaultExt="ses";
 SaveDialog1->FileName=Session->FileName;
 if(SaveDialog1->Execute())
  {
   Session->SaveToFile(SaveDialog1->FileName);
   Caption="GPIB V1.0 ["+Session->FileName+"]";       
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AExitExecute(TObject *Sender)
{
 Close();        
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ANetworkExecute(TObject *Sender)
{
//        
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AOperationsExecute(TObject *Sender)
{
//        
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
/*
 TDevice *Device1=new TDevice();
 Device1->DeviceName="Voltmeter";
 Device1->Params->LoadFromFile(AppPath+"Parameters\\"+"Parameters.3000");
// Device1->Params->SaveToFile(AppPath+"Parameters\\"+"Param.3000");
 Device1->ResultFiles->Add("Result11");
 Device1->ResultFiles->Add("Result12");
 Device1->ResultFiles->Add("Result13");

 TDevice *Device2=new TDevice();
 Device2->Load("E:\\Mazen\\GPIB\\DLLs\\3000\\Device3000.dll");

 Session->Add(Device1);
 Session->Add(Device2);

 Session->SaveToFile(AppPath+"Sessions\\"+"Session.ses");
*/
 if(Files)
  delete Files;
 if(Session)
  delete Session;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormClose(TObject *Sender, TCloseAction &Action)
{
 if(Session->Modified)
  {
   int Res=MessageDlg("Save changes to ["+Session->FileName+"]",mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo<<mbCancel,0);
   if(Res==mrYes)
    {
     ASaveAsSessionExecute(this);
     Action=caFree;
    }
   else
   if(Res==mrCancel)
    {
     Action=caNone;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AFinishAllSettingsExecute(TObject *Sender)
{
 int N=0;
 for(int i=0;i<Network1->Count;i++)
  {
   if(Network1->Items[i]->Enabled)
    N++;
  }  

 FormProgress->ProgressBar1->Max=N; 
 FormProgress->ProgressBar1->Position=0;
 FormProgress->Caption="Finish All Settings"; 
 FormProgress->Label1->Caption="Sending ..."; 
 FormProgress->Show();
 FormProgress->Update(); 

 for(int i=0;i<Network1->Count;i++)
  {
   if(Network1->Items[i]->Enabled)
    {
     // Send default settings which in memory now
     Session->Devices[Network1->Items[i]->Tag]->SendParameters();

     Delay(1000);

     FormProgress->ProgressBar1->StepIt();
     FormProgress->Update(); 
    }
  }
 FormProgress->Close();

 ASettings->Enabled=false;
 EnableSettings(ASettings->Enabled);
 Network1->Items[FinishNo]->Enabled=false;
 ANetwork->Enabled=false;
 AOperations->Enabled=true;
 AAnalysing->Enabled=true;
 EnableSettings1(AAnalysing->Enabled);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADevicesExecute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::EnableSettings(bool Etat)
{
 AEdit->Enabled=Etat;
 AFinishSettings->Enabled=Etat;
 AFinishAllSettings->Enabled=Etat;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::EnableSettings1(bool Etat)
{
 AGraph->Enabled=Etat;
 ADraw2Curves->Enabled=Etat;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AAnalysingExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADatabaseEditorExecute(TObject *Sender)
{
 FormEditor->OpenDialog1->InitialDir=AppPath+Session->ResultsDir;
 FormEditor->ShowModal();	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AGraphExecute(TObject *Sender)
{
 FormGraph->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AToolsExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AHelpExecute(TObject *Sender)
{
//        
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AIndexExecute(TObject *Sender)
{
 Application->HelpCommand(HELP_INDEX,0);       
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AContentsExecute(TObject *Sender)
{
 Application->HelpCommand(HELP_CONTENTS,0);       
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AAboutExecute(TObject *Sender)
{
 if(!FileExists(AppPath+"AboutLib.DLL"))
  {
   MessageDlg("File not found ["+AppPath+"AboutLib.DLL] on the application path.",mtError,TMsgDlgButtons()<<mbOK,0);
   return;
  }
 HINSTANCE hLib;
 hLib=LoadLibrary((AppPath+"AboutLib.DLL").c_str());
 if(hLib==NULL)
  {
   FreeLibrary(hLib);
   return;
  }

 typedef void  (*F_About)(TDevice *);
 F_About FAbout;

 FAbout=(F_About)GetProcAddress(hLib,"_About");
 if(FAbout==NULL)
  {
   MessageDlg("Error In Loading [About] Function ...",
              mtError,TMsgDlgButtons()<<mbOK,0);
   FreeLibrary(hLib);
   return;
  }
 TDevice *Device=new TDevice();
 (FAbout)(Device);
 if(Device)
  delete Device;
 FreeLibrary(hLib);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AConfigExecute(TObject *Sender)
{
 FormConfig->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AInterfaceExecute(TObject *Sender)
{
//        
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASelectDeviceExecute(TObject *Sender)
{
 TMenuItem *pItem=(TMenuItem *)Sender;
 if(pItem)
  {
   Session->DeviceNo=pItem->Tag;

   Session->Devices[pItem->Tag]->ShowInterface();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADeviceExecute(TObject *Sender)
{
 TMenuItem *pItem=(TMenuItem *)Sender;
 if(pItem)
  {
   Session->DeviceNo=pItem->Tag;

   // You don`t need to load default settings because they come from the DLL
   // AnsiString SettingFile=AppPath+Session->SettingsDir+DefaultName+Session->Devices[pItem->Tag]->DeviceExtention;
   // Session->Devices[pItem->Tag]->InParams->LoadFromFile(SettingFile,false);
  }

 ADevices->Enabled=false;
 ANetwork->Enabled=false;
 ASettings->Enabled=true;
 EnableSettings(true);
 AOperations->Enabled=false;
 AAnalysing->Enabled=false;
 EnableSettings1(AAnalysing->Enabled);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADeviceClickExecute(TObject *Sender)
{
 TMenuItem *pItem;

 // Changing Devices Items Check Status
 pItem=(TMenuItem *)Sender;
 if(!pItem)
  return;
 pItem->Checked=true;
 pItem->Enabled=false;

 // Rebuilding Network Items
 FormAddress->Caption=Remove(pItem->Caption,'&');
 FormAddress->ComboBox1->ItemIndex=0;
 if(FormAddress->ShowModal()==mrOk)
  {
   if(IsNew)
    Session->DeviceNo=Session->Count;
   else
    Session->DeviceNo=pItem->Tag;

   TMenuItem *pItem1=new TMenuItem(this);

   pItem1->Caption=pItem->Caption;
   pItem1->OnClick=ADeviceExecute;
   pItem1->ShortCut=pItem->ShortCut;
   pItem1->Hint=pItem->Hint;
   pItem1->Tag=Session->DeviceNo;
   Network1->Add(pItem1);

   TMenuItem *pItem2=new TMenuItem(this);

   pItem2->Caption=pItem->Caption;
   pItem2->OnClick=ASelectDeviceExecute;
   pItem2->ShortCut=pItem->ShortCut;
   pItem2->Hint=pItem->Hint;
   pItem2->Tag=Session->DeviceNo;
   Operations1->Add(pItem2);

   int Index=FormAddress->ComboBox1->ItemIndex;
   int IAddress=StrToInt(FormAddress->ComboBox1->Items->Strings[Index]);
   if(IsNew)
    {
     TDevice *Device=new TDevice();
     Device->Load(Files->Strings[pItem->Tag],true);
     Device->DeviceInit(IAddress);
     Session->Add(Device);
    }
   else
    {
     Session->Devices[Session->DeviceNo]->DeviceInit(IAddress);
    }
//   MessageBox(0,Session->Devices[Session->DeviceNo]->DeviceName.c_str(),"",0);

   DeviceFinishCount++; 
   if(DeviceFinishCount>=Files->Count)
    AFinishDevicesExecute(this);

   FormAddress->ComboBox1->Items->Delete(Index);
  }
 else
  {
   pItem->Checked=false;
   pItem->Enabled=true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADraw2CurvesExecute(TObject *Sender)
{
 FormDraw2Curves->ShowModal();        
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AInfoSessionExecute(TObject *Sender)
{
 FormInfo->ShowModal();        
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADeviceTesterExecute(TObject *Sender)
{
 FormDeviceTester->ShowModal();        
}
//---------------------------------------------------------------------------

