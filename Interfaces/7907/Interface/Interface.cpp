//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Interface.h"
#include "Single.h"
#include <mmSystem.h>
#include <Math.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma link "CGAUGES"
#pragma link "PERFGRAP"
#pragma resource "*.dfm"
TFormInterface *FormInterface;
//---------------------------------------------------------------------------
__fastcall TFormInterface::TFormInterface(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
inline int Round(float f)
{
 return (((f-int(f))>0.5)?int(f)+1:int(f));
}
//---------------------------------------------------------------------------
//-------------------Interface methods---------------------------------------
//---------------------------------------------------------------------------
void __fastcall TFormInterface::Divide(TPoint P1,TPoint P2,float Step,TStringList *List)
{
 float TimeScale=float(float(CSpinEdit6->Value)/1000.0)/187.0;
 float Y,a,b;
 if(P2.x!=P1.x)
  {
   a=((P1.y-P2.y)*VoltScale)/((P2.x-P1.x)*TimeScale);
   NY=Image1->Height-1-P1.y;
   b=NY*VoltScale-a*P1.x*TimeScale;
   for(float X=P1.x*TimeScale;X<P2.x*TimeScale;X+=Step)
    {
     Y=a*X+b;
     List->Add(FormatFloat("00.00",Y));
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInterface::DivideSin(float A,float B,float C,float Step,TStringList *List)
{
 float Y;
 float X;
 for(X=0.0;X<=(2.0*PI/B);X+=Step)
  {
   Y=Y0+A*sin(B*X+C);
   List->Add(FormatFloat("00.00",Y));
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::FormCreate(TObject *Sender)
{
 OutParams=new TAParams();
 InParams=new TAParams();
 Measures=new TMeasures();
 List=new TStringList();
 ListOpen=new TStringList();

 CGauge1->Progress=0;
 PointNo=-1;
 PointCount=100;

 DateTimePicker1->Time=Time();
 DateTimePicker2->Date=Date();

 BitBtn2->Enabled=true;
 BitBtn5->Enabled=false;

 FirstClick=true;
 Clicked=false;
 Image1->Canvas->Brush->Color=clWhite;
 Image1->Canvas->Brush->Style=bsSolid;
 Image1->Canvas->Pen->Color=clWhite;
 Image1->Canvas->Rectangle(0,0,Image1->Width,Image1->Height);
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::FormDestroy(TObject *Sender)
{
 if(OutParams)
  delete OutParams;
 if(InParams)
  delete InParams;
 if(Measures)
  delete Measures;
 if(List)
  delete List; 
 if(ListOpen)
  delete ListOpen; 
}
//---------------------------------------------------------------------------
void __fastcall TFormInterface::BitBtn3Click(TObject *Sender)
{
 UOP7907.uop7907_trig(UOP7907.instr_ID);
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::Timer2Timer(TObject *Sender)
{
 Panel2->Caption=Date().DateString()+"  "+Time().TimeString();
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::AFileExecute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::ASinExecute(TObject *Sender)
{
 Notebook1->ActivePage="Sin";
 Series1->Clear();
 CGauge1->Progress=0;
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::ACloseExecute(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormInterface::Plot(float AX,float AY)
{
 if(Series1->Count()>=PointCount)
  {
   Series1->Delete(0);
   Series1->AddXY(AX,AY,"",clTeeColor);
  }
 else
  {
   Series1->AddXY(AX,AY,"",clTeeColor);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::CSpinEdit5Change(TObject *Sender)
{
 PointCount=CSpinEdit5->Value;
}
//---------------------------------------------------------------------------/*

void __fastcall TFormInterface::Button1Click(TObject *Sender)
{
 UOP7907.uop7907_set_voltage_value(UOP7907.instr_ID,StrToFloat(Edit2->Text));
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::Button2Click(TObject *Sender)
{
 UOP7907.uop7907_set_current_value(UOP7907.instr_ID,StrToFloat(Edit3->Text));
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 NY=Image1->Height-1-Y;
 if(Button==mbLeft)
  {
   Clicked=true;
   P2=Point(X,Y);
   if(FirstClick)
    {
     P1=P2;
     List->Clear();

     TimeStep=(CSpinEdit2->Value*60+CSpinEdit3->Value)+float(CSpinEdit4->Value)/1000.0;
     RepeatCount=CSpinEdit1->Value;

     List->Add(FormatFloat("00.00",RepeatCount));
     List->Add(FormatFloat("00.00",TimeStep));
    }
   FirstClick=false;

   if(P2.x<P1.x)
    {
     MessageDlg("First point must be less than second point ...!",mtError,TMsgDlgButtons()<<mbOK,0);
     return;
    }

   Image1->Canvas->Pen->Mode=pmCopy;
   Image1->Canvas->Pen->Color=clBlue;
   Image1->Canvas->MoveTo(P1.x,P1.y);
   Image1->Canvas->LineTo(P2.x,P2.y);

   Divide(P1,P2,TimeStep,List);

   Image1->Canvas->Pen->Mode=pmNotXor;
   Image1->Canvas->Pen->Color=clBlue;
  }
 else
  {
   Clicked=false;
   FirstClick=true;

   Image1->Canvas->Pen->Color=clWhite;
   Image1->Canvas->Pen->Mode=pmCopy;
   Image1->Canvas->Brush->Color=clWhite;
   Image1->Canvas->Brush->Style=bsSolid;
   Image1->Canvas->Rectangle(0,0,Image1->Width,Image1->Height);

   SaveDialog1->Filter="Wave Form Files (*.wff)|*.wff";
   SaveDialog1->DefaultExt="wff";
   if(SaveDialog1->Execute())
    {
     TStringList *List1=new TStringList();

     List1->Add(List->Strings[0]);
     List1->Add(List->Strings[1]);
     List->Delete(0);
     List->Delete(0);

     Series1->Clear();
     float TimeScale=CSpinEdit6->Value/187.0;
     float x=P1.x*TimeScale;
     for(int i=0;i<List->Count;i++)
      {
       x+=TimeStep;
       Series1->AddXY(x,StrToFloat(List->Strings[i]),"",clRed);
      } 
      
     for(int j=0;j<RepeatCount;j++)
      {
       for(int i=0;i<List->Count;i++)
        List1->Add(List->Strings[i]);
      }
     List1->SaveToFile(SaveDialog1->FileName);

     if(List1)
      delete List1;
    }
  }
 P1=P2;
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::Image1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
 float TimeScale=float(float(CSpinEdit6->Value)/1000.0)/187.0;
 NY=Image1->Height-1-Y;
 Panel11->Caption=FormatFloat("00.00",X*TimeScale)+" , "+FormatFloat("00.00",NY*VoltScale);
 if(Clicked)
  {
   Image1->Canvas->MoveTo(P1.x,P1.y);
   Image1->Canvas->LineTo(P2.x,P2.y);

   P2=Point(X,Y);

   Image1->Canvas->MoveTo(P1.x,P1.y);
   Image1->Canvas->LineTo(P2.x,P2.y);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::ASegmentsExecute(TObject *Sender)
{
 Notebook1->ActivePage="Segment";
 Series1->Clear();
 CGauge1->Progress=0;
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::BitBtn2Click(TObject *Sender)
{
 OpenDialog1->Filter="Wave Form Files (*.wff)|*.wff";
 OpenDialog1->DefaultExt="wff";
 if(OpenDialog1->Execute())
  {
   ListOpen->LoadFromFile(OpenDialog1->FileName);

   RepeatCount=StrToFloat(ListOpen->Strings[0]);
   TimeStep=StrToFloat(ListOpen->Strings[1]);
   ListOpen->Delete(0);
   ListOpen->Delete(0);

   DateTimePicker1->Date=0;
   DateTimePicker2->Time=0;
   StartTime=DateTimePicker1->Time+DateTimePicker2->Date;

   Series1->Clear();
   CGauge1->Progress=0;
   PointNo=-1;
   StatusBar1->Panels->Items[0]->Text="";
   time=0;
   BitBtn2->Enabled=false;
   BitBtn5->Enabled=true;

   Word h,m,s,ms;
   StartTime.DecodeTime(&h,&m,&s,&ms);
   TStart=1000*(h*60*60+m*60+s)+ms;
   DWORD TInterval=TimeStep*1000.0*ListOpen->Count;
   A=(CGauge1->MaxValue-CGauge1->MinValue)/(TInterval);
   B=CGauge1->MinValue-A*TStart;

   IsFirst=true;
   
   Timer1->Interval=TimeStep*1000.0;
   Timer1->Enabled=true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::Timer1Timer(TObject *Sender)
{
 SysTime=Time()+Date();

 if(SysTime>=StartTime)
  {
   Panel10->Caption="Sending ...";
   if(IsFirst)
    StartM=timeGetTime();
   IsFirst=false;

   Word h,m,s,ms;
   SysTime.DecodeTime(&h,&m,&s,&ms);
   DWORD T=1000*(h*60*60+m*60+s)+ms;
   CGauge1->Progress=Round(A*T+B);
   if(CGauge1->Progress>=CGauge1->MaxValue-CGauge1->MinValue)
    {
     Timer1->Enabled=false;
     BitBtn2->Enabled=true;
     BitBtn5->Enabled=false;
     Panel10->Caption="";
     Panel12->Caption="";
     StatusBar1->Panels->Items[0]->Text="Send time finished successfully ...";
     return;
    }

   // Sending Data
   PointNo++;
   float f=StrToFloat(ListOpen->Strings[PointNo]);
   UOP7907.uop7907_set_voltage_value(UOP7907.instr_ID,f);

   // Display performance graph
   if(CheckBox1->Checked)
    {
     Plot(time,f);
     time+=TimeStep;
     Panel12->Caption=FormatFloat("0.00",f)+" %";
    }

   StatusBar1->Panels->Items[0]->Text="Sending ...";
  }
 else
  {
   Panel10->Caption="Waiting ...";
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInterface::Stop()
{
 Timer1->Enabled=false;
 BitBtn2->Enabled=true;
 BitBtn5->Enabled=false;
 Panel10->Caption="";
 CGauge1->Progress=0;
 StatusBar1->Panels->Items[0]->Text="Measure process stopped ...";
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::BitBtn5Click(TObject *Sender)
{
 Stop();        
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::BitBtn6Click(TObject *Sender)
{
 float A,B,C;
 try
  {
   A=StrToFloat(Edit1->Text);
  }
 catch(...)
  {
   MessageDlg("Error in reading A value...",mtError,TMsgDlgButtons()<<mbOK,0);
   return;
  }
 if(A+Y0>=VoltLimit)
  {
   MessageDlg("Maximum value of the voltage must be less than "+FormatFloat("0.0",VoltLimit)+"...",mtError,TMsgDlgButtons()<<mbOK,0);
   return;
  }
 B=StrToFloat(Edit4->Text); 
 try
  {
   C=DegToRad(StrToFloat(Edit5->Text));
  }
 catch(...)
  {
   MessageDlg("Error in reading C value...",mtError,TMsgDlgButtons()<<mbOK,0);
   return;
  }
 try
  {
   Y0=StrToFloat(Edit6->Text);
  }
 catch(...)
  {
   MessageDlg("Error in reading Voltage offset value...",mtError,TMsgDlgButtons()<<mbOK,0);
   return;
  }

 TimeStep=float(CSpinEdit2->Value*60+CSpinEdit3->Value)+float(CSpinEdit4->Value)/1000.0;
 RepeatCount=CSpinEdit1->Value;

 List->Clear();
 List->Add(FormatFloat("00.00",RepeatCount));
 List->Add(FormatFloat("00.00",TimeStep));
 for(int i=0;i<RepeatCount;i++)
  {
   DivideSin(A,B,C,TimeStep,List);
   if(i==0)
    {
     Series1->Clear();
     float x=0.0;
     for(int j=0;j<List->Count-2;j++)
      {
       x+=TimeStep;
       Series1->AddXY(x,StrToFloat(List->Strings[j+2]),"",clRed);
      }
    }
  }

 SaveDialog1->Filter="Sin Files (*.sin)|*.sin";
 SaveDialog1->DefaultExt="sin";
 if(SaveDialog1->Execute())
  {
   List->SaveToFile(SaveDialog1->FileName);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::FormActivate(TObject *Sender)
{
   if(InParams->Params[0]->Index!=1)
    VoltLimit=50.0;
   else
    VoltLimit=9.99;
   VoltScale=VoltLimit/146.0;

   if(InParams->Params[1]->Index!=1)
    BitBtn3->Enabled=false;
   else
    BitBtn3->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::BitBtn4Click(TObject *Sender)
{
 OpenDialog1->Filter="Sin Files (*.sin)|*.sin";
 OpenDialog1->DefaultExt="sin";
 if(OpenDialog1->Execute())
  {
   ListOpen->LoadFromFile(OpenDialog1->FileName);

   RepeatCount=StrToFloat(ListOpen->Strings[0]);
   TimeStep=StrToFloat(ListOpen->Strings[1]);
   ListOpen->Delete(0);
   ListOpen->Delete(0);

   DateTimePicker1->Date=0;
   DateTimePicker2->Time=0;
   StartTime=DateTimePicker1->Time+DateTimePicker2->Date;

   Series1->Clear();
   CGauge1->Progress=0;
   PointNo=-1;
   StatusBar1->Panels->Items[0]->Text="";
   time=0;

   Word h,m,s,ms;
   StartTime.DecodeTime(&h,&m,&s,&ms);
   TStart=1000*(h*60*60+m*60+s)+ms;
   DWORD TInterval=TimeStep*1000.0*ListOpen->Count;
   A=(CGauge1->MaxValue-CGauge1->MinValue)/(TInterval);
   B=CGauge1->MinValue-A*TStart;

   IsFirst=true;
   
   Timer1->Interval=TimeStep*1000.0;
   Timer1->Enabled=true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::BitBtn1Click(TObject *Sender)
{
 Stop();        
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::CSpinEdit6Change(TObject *Sender)
{
 float T=float(CSpinEdit6->Value)/1000.0;
 if(T>0.0)
  Edit4->Text=FormatFloat("00.00",2.0*PI/T);
}
//---------------------------------------------------------------------------

