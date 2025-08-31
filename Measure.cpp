//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Measure.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//------------------------TMeasure-------------------------------------------
//---------------------------------------------------------------------------
TMeasure::TMeasure()
{
 FComments=new TStringList();
 FParams=new TStringList();
}
//---------------------------------------------------------------------------
TMeasure::~TMeasure()
{
 if(FComments)
  delete FComments;
 if(FParams)
  delete FParams; 
}
//---------------------------------------------------------------------------
//-------------------------TMeasures-----------------------------------------
//---------------------------------------------------------------------------
TMeasures::TMeasures()
{
 FList=new TList();
 FModified=false;
}
//---------------------------------------------------------------------------
TMeasures::~TMeasures()
{
 if(FList)
  delete FList;
}
//---------------------------------------------------------------------------
int TMeasures::GetCount()
{
 return FList->Count;
}
//---------------------------------------------------------------------------
void TMeasures::Add(TMeasure *Measure)
{
 int Index=FList->IndexOf(Measure);
 if(Index<=-1)
  {
   FList->Add(Measure);
   FModified=true;
  }
 else
  {
   if(MessageDlg("This measure exists, would you like to replace it ?",mtWarning,TMsgDlgButtons()<<mbYes<<mbNo,0)==IDYES)
    {
     FList->Delete(Index);
     FList->Add(Measure);
     FModified=true;
    }
  }
}
//---------------------------------------------------------------------------
void TMeasures::Clear()
{
 // Clear() frees all memory allocated by its items, so that you needn`t
 // to use Free() methode.
 // Free();
 FList->Clear();
 FModified=true;
}
//---------------------------------------------------------------------------
void TMeasures::Delete(TMeasure *Measure)
{
 int Index=FList->IndexOf(Measure);
 /* TODO : You need to free memory allocated with this item */
 FList->Delete(Index);
 FModified=true;
}
//---------------------------------------------------------------------------
TMeasure *TMeasures::GetMeasure(int Index)
{
 if(FList->Count<=0)
  return NULL;
 return (TMeasure *)FList->Items[Index];
}
//---------------------------------------------------------------------------

