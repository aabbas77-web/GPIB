//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Graph.h"
#include "Axis.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormGraph *FormGraph;
//---------------------------------------------------------------------------
__fastcall TFormGraph::TFormGraph(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::Edit1Click(TObject *Sender)
{
 Table1->Active=false;
 FormAxis->Table=Table1;
 FormAxis->TableName="Temp1.db";
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
 DBChart1->Title->Text->Add("X measure Title : "+FormAxis->XTitle);
 DBChart1->Title->Text->Add("Y measure Title : "+FormAxis->YTitle);
 DBChart1->BottomAxis->Title->Caption=FormAxis->XName;
 DBChart1->LeftAxis->Title->Caption=FormAxis->YName;

 Series1->DataSource=Table1;
 Series1->YValues->ValueSource="YValues";
 Series1->XLabelsSource="XValues";
 Table1->Active=true;
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::Edit2Click(TObject *Sender)
{
 Table2->Active=false;
 FormAxis->Table=Table2;
 FormAxis->TableName="Temp2.db";
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

 DBChart2->Title->Text->Clear();
 DBChart2->Title->Text->Add("X measure Title : "+FormAxis->XTitle);
 DBChart2->Title->Text->Add("Y measure Title : "+FormAxis->YTitle);
 DBChart2->BottomAxis->Title->Caption=FormAxis->XName;
 DBChart2->LeftAxis->Title->Caption=FormAxis->YName;

 Series2->DataSource=Table2;
 Series2->YValues->ValueSource="YValues";
 Series2->XLabelsSource="XValues";
 Table2->Active=true;
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::Edit3Click(TObject *Sender)
{
 Table3->Active=false;
 FormAxis->Table=Table3;
 FormAxis->TableName="Temp3.db";
 if(FormAxis->ShowModal()==mrCancel)
  {
   Table3->Active=true;
   return;
  }
 if((FormAxis->ComboBox1->Text=="") ||
    (FormAxis->ComboBox2->Text==""))
  {
   MessageDlg("Invalid parameter name ...!",mtError,TMsgDlgButtons()<<mbOK,0);
   return;
  }

 DBChart3->Title->Text->Clear();
 DBChart3->Title->Text->Add("X measure Title : "+FormAxis->XTitle);
 DBChart3->Title->Text->Add("Y measure Title : "+FormAxis->YTitle);
 DBChart3->BottomAxis->Title->Caption=FormAxis->XName;
 DBChart3->LeftAxis->Title->Caption=FormAxis->YName;

 Series3->DataSource=Table3;
 Series3->YValues->ValueSource="YValues";
 Series3->XLabelsSource="XValues";
 Table3->Active=true;
}
//---------------------------------------------------------------------------

void __fastcall TFormGraph::Edit4Click(TObject *Sender)
{
 Table4->Active=false;
 FormAxis->Table=Table4;
 FormAxis->TableName="Temp4.db";
 if(FormAxis->ShowModal()==mrCancel)
  {
   Table4->Active=true;
   return;
  }
 if((FormAxis->ComboBox1->Text=="") ||
    (FormAxis->ComboBox2->Text==""))
  {
   MessageDlg("Invalid parameter name ...!",mtError,TMsgDlgButtons()<<mbOK,0);
   return;
  }

 DBChart4->Title->Text->Clear();
 DBChart4->Title->Text->Add("X measure Title : "+FormAxis->XTitle);
 DBChart4->Title->Text->Add("Y measure Title : "+FormAxis->YTitle);
 DBChart4->BottomAxis->Title->Caption=FormAxis->XName;
 DBChart4->LeftAxis->Title->Caption=FormAxis->YName;

 Series4->DataSource=Table4;
 Series4->YValues->ValueSource="YValues";
 Series4->XLabelsSource="XValues";
 Table4->Active=true;
}
//---------------------------------------------------------------------------

