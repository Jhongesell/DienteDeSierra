// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en trámite 1999-2000
// Revisión  1.1-A


//---------------------------------------------------------------------------
#include <vcl.h>
#include "ParamGlobales.h"
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TVCap_General *VCap_General;
//---------------------------------------------------------------------------

// Constructor de la forma
__fastcall TVCap_General::TVCap_General(TComponent* Owner) : TForm(Owner)
{
   Aceptar = false;
}

// Boton de aceptar cambios
void __fastcall TVCap_General::Button1Click(TObject *Sender)
{
   Aceptar = true;
   Close();        
}

// Al cambiar la condicion inicial del exponente de Lyapunov
void __fastcall TVCap_General::CheckBoxL1Click(TObject *Sender)
{
   TituloCondicionInicialL->Visible = !CheckBoxL1->Checked;
   EditL5->Visible = !CheckBoxL1->Checked;
}

// Al cambiar la condicion inicial de  sincronización
void __fastcall TVCap_General::CheckBoxS1Click(TObject *Sender)
{
   TituloCondicionInicialS->Visible = !CheckBoxS1->Checked;
   EditS5->Visible = !CheckBoxS1->Checked;
}

// Al cambiar la condicion inicial de  numero de rotacional
void __fastcall TVCap_General::CheckBoxR1Click(TObject *Sender)
{
   TituloCondicionInicialR->Visible = !CheckBoxR1->Checked;
   EditR2->Visible = !CheckBoxR1->Checked;
}

