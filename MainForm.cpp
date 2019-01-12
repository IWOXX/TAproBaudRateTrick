//---------------------------------------------------------------------------
// Test program to workaround the TApdComPort baud rate limitation
//---------------------------------------------------------------------------
// Turbo Power Asynch Pro has the problem, that you cannot set baud rates
// higher than 115200 baud. If you try to set a higher rate, you get an
// exception.
//
//  So the idea is to...
//
//  1. Continue using all TAPRO features as I think is an excellent
//     component.
//  2. Do the baud rate setting with an own function using TAPROs
//     TApdComPort handler and the system's DCB for that TAPRO port to
//     set a baudrate not allowed within the component.
//  3. Method:
//      a. Open the COM port as usual with TAPRO component
//      b. Use its handler to read the DCB with SetCommState(...)
//      c. Set the baudrate in the DCB record already read
//      d. Write back the DCB with new baudrate with SetCommState(...)
//
//  That's it...and you can start transmit and receive data and signals
//
//  Example to set your user defined COM port baud rate to TApdComPort use:
//
//  HANDLE com1Handle = (HANDLE) ApdComPort1->Dispatcher->ComHandle;
//      --> Read TApdComPort's dispatcher COM handler
//
//  int rc = SetBaudRate(com1Handle, Baudrate);
//      --> Now set the desired baudrate
//
//  TESTED up to 921600 baud with no issues
//  with a RIGOL DG4162 Function/Arbitrary WaveForm Generator
//
//  HINT: Make sure that your hardware supports the baudrate
//
//  (c)2019 IWOXX Software Development · Dieter Woellner
//          https://www.iwoxx.de
//
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
#include "ComPortUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdPort"
#pragma link "OoMisc"
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
// Global vars
//
LPCWSTR	gszPort = L"COM2";
HANDLE	hComm;
HANDLE 	com1Handle;
int 	Baudrate;
char	*lpBuf;
bool	flagReadingPort = false;



//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
	// Get current baudrate from combo box
	Baudrate = StrToInt(cbBaudrate->Items->Strings[cbBaudrate->ItemIndex]);

}

//---------------------------------------------------------------------------
// Open the Com port
//
void __fastcall TFormMain::btnOpenPortClick(TObject *Sender)
{
	int rc;

	cbBaudrate->Enabled = false;

	ApdComPort1->Open = true;
	memLog->Lines->Append("COM port opening OK");

	com1Handle = (HANDLE) ApdComPort1->Dispatcher->ComHandle;
	rc = SetBaudRate(com1Handle, Baudrate);
	switch(rc) {
		case 1:	 memLog->Lines->Append("Error getting current DCB settings"); break;
		case 2:	 memLog->Lines->Append("Error setting DCB baudrate"); break;
		default: memLog->Lines->Append("Setting baudrate OK"); break;

	}

}
//---------------------------------------------------------------------------

void __fastcall TFormMain::btnClosePortClick(TObject *Sender)
{
	ApdComPort1->Open = false;
	cbBaudrate->Enabled = true;
	memLog->Lines->Append("COM port closing OK");
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ApdComPort1TriggerAvail(TObject *CP, WORD Count)
{
	String rxData;

	for(int i=0; i<Count; i++)
		rxData+=ApdComPort1->GetChar();

	memLog->Lines->Append(rxData);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::cbBaudrateChange(TObject *Sender)
{
	Baudrate = StrToInt(cbBaudrate->Items->Strings[cbBaudrate->ItemIndex]);
}
//---------------------------------------------------------------------------

