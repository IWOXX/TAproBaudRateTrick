//---------------------------------------------------------------------------
//
// ComPortUitls.cpp and h. to be used in your code project
//
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
//      b. Use its handler to read the DCB using GetCommState(...)
//      c. Set the baudrate in the read DCB record
//      d. Write back the DCB with new baudrate using SetCommState(...)
//
//  That's it...and you can start transmit and receive data and signals
//  with your specific user defined baudrate.
//
//  Example to set your user defined COM port baud rate to TApdComPort use:
//
//  HANDLE com1Handle = (HANDLE) ApdComPort1->Dispatcher->ComHandle;
//      --> Read TApdComPort's dispatcher COM handler
//
//  int rc = SetBaudRate(com1Handle, Baudrate);
//      --> Now set the desired baudrate
//
//  TESTED up to 921600 baud with no issues firing continuous data stream
//  with a RIGOL DG4162 Function/Arbitrary WaveForm Generator
//
//  HINT: Make sure that your hardware supports the baudrate
//
//  (c)2019 IWOXX Software Development · Dieter Woellner
//          https://www.iwoxx.de
//
//---------------------------------------------------------------------------

#pragma hdrstop

#include "ComPortUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


//---------------------------------------------------------------------------
// Set baudrate in DCB via a known COM port handler
//---------------------------------------------------------------------------
// Parameters:
//
//  HANDLE comPortHandler	- handler of the used COM port
//  Integer baudRate        - required baudrate (any; must be supported by
//                            COM hardware
//
// Return values:
//
//  Integer             0   - OK; success
//                      1   - ERROR on GetCommState; getting DCB
//                      2   - ERROR on SetCommState; setting DCB
//
//
//  (c)2019 IWOXX Software Development · Dieter Woellner
//          https://www.iwoxx.de
//

Integer __fastcall SetBaudRate(HANDLE comPortHandler, Integer baudRate)
{
	int rc = 0; // Default: OK
	DCB dcb = {0};

	//---------- Get the DCB record via handler --------
	if (!GetCommState(comPortHandler, &dcb))
	{
		// Error getting current DCB settings
		rc = 1; // Error getting DCB
		return(rc);
	}

	//---------- Set the DCB with new baudrate ---------
	dcb.BaudRate = baudRate;    // Write new baudrate to DCB record and set it

	if (!SetCommState(comPortHandler, &dcb))
	{
		// Error getting current DCB settings
		rc = 2; // Error setting DCB
		return(rc);
	}


	return(0); // All OK
}
//---------------------------------------------------------------------------
