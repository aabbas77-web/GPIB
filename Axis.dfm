object FormAxis: TFormAxis
  Left = 402
  Top = 406
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Axis'
  ClientHeight = 151
  ClientWidth = 339
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
    Top = 110
    Width = 339
    Height = 41
    Align = alBottom
    TabOrder = 0
    object BitBtn1: TBitBtn
      Left = 94
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 0
      OnClick = BitBtn1Click
      Kind = bkOK
    end
    object BitBtn2: TBitBtn
      Left = 170
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 1
      OnClick = BitBtn2Click
      Kind = bkCancel
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 339
    Height = 110
    Align = alClient
    TabOrder = 1
    object GroupBox1: TGroupBox
      Left = 8
      Top = 4
      Width = 159
      Height = 99
      Caption = 'X Axe'
      TabOrder = 0
      object Label1: TLabel
        Left = 8
        Top = 16
        Width = 70
        Height = 13
        Caption = 'Measure name'
      end
      object Label3: TLabel
        Left = 8
        Top = 56
        Width = 48
        Height = 13
        Caption = 'Parameter'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object ComboBox1: TComboBox
        Left = 8
        Top = 72
        Width = 145
        Height = 21
        ItemHeight = 13
        TabOrder = 0
      end
      object ComboBox3: TComboBox
        Left = 8
        Top = 32
        Width = 145
        Height = 21
        ItemHeight = 13
        TabOrder = 1
        OnChange = ComboBox3Change
      end
    end
    object GroupBox2: TGroupBox
      Left = 172
      Top = 4
      Width = 159
      Height = 99
      Caption = 'Y Axe'
      TabOrder = 1
      object Label2: TLabel
        Left = 8
        Top = 16
        Width = 70
        Height = 13
        Caption = 'Measure name'
      end
      object Label4: TLabel
        Left = 8
        Top = 56
        Width = 48
        Height = 13
        Caption = 'Parameter'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object ComboBox2: TComboBox
        Left = 8
        Top = 72
        Width = 145
        Height = 21
        ItemHeight = 13
        TabOrder = 0
      end
      object ComboBox4: TComboBox
        Left = 8
        Top = 32
        Width = 145
        Height = 21
        ItemHeight = 13
        TabOrder = 1
        OnChange = ComboBox4Change
      end
    end
  end
end
