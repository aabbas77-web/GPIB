object FormGraph: TFormGraph
  Left = 252
  Top = 216
  Width = 544
  Height = 379
  Caption = 'Graph'
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
    Width = 536
    Height = 352
    Align = alClient
    BevelInner = bvLowered
    TabOrder = 0
    object Splitter1: TSplitter
      Left = 273
      Top = 2
      Width = 3
      Height = 348
      Cursor = crHSplit
    end
    object Panel2: TPanel
      Left = 2
      Top = 2
      Width = 271
      Height = 348
      Align = alLeft
      TabOrder = 0
      object Splitter2: TSplitter
        Left = 1
        Top = 181
        Width = 269
        Height = 3
        Cursor = crVSplit
        Align = alTop
      end
      object Panel4: TPanel
        Left = 1
        Top = 1
        Width = 269
        Height = 180
        Align = alTop
        TabOrder = 0
        object DBChart1: TDBChart
          Left = 1
          Top = 1
          Width = 267
          Height = 178
          BackWall.Brush.Color = clWhite
          BackWall.Brush.Style = bsClear
          Title.Text.Strings = (
            'First Part')
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
        end
      end
      object Panel5: TPanel
        Left = 1
        Top = 184
        Width = 269
        Height = 163
        Align = alClient
        TabOrder = 1
        object DBChart2: TDBChart
          Tag = 1
          Left = 1
          Top = 1
          Width = 267
          Height = 161
          BackWall.Brush.Color = clWhite
          BackWall.Brush.Style = bsClear
          Title.Text.Strings = (
            'Second Part')
          Legend.Visible = False
          View3D = False
          Align = alClient
          PopupMenu = PopupMenu2
          TabOrder = 0
          object Series2: TLineSeries
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
        end
      end
    end
    object Panel3: TPanel
      Left = 276
      Top = 2
      Width = 258
      Height = 348
      Align = alClient
      TabOrder = 1
      object Splitter3: TSplitter
        Left = 1
        Top = 181
        Width = 256
        Height = 3
        Cursor = crVSplit
        Align = alTop
      end
      object Panel6: TPanel
        Left = 1
        Top = 1
        Width = 256
        Height = 180
        Align = alTop
        TabOrder = 0
        object DBChart3: TDBChart
          Tag = 2
          Left = 1
          Top = 1
          Width = 254
          Height = 178
          BackWall.Brush.Color = clWhite
          BackWall.Brush.Style = bsClear
          Title.Text.Strings = (
            'Third Part')
          Legend.Visible = False
          View3D = False
          Align = alClient
          PopupMenu = PopupMenu3
          TabOrder = 0
          object Series3: TLineSeries
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
        end
      end
      object Panel7: TPanel
        Left = 1
        Top = 184
        Width = 256
        Height = 163
        Align = alClient
        TabOrder = 1
        object DBChart4: TDBChart
          Tag = 3
          Left = 1
          Top = 1
          Width = 254
          Height = 161
          BackWall.Brush.Color = clWhite
          BackWall.Brush.Style = bsClear
          Title.Text.Strings = (
            'Forth Part')
          Legend.Visible = False
          View3D = False
          Align = alClient
          PopupMenu = PopupMenu4
          TabOrder = 0
          object Series4: TLineSeries
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
        end
      end
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 128
    Top = 80
    object Edit1: TMenuItem
      Caption = '&Axis'
      OnClick = Edit1Click
    end
  end
  object PopupMenu2: TPopupMenu
    Left = 76
    Top = 259
    object Edit2: TMenuItem
      Caption = '&Edit'
      OnClick = Edit2Click
    end
  end
  object PopupMenu3: TPopupMenu
    Left = 326
    Top = 84
    object Edit3: TMenuItem
      Caption = '&Edit'
      OnClick = Edit3Click
    end
  end
  object PopupMenu4: TPopupMenu
    Left = 330
    Top = 237
    object Edit4: TMenuItem
      Caption = '&Axis'
      OnClick = Edit4Click
    end
  end
  object Table1: TTable
    Left = 156
    Top = 80
  end
  object Table2: TTable
    Left = 104
    Top = 259
  end
  object Table3: TTable
    Left = 354
    Top = 84
  end
  object Table4: TTable
    Left = 358
    Top = 237
  end
end
