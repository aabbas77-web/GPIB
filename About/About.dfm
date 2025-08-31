object FormAbout: TFormAbout
  Left = 190
  Top = 105
  AutoSize = True
  BorderIcons = []
  BorderStyle = bsNone
  Caption = 'GPIB V1.0'
  ClientHeight = 80
  ClientWidth = 120
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
  OnDeactivate = FormDeactivate
  OnKeyDown = FormKeyDown
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object AGif1: TAGif
    Left = 0
    Top = 0
    Width = 0
    Height = 0
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 80
    Height = 80
    AutoSize = True
    BevelInner = bvLowered
    BevelWidth = 3
    BorderWidth = 2
    TabOrder = 0
  end
end
