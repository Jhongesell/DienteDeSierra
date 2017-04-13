// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV5
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#ifndef AyudaH
#define AyudaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>

//---------------------------------------------------------------------------
class TAyudaForm : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *MenuArchivo;
        TMenuItem *MenuArchivoCarrar;
        TMenuItem *MenuEdicion;
        TMenuItem *MenuEdicionCopiar;
        TMenuItem *MenuEdicionSeleccionarTodo;
        TMenuItem *N1;
        TMenuItem *MenuArchivoConfigurarImpresora;
        TMenuItem *MenuArchivoImprimir;
        TPrintDialog *PrintDialog;
        TRichEdit *EditorAyuda;
        TFindDialog *FindDialog;
        TMenuItem *N2;
        TMenuItem *MenuEdicionBuscar;
        TStatusBar *BarraDeEstados;
        void __fastcall MenuArchivoConfigurarImpresoraClick(TObject *Sender);
        void __fastcall MenuArchivoCarrarClick(TObject *Sender);
        void __fastcall MenuEdicionCopiarClick(TObject *Sender);
        void __fastcall MenuEdicionSeleccionarTodoClick(TObject *Sender);
        void __fastcall MenuArchivoImprimirClick(TObject *Sender);
        void __fastcall MenuEdicionBuscarClick(TObject *Sender);
        void __fastcall FindDialogFind(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormDeactivate(TObject *Sender);
private:	// User declarations
        void  __fastcall OnHint(TObject *Sender);
public:		// User declarations
        __fastcall TAyudaForm(TComponent* Owner);


        const char *ARCHIVO;
        const char *TITULO;

              // Abre el archivo por omision
        void  Abrir_archivo(const char *tit, const char *arch);
};
#endif
