object FormConfig: TFormConfig
  Left = 190
  Top = 283
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Configurations'
  ClientHeight = 263
  ClientWidth = 360
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnActivate = FormActivate
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 222
    Width = 360
    Height = 41
    Align = alBottom
    TabOrder = 0
    object BitBtn1: TBitBtn
      Left = 104
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 0
      OnClick = BitBtn1Click
      Kind = bkOK
    end
    object BitBtn2: TBitBtn
      Left = 180
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 1
      Kind = bkCancel
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 360
    Height = 222
    Align = alClient
    TabOrder = 1
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 358
      Height = 220
      ActivePage = TabSheet2
      Align = alClient
      TabOrder = 0
      object TabSheet1: TTabSheet
        Caption = 'GPIB'
      end
      object TabSheet2: TTabSheet
        Caption = 'Session'
        ImageIndex = 1
        object GroupBox1: TGroupBox
          Left = 2
          Top = 4
          Width = 196
          Height = 114
          Caption = 'Directories'
          TabOrder = 0
          object Label1: TLabel
            Left = 8
            Top = 18
            Width = 55
            Height = 13
            BiDiMode = bdLeftToRight
            Caption = 'SessionsDir'
            ParentBiDiMode = False
          end
          object Label2: TLabel
            Left = 8
            Top = 42
            Width = 51
            Height = 13
            BiDiMode = bdLeftToRight
            Caption = 'SettingsDir'
            ParentBiDiMode = False
          end
          object Label3: TLabel
            Left = 8
            Top = 66
            Width = 48
            Height = 13
            BiDiMode = bdLeftToRight
            Caption = 'ResultsDir'
            ParentBiDiMode = False
          end
          object Label4: TLabel
            Left = 8
            Top = 90
            Width = 38
            Height = 13
            BiDiMode = bdLeftToRight
            Caption = 'DLLsDir'
            ParentBiDiMode = False
          end
          object EditSessions: TEdit
            Left = 68
            Top = 14
            Width = 121
            Height = 21
            TabOrder = 0
          end
          object EditSettings: TEdit
            Left = 68
            Top = 38
            Width = 121
            Height = 21
            TabOrder = 1
          end
          object EditResults: TEdit
            Left = 68
            Top = 62
            Width = 121
            Height = 21
            TabOrder = 2
          end
          object EditDLLs: TEdit
            Left = 68
            Top = 86
            Width = 121
            Height = 21
            TabOrder = 3
          end
        end
      end
    end
  end
end
