object FormInfo: TFormInfo
  Left = 190
  Top = 197
  Width = 544
  Height = 376
  Align = alClient
  BorderWidth = 2
  Caption = 'Session Informations'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 532
    Height = 326
    Align = alClient
    BevelInner = bvLowered
    BevelOuter = bvLowered
    BevelWidth = 3
    BorderWidth = 1
    TabOrder = 0
    object RichEdit1: TRichEdit
      Left = 7
      Top = 7
      Width = 518
      Height = 312
      Align = alClient
      BorderStyle = bsNone
      Color = clBtnFace
      Font.Charset = ARABIC_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Traditional Arabic'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      ScrollBars = ssBoth
      TabOrder = 0
    end
  end
  object ActionList1: TActionList
    Images = FormMain.ImageList1
    Left = 218
    Top = 86
    object AInformation: TAction
      Category = 'Information'
      Caption = '&Information'
      OnExecute = AInformationExecute
    end
    object ASave: TAction
      Category = 'Information'
      Caption = '&Save ...'
      ImageIndex = 8
      OnExecute = ASaveExecute
    end
    object AClose: TAction
      Category = 'Information'
      Caption = '&Close'
      ImageIndex = 18
      OnExecute = ACloseExecute
    end
  end
  object MainMenu1: TMainMenu
    Images = FormMain.ImageList1
    Left = 190
    Top = 86
    object AInformation1: TMenuItem
      Action = AInformation
      object Save1: TMenuItem
        Action = ASave
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Close1: TMenuItem
        Action = AClose
      end
    end
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'rtf'
    Filter = 'Rich Text Format (*.rtf)|*.rtf'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 246
    Top = 86
  end
end
