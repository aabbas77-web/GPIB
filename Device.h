//---------------------------------------------------------------------------
#ifndef DeviceH
#define DeviceH
//---------------------------------------------------------------------------
#include "Params.h"
#include "Measure.h"
//---------------------------------------------------------------------------
typedef void  (*F_CreateInterface)();
typedef void  (*F_DestroyInterface)();
typedef void  (*F_ShowInterface)();
typedef void  (*F_ShowModalInterface)();
typedef void  (*F_CloseInterface)();
typedef bool  (*F_ExecuteInterface)(TMeasures *);
typedef void  (*F_GetMeasures)(TMeasures *);
typedef void  (*F_DeviceInit)(int);
typedef void  (*F_DeviceClose)();
typedef void  (*F_SendParameters)(TAParams *);
typedef void  (*F_GetInParameters)(TAParams *);
typedef void  (*F_GetOutParameters)(TAParams *);
typedef int   (*F_GetInteger)();
typedef char *(*F_GetString)();
//---------------------------------------------------------------------------
class TDevice
{
private:
        F_DeviceClose FDeviceClose;
        F_DeviceInit FDeviceInit;
        F_CreateInterface FCreateInterface;
        F_DestroyInterface FDestroyInterface;
        F_ShowInterface FShowInterface;
        F_ShowModalInterface FShowModalInterface;
        F_CloseInterface FCloseInterface;
        F_ExecuteInterface FExecuteInterface;
        F_GetMeasures FGetMeasures;
        F_SendParameters FSendParameters;
        F_GetInParameters FGetInParameters;
        F_GetOutParameters FGetOutParameters;
        F_GetInteger FGetDeviceAddress;
        F_GetString FGetDeviceName;
        F_GetString FGetDeviceFilter;
        F_GetString FGetDeviceExtention;

        AnsiString FDeviceFilter;
        AnsiString FDeviceExtention;

protected:
        AnsiString FDeviceDLL;
        AnsiString FDeviceName;
        int        FDeviceAddress;
        bool       FModified;
        bool       FLoaded;
        bool       FCreated;
        HINSTANCE  hLib;
public:
       TDevice();
       ~TDevice();

       TAParams *InParams;
       TAParams *OutParams;
       TMeasures *Measures;

       void Error(AnsiString Function);
       AnsiString GetDeviceName(AnsiString FileName);
       void Load(AnsiString FileName,bool Create);

       void DeviceInit(int Address);
       void DeviceClose();
       bool ExecuteInterface();
       void SendParameters();

       void GetMeasures();
       void CreateInterface();
       void DestroyInterface();
       void ShowInterface();
       void ShowModalInterface();
       void CloseInterface();

       __property AnsiString DeviceName={read=FDeviceName};
       __property AnsiString DeviceFilter={read=FDeviceFilter};
       __property AnsiString DeviceExtention={read=FDeviceExtention};
       __property AnsiString DeviceDLL={read=FDeviceDLL};
       __property int DeviceAddress={read=FDeviceAddress};
       __property bool Modified={read=FModified,write=FModified};
       __property bool Loaded={read=FLoaded};
};
//---------------------------------------------------------------------------
#endif
