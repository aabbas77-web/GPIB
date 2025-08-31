//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "About.h"
#include "AAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AGif"
#pragma resource "*.dfm"
TFormAbout *FormAbout;
//---------------------------------------------------------------------------
__fastcall TFormAbout::TFormAbout(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormAbout::FormActivate(TObject *Sender)
{
 if(IsFirst)
  {
   AnsiString Path=ExtractFilePath(Application->ExeName);
   if(FileExists(Path+"GPIB.gif"))
    {
     AGif1->Load(Path+"GPIB.gif");
     Loaded=true;
    }
   else
    Loaded=false;
  }
 IsFirst=false; 

 if(Loaded)
  AGif1->Animate=true;
 else
  Close(); 
}
//---------------------------------------------------------------------------

void __fastcall TFormAbout::FormDeactivate(TObject *Sender)
{
 AGif1->Animate=false;
}
//---------------------------------------------------------------------------

void __fastcall TFormAbout::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if(Shift.Contains(ssCtrl))
   {
    Ali=Ali+char(Key);
    if(UpperCase(Ali).Pos(UpperCase("Ali"))>0)
     {
      FormAAbout=new TFormAAbout(Application);
      AGif1->Animate=false;
      FormAAbout->ShowModal();
      AGif1->Animate=true;
      if(FormAAbout)
       delete FormAAbout;
      Ali="";
     }
   }
  else
   Ali="";
}
//---------------------------------------------------------------------------

void __fastcall TFormAbout::FormCreate(TObject *Sender)
{
 IsFirst=true;        
}
//---------------------------------------------------------------------------

void __fastcall TFormAbout::FormResize(TObject *Sender)
{
 Left=(Screen->Width-Width)/2;
 Top=(Screen->Height-Height)/2;
}
//---------------------------------------------------------------------------

void __fastcall TFormAbout::AGif1Click(TObject *Sender)
{
 Close();        
}
//---------------------------------------------------------------------------

