//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "Session.h"
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include <Graphics.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TActionList *ActionList1;
        TMainMenu *MainMenu1;
        TMenuItem *Devices1;
        TMenuItem *Network1;
        TAction *ASettings;
        TAction *AEdit;
        TMenuItem *ASettings1;
        TMenuItem *AEdit1;
        TMenuItem *N1;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TAction *AFinishSettings;
        TMenuItem *Operations1;
        TMenuItem *FinishSettings1;
        TAction *ASession;
        TAction *ANewSession;
        TAction *AOpenSession;
        TAction *ASaveSession;
        TAction *ASaveAsSession;
        TAction *AExit;
        TMenuItem *ASession1;
        TMenuItem *ANewSession1;
        TMenuItem *N3;
        TMenuItem *AOpenSession1;
        TMenuItem *Saveas1;
        TMenuItem *ASaveSession1;
        TMenuItem *N4;
        TMenuItem *AExit1;
        TAction *ANetwork;
        TAction *AOperations;
        TAction *AFinishAllSettings;
        TMenuItem *FinishAllSettings1;
        TAction *ADevices;
        TAction *AFinishDevices;
        TStatusBar *StatusBar1;
	TImageList *ImageList1;
	TToolBar *ToolBar1;
	TToolButton *ToolButton1;
	TToolButton *ToolButton2;
	TToolButton *ToolButton3;
	TToolButton *ToolButton4;
	TToolButton *ToolButton5;
	TToolButton *ToolButton6;
	TToolButton *ToolButton7;
	TToolButton *ToolButton8;
	TToolButton *ToolButton9;
	TToolButton *ToolButton10;
	TAction *AAnalysing;
	TAction *ADatabaseEditor;
	TMenuItem *Analysing1;
	TAction *AGraph;
	TMenuItem *Graph1;
	TAction *ATools;
	TMenuItem *Tools1;
	TMenuItem *DatabaseEditor1;
        TAction *AHelp;
        TAction *AIndex;
        TAction *AContents;
        TAction *AAbout;
        TMenuItem *Help1;
        TMenuItem *Index1;
        TMenuItem *Contents1;
        TMenuItem *N2;
        TMenuItem *About1;
        TToolButton *ToolButton11;
        TToolButton *ToolButton12;
        TToolButton *ToolButton13;
        TToolButton *ToolButton14;
        TAction *AConfig;
        TMenuItem *Configurations1;
        TMenuItem *N5;
        TToolButton *ToolButton15;
        TImage *Image1;
        TAction *ASelectDevice;
        TAction *ADevice;
        TAction *ADeviceClick;
        TAction *ADraw2Curves;
        TMenuItem *Draw2Curves1;
        TAction *AInfoSession;
        TMenuItem *Information1;
        TToolButton *ToolButton16;
        TToolButton *ToolButton17;
        TToolButton *ToolButton18;
        TToolButton *ToolButton19;
        TToolButton *ToolButton20;
        TToolButton *ToolButton21;
        TAction *ADeviceTester;
        TMenuItem *DeviceTester1;
        TToolButton *ToolButton22;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall AEditExecute(TObject *Sender);
        void __fastcall ASettingsExecute(TObject *Sender);
        void __fastcall AFinishSettingsExecute(TObject *Sender);
        void __fastcall ASessionExecute(TObject *Sender);
        void __fastcall ANewSessionExecute(TObject *Sender);
        void __fastcall AOpenSessionExecute(TObject *Sender);
        void __fastcall ASaveSessionExecute(TObject *Sender);
        void __fastcall ASaveAsSessionExecute(TObject *Sender);
        void __fastcall AExitExecute(TObject *Sender);
        void __fastcall ANetworkExecute(TObject *Sender);
        void __fastcall AOperationsExecute(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall AFinishAllSettingsExecute(TObject *Sender);
        void __fastcall ADevicesExecute(TObject *Sender);
        void __fastcall AFinishDevicesExecute(TObject *Sender);
	void __fastcall AAnalysingExecute(TObject *Sender);
	void __fastcall ADatabaseEditorExecute(TObject *Sender);
	void __fastcall AGraphExecute(TObject *Sender);
	void __fastcall AToolsExecute(TObject *Sender);
        void __fastcall AHelpExecute(TObject *Sender);
        void __fastcall AIndexExecute(TObject *Sender);
        void __fastcall AContentsExecute(TObject *Sender);
        void __fastcall AAboutExecute(TObject *Sender);
        void __fastcall AConfigExecute(TObject *Sender);
        void __fastcall AInterfaceExecute(TObject *Sender);
        void __fastcall ASelectDeviceExecute(TObject *Sender);
        void __fastcall ADeviceExecute(TObject *Sender);
        void __fastcall ADeviceClickExecute(TObject *Sender);
        void __fastcall ADraw2CurvesExecute(TObject *Sender);
        void __fastcall AInfoSessionExecute(TObject *Sender);
        void __fastcall ADeviceTesterExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormMain(TComponent* Owner);
        void __fastcall NewSession();
        void __fastcall FindFiles(AnsiString Path,TStringList *Files);
        AnsiString __fastcall Remove(AnsiString Text,char C);
        void __fastcall Delay(int MS);
	void __fastcall EnableSettings(bool Etat);
	void __fastcall EnableSettings1(bool Etat);

        AnsiString AppPath;
        int FinishNo;
        bool IsNew;
        int DeviceFinishCount;

        TDeviceSession *Session;
        TStringList *Files;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
