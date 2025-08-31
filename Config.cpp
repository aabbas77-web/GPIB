//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Config.h"
#include "Main.h"
//---------------------------------------------------------------------------
#include <inifiles.hpp>
#include <FileCtrl.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormConfig *FormConfig;
//---------------------------------------------------------------------------
__fastcall TFormConfig::TFormConfig(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormConfig::FormCreate(TObject *Sender)
{
 AppPath=ExtractFilePath(Application->ExeName);

 LoadConfig();

 if(!DirectoryExists(FormMain->Session->SessionsDir))
  CreateDir(FormMain->Session->SessionsDir);
 if(!DirectoryExists(FormMain->Session->SettingsDir))
  CreateDir(FormMain->Session->SettingsDir);
 if(!DirectoryExists(FormMain->Session->ResultsDir))
  CreateDir(FormMain->Session->ResultsDir);
 if(!DirectoryExists(FormMain->Session->DLLsDir))
  CreateDir(FormMain->Session->DLLsDir);
}
//---------------------------------------------------------------------------
void __fastcall TFormConfig::LoadConfig()
{
 TIniFile *IniFile=new TIniFile(AppPath+ConfigName);

 FormMain->Session->UntitledName=IniFile->ReadString("Session","UntitledName","Untitled.ses");
 FormMain->Session->DefaultName=IniFile->ReadString("Session","DefaultName","Default");

 FormMain->Session->SessionsDir=IniFile->ReadString("Session","SessionsDir","Sessions\\");
 FormMain->Session->SettingsDir=IniFile->ReadString("Session","SettingsDir","Settings\\");
 FormMain->Session->ResultsDir=IniFile->ReadString("Session","ResultsDir","Results\\");
 FormMain->Session->DLLsDir=IniFile->ReadString("Session","DLLsDir","DLLs\\");

 if(IniFile)
  delete IniFile;
}
//---------------------------------------------------------------------------

void __fastcall TFormConfig::SaveConfig()
{
 TIniFile *IniFile=new TIniFile(AppPath+ConfigName);

 IniFile->WriteString("Session","UntitledName",FormMain->Session->UntitledName);
 IniFile->WriteString("Session","DefaultName",FormMain->Session->DefaultName);

 IniFile->WriteString("Session","SessionsDir",FormMain->Session->SessionsDir);
 IniFile->WriteString("Session","SettingsDir",FormMain->Session->SettingsDir);
 IniFile->WriteString("Session","ResultsDir",FormMain->Session->ResultsDir);
 IniFile->WriteString("Session","DLLsDir",FormMain->Session->DLLsDir);

 if(IniFile)
  delete IniFile;
}
//---------------------------------------------------------------------------

void __fastcall TFormConfig::FormActivate(TObject *Sender)
{
 EditSessions->Text=FormMain->Session->SessionsDir;
 EditSettings->Text=FormMain->Session->SettingsDir;
 EditResults->Text=FormMain->Session->ResultsDir;
 EditDLLs->Text=FormMain->Session->DLLsDir;
}
//---------------------------------------------------------------------------

void __fastcall TFormConfig::BitBtn1Click(TObject *Sender)
{
 FormMain->Session->SessionsDir=EditSessions->Text;
 FormMain->Session->SettingsDir=EditSettings->Text;
 FormMain->Session->ResultsDir=EditResults->Text;
 FormMain->Session->DLLsDir=EditDLLs->Text;

 if(!DirectoryExists(FormMain->Session->SessionsDir))
  CreateDir(FormMain->Session->SessionsDir);
 if(!DirectoryExists(FormMain->Session->SettingsDir))
  CreateDir(FormMain->Session->SettingsDir);
 if(!DirectoryExists(FormMain->Session->ResultsDir))
  CreateDir(FormMain->Session->ResultsDir);
 if(!DirectoryExists(FormMain->Session->DLLsDir))
  CreateDir(FormMain->Session->DLLsDir);
}
//---------------------------------------------------------------------------

void __fastcall TFormConfig::FormDestroy(TObject *Sender)
{
 SaveConfig();        
}
//---------------------------------------------------------------------------

