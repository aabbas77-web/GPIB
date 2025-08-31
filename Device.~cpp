//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Device.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
TDevice::TDevice()
{
 Measures=new TMeasures();
 InParams=new TAParams();
 OutParams=new TAParams();
 FModified=false;
 FLoaded=false;
 FCreated=false;
}
//---------------------------------------------------------------------------
TDevice::~TDevice()
{
 if(FLoaded)
  {
   if(FCreated)
    DestroyInterface();
   if(!FreeLibrary(hLib))
    Error("FreeLibrary");
  }  
 if(InParams)
  delete InParams;
 InParams=NULL;
 if(OutParams)
  delete OutParams;
 OutParams=NULL;
 if(Measures)
  delete Measures;
 Measures=NULL; 
}
//---------------------------------------------------------------------------
void TDevice::Load(AnsiString FileName,bool Create)
{
 FDeviceDLL=FileName;
 try
  {
   hLib=LoadLibrary(FDeviceDLL.c_str());
   FModified=false;
   if(hLib==NULL)
    {
     Error(FDeviceDLL.c_str());
     if(!FreeLibrary(hLib))
      Error("FreeLibrary");
     FLoaded=false;
     return;
    }

   // Clear Result Files
   Measures->Clear();
   OutParams->Clear();
   InParams->Clear();

   // Device In Parameters
   FGetInParameters=(F_GetInParameters)GetProcAddress(hLib,"_GetDeviceInParameters");
   if(FGetInParameters==NULL)
    {
     FLoaded=false;
     MessageDlg("Error In Loading [GetDeviceInParameters] Function ...",
                mtError,TMsgDlgButtons()<<mbOK,0);
     if(!FreeLibrary(hLib))
      Error("FreeLibrary");
     return;
    }
   (FGetInParameters)(InParams);

   // Device Out Parameters
   FGetOutParameters=(F_GetOutParameters)GetProcAddress(hLib,"_GetDeviceOutParameters");
   if(FGetOutParameters==NULL)
    {
     FLoaded=false;
     MessageDlg("Error In Loading [GetDeviceOutParameters] Function ...",
                mtError,TMsgDlgButtons()<<mbOK,0);
     if(!FreeLibrary(hLib))
      Error("FreeLibrary");
     return;
    }
   (FGetOutParameters)(OutParams);

   // DeviceAddress
   FGetDeviceAddress=(F_GetInteger)GetProcAddress(hLib,"_GetDeviceAddress");
   if(FGetDeviceAddress==NULL)
    {
     FLoaded=false;
     MessageDlg("Error In Loading [GetDeviceAddress] Function ...",
                mtError,TMsgDlgButtons()<<mbOK,0);
     if(!FreeLibrary(hLib))
      Error("FreeLibrary");
     return;
    }
   FDeviceAddress=(FGetDeviceAddress)();

   // DeviceName
   FGetDeviceName=(F_GetString)GetProcAddress(hLib,"_GetDeviceName");
   if(FGetDeviceName==NULL)
    {
     FLoaded=false;
     MessageDlg("Error In Loading [GetDeviceName] Function ...",
                mtError,TMsgDlgButtons()<<mbOK,0);
     if(!FreeLibrary(hLib))
      Error("FreeLibrary");
     return;
    }
   FDeviceName=AnsiString((FGetDeviceName)());

   // DeviceFilter
   FGetDeviceFilter=(F_GetString)GetProcAddress(hLib,"_GetDeviceFilter");
   if(FGetDeviceFilter==NULL)
    {
     FLoaded=false;
     MessageDlg("Error In Loading [GetDeviceFilter] Function ...",
                mtError,TMsgDlgButtons()<<mbOK,0);
     if(!FreeLibrary(hLib))
      Error("FreeLibrary");
     return;
    }
   FDeviceFilter=AnsiString((FGetDeviceFilter)());

   // DeviceExtention
   FGetDeviceExtention=(F_GetString)GetProcAddress(hLib,"_GetDeviceExtention");
   if(FGetDeviceExtention==NULL)
    {
     FLoaded=false;
     MessageDlg("Error In Loading [GetDeviceExtention] Function ...",
                mtError,TMsgDlgButtons()<<mbOK,0);
     if(!FreeLibrary(hLib))
      Error("FreeLibrary");
     return;
    }
   FDeviceExtention=AnsiString((FGetDeviceExtention)());
   FLoaded=true;

   FCreated=Create;
   if(FCreated)
    CreateInterface();
  }
 catch(...)
  {
   MessageDlg("Error In Loading Device Data ...",
              mtError,TMsgDlgButtons()<<mbOK,0);
   if(!FreeLibrary(hLib))
    Error("FreeLibrary");
   FLoaded=false;
   return;
  }
}
//---------------------------------------------------------------------------
void TDevice::SendParameters()
{
 if(FLoaded)
  {
   // SendParameters
   FSendParameters=(F_SendParameters)GetProcAddress(hLib,"_SendParameters");
   if(FSendParameters==NULL)
    {
     MessageDlg("Error In Loading [SendParameters] Function ...",
                mtError,TMsgDlgButtons()<<mbOK,0);
     if(!FreeLibrary(hLib))
      Error("FreeLibrary");
     return;
    }

   (FSendParameters)(InParams);
  }
 else
  {
   MessageDlg("Device library not loaded...",
              mtError,TMsgDlgButtons()<<mbOK,0);
  }
}
//---------------------------------------------------------------------------
void TDevice::CreateInterface()
{
 if(FLoaded)
  {
   // CreateInterface
   FCreateInterface=(F_CreateInterface)GetProcAddress(hLib,"_CreateInterface");
   if(FCreateInterface==NULL)
    {
     MessageDlg("Error In Loading [CreateInterface] Function ...",
                mtError,TMsgDlgButtons()<<mbOK,0);
     if(!FreeLibrary(hLib))
      Error("FreeLibrary");
     return;
    }

   (FCreateInterface)();
   FCreated=true;
   FModified=true;
  }
 else
  {
   MessageDlg("Device library not loaded...",
              mtError,TMsgDlgButtons()<<mbOK,0);
   return;
  }
}
//---------------------------------------------------------------------------
void TDevice::DestroyInterface()
{
 if(FLoaded)
  {
   // DestroyInterface
   FDestroyInterface=(F_DestroyInterface)GetProcAddress(hLib,"_DestroyInterface");
   if(FDestroyInterface==NULL)
    {
     MessageDlg("Error In Loading [DestroyInterface] Function ...",
                mtError,TMsgDlgButtons()<<mbOK,0);
     if(!FreeLibrary(hLib))
      Error("FreeLibrary");
     return;
    }

   (FDestroyInterface)();
   FCreated=false;
   FModified=true;
  }
 else
  {
   MessageDlg("Device library not loaded...",
              mtError,TMsgDlgButtons()<<mbOK,0);
   return;
  }
}
//---------------------------------------------------------------------------
void TDevice::ShowInterface()
{
 if(FLoaded)
  {
   // ShowInterface
   FShowInterface=(F_ShowInterface)GetProcAddress(hLib,"_ShowInterface");
   if(FShowInterface==NULL)
    {
     MessageDlg("Error In Loading [ShowInterface] Function ...",
                mtError,TMsgDlgButtons()<<mbOK,0);
     if(!FreeLibrary(hLib))
      Error("FreeLibrary");
     return;
    }

   (FShowInterface)();
   FModified=true;
  }
 else
  {
   MessageDlg("Device library not loaded...",
              mtError,TMsgDlgButtons()<<mbOK,0);
   return;
  }
}
//---------------------------------------------------------------------------
void TDevice::ShowModalInterface()
{
 if(FLoaded)
  {
   // ShowModalInterface
   FShowModalInterface=(F_ShowModalInterface)GetProcAddress(hLib,"_ShowModalInterface");
   if(FShowModalInterface==NULL)
    {
     MessageDlg("Error In Loading [ShowModalInterface] Function ...",
                mtError,TMsgDlgButtons()<<mbOK,0);
     if(!FreeLibrary(hLib))
      Error("FreeLibrary");
     return;
    }

   (FShowModalInterface)();
   FModified=true;
  }
 else
  {
   MessageDlg("Device library not loaded...",
              mtError,TMsgDlgButtons()<<mbOK,0);
   return;
  }
}
//---------------------------------------------------------------------------
void TDevice::CloseInterface()
{
 if(FLoaded)
  {
   // CloseInterface
   FCloseInterface=(F_CloseInterface)GetProcAddress(hLib,"_CloseInterface");
   if(FCloseInterface==NULL)
    {
     MessageDlg("Error In Loading [CloseInterface] Function ...",
                mtError,TMsgDlgButtons()<<mbOK,0);
     if(!FreeLibrary(hLib))
      Error("FreeLibrary");
     return;
    }

   (FCloseInterface)();
   FModified=true;
  }
 else
  {
   MessageDlg("Device library not loaded...",
              mtError,TMsgDlgButtons()<<mbOK,0);
   return;
  }
}
//---------------------------------------------------------------------------
bool TDevice::ExecuteInterface()
{
 if(FLoaded)
  {
   // ExecuteInterface
   FExecuteInterface=(F_ExecuteInterface)GetProcAddress(hLib,"_ExecuteInterface");
   if(FExecuteInterface==NULL)
    {
     MessageDlg("Error In Loading [ExecuteInterface] Function ...",
                mtError,TMsgDlgButtons()<<mbOK,0);
     if(!FreeLibrary(hLib))
      Error("FreeLibrary");
     return false;
    }

   bool Result=(FExecuteInterface)(Measures);
   FModified=true;

   return Result;
  }
 else
  {
   MessageDlg("Device library not loaded...",
              mtError,TMsgDlgButtons()<<mbOK,0);
   return false;
  }
}
//---------------------------------------------------------------------------
void TDevice::GetMeasures()
{
 if(FLoaded)
  {
   // GetMeasures
   FGetMeasures=(F_GetMeasures)GetProcAddress(hLib,"_GetMeasures");
   if(FGetMeasures==NULL)
    {
     MessageDlg("Error In Loading [GetMeasures] Function ...",
                mtError,TMsgDlgButtons()<<mbOK,0);
     if(!FreeLibrary(hLib))
      Error("FreeLibrary");
     return;
    }

   (FGetMeasures)(Measures);
   FModified=true;
  }
 else
  {
   MessageDlg("Device library not loaded...",
              mtError,TMsgDlgButtons()<<mbOK,0);
   return;
  }
}
//---------------------------------------------------------------------------
void TDevice::Error(AnsiString Function)
{
 DWORD dw = GetLastError();
 AnsiString Text="["+Function+"] failed... ,\n and returned the Code Error: "+IntToStr(dw);
 MessageDlg(Text.c_str(),mtError,TMsgDlgButtons()<<mbOK,0);
}
//---------------------------------------------------------------------------
void TDevice::DeviceInit(int Address)
{
 if(FLoaded)
  {
   // DeviceInit
   FDeviceInit=(F_DeviceInit)GetProcAddress(hLib,"_DeviceInit");
   if(FDeviceInit==NULL)
    {
     MessageDlg("Error In Loading [DeviceInit] Function ...",
                mtError,TMsgDlgButtons()<<mbOK,0);
     return;
    }

    FDeviceAddress=Address;
   (FDeviceInit)(FDeviceAddress);
  }
 else
  {
   MessageDlg("Device library not loaded...",
              mtError,TMsgDlgButtons()<<mbOK,0);
  }
}
//---------------------------------------------------------------------------
void TDevice::DeviceClose()
{
 if(FLoaded)
  {
   // DeviceClose
   FDeviceClose=(F_DeviceClose)GetProcAddress(hLib,"_DeviceClose");
   if(FDeviceClose==NULL)
    {
     MessageDlg("Error In Loading [DeviceClose] Function ...",
                mtError,TMsgDlgButtons()<<mbOK,0);
     if(!FreeLibrary(hLib))
      Error("FreeLibrary");
     return;
    }

   (FDeviceClose)();
  }
 else
  {
   MessageDlg("Device library not loaded...",
              mtError,TMsgDlgButtons()<<mbOK,0);
  }
}
//---------------------------------------------------------------------------
AnsiString TDevice::GetDeviceName(AnsiString FileName)
{
 HINSTANCE hLib=LoadLibrary(FileName.c_str());
 if(hLib==NULL)
  {
   FreeLibrary(hLib);
   return "";
  }

 // DeviceName
 FGetDeviceName=(F_GetString)GetProcAddress(hLib,"_GetDeviceName");
 if(FGetDeviceName==NULL)
  {
   FreeLibrary(hLib);
   return "";
  }
 FDeviceName=AnsiString((FGetDeviceName)());
 FreeLibrary(hLib);
 return FDeviceName;
}
//---------------------------------------------------------------------------

