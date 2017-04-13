// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en trámite 1999-2000
// Revisión  1.1-A


//---------------------------------------------------------------------------
#ifndef VentanaCirculoH
#define VentanaCirculoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include "V_pixel.hpp"
#include "FuncionDisparo.hpp"
#include "ParamCirculo.h"

#define ADELANTE    1
#define ATRAZ       0
//---------------------------------------------------------------------------
class TFormaCirculo : public TForm
{
   __published:	// IDE-managed Components
        TStatusBar *BarraDeEstadosCirculo;
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
        TMenuItem *MenuCalcularCirculo;
        TMenuItem *MenuCalcularNumeroRotacion;
        TMenuItem *MenuCalcularSincronizacin;
        TMenuItem *MenuCalcularExpLyapunov;
        TMenuItem *Separador3;
        TMenuItem *MenuCalcularDetenerelcalculo;
        TMenuItem *MenuVentana;
        TMenuItem *MenuVentanaLimpiar;
        TMenuItem *MenuConfigurar;
        TMenuItem *MenuConfigurarParametros;
        TMenuItem *MenuConfigurarVisualizar;
        TMenuItem *MenuConfigurarCalculo;
        TMenuItem *MenuAyuda;
        TMenuItem *MenuAyudaAcercade;
        TMenuItem *Separador1;
        TMenuItem *MenuAyudaCirculo;
        TTimer *Timer1;
        TPopupMenu *PopupMenu1;
        TMenuItem *FijarCondicIninicial;
        TMenuItem *Separador5;
        TPanel *Panel1;
        TPaintBox *VTCirculo;
        void __fastcall MenuArchivoCerrarClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall MenuAyudaAcercadeClick(TObject *Sender);
        void __fastcall MenuAyudaCirculoClick(TObject *Sender);
        void __fastcall MenuCalcularIteracinesenCirculoClick(TObject *Sender);
        void __fastcall MenuCalcularNumRotacionClick(TObject *Sender);
        void __fastcall MenuCalcularSincronizacionClick(TObject *Sender);
        void __fastcall MenuCalcularExpLyapunovClick(TObject *Sender);
        void __fastcall MenuVentanaLimpiarClick(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall MenuConfigurarParametrosClick(TObject *Sender);
        void __fastcall MenuArchivoGrabarBMPClick(TObject *Sender);
        void __fastcall MenuArchivoImprimirClick(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall MenuConfigurarVisualizarClick(TObject *Sender);
        void __fastcall MenuConfigurarCalculoClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall MenuCalcularDetenerelcalculoClick(TObject *Sender);
        void __fastcall VTCirculoMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall FijarCondicIninicialClick(TObject *Sender);
        void __fastcall VTCirculoMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall VTCirculoMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall VTCirculoPaint(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormDeactivate(TObject *Sender);
   private:	// User declarations
        // Funcion de disparo
        FuncionDisparo         fun_disp;

        // Variables para mostrar la posición del mouse dentro de la ventana
        Dimencion_Ventana      Vs;
        char                   Msg[100];
        long double            xCondicion_inicial;
        long double            aux;
        long double            xCondicion_inicial_visualizada;
        int                    tmppx, tmppy;
        int                    tmppxa, tmppya;
        bool                   MousePresionado;
        

        // Puntero a la ventana de configuracion
        TVCap_Circunferencia  *configura;
        char                   xcad[200];

        Arreglo_pixeles        pix[2];             // Clase que contiene los graficos generados
        C_2D                   Escala;             // Escala del gráfico de iteraciones en la circunferencia
        unsigned int           Pix_x;              // Longitud en pixeles de la ventana
        unsigned int           Pix_y;              // Longitud en pixeles de la ventana
        Dimencion_Ventana      Dim_Vtn;            // Dimensiones de la ventana de pixeles
        TColor                 Color_grafica[4];   // Colores a usar dentro de la ventena de pixeles
        TColor                 Color_fondo;
        bool                   Detener_calculo;    // Indica si es necesario detener el calculo por el usuario
        unsigned int           Iteraciones;        // Numero de iteraciones 
        C_2D                   Condicion_inicial;  // Condición inicial
        bool                   Tipo_integracion;
        bool                   Sw_Visualiza_grafico;
        bool                   Sw_Visualiza_referencia;


                              
       void                   Calcula_referencia(void);
       void                   Calcula_iteraciones(void);
       
       void                   Grafica(bool tp = true);
       void                   Visualiza_marca(const int x, const int y, const TColor color);
       void                   Grafica_condicion_inicial(void);
       void                   Limpiar_vantana(void);
       void                   Limpia_matriz_pixeles(void)
                              {
                                 pix[1].Asigna_todo_array(false);
                              }
        void                  PasarValoresConfiguracion(void);
        void                  RetornarValoresConfiguracion(void);
        void                   __fastcall OnHint(TObject *Sender);
   public:		// User declarations
        __fastcall TFormaCirculo(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif

