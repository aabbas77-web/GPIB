//---------------------------------------------------------------------------
#ifndef MeasureH
#define MeasureH
//---------------------------------------------------------------------------
#include "Params.h"
//---------------------------------------------------------------------------
class TMeasure
{
private:
        AnsiString  FFileName;
        AnsiString  FTitle;
        TDateTime   FStartTime;
        TDateTime   FEndTime;
        TSystemTime FInterval;
        TStringList *FComments;
        TStringList *FParams;
public:
        TMeasure();
        ~TMeasure();

        __property AnsiString  FileName={read=FFileName,write=FFileName};
        __property AnsiString  Title={read=FTitle,write=FTitle};
        __property TDateTime   StartTime={read=FStartTime,write=FStartTime};
        __property TDateTime   EndTime={read=FEndTime,write=FEndTime};
        __property TSystemTime   Interval={read=FInterval,write=FInterval};
        __property TStringList *Params={read=FParams,write=FParams};
        __property TStringList *Comments={read=FComments,write=FComments};
};
//---------------------------------------------------------------------------
class TMeasures
{
private:
        TList *FList;
        int FCount;
        bool FModified;

        int GetCount();
        TMeasure *GetMeasure(int Index);
public:
        TMeasures();
        ~TMeasures();

        void Add(TMeasure *Measure);
        void Clear();
        void Free();
        void Delete(TMeasure *Measure);

        __property int Count={read=GetCount};
        __property bool Modified={read=FModified,write=FModified};
        __property TMeasure *Measures[int]={read=GetMeasure};
};
//---------------------------------------------------------------------------
#endif
