// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en trámite 1999-2000
// Revisión  1.1-A


//---------------------------------------------------------------------------
#ifndef VentanaLevantamientosH
#define VentanaLevantamientosH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include "V_pixel.hpp"
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include "FuncionDisparo.hpp"
#include "ParamLevantamientos.h"

#define ADELANTE    1
#define ATRAZ       0
//---------------------------------------------------------------------------
class TFormaLevantamientos : public TForm
{
   __published:	// IDE-managed Components
        TStatusBar *BarraDeEstadosLevantamientos;
        TSavePictureDialog *SaveDialog;
        TMainMenu *MenuPrincipal;
        TMenuItem *MenuArchivo;
        TMenuItem *MenuArchivoGrabarBMP;
        TMenuItem *MenuArchivoImprimir;
        TMenuItem *Separador4;
        TMenuItem *MenuArchivoGrabarConfiguracion;
        TMenuItem *MenuArchivoLeerConfiguracion;
        TMenuItem *MenuArchivoReportedeConfiguracion;
        TMenuItem *Separador2;
        TMenuItem *MenuArchivoCerrar;
        TMenuItem *MenuEdicion;
        TMenuItem *MenuEdicionCopiar;
        TMenuItem *MenuEdicionPegar;
        TMenuItem *MenuCalcular;
        TMenuItem *MenuCalcularLevantamientos;
        TMenuItem *MenuCalcularNumeroRotacion;
        TMenuItem *MenuCalcularSincronizacin;
        TMenuItem *MenuCalcularExpLyapunov;
        TMenuItem *Separador3;
        TMenuItem *MenuCalcularDetenerelcalculo;
        TMenuItem *MenuVentana;
        TMenuItem *MenuVentanaLimpiar;
        TMenuItem *MenuConfigurar;
        TMenuItem *MenuConfigurarParametros;
        TMenuItem *MenuConfigurarDimenciones;
        TMenuItem *MenuConfigurarVisualizar;
        TMenuItem *MenuConfigurarCalculo;
        TMenuItem *MenuAyuda;
        TMenuItem *MenuAyudaAcercade;
        TMenuItem *Separador1;
        TMenuItem *MenuAyudaLevantamientos;
        TMenuItem *CalculaIteraciones;
        TPopupMenu *PopupMenu1;
        TMenuItem *FijarCondicIninicial;
        TTimer *Timer1;
        TMenuItem *Separador5;
        TPanel *Panel1;
        TPaintBox *VTLevantamientos;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall MenuArchivoCerrarClick(TObject *Sender);
        void __fastcall MenuAyudaLevantamientosClick(TObject *Sender);
        void __fastcall MenuAyudaAcercadeClick(TObject *Sender);
        void __fastcall MenuCalcularLevantamientosClick(TObject *Sender);
        void __fastcall MenuVentanaLimpiarClick(TObject *Sender);
        void __fastcall MenuCalcularNumeroRotacionClick(TObject *Sender);
        void __fastcall MenuCalcularSincronizacinClick(TObject *Sender);
        void __fastcall MenuCalcularExpLyapunovClick(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall MenuCalcularIteracionesClick(TObject *Sender);
        void __fastcall MenuConfigurarCalculoClick(TObject *Sender);
        void __fastcall MenuArchivoGrabarBMPClick(TObject *Sender);
        void __fastcall MenuArchivoImprimirClick(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall MenuConfigurarParametrosClick(TObject *Sender);
        void __fastcall MenuConfigurarDimensionesClick(TObject *Sender);
        void __fastcall MenuConfigurarVisualizarClick(TObject *Sender);
        void __fastcall FijarCondicIninicialClick(TObject *Sender);
        void __fastcall VTLevantamientosMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall MenuCalcularDetenerelcalculoClick(TObject *Sender);
        void __fastcall VTLevantamientosPaint(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormDeactivate(TObject *Sender);
   private:	// User declarations
        // Funcion de Disparo
        FuncionDisparo         fun_disp;
                               
        // Puntero a la ventana de configuracion
        TVCap_Levantamientos *configura;
        char                  xcad[200];

        // Variables para mostrar la posición del mouse dentro de la ventana
        Dimencion_Ventana      Vs;
        char                   Msg[200];

        Arreglo_pixeles        pix[4]; // Clase que contiene los graficos generados   

        C_2D                    Escala; // Escala del gráfico
        unsigned int           Pix_x;
        unsigned int           Pix_y; 
        Dimencion_Ventana      Dim_Vtn;
        TColor                 Color_grafica[4];
        TColor                 Color_fondo;
        unsigned int           Puntos_trazar;
        unsigned int           Num_iteraciones;
        C_2D                    Condicion_inicial;
   
        bool                   Tipo_integracion;
        bool                   Sw_Visualiza_grafico;
        bool                   Sw_Visualiza_identidad;
        bool                   Sw_Visualiza_referencia;
        bool                   Sw_Visualiza_linea;
        bool                   Detener_calculo;
       

                               // Constructor de la clase 
                               Levantamientos(void);

        void                   Calcula_Levantamiento(void);
        void                   Calcula_lineas_levantamientos(void);
        void                   Calcula_referencia(void);
        
        void                   Grafica(bool limpia);
        void                   Limpiar_vantana(void);
        void                   Limpia_matriz_pixeles(void)
                               {
                                  pix[2].Asigna_todo_array(false);
                                  pix[3].Asigna_todo_array(false);
                               }
        void                   PasarValoresConfiguracion(void);
        void                   RetornarValoresConfiguracion(void);

        void                   __fastcall OnHint(TObject *Sender);
   public:		// User declarations
        __fastcall TFormaLevantamientos(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif

