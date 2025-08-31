object FormDraw2Curves: TFormDraw2Curves
  Left = 190
  Top = 279
  Width = 340
  Height = 306
  Caption = 'Draw 2 Curves'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object DBChart1: TDBChart
    Left = 0
    Top = 0
    Width = 332
    Height = 279
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      'Draw 2 Curves')
    BottomAxis.Title.Caption = 'X1'
    LeftAxis.Title.Caption = 'Y1'
    Legend.Visible = False
    View3D = False
    Align = alClient
    PopupMenu = PopupMenu1
    TabOrder = 0
    object Series1: TLineSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clRed
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
    object Series2: TLineSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clGreen
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 128
    Top = 80
    object Curve11: TMenuItem
      Caption = 'Curve 1'
      OnClick = Curve11Click
    end
    object Curve21: TMenuItem
      Caption = 'Curve 2'
      OnClick = Curve21Click
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object ShowCurve11: TMenuItem
      Caption = 'Show Curve 1'
      Checked = True
      OnClick = ShowCurve11Click
    end
    object ShowCurve21: TMenuItem
      Caption = 'Show Curve 2'
      Checked = True
      OnClick = ShowCurve21Click
    end
  end
  object Table1: TTable
    Left = 156
    Top = 80
  end
  object Table2: TTable
    Left = 184
    Top = 80
  end
end
