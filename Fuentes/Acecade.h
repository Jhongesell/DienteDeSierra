// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en trámite 1999-2000
// Revisión  1.1-A


#ifndef AcecadeH
#define AcecadeH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TVAcercaDe : public TForm
{
__published:	// IDE-managed Components
        TBitBtn *BitBtn1;
        TPanel *Panel1;
        TImage *Image1;
        TLabel *Label10;
        TLabel *NombreSistema;
        TLabel *Label13;
        TLabel *FechaGeneracion;
        TLabel *Label14;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label17;
        TLabel *Label18;
        TLabel *Label19;
        TLabel *Label20;
        TLabel *Label21;
        TLabel *Label22;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        void __fastcall Label10Click(TObject *Sender);
        void __fastcall Label15Click(TObject *Sender);
        void __fastcall Label16Click(TObject *Sender);
        void __fastcall Label17Click(TObject *Sender);
        void __fastcall Label18Click(TObject *Sender);
        void __fastcall Label19Click(TObject *Sender);
        void __fastcall Label3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TVAcercaDe(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
 
