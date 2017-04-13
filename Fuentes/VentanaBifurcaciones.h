// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en trámite 1999-2000
// Revisión  1.1-A


#ifndef VentanaBifurcacionesH
#define VentanaBifurcacionesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "FuncionDisparo.hpp"
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include "V_pixel.hpp"
#include "FuncionDisparo.hpp"
#include "ParamBifurcaciones.h"

#define ADELANTE         1
#define ATRAZ            0
#define NUM_MAX_DIM_ZOOM 10
//---------------------------------------------------------------------------
class TFormaBifurcaciones : public TForm
{
   __published:	// IDE-managed Components
        TStatusBar *BarraDeEstadosBifurcaciones;
        TMainMenu *MenuPrincipal;
        TMenuItem *MenuArchivo;
        TMenuItem *MenuArchivoGrabarConfiguracion;
        TMenuItem *MenuArchivoLeerConfiguracion;
        TMenuItem *MenuArchivoReportedeConfiguracion;
        TMenuItem *Separador2;
        TMenuItem *MenuArchivoCerrar;
        TMenuItem *MenuEdicion;
        TMenuItem *MenuEdicionCopiar;
        TMenuItem *MenuEdicionPegar;
        TMenuItem *MenuCalcular;
        TMenuItem *MenuCalcularBifurcaciones;
        TMenuItem *MenuCalcularNumeroRotacion;
        TMenuItem *MenuCalcularSincronizacin;
        TMenuItem *MenuCalcularExpLyapunov;
        TMenuItem *MenuVentana;
        TMenuItem *MenuVentanaLimpiar;
        TMenuItem *MenuConfigurar;
        TMenuItem *MenuConfigurarParametros;
        TMenuItem *MenuAyuda;
        TMenuItem *MenuAyudaAcercade;
        TMenuItem *Separador1;
        TMenuItem *MenuAyudaBifurcaciones;
        TSplitter *Splitter1;
        TMenuItem *Separador3;
        TMenuItem *MenuCalcularDetenerelcalculo;
        TMenuItem *Separador4;
        TMenuItem *MenuArchivoGrabarBMP;
        TMenuItem *MenuArchivoImprimir;
        TSavePictureDialog *SaveDialog;
        TMenuItem *MenuConfigurarDimencionesBif;
        TMenuItem *MenuConfigurarVisualizar;
        TMenuItem *MenuConfigurarCalculo;
        TMenuItem *MenuConfiguraDimensionesExp;
        TTimer *Timer1;
        TMenuItem *Separador5;
        TMenuItem *MenuVentanaZoomOut;
        TMenuItem *Separador6;
        TMenuItem *MenuVentanaDimensionesOriginales;
        TPanel *Panel1;
        TPaintBox *VTBifurcaciones;
        TPanel *Panel2;
        TPaintBox *VTExponenteLyapunov;
        void __fastcall MenuArchivoCerrarClick(TObject *Sender);
        void __fastcall MenuAyudaBifurcacionesClick(TObject *Sender);
        void __fastcall MenuAyudaAcercadeClick(TObject *Sender);
        void __fastcall MenuCalcularNumRotacionClick(TObject *Sender);
        void __fastcall MenuCalculaBifurcacionesClick(TObject *Sender);
        void __fastcall MenuCalcularSincronizacionClick(TObject *Sender);
        void __fastcall MenuCalculaeExpLyapunovClick(TObject *Sender);
        void __fastcall MenuVentanaLimpiarClick(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall MenuCalcularDetenerelcalculoClick(TObject *Sender);
        void __fastcall MenuConfigurarParametrosClick(TObject *Sender);
        void __fastcall MenuArchivoGrabarBMPClick(TObject *Sender);
        void __fastcall MenuArchivoImprimirClick(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall MenuConfigurarDimencionesBifClick(TObject *Sender);
        void __fastcall MenuConfigurarVisualizarClick(TObject *Sender);
        void __fastcall MenuConfigurarCalculoClick(TObject *Sender);
        void __fastcall VTBifurcacionesMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall VTExponenteLyapunovMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall MenuConfiguraDimensionesExpClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall VTBifurcacionesMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall VTBifurcacionesMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall MenuVentanaZoomOutClick(TObject *Sender);
        void __fastcall MenuVentanaDimensionesOriginalesClick(
          TObject *Sender);
        void __fastcall VTExponenteLyapunovPaint(TObject *Sender);
        void __fastcall VTBifurcacionesPaint(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormDeactivate(TObject *Sender);
   private:	// User declarations
        // Funcion de disparo
        FuncionDisparo         fun_disp;

        // Puntero a la ventana de configuracion
        TVCap_Bifurcaciones   *configura;
        char                   xcad[300];

        // Variables necesarias para dibujar recuadro de selecccion de una area 
        Definicion_Ventana     Vt1, Vt2, xVt;
        Dimencion_Ventana      Vs;
        bool                   Ventana_seleccionada;
        bool                   Sw_Dibuja_rectangulo;
        bool                   Sw_Dibuja_rectangulo_ant;
        bool                   Sw_Recuadro_activo;
        int                    Ind_zoom;
        Dimencion_Ventana      Dim_zoom[NUM_MAX_DIM_ZOOM];
        Dimencion_Ventana      Dim_orig;

        // Variables para mostrar la posición del mouse dentro de la ventana
        char                   Msg[100];

        Arreglo_pixeles        pix[4];  // Clase que contiene los graficos generados
        C_2D                   Escala1; // Escala del gráfico de Bifurcaciones
        C_2D                   Escala2; // Escala del gráfico del Exponente de Lyapunov
        unsigned int           Pix_x;
        unsigned int           Pix_y; 
        Dimencion_Ventana      Dim_Vtn;
        Dimencion_Ventana      Dim_Vtn2;
        long double            Condicion_inicial;
        int                    Parametro_bifurcar;
        bool                   Sw_Cond_inicial_aleatoria;
        TColor                 Color_grafica[3];
        TColor                 Color_fondo;
        bool                   Tipo_integracion;
        bool                   Sw_cancela_calculo;
        unsigned int           Puntos_calcular;
        unsigned int           Puntos_trazar;
        bool                   Sw_Visualiza_bifurcaciones;
        bool                   Sw_Visualiza_exponente;
        bool                   Sw_Visualiza_referencia;
        bool                   Sw_Proceso_calculo;
        bool                   Sw_cerrar_ventana;

                               // Constructor de la clase 
                               Bifurcaciones(void);
        void                   Calcula_bifurcaciones(void);
       
        void                   Grafica(void);
        void                   Limpiar_vantana(void);
        void                   Limpia_matriz_pixeles(void)
                               {   
                                  pix[0].Asigna_todo_array(false);
                                  pix[1].Asigna_todo_array(false);
                               }
        void                   PasarValoresConfiguracion(void);
        void                   RetornarValoresConfiguracion(void);

        void                   __fastcall OnHint(TObject *Sender);
   public:		// User declarations
        __fastcall TFormaBifurcaciones(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif

