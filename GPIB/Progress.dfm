object FormProgress: TFormProgress
  Left = 339
  Top = 503
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = 'Progress'
  ClientHeight = 59
  ClientWidth = 277
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
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 277
    Height = 59
    Align = alClient
    BevelInner = bvRaised
    BevelOuter = bvLowered
    BevelWidth = 3
    TabOrder = 0
    object Label1: TLabel
      Left = 9
      Top = 9
      Width = 51
      Height = 13
      Caption = 'Sending ...'
    end
    object ProgressBar1: TProgressBar
      Left = 9
      Top = 27
      Width = 252
      Height = 16
      Min = 0
      Max = 100
      Smooth = True
      Step = 1
      TabOrder = 0
    end
  end
end
