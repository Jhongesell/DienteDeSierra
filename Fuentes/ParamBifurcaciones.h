// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en trámite 1999-2000
// Revisión  1.1-A


//---------------------------------------------------------------------------
#ifndef ParamBifurcacionesH
#define ParamBifurcacionesH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Tabnotbk.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Dialogs.hpp>
//---------------------------------------------------------------------------
class TVCap_Bifurcaciones : public TForm
{
__published:	// IDE-managed Components
   TTabbedNotebook *TabbedNotebook1;
   TPanel *Panel1;
   TPanel *Panel2;
   TGroupBox *GroupBox2;
   TLabel *Label6;
   TLabel *Label7;
   TGroupBox *GroupBox1;
   TLabel *Label4;
   TLabel *Label5;
        TEdit *EditHMin;
        TEdit *EditHMax;
        TEdit *EditVMin;
        TEdit *EditVMax;
   TPanel *Panel3;
   TCheckBox *CheckBox1;
   TCheckBox *CheckBox2;
   TCheckBox *CheckBox3;
   TPanel *Panel5;
   TPanel *Panel6;
   TPanel *Panel7;
   TPanel *Panel4;
   TLabel *Label8;
   TLabel *Label9;
   TEdit *Edit8;
   TEdit *Edit9;
   TGroupBox *GroupBox3;
   TRadioButton *RadioButton1;
   TRadioButton *RadioButton2;
   TButton *Button1;
   TColorDialog *ColorDialog;
        TCheckBox *CheckBox4;
        TPanel *Panel8;
        TStaticText *StaticText1;
        TComboBox *ComboBoxParamertoBifurcar;
        TStaticText *StaticText2;
        TListBox *ListBoxParametros;
        TPanel *Panel9;
        TGroupBox *GroupBox4;
        TLabel *Label1;
        TLabel *Label2;
        TGroupBox *GroupBox5;
        TLabel *Label3;
        TLabel *Label11;
        TEdit *EditHMin2;
        TEdit *EditHMax2;
        TEdit *EditVMin2;
        TEdit *EditVMax2;
        TStaticText *NombreParametro;
        TEdit *EditValorParametro;
        TStaticText *TituloCondicionInicial;
        TEdit *Edit14;
        TCheckBox *CheckBox5;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Panel8Click(TObject *Sender);
        void __fastcall Panel5Click(TObject *Sender);
        void __fastcall Panel6Click(TObject *Sender);
        void __fastcall Panel7Click(TObject *Sender);
        void __fastcall ListBoxParametrosClick(TObject *Sender);
        void __fastcall EditValorParametroKeyPress(TObject *Sender,
          char &Key);
        void __fastcall CheckBox5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        bool Aceptar;

   __fastcall TVCap_Bifurcaciones(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
 
 
 

