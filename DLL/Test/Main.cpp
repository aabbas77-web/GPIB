//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Dialog.h"
//---------------------------------------------------------------------------
#pragma argsused
//---------------------------------------------------------------------------
extern "C" __declspec(dllexport) bool GetPassword(AnsiString &Password);
//---------------------------------------------------------------------------
bool GetPassword(AnsiString &Password)
{
 bool Result=false;
 Password="";
 TFormDialog *Dialog=new TFormDialog(Application);
 if(Dialog->ShowModal()==mrOk)
  {
   Result=true;
   Password=Dialog->Edit1->Text;
  }
 if(Dialog)
  delete Dialog;
 return Result; 
}
//---------------------------------------------------------------------------
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
 return 1;
}
//---------------------------------------------------------------------------
