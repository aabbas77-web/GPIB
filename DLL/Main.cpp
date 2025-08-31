//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button1Click(TObject *Sender)
{
 try
  {
   PasswordDLL=LoadLibrary("Test.DLL");
   if(PasswordDLL==NULL)
    {
     MessageDlg("[Test.DLL] Error In Loading Library ...",
                mtError,TMsgDlgButtons()<<mbOK,0);
    }
   GetPassword=(F_GetPassword)GetProcAddress(PasswordDLL,"_GetPassword");
   if(GetPassword!=NULL)
    {
     AnsiString Password;
     bool Status=(GetPassword)(Password);
     if(Status)
      Edit1->Text=Password;
     else
      Edit1->Text="Error ...";
    }
   else
    MessageDlg("Error In Loading [GetPassword] Function (Level 1)",
               mtError,TMsgDlgButtons()<<mbOK,0);
   FreeLibrary(PasswordDLL);
  }
 catch(...)
  {
   MessageDlg("Error In Loading Dipix Data ...",
              mtError,TMsgDlgButtons()<<mbOK,0);
  }
}
//---------------------------------------------------------------------------

