object FormMain: TFormMain
  Left = 0
  Top = 0
  Caption = 'FormMain'
  ClientHeight = 411
  ClientWidth = 852
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object lblProtocol: TLabel
    Left = 24
    Top = 21
    Width = 39
    Height = 13
    Caption = 'Protocol'
  end
  object Label1: TLabel
    Left = 263
    Top = 365
    Width = 51
    Height = 13
    Caption = 'Baud rate:'
  end
  object lblBaudrateHint: TLabel
    Left = 480
    Top = 365
    Width = 147
    Height = 13
    Caption = 'Close port to change baudrate'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMaroon
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 263
    Top = 389
    Width = 473
    Height = 13
    Caption = 
      'This program starts receiving data as soon as you press "Open Po' +
      'rt" and stops with "Close Port"!!!'
  end
  object memLog: TMemo
    Left = 24
    Top = 40
    Width = 801
    Height = 305
    TabOrder = 0
  end
  object btnOpenPort: TButton
    Left = 24
    Top = 360
    Width = 75
    Height = 25
    Caption = 'Open Port'
    TabOrder = 1
    OnClick = btnOpenPortClick
  end
  object btnClosePort: TButton
    Left = 120
    Top = 360
    Width = 75
    Height = 25
    Caption = 'Close Port'
    TabOrder = 2
    OnClick = btnClosePortClick
  end
  object cbBaudrate: TComboBox
    Left = 320
    Top = 362
    Width = 145
    Height = 21
    ItemIndex = 10
    TabOrder = 3
    Text = '9600'
    OnChange = cbBaudrateChange
    Items.Strings = (
      '150'
      '300'
      '600'
      '1200'
      '1800'
      '2000'
      '2400'
      '3600'
      '4800'
      '7200'
      '9600'
      '10400'
      '14400'
      '19200'
      '28800'
      '38400'
      '56000'
      '57600'
      '115200'
      '230400'
      '460800'
      '921600')
  end
  object ApdComPort1: TApdComPort
    ComNumber = 2
    Baud = 9600
    PromptForPort = False
    Tracing = tlOn
    TraceName = 'APRO.TRC'
    Logging = tlOn
    LogName = 'APRO.LOG'
    OnTriggerAvail = ApdComPort1TriggerAvail
    Left = 808
    Top = 360
  end
end
