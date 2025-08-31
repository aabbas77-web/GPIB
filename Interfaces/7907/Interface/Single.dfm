object FormSingle: TFormSingle
  Left = 730
  Top = 120
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Results'
  ClientHeight = 178
  ClientWidth = 274
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
    Top = 0
    Width = 274
    Height = 147
    Align = alClient
    Color = clBtnFace
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 0
  end
  object Panel1: TPanel
    Left = 0
    Top = 147
    Width = 274
    Height = 31
    Align = alBottom
    TabOrder = 1
    object BitBtn1: TBitBtn
      Left = 99
      Top = 3
      Width = 75
      Height = 25
      TabOrder = 0
      Kind = bkOK
    end
  end
end
