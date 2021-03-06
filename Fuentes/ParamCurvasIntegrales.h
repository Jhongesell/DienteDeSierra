// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Direcci�n: Amsterdam 312 col. Hip�dromo Condesa
// Tel�fono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr�mite 1999-2000
// Revisi�n  1.1-A


//---------------------------------------------------------------------------
#ifndef ParamCurvasIntegralesH
#define ParamCurvasIntegralesH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Tabnotbk.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Dialogs.hpp>
#include <vcl\Buttons.hpp>
//---------------------------------------------------------------------------
class TVCap_CIntegrales : public TForm
{
__published:	// IDE-managed Components
        TTabbedNotebook *TabbedNotebook1;
        TPanel *Panel1;
        TButton *Button1;
        TPanel *Panel3;
        TPanel *Panel4;
        TEdit *Edit8;
        TLabel *Label8;
   TCheckBox *CheckBox1;
   TCheckBox *CheckBox2;
   TCheckBox *CheckBox3;
   TCheckBox *CheckBox4;
   TColorDialog *ColorDialog;
   TPanel *Panel5;
   TPanel *Panel6;
   TPanel *Panel7;
   TPanel *Panel8;
   TGroupBox *GroupBox3;
   TRadioButton *RadioButton1;
   TRadioButton *RadioButton2;
        TCheckBox *CheckBox6;
        TPanel *Panel10;
        TGroupBox *GroupBox1;
        TLabel *Label4;
        TLabel *Label5;
        TEdit *EditHMin;
        TEdit *EditHMax;
        TGroupBox *GroupBox2;
        TLabel *Label6;
        TLabel *Label7;
        TEdit *EditVMin;
        TEdit *EditVMax;
        TStaticText *StaticText1;
        TListBox *ListBoxParametros;
        TStaticText *NombreParametro;
        TEdit *EditValorParametro;
   void __fastcall Button1Click(TObject *Sender);
   void __fastcall Panel5Click(TObject *Sender);
   void __fastcall Panel6Click(TObject *Sender);
   void __fastcall Panel7Click(TObject *Sender);
   void __fastcall Panel8Click(TObject *Sender);
        void __fastcall ListBoxParametrosClick(TObject *Sender);
        void __fastcall EditValorParametroKeyPress(TObject *Sender,
          char &Key);
        void __fastcall Panel10Click(TObject *Sender);
   
private:	// User declarations
public:		// User declarations
        bool Aceptar;

        __fastcall TVCap_CIntegrales(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
 
