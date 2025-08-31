//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("GPIB.res");
USEFORM("Main.cpp", FormMain);
USEFORM("Edit.cpp", FormEdit);
USEUNIT("Device.cpp");
USEUNIT("Session.cpp");
USEUNIT("Params.cpp");
USEUNIT("GPIBDLL.cpp");
USEFORM("Address.cpp", FormAddress);
USEFORM("Progress.cpp", FormProgress);
USEFORM("Editor.cpp", FormEditor);
USEFORM("Graph.cpp", FormGraph);
USEFORM("Axis.cpp", FormAxis);
USEUNIT("Measure.cpp");
USEFORM("Config.cpp", FormConfig);
USEFORM("Settings.cpp", FormSettings);
USEFORM("Draw2Curves.cpp", FormDraw2Curves);
USEFORM("Format.cpp", FormFormat);
USEFORM("Info.cpp", FormInfo);
USEFORM("DeviceTester.cpp", FormDeviceTester);
USEFORM("Start.cpp", FormStart);
//---------------------------------------------------------------------------
#include "Start.h"
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 TFormStart *Form=new TFormStart(Application);
                 Form->Show();
                 Form->Update();

                 Application->Initialize();
                 Application->Title = "GPIB V1.0";
                 Application->HelpFile = "E:\\Mazen\\GPIB\\GPIB.HLP";
                 Application->CreateForm(__classid(TFormMain), &FormMain);
		Application->CreateForm(__classid(TFormConfig), &FormConfig);
		Application->CreateForm(__classid(TFormEdit), &FormEdit);
		Application->CreateForm(__classid(TFormAddress), &FormAddress);
		Application->CreateForm(__classid(TFormProgress), &FormProgress);
		Application->CreateForm(__classid(TFormEditor), &FormEditor);
		Application->CreateForm(__classid(TFormGraph), &FormGraph);
		Application->CreateForm(__classid(TFormSettings), &FormSettings);
		Application->CreateForm(__classid(TFormDraw2Curves), &FormDraw2Curves);
		Application->CreateForm(__classid(TFormAxis), &FormAxis);
		Application->CreateForm(__classid(TFormFormat), &FormFormat);
		Application->CreateForm(__classid(TFormInfo), &FormInfo);
		Application->CreateForm(__classid(TFormDeviceTester), &FormDeviceTester);
		Application->CreateForm(__classid(TFormStart), &FormStart);
		Form->Close();
                 if(Form)
                  delete Form;

                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
