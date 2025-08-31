object FormDeviceTester: TFormDeviceTester
  Left = 190
  Top = 105
  Width = 479
  Height = 376
  Caption = 'Device Tester V1.0'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object RichEdit1: TRichEdit
    Left = 0
    Top = 38
    Width = 471
    Height = 311
    Align = alClient
    Font.Charset = ARABIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Traditional Arabic'
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 0
    WordWrap = False
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 471
    Height = 38
    Align = alTop
    AutoSize = True
    TabOrder = 1
    object ToolBar1: TToolBar
      Left = 1
      Top = 1
      Width = 469
      Height = 36
      AutoSize = True
      ButtonHeight = 32
      ButtonWidth = 71
      Caption = 'ToolBar1'
      EdgeBorders = [ebLeft, ebTop, ebRight, ebBottom]
      Flat = True
      Font.Charset = ARABIC_CHARSET
      Font.Color = clBlack
      Font.Height = -16
      Font.Name = 'Traditional Arabic'
      Font.Style = [fsBold]
      ParentFont = False
      ShowCaptions = True
      TabOrder = 0
      object ToolButton1: TToolButton
        Left = 0
        Top = 0
        Caption = 'Load'
        ImageIndex = 0
        OnClick = ToolButton1Click
      end
      object ToolButton2: TToolButton
        Left = 71
        Top = 0
        Caption = 'Init'
        ImageIndex = 1
        OnClick = ToolButton2Click
      end
      object ToolButton3: TToolButton
        Left = 142
        Top = 0
        Caption = 'Close'
        ImageIndex = 2
        OnClick = ToolButton3Click
      end
      object ToolButton4: TToolButton
        Left = 213
        Top = 0
        Caption = 'Interface'
        ImageIndex = 3
        OnClick = ToolButton4Click
      end
      object ToolButton5: TToolButton
        Left = 284
        Top = 0
        Caption = 'Save ...'
        ImageIndex = 4
        OnClick = ToolButton5Click
      end
    end
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = 'DLL'
    Filter = 'DLL Files (*.DLL)|*.DLL'
    Left = 73
    Top = 164
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'rtf'
    Filter = 'Rich Text Format (*.rtf)|*.rtf'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 101
    Top = 164
  end
end
