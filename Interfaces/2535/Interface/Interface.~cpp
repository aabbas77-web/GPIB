//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Interface.h"
#include "Single.h"
#include <mmSystem.h>
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

void __fastcall TFormInterface::FormCreate(TObject *Sender)
{
 OutParams=new TAParams();
 InParams=new TAParams();
 Measures=new TMeasures();

 PointCount=100;

 EnableControls(false);
}
//---------------------------------------------------------------------------
void __fastcall TFormInterface::Init()
{
 for(int i=0;i<OutParams->Count;i++)
  {
   switch(OutParams->Params[i]->Group)
    {
     case 0:
      {
       ComboBox1->Items->Add(OutParams->Params[i]->Name);
       break;
      }
     case 1:
      {
//       ComboBox2->Items->Add(OutParams->Params[i]->Name);
       break;
      }
     case 2:
      {
//       ComboBox3->Items->Add(OutParams->Params[i]->Name);
       break;
      }
     case 3:
      {
//       ComboBox5->Items->Add(OutParams->Params[i]->Name);
       break;
      }
    }
  }
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
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::ListBoxChanged()
{
 ComboBox4->Items->Assign(ListBox1->Items);
 ComboBox4->Text="";
 int Index;
 Index=ComboBox4->Items->IndexOf("StartTime");
 if(Index>=0)
  ComboBox4->Items->Delete(Index);
 Index=ComboBox4->Items->IndexOf("EndTime");
 if(Index>=0)
  ComboBox4->Items->Delete(Index);
 Index=ComboBox4->Items->IndexOf("MeanTime");
 if(Index>=0)
  ComboBox4->Items->Delete(Index);
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::ComboBox1Change(TObject *Sender)
{
 TComboBox *pComboBox=(TComboBox *)Sender;
 if(pComboBox)
  {
   if(ListBox1->Items->IndexOf(pComboBox->Text)<=-1)
    {
     ListBox1->Items->Add(pComboBox->Text);
     ListBoxChanged();
    }

   switch(pComboBox->Tag)
    {
     case 0:
      {
//       PM3000.pm3000_conf_meas_select_list(PM3000.instr_ID,0,pComboBox->ItemIndex + 5);
       break;
      }
     case 1:
      {
//       PM3000.pm3000_conf_meas_select_list(PM3000.instr_ID,0,pComboBox->ItemIndex + 5);
       break;
      }
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::Measure(TStringList *List)
{
 // Add new record
 if(!IsSingle)
  {
   Table1->Append();

   StartT=timeGetTime()-StartM;
   Table1->FieldByName("StartTime")->AsString=FormatFloat("0.000",StartT);
  }

 double Value=0.0;

 // Third Group
 if(ComboBox1->Text!="")
  {
   float function_value;//return just one value
   int Error=PM2535.pm2535_set_function (PM2535.instr_ID, ComboBox1->ItemIndex);
   if(Error!=0)
    {
     Stop();
     PM2535.gpiberr("Error Set Function Data");
     return;
    }
   Error=PM2535.pm2535_measure (PM2535.instr_ID, function_value);
   if(Error!=0)
    {
     Stop();
     PM2535.gpiberr("Error Read Result ");
     return;
    }
   AnsiString Name=ComboBox1->Text;
   if(!IsSingle)
    {
     if(ComboBox4->Text==Name)
      Value=function_value;

     Table1->FieldByName(Name)->AsString=FormatFloat("0.000",function_value);
    }
   else
    List->Add(Name+" = "+FormatFloat("0.000",function_value));
  }


/*
 // Third Group
 if(ComboBox1->Text!="")
  {
   float function_value;//return just one value
   int Error=PM2535.pm2535_set_function (PM2535.instr_ID, ComboBox1->ItemIndex);
   if(Error!=0)
    {
     Stop();
     PM2535.gpiberr("Error Set Function Data");
     return;
    }
   Error=PM2535.pm2535_measure (PM2535.instr_ID, function_value);
   if(Error!=0)
    {
     Stop();
     PM2535.gpiberr("Error Read Result ");
     return;
    }
   AnsiString Name=ComboBox1->Text;
   if(!IsSingle)
    {
     if(ComboBox4->Text==Name)
      Value=fun_value;

     Table1->FieldByName(Name)->AsString=FormatFloat("0.000",fun_value);
    }
   else
    List->Add(Name+" = "+FormatFloat("0.000",fun_value));
  }

 // Forth Group
 if(ComboBox5->Text!="")
  {
   float fun_value;//return just one value
   int Error=PM3000.pm3000_meas_read_single_meas(PM3000.instr_ID, InParams->Params[8]->Index, ComboBox5->ItemIndex, fun_value);
   if(Error!=0)
    {
     Stop();
     PM3000.gpiberr("Error Read Fundamental Function Data");
     return;
    }
   AnsiString Name=ComboBox5->Text;
   if(!IsSingle)
    {
     if(ComboBox4->Text==Name)
      Value=fun_value;

     Table1->FieldByName(Name)->AsString=FormatFloat("0.000",fun_value);
    }
   else
    List->Add(Name+" = "+FormatFloat("0.000",fun_value));
  }
*/
 if(!IsSingle)
  {
   EndT=timeGetTime()-StartM;
   Table1->FieldByName("EndTime")->AsString=FormatFloat("0.000",EndT);
   // Replace this the mean value
   Table1->FieldByName("MeanTime")->AsString=FormatFloat("0.000",(EndT+StartT)/2.0);
   // Save last record
   Table1->Post();
  }

 // Display performance graph
 if(!IsSingle)
  {
   if(CheckBox1->Checked)
    {
     Plot(StartT,Value);
     Panel12->Caption=FormatFloat("000.000",Value)+" %";
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormInterface::BitBtn3Click(TObject *Sender)
{
 IsSingle=true;
 TStringList *List=new TStringList();
 TFormSingle *Form=new TFormSingle(Application);

 Measure(List);
 for(int i=0;i<List->Count-3;i++)
  Form->RichEdit1->Lines->Add(List->Strings[i]);
 Form->ShowModal();

 if(List)
  delete List;
 if(Form)
  delete Form;
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::Timer1Timer(TObject *Sender)
{
 SysTime=Time()+Date();

 if(SysTime>=StartTime)
  {
   Panel10->Caption="Measuring ...";
   if(IsFirst)
    StartM=timeGetTime();
   IsFirst=false;

   if(SysTime>=EndTime)
    {
     Timer1->Enabled=false;
     ANewMeasure->Enabled=true;
     BitBtn1->Enabled=false;
     Panel10->Caption="";
     Table1->Active=false;
     StatusBar1->Panels->Items[0]->Text="Measure time finished successfully ...";
     return;
    }

   // Read measure And Store in Database
   Measure(NULL);

   StatusBar1->Panels->Items[0]->Text="Measuring ...";

   Word h,m,s,ms;
   SysTime.DecodeTime(&h,&m,&s,&ms);
   DWORD T=1000*(h*60*60+m*60+s)+ms;
   CGauge1->Progress=Round(A*T+B);
  }
 else
  {
   Panel10->Caption="Waiting ...";
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::BitBtn4Click(TObject *Sender)
{
 DateTimePicker1->Date=0;
 DateTimePicker2->Time=0;
 StartTime=DateTimePicker1->Time+DateTimePicker2->Date;

 DateTimePicker3->Date=0;
 DateTimePicker4->Time=0;
 EndTime=DateTimePicker3->Time+DateTimePicker4->Date;

 if(EndTime<=StartTime)
  {
   MessageDlg("Start time must be less than end time ...!",mtError,TMsgDlgButtons()<<mbOK,0);
   return;
  }

 // Create new table for the newer measurement
 Path=ExtractFilePath(Application->ExeName)+"Results\\";
 if(!DirectoryExists(Path))
  {
   MessageDlg(("["+Path+"] not found,\n I`ll create it for you ...!?").c_str(),mtInformation,TMsgDlgButtons()<<mbOK,0);
   CreateDir(Path);
  }
 if(ListBox1->Items->Count<=0)
  {
   MessageDlg("You must select parameters for measuring ...!",mtInformation,TMsgDlgButtons()<<mbOK,0);
   return;
  }
 if(Edit1->Text.IsEmpty())
  {
   MessageDlg("You must enter a title for this measure ...!",mtInformation,TMsgDlgButtons()<<mbOK,0);
   return;
  }
 SaveDialog1->InitialDir=Path;
 if(!SaveDialog1->Execute())
  return;
 TableName=ExtractFileName(SaveDialog1->FileName);
 CreateTable(Path,TableName);

 Table1->Active=false;
 Table1->DatabaseName=Path;
 Table1->TableName=TableName;
 Table1->Active=true;

 ListBox1->Items->Add("StartTime");
 ListBox1->Items->Add("EndTime");
 ListBox1->Items->Add("MeanTime");

 Word h,m,s,ms;
 StartTime.DecodeTime(&h,&m,&s,&ms);
 TStart=1000*(h*60*60+m*60+s)+ms;
 EndTime.DecodeTime(&h,&m,&s,&ms);
 TEnd=1000*(h*60*60+m*60+s)+ms;
 A=(CGauge1->MaxValue-CGauge1->MinValue)/(TEnd-TStart);
 B=CGauge1->MinValue-A*TStart;

 TMeasure *Measure=new TMeasure();
 Measure->FileName=SaveDialog1->FileName;
 Measure->Title=Edit1->Text;
 Measure->StartTime=StartTime;
 Measure->EndTime=EndTime;

 Measure->Interval.wHour=CSpinEdit1->Value;
 Measure->Interval.wMinute=CSpinEdit2->Value;
 Measure->Interval.wSecond=CSpinEdit3->Value;
 Measure->Interval.wMilliseconds=CSpinEdit4->Value;

 Measure->Params->AddStrings(ListBox1->Items);
 Measure->Comments->Assign(RichEdit1->Lines);
 Measures->Add(Measure);

 IsFirst=true;

 EnableControls(false);

 IsSingle=false;

 DWORD TI=1000*(CSpinEdit1->Value*60*60+CSpinEdit2->Value*60+CSpinEdit3->Value)+CSpinEdit4->Value;
 Timer1->Interval=TI;
 Timer1->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::Timer2Timer(TObject *Sender)
{
 Panel2->Caption=Date().DateString()+"  "+Time().TimeString();        
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::AMeasureExecute(TObject *Sender)
{
//        
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::ANewMeasureExecute(TObject *Sender)
{
 EnableControls(true);
 ANewMeasure->Enabled=false;
 IsFirst=true;
 // Clear Select Lists
// PM3000.pm3000_conf_meas_select_list(PM3000.instr_ID,1,0);
}
//---------------------------------------------------------------------------
void __fastcall TFormInterface::CreateTable(AnsiString Path,AnsiString TableName)
{
 if(FileExists(Path+TableName))
  {
   if(MessageDlg("This table exist in this path, overwrite it ?",mtWarning,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrNo)
    return;
  }

 TTable *Table=new TTable(this); 
 // Deactivate the table before changing its database name
 Table->Active=false;
 Table->DatabaseName=Path;

 // Determine table type
 Table->TableType=ttParadox;
 Table->TableName=TableName;

 // Define Fields
 Table->FieldDefs->Clear();
 TFieldDef *pNewDef;

 pNewDef=Table->FieldDefs->AddFieldDef();
 pNewDef->Name="StartTime";
 pNewDef->DataType=ftFloat;

 pNewDef=Table->FieldDefs->AddFieldDef();
 pNewDef->Name="EndTime";
 pNewDef->DataType=ftFloat;

 pNewDef=Table->FieldDefs->AddFieldDef();
 pNewDef->Name="MeanTime";
 pNewDef->DataType=ftFloat;
 for(int i=0;i<ListBox1->Items->Count;i++)
  {
   pNewDef=Table->FieldDefs->AddFieldDef();
   pNewDef->Name=ListBox1->Items->Strings[i];
   pNewDef->DataType=ftFloat;
  }
  
/*
 pNewDef=Table->FieldDefs->AddFieldDef();
 pNewDef->Name="StartTime";
 pNewDef->DataType=ftString;
 pNewDef->Size=30;

 pNewDef=Table->FieldDefs->AddFieldDef();
 pNewDef->Name="EndTime";
 pNewDef->DataType=ftString;
 pNewDef->Size=30;

 pNewDef=Table->FieldDefs->AddFieldDef();
 pNewDef->Name="MeanTime";
 pNewDef->DataType=ftString;
 pNewDef->Size=30;
 for(int i=0;i<ListBox1->Items->Count;i++)
  {
   pNewDef=Table->FieldDefs->AddFieldDef();
   pNewDef->Name=ListBox1->Items->Strings[i];
   pNewDef->DataType=ftString;
   pNewDef->Size=15;
  }
*/
 // Define Indexs
 Table->IndexDefs->Clear();
 // The first index needn`t to determine its name because it is primary index
 Table->IndexDefs->Add("","StartTime",TIndexOptions()<<ixPrimary<<ixUnique);
 Table->IndexDefs->Add("EndTimeIndex","EndTime",TIndexOptions()<<ixCaseInsensitive);

 // Create the table
 Table->CreateTable();

 if(Table)
  delete Table;
} 
//---------------------------------------------------------------------------

void __fastcall TFormInterface::Delete1Click(TObject *Sender)
{
 int Index;
 Index=ComboBox3->Items->IndexOf(ListBox1->Items->Strings[ListBox1->ItemIndex]);
 if(Index>=0)
  {
   ComboBox3->Text="";
  }

 Index=ComboBox4->Items->IndexOf(ListBox1->Items->Strings[ListBox1->ItemIndex]);
 if(Index>=0)
  {
   ComboBox4->Text="";
  }
 ListBox1->Items->Delete(ListBox1->ItemIndex);
 ListBoxChanged();
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::DeleteAll1Click(TObject *Sender)
{
 ListBox1->Clear();
 ListBoxChanged();

 ComboBox1->Text="";
 ComboBox2->Text="";
 ComboBox3->Text="";
 ComboBox5->Text="";
}
//---------------------------------------------------------------------------
void __fastcall TFormInterface::Stop()
{
 ANewMeasure->Enabled=true;
 Timer1->Enabled=false;
 BitBtn1->Enabled=false;
 Panel10->Caption="";
 Table1->Active=false;
 StatusBar1->Panels->Items[0]->Text="Measure process stopped ...";
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::BitBtn1Click(TObject *Sender)
{
 Stop();	
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
//---------------------------------------------------------------------------

void __fastcall TFormInterface::ComboBox3Change(TObject *Sender)
{
 bool Found=false;
 for(int i=0;i<ComboBox3->Items->Count;i++)
  {
   if(ListBox1->Items->IndexOf(ComboBox3->Items->Strings[i])>=0)
    {
     Found=true;
     break;
    }
  }
 if(!Found)
  {
   ListBox1->Items->Add(ComboBox3->Text);
   ListBoxChanged();
  } 
}
//---------------------------------------------------------------------------
void __fastcall TFormInterface::EnableControls(bool Etat)
{
 if(Etat)
  {
   ComboBox4->Clear();
   ComboBox1->Text="";
   ComboBox2->Text="";
   ComboBox3->Text="";
   ComboBox5->Text="";

   ComboBox1->ItemIndex=-1;
   ComboBox2->ItemIndex=-1;
   ComboBox3->ItemIndex=-1;
   ComboBox5->ItemIndex=-1;

   ListBox1->Clear();
   Series1->Clear();

   Edit1->Text="";
   RichEdit1->Clear();
   CheckBox1->Checked=false;
   Panel12->Caption="";
   StatusBar1->Panels->Items[0]->Text="";

   DateTimePicker1->Time=Time();
   DateTimePicker2->Date=Date();

   DateTimePicker3->Time=Time();
   DateTimePicker4->Date=Date();

   CGauge1->Progress=0;
  }
 BitBtn1->Enabled=true;

 GroupBox1->Enabled=Etat;
 GroupBox2->Enabled=Etat;
 GroupBox3->Enabled=Etat;
 ComboBox4->Enabled=Etat;
 CheckBox1->Checked=((ComboBox4->ItemIndex>=0)?true:false);
 BitBtn4->Enabled=Etat;
 GroupBox4->Enabled=Etat;
 Panel11->Enabled=Etat;
}
//---------------------------------------------------------------------------

void __fastcall TFormInterface::ComboBox5Change(TObject *Sender)
{
 bool Found=false;
 for(int i=0;i<ComboBox5->Items->Count;i++)
  {
   if(ListBox1->Items->IndexOf(ComboBox5->Items->Strings[i])>=0)
    {
     Found=true;
     break;
    }
  }
 if(!Found)
  {
   ListBox1->Items->Add(ComboBox5->Text);
   ListBoxChanged();
  } 
}
//---------------------------------------------------------------------------

