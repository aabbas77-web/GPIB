//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Params.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//-------------------------TAParam--------------------------------------------
//---------------------------------------------------------------------------
TAParam::TAParam()
{
 Values=new TStringList();
}
//---------------------------------------------------------------------------
TAParam::~TAParam()
{
 if(Values)
  delete Values;
 Values=NULL; 
}
//---------------------------------------------------------------------------
//-------------------------TAParams------------------------------------------
//---------------------------------------------------------------------------
TAParams::TAParams()
{
 FList=new TList();
 FModified=false;
 FFirstShift=0;
 FSecondShift=0;
}
//---------------------------------------------------------------------------
TAParams::~TAParams()
{
 Clear();
 if(FList)
  delete FList;
 FList=NULL;
}
//---------------------------------------------------------------------------
void TAParams::Free()
{
 for(int i=0;i<FList->Count;i++)
  {
   TAParam *pParam=(TAParam *)FList->Items[i];
   if(pParam)
    delete pParam;
   pParam=NULL;
  }
 FModified=true;
}
//---------------------------------------------------------------------------
void TAParams::SaveToFile(AnsiString FileName,bool withValues)
{
 if(FileExists(FileName))
  DeleteFile(FileName);
 FFileName=FileName;
 TIniFile *IniFile=new TIniFile(FFileName);

 for(int i=0;i<FList->Count;i++)
  {
   TAParam *Param=(TAParam *)FList->Items[i];
   IniFile->WriteInteger(Param->Name,"Index",Param->Index);
   if(withValues)
    {
     for(int j=0;j<Param->Values->Count;j++)
      IniFile->WriteString(Param->Name,"V"+IntToStr(j+1),Param->Values->Strings[j]);
    }  
  }

 if(IniFile)
  delete IniFile;
 FModified=false;
}
//---------------------------------------------------------------------------
void TAParams::LoadFromFile(AnsiString FileName,bool withValues)
{
 FFileName=FileName;
 TIniFile *IniFile=new TIniFile(FileName);
 TStringList *ParamNames=new TStringList();
 TStringList *Values=new TStringList();

 // [Parameters]
 IniFile->ReadSections(ParamNames);
 // [Parameter 1..n]
 for(int i=0;i<ParamNames->Count;i++)
  {
   if(withValues)
    {
     Clear();
     TAParam *Param=new TAParam();
     Param->Name=ParamNames->Strings[i];
     Values->Clear();
     GetSectionValues(IniFile,Param->Name,Values);
     Param->Index=StrToInt(Values->Strings[0].Trim());
     Values->Delete(0);
     Param->Values->Assign(Values);
     FList->Add(Param);
    }
   else
    {
     TAParam *Param=(TAParam *)FList->Items[i];
     Param->Name=ParamNames->Strings[i];
     Values->Clear();
     GetSectionValues(IniFile,Param->Name,Values);
     Param->Index=StrToInt(Values->Strings[0].Trim());
    }
  }

 if(Values)
  delete Values;
 if(ParamNames)
  delete ParamNames;
 if(IniFile)
  delete IniFile;
 FModified=false;
}
//---------------------------------------------------------------------------
int TAParams::GetCount()
{
 return FList->Count;
}
//---------------------------------------------------------------------------
void TAParams::Add(TAParam *Param)
{
 int Index=FList->IndexOf(Param);
 if(Index<=-1)
  {
   if(Param->Group==0)
    FFirstShift++;
   else
   if(Param->Group==1)
    FSecondShift++;
    
   FList->Add(Param);
   FModified=true;
  }
 else
  {
   if(MessageDlg("This parameter exists, would you like to replace it ?",mtWarning,TMsgDlgButtons()<<mbYes<<mbNo,0)==IDYES)
    {
     if(Param->Group==0)
      FFirstShift++;
     else
     if(Param->Group==1)
      FSecondShift++;

     FList->Delete(Index);
     FList->Add(Param);
     FModified=true;
    }
  }
}
//---------------------------------------------------------------------------
void TAParams::Clear()
{
 // Clear() frees all memory allocated by its items, so that you needn`t
 // to use Free() methode.
 // Free();
 FList->Clear();
 FModified=true;
 FFirstShift=0;
 FSecondShift=0;
}
//---------------------------------------------------------------------------
void TAParams::Delete(TAParam *Param)
{
 int Index=FList->IndexOf(Param);
 /* TODO : You need to free memory allocated with this item */
 FList->Delete(Index);
 FModified=true;
}
//---------------------------------------------------------------------------
TAParam *TAParams::GetParam(int Index)
{
 if(FList->Count<=0)
  return NULL;
 return (TAParam *)FList->Items[Index];
}
//---------------------------------------------------------------------------
void TAParams::GetSectionValues(TIniFile *IniFile,AnsiString Section,TStrings *Values)
{
 IniFile->ReadSectionValues(Section,Values);

 AnsiString S;
 int Index;
 for(int i=0;i<Values->Count;i++)
  {
   S=Values->Strings[i];
   Index=S.Pos("=");
   S.Delete(1,Index);
   Values->Strings[i]=S;
  }
}
//---------------------------------------------------------------------------
int TAParams::GetItemIndex(int Index,int Group)
{
 int ItemIndex;
 if(Group==0)
  ItemIndex=Index;
 else
 if(Group==1)
  ItemIndex=Index+FFirstShift;
 else
 if(Group==2)
  ItemIndex=Index+FFirstShift+FSecondShift;
 return ItemIndex;
}
//---------------------------------------------------------------------------
TAParam *TAParams::GetParamIG(int Index,int Group)
{
 if(FList->Count<=0)
  return NULL;
 return (TAParam *)FList->Items[GetItemIndex(Index,Group)];
}
//---------------------------------------------------------------------------

