// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A

//---------------------------------------------------------------------------
#ifndef ACX-WebBrowserH
#define ACX-WebBrowserH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <NMHTML.hpp>
#include <OleCtrls.hpp>
#include <Buttons.hpp>
#include "SHDocVw_OCX.h"
//---------------------------------------------------------------------------
class TFormaWebBrowzer : public TForm
{
__published:	// IDE-managed Components
        TWebBrowser_V1 *WebBrowser1;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
        __fastcall TFormaWebBrowzer(TComponent* Owner);
        void Parametros(const char *path);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormaWebBrowzer *FormaWebBrowzer;
//---------------------------------------------------------------------------
#endif
