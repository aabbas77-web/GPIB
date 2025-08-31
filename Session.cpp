//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Session.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
TDeviceSession::TDeviceSession()
{
 FPath=ExtractFilePath(Application->ExeName);
 FFileName=FPath+SessionsDir+UntitledName;
 FList=new TList();
 FModified=false;
 FDeviceNo=0;
}
//---------------------------------------------------------------------------
TDeviceSession::~TDeviceSession()
{
 Clear();
 if(FList)
  delete FList;
 FList=NULL;
}
//---------------------------------------------------------------------------
void TDeviceSession::Free()
{
 for(int i=0;i<FList->Count;i++)
  {
   TDevice *pDevice=(TDevice *)FList->Items[i];
   if(pDevice)
    delete pDevice;
   pDevice=NULL;
  }
 FModified=true;
}
//---------------------------------------------------------------------------
void TDeviceSession::New()
{
 FPath=ExtractFilePath(Application->ExeName);
 FFileName=FPath+SessionsDir+UntitledName;
 Clear();
 FModified=false;
}
//---------------------------------------------------------------------------
void TDeviceSession::SaveToFile(AnsiString FileName)
{
 if(FileExists(FileName))
  DeleteFile(FileName);
 FPath=ExtractFilePath(FileName);
 AnsiString AppPath=ExtractFilePath(Application->ExeName);
 FFileName=FileName;
 TIniFile *IniFile=new TIniFile(FileName);

 // [Header]
 IniFile->WriteString("Header","SessionPath",FPath);

 // [Devices]
 for(int i=0;i<FList->Count;i++)
  {
   AnsiString DeviceName=((TDevice *)FList->Items[i])->DeviceName;
   IniFile->WriteString("Devices","Device"+IntToStr(i+1),DeviceName);
  }
 // [Device 1..n]
 for(int i=0;i<FList->Count;i++)
  {
   TDevice *Device=(TDevice *)FList->Items[i];
   AnsiString DeviceName=Device->DeviceName;

   IniFile->WriteString(DeviceName,"DLL_File",Device->DeviceDLL);

   // Save edited settings
   AnsiString Name=ChangeFileExt(ExtractFileName(FFileName),Devices[i]->DeviceExtention);
   AnsiString SettingFile=AppPath+SettingsDir+Name;
   Device->InParams->SaveToFile(SettingFile,false);
   IniFile->WriteString(DeviceName,"Setting_File",SettingFile);

   // Save measure informations
   for(int j=0;j<Device->Measures->Count;j++)
    {
     AnsiString Title=Device->Measures->Measures[j]->Title;
     IniFile->WriteString(DeviceName+"_Measures","Measure"+IntToStr(j+1),Title);
    } 
   for(int j=0;j<Device->Measures->Count;j++)
    {
     AnsiString Title=Device->Measures->Measures[j]->Title;
     IniFile->WriteString(DeviceName+"_Measures_"+Title,"Title",Title);
     IniFile->WriteString(DeviceName+"_Measures_"+Title,"File Name",Device->Measures->Measures[j]->FileName);
     IniFile->WriteString(DeviceName+"_Measures_"+Title,"Start Time",Device->Measures->Measures[j]->StartTime);
     IniFile->WriteString(DeviceName+"_Measures_"+Title,"End Time",Device->Measures->Measures[j]->EndTime);

     IniFile->WriteString(DeviceName+"_Measures_"+Title,"Interval_Hour",Device->Measures->Measures[j]->Interval.wHour);
     IniFile->WriteString(DeviceName+"_Measures_"+Title,"Interval_Minute",Device->Measures->Measures[j]->Interval.wMinute);
     IniFile->WriteString(DeviceName+"_Measures_"+Title,"Interval_Second",Device->Measures->Measures[j]->Interval.wSecond);
     IniFile->WriteString(DeviceName+"_Measures_"+Title,"Interval_MS",Device->Measures->Measures[j]->Interval.wMilliseconds);

     for(int k=0;k<Device->Measures->Measures[j]->Params->Count;k++)
      IniFile->WriteString(DeviceName+"_Measures_"+Title+"_Params","Param"+IntToStr(k+1),Device->Measures->Measures[j]->Params->Strings[k]);
     for(int k=0;k<Device->Measures->Measures[j]->Comments->Count;k++)
      IniFile->WriteString(DeviceName+"_Measures_"+Title+"_Comments","Line"+IntToStr(k+1),Device->Measures->Measures[j]->Comments->Strings[k]);
    }

   Device->Modified=false; 
  }

 if(IniFile)
  delete IniFile;
 FModified=false;
}
//---------------------------------------------------------------------------
void TDeviceSession::LoadFromFile(AnsiString FileName)
{
 Clear();
 FPath=ExtractFilePath(FileName);
 FFileName=FileName;
 TIniFile *IniFile=new TIniFile(FileName);
 TStringList *Values=new TStringList();
 TStringList *Titles=new TStringList();

 // [Header]
// SessionPath=IniFile->ReadString("Header","SessionPath","");

 // [Devices]
 GetSectionValues(IniFile,"Devices",Values);
 // [Device 1..n]
 for(int i=0;i<Values->Count;i++)
  {
   TDevice *Device=new TDevice();
   AnsiString DeviceName=Values->Strings[i];

   AnsiString DLLFile=IniFile->ReadString(DeviceName,"DLL_File","");
   Device->Load(DLLFile,true);

   AnsiString SettingFile=IniFile->ReadString(DeviceName,"Setting_File","");
   Device->InParams->LoadFromFile(SettingFile,false);

   // Load measure informations
   Titles->Clear();
   GetSectionValues(IniFile,DeviceName+"_Measures",Titles);
   for(int j=0;j<Titles->Count;j++)
    {
     TMeasure *Measure=new TMeasure();
     AnsiString Title=Titles->Strings[j];
     Measure->Title=IniFile->ReadString(DeviceName+"_Measures_"+Title,"Title","");
     Measure->FileName=IniFile->ReadString(DeviceName+"_Measures_"+Title,"File Name","");
     Measure->StartTime=IniFile->ReadString(DeviceName+"_Measures_"+Title,"Start Time","");
     Measure->EndTime=IniFile->ReadString(DeviceName+"_Measures_"+Title,"End Time","");

     Measure->Interval.wHour=IniFile->ReadInteger(DeviceName+"_Measures_"+Title,"Interval_Hour",0);
     Measure->Interval.wMinute=IniFile->ReadInteger(DeviceName+"_Measures_"+Title,"Interval_Minute",0);
     Measure->Interval.wSecond=IniFile->ReadInteger(DeviceName+"_Measures_"+Title,"Interval_Second",0);
     Measure->Interval.wMilliseconds=IniFile->ReadInteger(DeviceName+"_Measures_"+Title,"Interval_MS",1);

     GetSectionValues(IniFile,DeviceName+"_Measures_"+Title+"_Params",Measure->Params);
     GetSectionValues(IniFile,DeviceName+"_Measures_"+Title+"_Comments",Measure->Comments);

     Device->Measures->Add(Measure);
    }

   FList->Add(Device);
  }

 if(Values)
  delete Values;
 if(Titles)
  delete Titles;
 if(IniFile)
  delete IniFile;
 FModified=false;
}
//---------------------------------------------------------------------------
void TDeviceSession::GetSectionValues(TIniFile *IniFile,AnsiString Section,TStrings *Values)
{
 TStringList *List=new TStringList();

 IniFile->ReadSectionValues(Section,List);

 AnsiString S;
 int Index;
 for(int i=0;i<List->Count;i++)
  {
   S=List->Strings[i];
   Index=S.Pos("=");
   S.Delete(1,Index);
   Values->Add(S);
  }

 if(List)
  delete List; 
}
//---------------------------------------------------------------------------
int TDeviceSession::GetCount()
{
 return FList->Count;
}
//---------------------------------------------------------------------------
void TDeviceSession::Add(TDevice *Device)
{
 int Index=FList->IndexOf(Device);
 if(Index<=-1)
  {
   FList->Add(Device);
   FModified=true;
  } 
 else
  {
   if(MessageDlg("This device exists, would you like to replace it ?",mtWarning,TMsgDlgButtons()<<mbYes<<mbNo,0)==IDYES)
    {
     FList->Delete(Index);
     FList->Add(Device);
     FModified=true;
    }
  }
}
//---------------------------------------------------------------------------
void TDeviceSession::Clear()
{
 // Clear() frees all memory allocated by its items, so that you needn`t
 // to use Free() methode.
 // Free();
 FList->Clear();
 FModified=true;
}
//---------------------------------------------------------------------------
void TDeviceSession::Delete(TDevice *Device)
{
 int Index=FList->IndexOf(Device);
 /* TODO : You need to free memory allocated with this item */
 FList->Delete(Index);
 FModified=true;
}
//---------------------------------------------------------------------------
TDevice *TDeviceSession::GetDevice(int Index)
{
 if(FList->Count<=0)
  return NULL;
 return (TDevice *)FList->Items[Index];
}
//---------------------------------------------------------------------------
bool TDeviceSession::GetModified()
{
 if(FModified)
  return true;
 else
  {
   for(int i=0;i<FList->Count;i++)
    {
     TDevice *pDevice=(TDevice *)FList->Items[i];
     if(pDevice->Modified)
      return true;
    }
  }
 return false; 
}
//---------------------------------------------------------------------------

