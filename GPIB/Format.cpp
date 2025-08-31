//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Format.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormFormat *FormFormat;
//---------------------------------------------------------------------------
__fastcall TFormFormat::TFormFormat(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormFormat::BitBtn1Click(TObject *Sender)
{
 if(Edit1->Text!="")
  ModalResult=mrOk;        
}
//---------------------------------------------------------------------------
