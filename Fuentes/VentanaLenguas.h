// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en trámite 1999-2000
// Revisión  1.1-A


//---------------------------------------------------------------------------
#ifndef VentanaLenguasH
#define VentanaLenguasH
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
#define NUM_MAX_DIM_ZOOM 10
//---------------------------------------------------------------------------
class TFormaLenguas : public TForm
{
   __published:	// IDE-managed Components
        TStatusBar *BarraDeEstadosLenguas;
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
        TTimer *Timer1;
        TMenuItem *Separador5;
        TPanel *Panel1;
        TPaintBox *VTLenguas;
        TMenuItem *Separador6;
        TMenuItem *MenuArchivoLoadFileofTongues;
        TMenuItem *Separador7;
        TMenuItem *MenuVentanaSelectTongues;
        TOpenDialog *OpenDialogLenguas;
        TSaveDialog *SaveDialogLenguas;
        TMenuItem *N1;
        TMenuItem *MenuVentanaZoomOut;
        TMenuItem *MenuVentanaOriginalDimentions;
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
        void __fastcall MenuConfigurarCalculoClick(TObject *Sender);
        void __fastcall MenuArchivoGrabarBMPClick(TObject *Sender);
        void __fastcall MenuArchivoImprimirClick(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall MenuConfigurarParametrosClick(TObject *Sender);
        void __fastcall MenuConfigurarDimensionesClick(TObject *Sender);
        void __fastcall MenuConfigurarVisualizarClick(TObject *Sender);
        void __fastcall FijarCondicIninicialClick(TObject *Sender);
        void __fastcall VTLenguasMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall MenuCalcularDetenerelcalculoClick(TObject *Sender);
        void __fastcall VTLenguasPaint(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormDeactivate(TObject *Sender);
        void __fastcall MenuArchivoLoadFileofTonguesClick(TObject *Sender);
        void __fastcall VTLenguasMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall VTLenguasMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall MenuVentanaOriginalDimentionsClick(TObject *Sender);
        void __fastcall MenuVentanaZoomOutClick(TObject *Sender);
   private:	// User declarations
        // Funcion de Disparo
        FuncionDisparo         fun_disp;
                               
        // Puntero a la ventana de configuracion
        TVCap_Levantamientos *configura;
        char                  xcad[200];

        // Variables para mostrar la posición del mouse dentro de la ventana
        Dimencion_Ventana      Vs;
        char                   Msg[200];

        Arreglo_pixeles        pix[16]; // Clase que contiene los graficos generados   

        C_2D                    Escala; // Escala del gráfico
        unsigned int           Pix_x;
        unsigned int           Pix_y; 
        Dimencion_Ventana      Dim_Vtn;
        TColor                 Color_fondo;
        unsigned int           Puntos_trazar;
        unsigned int           Num_iteraciones;
        C_2D                    Condicion_inicial;
   
        bool                   Tipo_integracion;
        bool                   Detener_calculo;
        bool                   Sw_Proceso_calculo;
        bool                   Sw_cerrar_ventana;
       
        // Variables necesarias para dibujar recuadro de selecccion de una area 
        Definicion_Ventana     Vt1, Vt2, xVt;
        bool                   Ventana_seleccionada;
        bool                   Sw_Dibuja_rectangulo;
        bool                   Sw_Dibuja_rectangulo_ant;
        bool                   Sw_Recuadro_activo;
        int                    Ind_zoom;
        Dimencion_Ventana      Dim_zoom[NUM_MAX_DIM_ZOOM];
        Dimencion_Ventana      Dim_orig;

                               // Constructor de la clase 
                               Levantamientos(void);

        
        void                   Grafica(bool limpia);
        void                   Limpiar_vantana(void);
        void                   Limpia_matriz_pixeles(void)
                               {
                                  for (int i = 0; i < 16; i++) pix[i].Asigna_todo_array(false);
                               }
        void                   PasarValoresConfiguracion(void);
        void                   RetornarValoresConfiguracion(void);

        void                   __fastcall OnHint(TObject *Sender);

        int  Leer_Encabezado(void);
        int  Encontrar_todas_sincronizaciones(void);
        int  Leer_Especificaciones_Calculo(void);
        void Leer_Linea_Archivo(float *Resonancy, FILE *ApTongue);
        int  Analizar_Entrada(const float *, unsigned int *, unsigned int *);
        void Ordenacion(unsigned int *, unsigned int *);
        void Grabar_encabezado_archivo(void);
        void Calcula_Lenguas_Solicitadas(const long double a, const long double b);
        void Calcula_Lenguas_Todas(const long double a, const long double b);
        void inicia(void), Make_Mark(void);
        long double Siguiente_Disparo(const long double);  //Funcion que calcula los disparos 
        // Archivo de salida
        FILE *OutField;      
        // Archivo de lectura
        FILE *InField;
        // Numero de sisncronizaciones encontradas al leer el archivo de sincronizaciones
        unsigned int N_Sincro_encontradas;
        unsigned int Intern;
        unsigned int ItsTrans, //Cantidad de Iteraciones del Periodo Transitorio
            SizeOrbits,//Tamaño máximo de orbitas a detectar
            NCondInits, //Cantidad de conds. iniciales aleatorias elegidas para cada conj. de param. determin.
            Iterated,   //Orden de iterada de la funcion
            SizeTgs;    //Numero de Lenguas (Regiones de Sincronizacion)
                                                                             

        char THE_END;

        unsigned int *Tongues_P, *Tongues_Q;//Determinaci¢n de las Lenguas y su Color
        unsigned int Encontro;  //Determina si se ha encontrado alguna posible orbita periodica
        unsigned int SINCROS;
        unsigned int PtsX, PtsY;    

        long double a, b;
        float Terminador;
        float MinX, MaxX, MinY, MaxY;
        char Archivo_lenguas[300];

   public:		// User declarations
        __fastcall TFormaLenguas(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif

