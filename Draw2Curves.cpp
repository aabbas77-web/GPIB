//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Draw2Curves.h"
#include "Axis.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormDraw2Curves *FormDraw2Curves;
//---------------------------------------------------------------------------
__fastcall TFormDraw2Curves::TFormDraw2Curves(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormDraw2Curves::Curve11Click(TObject *Sender)
{
 Table1->Active=false;
 FormAxis->Table=Table1;
 FormAxis->TableName="Temp01.db";
 if(FormAxis->ShowModal()==mrCancel)
  {
   Table1->Active=true;
   return;
  }
 if((FormAxis->ComboBox1->Text=="") ||
    (FormAxis->ComboBox2->Text==""))
  {
   MessageDlg("Invalid parameter name ...!",mtError,TMsgDlgButtons()<<mbOK,0);
   return;
  }

 DBChart1->Title->Text->Clear();
 X11Title=FormAxis->XTitle;
 Y11Title=FormAxis->YTitle;
 DBChart1->Title->Text->Add("X1 measure Title : "+X11Title);
 DBChart1->Title->Text->Add("Y1 measure Title : "+Y11Title);
 DBChart1->Title->Text->Add("X2 measure Title : "+X21Title);
 DBChart1->Title->Text->Add("Y2 measure Title : "+Y21Title);
 X1Title=FormAxis->XName;
 DBChart1->BottomAxis->Title->Caption=X1Title+" , "+X2Title;
 Y1Title=FormAxis->YName;
 DBChart1->LeftAxis->Title->Caption=Y1Title+" , "+Y2Title;

 Series1->DataSource=Table1;
 Series1->YValues->ValueSource="YValues";
 Series1->XLabelsSource="XValues";
 Table1->Active=true;
}
//---------------------------------------------------------------------------
void __fastcall TFormDraw2Curves::Curve21Click(TObject *Sender)
{
 Table2->Active=false;
 FormAxis->Table=Table2;
 FormAxis->TableName="Temp02.db";
 if(FormAxis->ShowModal()==mrCancel)
  {
   Table2->Active=true;
   return;
  }
 if((FormAxis->ComboBox1->Text=="") ||
    (FormAxis->ComboBox2->Text==""))
  {
   MessageDlg("Invalid parameter name ...!",mtError,TMsgDlgButtons()<<mbOK,0);
   return;
  }

 DBChart1->Title->Text->Clear();
 X21Title=FormAxis->XTitle;
 Y21Title=FormAxis->YTitle;
 DBChart1->Title->Text->Add("X1 measure Title : "+X11Title);
 DBChart1->Title->Text->Add("Y1 measure Title : "+Y11Title);
 DBChart1->Title->Text->Add("X2 measure Title : "+X21Title);
 DBChart1->Title->Text->Add("Y2 measure Title : "+Y21Title);
 X2Title=FormAxis->XName;
 DBChart1->BottomAxis->Title->Caption=X1Title+" , "+X2Title;
 Y2Title=FormAxis->YName;
 DBChart1->LeftAxis->Title->Caption=Y1Title+" , "+Y2Title;

 Series2->DataSource=Table2;
 Series2->YValues->ValueSource="YValues";
 Series2->XLabelsSource="XValues";
 Table2->Active=true;
}
//---------------------------------------------------------------------------
void __fastcall TFormDraw2Curves::ShowCurve11Click(TObject *Sender)
{
 ShowCurve11->Checked=!ShowCurve11->Checked;
 Series1->Active=ShowCurve11->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TFormDraw2Curves::ShowCurve21Click(TObject *Sender)
{
 ShowCurve21->Checked=!ShowCurve21->Checked;
 Series2->Active=ShowCurve21->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TFormDraw2Curves::FormCreate(TObject *Sender)
{
 X1Title="";
 X2Title="";
 Y1Title="";
 Y2Title="";

 X11Title="";
 X21Title="";
 Y11Title="";
 Y21Title="";
}
//---------------------------------------------------------------------------

