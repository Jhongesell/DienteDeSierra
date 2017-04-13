// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en trámite 1999-2000
// Revisión  1.1-A


//---------------------------------------------------------------------------
#ifndef VentanaPrincipalH
#define VentanaPrincipalH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "DefinicionEcuacion.hpp"
#include "ParamGlobales.h"
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>

//---------------------------------------------------------------------------
class TFormaPrincipal : public TForm
{
   __published:	// IDE-managed Components
        TStatusBar *BarraDeEstadoPrincipal;
        TMainMenu *Menu;
        TMenuItem *MenuArchivo;
        TMenuItem *MenuArchivoTerminarPrograma;
        TMenuItem *MenuConfigurar;
        TMenuItem *MenuAyuda;
        TPanel *PanelEscenarios;
        TPanel *PanelIconosAccion;
        TSpeedButton *IconoEscenarioCurvasIntegrales;
        TSpeedButton *IconoEscenarioLevantamientos;
        TSpeedButton *IconoEscenarioToro;
        TSpeedButton *IconoEscenarioCirculo;
        TSpeedButton *IconoEscenarioBifurcaciones;
        TMenuItem *MenuAyudaAcercade;
        TMenuItem *MenuAyudaGeneral;
        TMenuItem *MenuAyudaBifurcaciones;
        TMenuItem *MenuAyudaCirculo;
        TMenuItem *MenuAyudaToro;
        TMenuItem *MenuAyudaCurvasIntegrales;
        TMenuItem *MenuAyudaLevantamientos;
        TMenuItem *MenuConfigurarNumRotacion;
        TMenuItem *MenuConfigurarSincronizacion;
        TMenuItem *MenuConfigurarExpLyapunov;
        TSpeedButton *IconoAccionNumRotacion;
        TSpeedButton *IconoAccionSincronizacion;
        TSpeedButton *IconoAccionExpLyapunov;
        TSpeedButton *IconoAccionConfigurarEscenario;
        TSpeedButton *IconoAccionCalcular;
        TSpeedButton *IconoAccionDetenerCalculo;
        TSpeedButton *IconoAccionLimpiarVentana;
        TSpeedButton *IconoEscenarioTongues;
        TMenuItem *Separador1;
        TMenuItem *MenuArchivoPrintsetup;
        TPrinterSetupDialog *PrinterSetupDialog;
        TMenuItem *MenuScenery;
        TMenuItem *MenuSceneryIntegralCurves;
        TMenuItem *MenuSceneryLifts;
        TMenuItem *MenuSceneryTorous;
        TMenuItem *MenuSceneryCircle;
        TMenuItem *MenuSceneryBifurcation;
        TMenuItem *MenuSceneryTongle;
        TMenuItem *MenuCalculate;
        TMenuItem *MenuCalculateRotationnumber;
        TMenuItem *MenuCalculateSynchronization;
        TMenuItem *MenuCalculateLyapunovExponent;
        TMenuItem *MenuCalculateStartcalculations;
        TMenuItem *MenuCalculateStopcalculations;
        TMenuItem *MenuWindowErasescenery;
        TMenuItem *Separador2;
        TMenuItem *Separador3;
        TMenuItem *MenuConfigurarScenery;
        TMenuItem *MenuWindow;
        TMenuItem *Separador4;
        TMenuItem *MenuAyudaLenguas;
        TMenuItem *Separador6;
        TMenuItem *MenuArchivoEditFile;
        TMenuItem *Separador8;
        TMenuItem *MenuArchivoPrintFile;
        TOpenPictureDialog *OpenPictureDialog;
        TMenuItem *Separador7;
        TMenuItem *MenuVentanaConformalZoom;
        TMenuItem *N1;
        TMenuItem *LabDinmicanoLineal1;
        void __fastcall MenuArchivoTerminarProgramaClick(TObject *Sender);
        void __fastcall IconoEscenarioBifurcacionesClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall IconoEscenarioCirculoClick(TObject *Sender);
        void __fastcall IconoEscenarioToroClick(TObject *Sender);
        void __fastcall IconoEscenarioCurvasIntegralesClick(
          TObject *Sender);
        void __fastcall IconoEscenarioLevantamientosClick(TObject *Sender);
        void __fastcall MenuAyudaAcercadeClick(TObject *Sender);
        void __fastcall MenuAyudaGeneralClick(TObject *Sender);
        void __fastcall MenuAyudaBifurcacionesClick(TObject *Sender);
        void __fastcall MenuAyudaCirculoClick(TObject *Sender);
        void __fastcall MenuAyudaToroClick(TObject *Sender);
        void __fastcall MenuAyudaCurvasIntegralesClick(TObject *Sender);
        void __fastcall MenuAyudaLevantamientosClick(TObject *Sender);
        void __fastcall MenuConfigurarNumRotacionClick(TObject *Sender);
        void __fastcall MenuConfigurarSincronizacionClick(TObject *Sender);
        void __fastcall MenuConfigurarExpLyapunovClick(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall IconoAccionLimpiarVentanaClick(TObject *Sender);
        void __fastcall IconoAccionNumRotacionClick(TObject *Sender);
        void __fastcall IconoAccionSincronizacionClick(TObject *Sender);
        void __fastcall IconoAccionExpLyapunovClick(TObject *Sender);
        void __fastcall IconoAccionConfigurarEscenarioClick(
          TObject *Sender);
        void __fastcall IconoAccionCalcularClick(TObject *Sender);
        void __fastcall IconoAccionDetenerCalculoClick(TObject *Sender);
        void __fastcall IconoEscenarioTonguesClick(TObject *Sender);
        void __fastcall MenuArchivoPrintsetupClick(TObject *Sender);
        void __fastcall MenuAyudaLenguasClick(TObject *Sender);
        void __fastcall MenuArchivoEditFileClick(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall MenuArchivoPrintFileClick(TObject *Sender);
        void __fastcall MenuVentanaConformalZoomClick(TObject *Sender);
        void __fastcall LabDinmicanoLineal1Click(TObject *Sender);
   private:	// User declarations
        // Objeto definición de la ecuación
        DefinicionEcuacion def_ecu;
        char               TituloAplicacion[250];

        // Puntero a la ventana de configuracion
        TVCap_General     *configura;
        char               xcad[200];
        
        // Controla la visualizacion de Hint en la barra de estado
        void __fastcall OnHint(TObject *Sender);
        void            PasarValoresConfiguracion(void);
        void            RetornarValoresConfiguracion(void);
        
   public:		// User declarations
        __fastcall TFormaPrincipal(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormaPrincipal *FormaPrincipal;
//---------------------------------------------------------------------------
#endif

