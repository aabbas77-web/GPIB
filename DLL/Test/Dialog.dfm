object FormDialog: TFormDialog
  Left = 191
  Top = 105
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Dialog'
  ClientHeight = 81
  ClientWidth = 238
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 4
    Top = 5
    Width = 46
    Height = 13
    Caption = 'Password'
  end
  object Edit1: TEdit
    Left = 4
    Top = 21
    Width = 228
    Height = 21
    PasswordChar = '*'
    TabOrder = 0
  end
  object BitBtn1: TBitBtn
    Left = 43
    Top = 51
    Width = 75
    Height = 25
    TabOrder = 1
    Kind = bkOK
  end
  object BitBtn2: TBitBtn
    Left = 120
    Top = 51
    Width = 75
    Height = 25
    TabOrder = 2
    Kind = bkCancel
  end
end
