object FormAddress: TFormAddress
  Left = 191
  Top = 452
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Device Address'
  ClientHeight = 92
  ClientWidth = 253
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
    Top = 51
    Width = 253
    Height = 41
    Align = alBottom
    TabOrder = 0
    object BitBtn1: TBitBtn
      Left = 51
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 0
      Kind = bkOK
    end
    object BitBtn2: TBitBtn
      Left = 126
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
    Width = 253
    Height = 51
    Align = alClient
    TabOrder = 1
    object Label1: TLabel
      Left = 7
      Top = 7
      Width = 103
      Height = 13
      Caption = 'Enter Device Address'
    end
    object ComboBox1: TComboBox
      Left = 7
      Top = 23
      Width = 238
      Height = 21
      ItemHeight = 13
      TabOrder = 0
    end
  end
end
