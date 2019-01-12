# TAproBaudRateTrick
Turbo Power Asynch Pro (TAPRO) baudrate fix for user defined baudrates also higher than 115200 baud

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
