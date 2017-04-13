// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en trámite 1999-2000
// Revisión  1.1-A


//---------------------------------------------------------------------------
#ifndef ParamGlobalesH
#define ParamGlobalesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Tabnotbk.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TVCap_General : public TForm
{
__published:	// IDE-managed Components
        TTabbedNotebook *TabbedNotebook1;
        TButton *Button1;
        TPanel *Panel2;
        TLabel *Label4;
        TEdit *EditR1;
        TPanel *Panel3;
        TLabel *Label5;
        TEdit *EditS1;
        TLabel *Label6;
        TEdit *EditS2;
        TLabel *Label7;
        TEdit *EditS3;
        TLabel *Label8;
        TEdit *EditS4;
        TPanel *Panel4;
        TStaticText *TituloCondicionInicialR;
        TEdit *EditR2;
        TStaticText *TituloCondicionInicialS;
        TEdit *EditS5;
        TLabel *Label10;
        TEdit *EditL2;
        TLabel *Label11;
        TEdit *EditL3;
        TStaticText *TituloCondicionInicialL;
        TEdit *EditL5;
        TEdit *EditL4;
        TStaticText *StaticText4;
        TCheckBox *CheckBoxL1;
        TCheckBox *CheckBoxS1;
        TCheckBox *CheckBoxR1;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall CheckBoxL1Click(TObject *Sender);
        void __fastcall CheckBoxS1Click(TObject *Sender);
        void __fastcall CheckBoxR1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        bool Aceptar;

        __fastcall TVCap_General(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TVCap_General *VCap_General;
//---------------------------------------------------------------------------
#endif
