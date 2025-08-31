//---------------------------------------------------------------------------
#ifndef SessionH
#define SessionH
//---------------------------------------------------------------------------
#include "Device.h"
//---------------------------------------------------------------------------
class TDeviceSession
{
private:
        AnsiString FFileName;
        TList *FList;
        AnsiString FPath;
        bool FModified;
        int FDeviceNo;

        int GetCount();
        bool GetModified();
        TDevice *GetDevice(int Index);
public:
       TDeviceSession();
       ~TDeviceSession();

       void GetSectionValues(TIniFile *IniFile,AnsiString Section,TStrings *Values);

       void New();
       void SaveToFile(AnsiString FileName);
       void LoadFromFile(AnsiString FileName);

       void Add(TDevice *Device);
       void Clear();
       void Free();
       void Delete(TDevice *Device);

       AnsiString UntitledName;
       AnsiString SessionsDir;
       AnsiString SettingsDir;
       AnsiString DefaultName;
       AnsiString ResultsDir;
       AnsiString DLLsDir;

       __property AnsiString FileName={read=FFileName};
       __property AnsiString Path={read=FPath}; 
       __property int Count={read=GetCount};
       __property int DeviceNo={read=FDeviceNo,write=FDeviceNo};
       __property bool Modified={read=GetModified,write=FModified};
       __property TDevice *Devices[int]={read=GetDevice};
};
//---------------------------------------------------------------------------
#endif
