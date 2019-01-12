//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdPort.hpp"
#include "OoMisc.hpp"
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	TMemo *memLog;
	TLabel *lblProtocol;
	TButton *btnOpenPort;
	TButton *btnClosePort;
	TApdComPort *ApdComPort1;
	TComboBox *cbBaudrate;
	TLabel *Label1;
	TLabel *lblBaudrateHint;
	TLabel *Label2;
	void __fastcall btnOpenPortClick(TObject *Sender);
	void __fastcall btnClosePortClick(TObject *Sender);
	void __fastcall ApdComPort1TriggerAvail(TObject *CP, WORD Count);
	void __fastcall cbBaudrateChange(TObject *Sender);
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------


#endif
