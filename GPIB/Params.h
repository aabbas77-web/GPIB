//---------------------------------------------------------------------------
#ifndef ParamsH
#define ParamsH
//---------------------------------------------------------------------------
#include <IniFiles.hpp>
#include <FileCtrl.hpp>
//---------------------------------------------------------------------------
class TAParam
{
public:
       TAParam();
       ~TAParam();

       AnsiString Name;// Parameter Name
       int Index;// Current Index Or Default Index

       int Group;
       TStringList *Values;// All Possible Values For This Parameter
};
//---------------------------------------------------------------------------
class TAParams
{
private:
        AnsiString FFileName;
        TList *FList;
        bool FModified;
        int FFirstShift;
        int FSecondShift;

        int GetCount();
        TAParam *GetParam(int Index);
        TAParam *GetParamIG(int Index,int Group);
public:
        TAParams();
        ~TAParams();

        void GetSectionValues(TIniFile *IniFile,AnsiString Section,TStrings *Values);

        void SaveToFile(AnsiString FileName,bool withValues);
        void LoadFromFile(AnsiString FileName,bool withValues);

        void Add(TAParam *Param);
        void Clear();
        void Free();
        void Delete(TAParam *Param);
        int  GetItemIndex(int Index,int Group);

        __property AnsiString FileName={read=FFileName};
        __property int Count={read=GetCount};
        __property bool Modified={read=FModified,write=FModified};
        __property TAParam *Params[int]={read=GetParam};
        __property TAParam *ParamsIG[int][int]={read=GetParamIG};
};
//---------------------------------------------------------------------------
#endif
