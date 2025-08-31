//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "GPIBDLL.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
TGPIB::TGPIB()
{
}
//---------------------------------------------------------------------------
TGPIB::~TGPIB()
{
}
//---------------------------------------------------------------------------
void TGPIB::Load(AnsiString FileName)
{
 FDeviceDLL=FileName;
 HINSTANCE hLib;
 try
  {
   if(FLoaded)
    {
     MessageDlg("Library is loaded... ["+FDeviceDLL+"]",
                mtError,TMsgDlgButtons()<<mbOK,0);
     return;
    }
   hLib=LoadLibrary(FDeviceDLL.c_str());
   if(hLib==NULL)
    {
     Error(FDeviceDLL.c_str());
     FreeLibrary(hLib);
     FLoaded=false;
     return;
    }
   FreeLibrary(hLib);
   FLoaded=true;
  }
 catch(...)
  {
   MessageDlg("Error In Loading Device Data ...",
              mtError,TMsgDlgButtons()<<mbOK,0);
   FreeLibrary(hLib);
   FLoaded=false;
   return;
  }
}
//---------------------------------------------------------------------------
void TGPIB::Error(AnsiString Function)
{
 DWORD dw = GetLastError();
 AnsiString Text="["+Function+"] failed... ,\n and returned the Code Error: "+IntToStr(dw);
 MessageDlg(Text.c_str(),mtError,TMsgDlgButtons()<<mbOK,0);
}
//---------------------------------------------------------------------------
int *TGPIB::Pibsta()
{
 if(FLoaded)
  {
   HINSTANCE hLib=LoadLibrary(FDeviceDLL.c_str());
   if(hLib==NULL)
    {
     Error(FDeviceDLL.c_str());
     FreeLibrary(hLib);
     return NULL;
    }

   // Pibsta
   FPibsta=(F_Pibsta)GetProcAddress(hLib,"user_ibsta");
   if(FPibsta==NULL)
    {
     MessageDlg("Error In Loading [user_ibsta] Function ...",
                mtError,TMsgDlgButtons()<<mbOK,0);
     FreeLibrary(hLib);
     return NULL;
    }

   int *Result=(FPibsta)();
   FreeLibrary(hLib);

   return Result;
  }
 else
  {
   MessageDlg("GPIB library not loaded...",
              mtError,TMsgDlgButtons()<<mbOK,0);
   return NULL;           
  } 
}
//---------------------------------------------------------------------------
int *TGPIB::Piberr()
{
 if(FLoaded)
  {
   HINSTANCE hLib=LoadLibrary(FDeviceDLL.c_str());
   if(hLib==NULL)
    {
     Error(FDeviceDLL.c_str());
     FreeLibrary(hLib);
     return NULL;
    }

   // Piberr
   FPiberr=(F_Pibsta)GetProcAddress(hLib,"user_iberr");
   if(FPiberr==NULL)
    {
     MessageDlg("Error In Loading [user_iberr] Function ...",
                mtError,TMsgDlgButtons()<<mbOK,0);
     FreeLibrary(hLib);
     return NULL;
    }

   int *Result=(FPiberr)();
   FreeLibrary(hLib);

   return Result;
  }
 else
  {
   MessageDlg("GPIB library not loaded...",
              mtError,TMsgDlgButtons()<<mbOK,0);
   return NULL;           
  } 
}
//---------------------------------------------------------------------------
long *TGPIB::Pibcntl()
{
 if(FLoaded)
  {
   HINSTANCE hLib=LoadLibrary(FDeviceDLL.c_str());
   if(hLib==NULL)
    {
     Error(FDeviceDLL.c_str());
     FreeLibrary(hLib);
     return NULL;
    }

   // Pibcntl
   FPibcntl=(F_Pibcntl)GetProcAddress(hLib,"user_ibcnt");
   if(FPibcntl==NULL)
    {
     MessageDlg("Error In Loading [user_ibcnt] Function ...",
                mtError,TMsgDlgButtons()<<mbOK,0);
     FreeLibrary(hLib);
     return NULL;
    }

   long *Result=(FPibcntl)();
   FreeLibrary(hLib);

   return Result;
  }
 else
  {
   MessageDlg("GPIB library not loaded...",
              mtError,TMsgDlgButtons()<<mbOK,0);
   return NULL;           
  } 
}
//---------------------------------------------------------------------------

