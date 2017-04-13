// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV5
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#include <vcl.h>
#include <stdlib.h>
#include "Ayuda.h"
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

#ifdef _IDIOMA_ESPANOL_
   #define TXT01 "Buscar"
   #define TXT02 "Fin del documento"
   #define TXT03 "Error en solicitud de memoria dinámica"
#else
   #define TXT01 "Find"
   #define TXT02 "End of document"
   #define TXT03 "Error in allocation memory"
#endif


__fastcall TAyudaForm::TAyudaForm(TComponent* Owner): TForm(Owner)
{
#ifdef _IDIOMA_ESPANOL_
   MenuArchivo->Caption                    = "&Archivo";
   MenuArchivoConfigurarImpresora->Caption = "&Configurar impresora";
   MenuArchivoConfigurarImpresora->Hint    = "Configurar impresora";
   MenuArchivoImprimir->Caption            = "&Imprimir";
   MenuArchivoImprimir->Hint               = "Imprimir";
   MenuArchivoCarrar->Caption              = "&Cerrar";
   MenuArchivoCarrar->Hint                 = "Cerrar esta ventana";
   MenuEdicion->Caption                    = "&Editor";
   MenuEdicionCopiar->Caption              = "&Copiar";
   MenuEdicionCopiar->Hint                 = "Copiar";
   MenuEdicionSeleccionarTodo->Caption     = "&Seleccionar todo";
   MenuEdicionSeleccionarTodo->Hint        = "Seleccionar todo";
   MenuEdicionBuscar->Caption              = "Buscar";
   MenuEdicionBuscar->Hint                 = "Buscar texto";
#else
   MenuArchivo->Caption                    = "&File";
   MenuArchivoConfigurarImpresora->Caption = "Print &Settings";
   MenuArchivoConfigurarImpresora->Hint    = "Print settings";
   MenuArchivoImprimir->Caption            = "&Print";
   MenuArchivoImprimir->Hint               = "Print";
   MenuArchivoCarrar->Caption              = "&Close";
   MenuArchivoCarrar->Hint                 = "Close this window";
   MenuEdicion->Caption                    = "&Edit";
   MenuEdicionCopiar->Caption              = "&Copy";
   MenuEdicionCopiar->Hint                 = "Copy";
   MenuEdicionSeleccionarTodo->Caption     = "&Select All";
   MenuEdicionSeleccionarTodo->Hint        = "Select all";
   MenuEdicionBuscar->Caption              = "Find";
   MenuEdicionBuscar->Hint                 = "Find text";
#endif
}


// Abre el archivo por omision
void TAyudaForm::Abrir_archivo(const char *tit, const char *arch)
{
   TITULO = tit;
   ARCHIVO = arch;
   Caption = TITULO;
   EditorAyuda->Clear();
   try {
      if(arch[0]) EditorAyuda->Lines->LoadFromFile(ARCHIVO);
   } catch (...) {};
}

// Imprime el archivo
void __fastcall TAyudaForm::MenuArchivoImprimirClick(TObject *Sender)
{
   EditorAyuda->Print(TITULO);
}


// Configura la impresora
void __fastcall TAyudaForm::MenuArchivoConfigurarImpresoraClick(TObject *Sender)
{
   PrintDialog->Execute();
}

// Salir del programa
void __fastcall TAyudaForm::MenuArchivoCarrarClick(TObject *Sender)
{
   Close();        
}

// Copia el texto seleccionado
void __fastcall TAyudaForm::MenuEdicionCopiarClick(TObject *Sender)
{
   EditorAyuda->CopyToClipboard();        
}

// Selecciona todo el texto
void __fastcall TAyudaForm::MenuEdicionSeleccionarTodoClick(TObject *Sender)
{
   EditorAyuda->SelectAll();                
}


void __fastcall TAyudaForm::MenuEdicionBuscarClick(TObject *Sender)
{
    FindDialog->FindText = EditorAyuda->SelText;
    FindDialog->Execute();
}


void __fastcall TAyudaForm::FindDialogFind(TObject *Sender)
{
    Show();
    TSearchTypes st;
    TFindDialog *cd;
    int newpos;

    if ((cd = dynamic_cast<TFindDialog *> (Sender)) == 0) MessageBox(NULL, TXT03, TXT01, MB_OK + MB_ICONSTOP);

    if (cd->Options.Contains(frMatchCase)) st << stMatchCase;
    if (cd->Options.Contains(frWholeWord)) st << stWholeWord;

    if (EditorAyuda->SelLength) EditorAyuda->SelStart += 1;

    newpos = EditorAyuda->FindText(cd->FindText, EditorAyuda->SelStart, EditorAyuda->Text.Length(), st);

    if (newpos != -1) {
        EditorAyuda->SelStart = newpos;
        EditorAyuda->SelLength = cd->FindText.Length();
     } else {
        MessageBox(NULL, TXT02, TXT01, MB_OK + MB_ICONINFORMATION);
        EditorAyuda->SelStart = 0;
    }
}

// Al activar la forma
void __fastcall TAyudaForm::FormActivate(TObject *Sender)
{
   Application->OnHint = OnHint;
}

// OnHint
void  __fastcall TAyudaForm::OnHint(TObject *Sender)
{
   BarraDeEstados->SimpleText = Application->Hint;
}

// Al desactivar la forma
void __fastcall TAyudaForm::FormDeactivate(TObject *Sender)
{
   Application->OnHint = NULL;
}


