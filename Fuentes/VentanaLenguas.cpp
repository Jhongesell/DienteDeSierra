// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en trámite 1999-2000
// Revisión  1.1-A


//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <Printers.hpp>
#include "Acecade.h"
#include "Ayuda.h"
#include "VentanaLenguas.h"
#include "Sincronizaciones.hpp"
#include "NumeroRotacion.hpp"
#include "ExponenteLyapunov.hpp"
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define FIN 9999.0 //Determina el final del archivo de almacenamiento
#define DESACTIVADO 0   
#define ACTIVADO  1
#define FALSO 0
#define VERDADERO 1
#define MAYORSINCRONIZACION  255
#define MAX_ARREGLO          1000
#define CLAVE_ENCABEZADO "LDNL0000"
#define TOLERANCIA 1e-15

//---------------------------------------------------------------------------
// Objetosglobales del sistema IyD
extern  Sincronizaciones       sincro;
extern  NumeroRotacion         num_rot;
extern  ExponenteLyapunov      exp_lyap;

// Variables globales de control de escenarios
extern  bool                   Limpiar_ventana;
extern  void                  *Ventana_activa;
extern  bool                   Calcular_sincronizaciones;
extern  bool                   Calcular_numero_rotacion;
extern  bool                   Calcular_exponente_lyapunov;  
extern  bool                   Configura_escenario;
extern  bool                   Calcula_escenario;
extern  bool                   Detener_Calculo;
extern  char                  *COMPANIA;
extern  char                  *E_MAIL;
extern  bool                   Zoom_manteniendo_aspecto;

const char *VG_TXT01   = "Arrastre el mouse para seleccionar el área";
TColor Colores[] = {
   clWhite,
   clMaroon,
   clGreen,
   clOlive,
   clNavy,
   clPurple,
   clTeal,
   clRed,
   clLime,
   clYellow,
   clBlue,
   clFuchsia,
   clAqua,
   clGray,
   clSilver,
   clBlack
};




// Al cerrar la forma ...
void __fastcall TFormaLenguas::FormClose(TObject *Sender,TCloseAction &Action)
{
   Ventana_activa = NULL;
   if(Tongues_P) delete [] Tongues_P;
   if(Tongues_Q) delete [] Tongues_Q;
   Free();     
}

// Al solicitar cerrar la ventana ...
void __fastcall TFormaLenguas::FormCloseQuery(TObject *Sender, bool &CanClose)
{
   CanClose = false;
   if (MessageBox(Handle,"Do you wish to close this window?","Toungues scenery",MB_YESNO + MB_ICONQUESTION)  == IDYES) {
      CanClose = true;
      Sw_cerrar_ventana = true;
   }
}

// Al dibujar la forma ...// Al cambiar de tamaño ...
void __fastcall TFormaLenguas::FormResize(TObject *Sender)
{
   // Calcula la escala de la ventana de visualizacion
   Escala.X = (VTLenguas->Width -1) / (long double) (Dim_Vtn.Xf - Dim_Vtn.Xi);
   Escala.Y = (VTLenguas->Height -1) / (long double) (Dim_Vtn.Yf - Dim_Vtn.Yi);
   // Grafica el contenido de la ventana
   Grafica(true);        
}


///////////////////////////////////////////////////////////////////////////////
//  Definición de Comportamientos del Menu 
///////////////////////////////////////////////////////////////////////////////

// Menu Archivo->Cerrar
void __fastcall TFormaLenguas::MenuArchivoCerrarClick(TObject *Sender)
{
   Close();        
}

// Menu->Archivo->Grabar BMP
void __fastcall TFormaLenguas::MenuArchivoGrabarBMPClick(TObject *Sender)
{
   TRect   xRect = Rect(0,0,VTLenguas->Width,VTLenguas->Height);
   Graphics::TBitmap *Bitmap = new Graphics::TBitmap;
   Bitmap->Width = VTLenguas->Width;
   Bitmap->Height = VTLenguas->Height;
   Bitmap->Canvas->CopyRect(xRect, VTLenguas->Canvas, xRect);
   SaveDialog->Title = "Save as ...";
   if (SaveDialog->Execute()) {
      Bitmap->SaveToFile(SaveDialog->FileName);           
   }
   VTLenguas->Canvas->Draw(0,0,Bitmap);
   delete Bitmap;
}

// Menu->Archivo->Imprimir
void __fastcall TFormaLenguas::MenuArchivoImprimirClick(TObject *Sender)
{
   TRect   xRect = Rect(0,0,ClientWidth,ClientHeight);
   Graphics::TBitmap *Bitmap = new Graphics::TBitmap;
   Bitmap->Width = ClientWidth;
   Bitmap->Height = ClientHeight;
   Bitmap->Canvas->CopyRect(xRect, Canvas, xRect);
   Bitmap->SaveToFile("Prn_img.bmp");
   delete Bitmap;
   Bitmap = new Graphics::TBitmap;
   Bitmap->LoadFromFile("Prn_img.bmp");
   Printer()->BeginDoc();
   Printer()->Canvas->TextOut(100,10,Application->Title);
   Printer()->Canvas->TextOut(100,100,Caption);
   Printer()->Canvas->StretchDraw(Rect(100,300,Printer()->PageWidth-100,Printer()->PageWidth-200),Bitmap);
   Printer()->Canvas->TextOut(100,(Printer()->PageWidth - 100),COMPANIA);
   Printer()->Canvas->TextOut(100,(Printer()->PageWidth - 10),E_MAIL);
   Printer()->EndDoc();
   delete Bitmap;
   unlink("Prn_img.bmp");
}

// Menu->Calcular->Calcular levantamientos
void __fastcall TFormaLenguas::MenuCalcularLevantamientosClick(TObject *Sender)
{
   if (!SaveDialogLenguas->Execute()) return;
   strcpy(Archivo_lenguas,SaveDialogLenguas->FileName.c_str());

   Sw_Proceso_calculo = true;
   Sw_cerrar_ventana = false; 
   Detener_calculo = false;
   TCursor antcursor = Cursor;
   // Inicializa la variable de cancelacion del calculo

   // Cambia el cursor del mouse
   Cursor = crHourGlass;
   Tongues_P = NULL;
   Tongues_Q = NULL;
   Intern = 0;
   ItsTrans = 500, //Cantidad de Iteraciones del Periodo Transitorio
   SizeOrbits = 5000,//Tamaño máximo de orbitas a detectar
   NCondInits = 3, //Cantidad de conds. iniciales aleatorias elegidas para cada conj. de param. determin.
   Iterated = 1,   //Orden de iterada de la funcion
   SizeTgs = 5;    //Numero de Lenguas (Regiones de Sincronizacion)
                                                                             

   THE_END = DESACTIVADO;

   Encontro=FALSO;  //Determina si se ha encontrado alguna posible orbita periodica
   SINCROS=DESACTIVADO;

   Terminador = FIN;



   long double Incx, Incy;
   // Eleccion de Lenguas a calcular
   if (Leer_Especificaciones_Calculo()) return;              
   Incx = ((MaxX - MinX) / ((long double) PtsX));  
   Incy = ((MaxY - MinY) / ((long double) PtsY));
   
   //  abrir archivo para almacenamiento
   OutField = fopen(Archivo_lenguas,"wb");
   if( OutField == NULL ) return;
   // Grabar encabezado de archivo de lenguas
   Grabar_encabezado_archivo();
   //Eleccion de funcion para calcular lenguas
   //Cuando SINCROS esta ACTIVADO, indica que se proporciono una lista de sincronizaciones para pintarlas
   //en caso contrario, indica que no se proporciono una lista de sincronizaciones
   if(SINCROS == ACTIVADO)
   {   
       //Tamano maximo de sincronizacion a detectar
       SizeOrbits = Tongues_Q[SizeTgs-1];
       //Los siguientes dos "for" hacen la red de puntos en el plano (a,b)
       for (a = MinX; a <= MaxX; a += Incx)  //Step in eje X (Horizontal)
       {
          Application->ProcessMessages();
          if (Sw_cerrar_ventana || Detener_calculo) break;
          sprintf(xcad,"Calculating Tongues of the parameter a = %Lf (this process may last several minutes).", a);
          BarraDeEstadosLenguas->SimpleText=(AnsiString) xcad;
          for (b = MinY; b <= MaxY; b += Incy )  //Step in eje Y (Vertical)
          {
             Calcula_Lenguas_Solicitadas(a, b);
          }
       }
   }
   else
   {
       //Los siguientes dos "for" hacen la red de puntos en el plano (a,b)
       for (a = MinX; a <= MaxX; a += Incx )  //Step in eje X (Horizontal)
       {
          Application->ProcessMessages();
          if (Sw_cerrar_ventana || Detener_calculo) break;
          sprintf(xcad,"Calculating Tongues of the parameter a =%Lf (this process may last several minutes).", a);
          BarraDeEstadosLenguas->SimpleText=(AnsiString) xcad;
          for (b = MinY; b <= MaxY; b += Incy )  //Step in eje Y (Vertical)
          {
             Calcula_Lenguas_Todas(a, b);
          }
       }
   }

   // Cerrar archivo
   fwrite(&Terminador, sizeof(Terminador), 1, OutField);
   fclose(OutField);
   delete[] Tongues_Q;
   delete[] Tongues_P;
   BarraDeEstadosLenguas->SimpleText=(AnsiString) " ";
   Cursor = antcursor;
   Sw_Proceso_calculo = false;
}

// Menu->Calcular->Numero de Rotación
void __fastcall TFormaLenguas::MenuCalcularNumeroRotacionClick(TObject *Sender)
{
   TCursor antcursor = Cursor;
   // Cambia el cursor del mouse
   Cursor = crHourGlass;
   long double p[NUM_MAX_PARAMETROS], rot;
   BarraDeEstadosLenguas->SimpleText = (AnsiString) "Calculating rotation number (this process may last several seconds).";
   // Recupera los parámetros por omisión
   fun_disp.RetornaParametros(p);
   // Cambiar parámetros
   num_rot.AsignaParametros(p);
   rot = num_rot.Calcula(Tipo_integracion);
   char xcad[200];
   sprintf(xcad,"Rotation number: %Lf",rot);
   MessageBox(NULL,xcad,"Tongues scenery",MB_OK+MB_ICONINFORMATION);
   BarraDeEstadosLenguas->SimpleText = (AnsiString) " ";
   // Cambia el cursor del mouse
   Cursor = antcursor;
}

// Menu->Calcular->Sincronización
void __fastcall TFormaLenguas::MenuCalcularSincronizacinClick(TObject *Sender)
{
   TCursor antcursor = Cursor;
   // Cambia el cursor del mouse
   Cursor = crHourGlass;
   long double p[NUM_MAX_PARAMETROS];
   unsigned int xp, xq;
   BarraDeEstadosLenguas->SimpleText = (AnsiString) "Calculating synchronization (this process may last several seconds).";
   // Recupera los parámetros por omisión
   fun_disp.RetornaParametros(p);
   // Cambiar parámetros
   sincro.AsignaParametros(p);
   sincro.Calcula(Tipo_integracion, xp, xq);
   char xcad[200];
   sprintf(xcad,"Synchronization: %u /%u ",xp,xq);
   MessageBox(NULL,xcad,"Tongues scenery",MB_OK+MB_ICONINFORMATION);
   BarraDeEstadosLenguas->SimpleText = (AnsiString) " ";
   // Cambia el cursor del mouse
   Cursor = antcursor;
}

// Menu->Calcular->Exponente de Lyapunov
void __fastcall TFormaLenguas::MenuCalcularExpLyapunovClick(TObject *Sender)
{
   TCursor antcursor = Cursor;
   // Cambia el cursor del mouse
   Cursor = crHourGlass;
   // Cambia el cursor del mouse
   Cursor = antcursor;
   long double p[NUM_MAX_PARAMETROS], rot;
   BarraDeEstadosLenguas->SimpleText = (AnsiString) "Calculating Lyapunov exponent (this process may last several seconds).";
   // Recupera los parámetros por omisión
   fun_disp.RetornaParametros(p);
   // Cambiar parámetros
   exp_lyap.AsignaParametros(p);
   rot = exp_lyap.Calcula(Tipo_integracion);
   char xcad[200];
   sprintf(xcad,"Lyapunov exponent: %Lf",rot);
   MessageBox(NULL,xcad,"Tongues scenery",MB_OK+MB_ICONINFORMATION);
   BarraDeEstadosLenguas->SimpleText = (AnsiString) " ";
   // Cambia el cursor del mouse
   Cursor = antcursor;
}

// Menu->ventana->limpiar
void __fastcall TFormaLenguas::MenuVentanaLimpiarClick(TObject *Sender)
{
   Limpia_matriz_pixeles();
   Grafica(true);
}



// Menu->Ventana->Zoom Out
void __fastcall TFormaLenguas::MenuVentanaZoomOutClick(TObject *Sender)
{
   // Almacena las dimensiones actuales
   if (Ind_zoom > 0) {
      Ind_zoom --;
      Dim_Vtn = Dim_zoom[Ind_zoom];
      pix[0].Cambia_dimension(Dim_Vtn);
      FormResize(this);
//      Calcula_bifurcaciones();
      if (Ind_zoom < 1) MenuVentanaZoomOut->Enabled = false;
   }
}

// Menu->Ventana->Dimensiones originales
void __fastcall TFormaLenguas::MenuVentanaOriginalDimentionsClick(TObject *Sender)
{
   Dim_Vtn = Dim_orig;
   Ind_zoom = 0;
   MenuVentanaZoomOut->Enabled = false;
   // Actualiza las dimensiones de las ventanas de trabajo
   pix[0].Cambia_dimension(Dim_Vtn);
   FormResize(this);
//   Calcula_bifurcaciones();
}


// Menu->Configurar->Parametros
void __fastcall TFormaLenguas::MenuConfigurarParametrosClick(TObject *Sender)
{
   configura = new TVCap_Levantamientos(this);
   if (configura) {
      PasarValoresConfiguracion();
      configura->TabbedNotebook1->PageIndex = 0;
      configura->ShowModal();
      RetornarValoresConfiguracion();
      delete configura;
   }
}

// Menu->Configurar->Dimensiones
void __fastcall TFormaLenguas::MenuConfigurarDimensionesClick(TObject *Sender)
{
   configura = new TVCap_Levantamientos(this);
   if (configura) {
      PasarValoresConfiguracion();
      configura->TabbedNotebook1->PageIndex = 1;
      configura->ShowModal();
      RetornarValoresConfiguracion();
      delete configura;
   }
}

// Menu->Configurar->Visualizar
void __fastcall TFormaLenguas::MenuConfigurarVisualizarClick(TObject *Sender)
{
   configura = new TVCap_Levantamientos(this);
   if (configura) {
      PasarValoresConfiguracion();
      configura->TabbedNotebook1->PageIndex = 2;
      configura->ShowModal();
      RetornarValoresConfiguracion();
      delete configura;
   }
}

// Menu->Configurar->Escenario
void __fastcall TFormaLenguas::MenuConfigurarCalculoClick(TObject *Sender)
{
   configura = new TVCap_Levantamientos(this);
   if (configura) {
      PasarValoresConfiguracion();
      configura->TabbedNotebook1->PageIndex = 3;
      configura->ShowModal();
      RetornarValoresConfiguracion();
      delete configura;
   }
}


// Acerca de ...
void __fastcall TFormaLenguas::MenuAyudaAcercadeClick(TObject *Sender)
{
   TVAcercaDe *Acercade = new TVAcercaDe(this);
   if (Acercade) {
      Acercade->ShowModal();
      delete Acercade;
   }
}

// Ayuda de TFormaLevantamientos
void __fastcall TFormaLenguas::MenuAyudaLevantamientosClick(TObject *Sender)
{
   TAyudaForm *Ayuda = new TAyudaForm(this);
   if (Ayuda) {
      Ayuda->Abrir_archivo("Tongues scenery","Tongues.hlp");
      Ayuda->Show();
   }
}



///////////////////////////////////////////////////////////////////////////////
//  Definición de Comportamientos de TFormaLevantamientos 
///////////////////////////////////////////////////////////////////////////////

// Constructor de la clase
__fastcall TFormaLenguas::TFormaLenguas(TComponent* Owner) : TForm(Owner)
{
   // Inicializa el indicador de recuadro
   Sw_Dibuja_rectangulo = false;
   Ventana_seleccionada = false;
   Sw_Recuadro_activo = true;

   Detener_calculo = false;
   Sw_cerrar_ventana = false;
   // Dimenciones de la ventana
   Dim_Vtn.Xi = 0.0;
   Dim_Vtn.Xf = 1.0;
   Dim_Vtn.Yi = 0.0;
   Dim_Vtn.Yf = 1.0;
   // Longitud de la ventana de pixeles
   Pix_x = 1024;
   Pix_y = 768;
   // Inicializa la ventana de pixeles
   for (int i = 0; i < 16; i++) pix[i].Inicializa(Pix_x, Pix_y, false,Dim_Vtn);
   
   // Condición inicial
   Condicion_inicial.X = 0.0; 
   Condicion_inicial.Y = 0.0;
   // Configuracion de lineas en el levantamiento
   Num_iteraciones = 1;
   Color_fondo = clSilver;

   // Puntos a trazar en la curva
   Puntos_trazar = Pix_x;
   // Tipo de inegración en este escenario
   Tipo_integracion = ADELANTE;
}

// Grafica el mapa de pixeles
void TFormaLenguas::Grafica(bool limpia)
{
   unsigned int x, y, i;
   // Calcula la escala de la ventana de visualizacion con respecto a la ventana de pixeles
   C_2D esc;
   
   if (limpia) Limpiar_vantana();
   esc.X = VTLenguas->Width / (long double) Pix_x;
   esc.Y = VTLenguas->Height / (long double) Pix_y;
   // Visualiza la ventana de pixeles
   for(i = 0; i < 16; i++) {
      for(y = 0; y < Pix_y; y++) {
          for(x = 0; x < Pix_x; x++) {
              if(pix[i].Retorna_valor(x, y)) VTLenguas->Canvas->Pixels[x * esc.X][y * esc.Y] = Colores[i];
          }
      }
   } 
}

// Limpia la ventana de graficacion
void TFormaLenguas::Limpiar_vantana(void)
{
   VTLenguas->Canvas->Pen->Color = Color_fondo;
   VTLenguas->Canvas->Brush->Color = Color_fondo;
   VTLenguas->Canvas->Rectangle(0, 0, VTLenguas->Width, VTLenguas->Height);
}

//#error Si se solicita cerrar ventana cancelar calculo y visualización

///////////////////////////////////////////////////////////////////////////////
// Controla el movimiento del mouse y genereación del recuadro para el zoom del
// la ventana de Lenguas
///////////////////////////////////////////////////////////////////////////////
// Cuando el mouse es movido
void __fastcall TFormaLenguas::VTLenguasMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
   if (Sw_Recuadro_activo) {
      if (Sw_Dibuja_rectangulo) {
         TPenMode mode;

         mode = VTLenguas->Canvas->Pen->Mode;
         VTLenguas->Canvas->Pen->Mode = pmNot;
      
         if (Sw_Dibuja_rectangulo_ant) {
            VTLenguas->Canvas->MoveTo(Vt2.Xi,Vt2.Yi);
            VTLenguas->Canvas->LineTo(Vt2.Xf,Vt2.Yi);
            VTLenguas->Canvas->MoveTo(Vt2.Xi,Vt2.Yi);
            VTLenguas->Canvas->LineTo(Vt2.Xi,Vt2.Yf);
            VTLenguas->Canvas->MoveTo(Vt2.Xf,Vt2.Yf);
            VTLenguas->Canvas->LineTo(Vt2.Xi,Vt2.Yf);
            VTLenguas->Canvas->MoveTo(Vt2.Xf,Vt2.Yf);
            VTLenguas->Canvas->LineTo(Vt2.Xf,Vt2.Yi);
         }
         VTLenguas->Canvas->MoveTo(Vt1.Xi,Vt1.Yi);
         VTLenguas->Canvas->LineTo(X,Vt1.Yi);
         VTLenguas->Canvas->MoveTo(Vt1.Xi,Vt1.Yi);
         VTLenguas->Canvas->LineTo(Vt1.Xi,Y);
         VTLenguas->Canvas->MoveTo(X,Y);
         VTLenguas->Canvas->LineTo(Vt1.Xi,Y);
         VTLenguas->Canvas->MoveTo(X,Y);
         VTLenguas->Canvas->LineTo(X,Vt1.Yi);
      
         Vt2.Xf = X;
         Vt2.Yf = Y;
         VTLenguas->Canvas->Pen->Mode = mode;
         Sw_Dibuja_rectangulo_ant = true;

         // Ajusta a que xVt tenga el inicio y el final de la ventana
         xVt.Xi = Vt1.Xi, xVt.Xf = Vt2.Xf, xVt.Yi = Vt1.Yi, xVt.Yf = Vt2.Yf;
         int  xtmp;
         if (xVt.Xi > xVt.Xf) xtmp = xVt.Xi, xVt.Xi = xVt.Xf, xVt.Xf = xtmp;
         if (xVt.Yi > xVt.Yf) xtmp = xVt.Yi, xVt.Yi = xVt.Yf, xVt.Yf = xtmp;
         // Ajusta los valores a la longitud de la ventana
         if (xVt.Xi < 0) xVt.Xi = 0;
         if (xVt.Yi < 0) xVt.Yi = 0;
         if (xVt.Xf > VTLenguas->Width) xVt.Xf = VTLenguas->Width;
         if (xVt.Yf > VTLenguas->Height) xVt.Yf = VTLenguas->Height;
         // Visualiza los valores de la region seleccionada segun la dimención de la ventana
         Vs.Xi = xVt.Xi / Escala.X + Dim_Vtn.Xi;
         Vs.Yi = (-(xVt.Yi - VTLenguas->Height) / Escala.Y) + Dim_Vtn.Yi;
         Vs.Xf = xVt.Xf / Escala.X + Dim_Vtn.Xi;
         Vs.Yf = (-(xVt.Yf - VTLenguas->Height) / Escala.Y) + Dim_Vtn.Yi;
         sprintf(xcad,"%s: (%3.5Lf, %3.5Lf, %3.5Lf, %3.5Lf)",VG_TXT01,Vs.Xi,Vs.Yf,Vs.Xf,Vs.Yi);
         BarraDeEstadosLenguas->SimpleText = (AnsiString) xcad;
      } else {
         Vs.Xf = X, Vs.Yf = Y;
         Vs.Xi = Vs.Xf / Escala.X + Dim_Vtn.Xi;
         Vs.Yi = (-(Vs.Yf - VTLenguas->Height) / Escala.Y) + Dim_Vtn.Yi;

         sprintf(Msg,"Mouse position: (%3.8Lf, %3.8Lf)", Vs.Xi, Vs.Yi);
         BarraDeEstadosLenguas->SimpleText = (AnsiString) Msg;
      }    
   }
}


// Cuando el mouse es presionado
void __fastcall TFormaLenguas::VTLenguasMouseDown(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y)
{
   if (Sw_Recuadro_activo) {
      if (Button == mbLeft) {
         Vt2.Xf = Vt1.Xf = Vt2.Xi = Vt1.Xi = X;
         Vt2.Yf = Vt1.Yf = Vt2.Yi = Vt1.Yi = Y;
         Sw_Dibuja_rectangulo = true;
         Sw_Dibuja_rectangulo_ant = false;
         Ventana_seleccionada = false;
      }
   }
}

// Cuando el mouse es soltado
void __fastcall TFormaLenguas::VTLenguasMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
   if (Sw_Recuadro_activo) {
      if (Button == mbLeft) {
         TPenMode mode;
         mode = VTLenguas->Canvas->Pen->Mode;
         VTLenguas->Canvas->Pen->Mode = pmNot;
         VTLenguas->Canvas->MoveTo(Vt2.Xi,Vt2.Yi);
         VTLenguas->Canvas->LineTo(Vt2.Xf,Vt2.Yi);
         VTLenguas->Canvas->MoveTo(Vt2.Xi,Vt2.Yi);
         VTLenguas->Canvas->LineTo(Vt2.Xi,Vt2.Yf);
         VTLenguas->Canvas->MoveTo(Vt2.Xf,Vt2.Yf);
         VTLenguas->Canvas->LineTo(Vt2.Xi,Vt2.Yf);
         VTLenguas->Canvas->MoveTo(Vt2.Xf,Vt2.Yf);
         VTLenguas->Canvas->LineTo(Vt2.Xf,Vt2.Yi);
         VTLenguas->Canvas->Pen->Mode = mode;
         Vt1.Xf = X;
         Vt1.Xf = Y;
         Sw_Dibuja_rectangulo = false;
         Sw_Dibuja_rectangulo_ant = false;
         BarraDeEstadosLenguas->SimpleText = (AnsiString) " ";
         Ventana_seleccionada = true;
         // Revisa si realmente se solicito el zoom
         if (abs(Vt2.Xf - Vt2.Xi) > 5 && abs(Vt2.Yf - Vt2.Yi) > 5) {
            // Pregunta si se desea hacer el zoom
            if (MessageBox(Handle,"Do you wish to zoom?","Bifurcations scenery",MB_YESNO + MB_ICONQUESTION)  == IDYES) {
               // Almacena las dimensiones actuales
               Dim_zoom[Ind_zoom] = Dim_Vtn;
               if ((Ind_zoom + 1) < NUM_MAX_DIM_ZOOM) Ind_zoom ++;
               MenuVentanaZoomOut->Enabled = true;
               long double incx = fabsl(Vs.Xf - Vs.Xi);
               long double incy = fabsl(Vs.Yf - Vs.Yi);
               long double inc  = (incx > incy ? incx : incy);
               // Actualiza las dimensiones de las ventanas de trabajo
               Dim_Vtn.Xi = Vs.Xi;
               Dim_Vtn.Yi = Vs.Yf;
               
               if (Zoom_manteniendo_aspecto) {
                  Dim_Vtn.Xf = Vs.Xi + inc;
                  Dim_Vtn.Yf = Vs.Yf + inc;
                } else {
                  Dim_Vtn.Xf = Vs.Xf;
                  Dim_Vtn.Yf = Vs.Yi;
               }
               pix[0].Cambia_dimension(Dim_Vtn);
               FormResize(this);
//               Calcula_bifurcaciones();
            }
         }
      }
   }
}


void __fastcall TFormaLenguas::FijarCondicIninicialClick(TObject *Sender)
{
   Condicion_inicial.X = Vs.Xi; 
   Condicion_inicial.Y = 0.0;
}

// Pasa los valores de configuración de la ventana de captura
void TFormaLenguas::PasarValoresConfiguracion(void)
{
   ////////////////////////////////////////////////////////
   // Parámetros
   ////////////////////////////////////////////////////////
   // Parámetros
   configura->ListBoxParametros->Items->Clear();
   for( int i = 0; i < fun_disp.Numero_parametros; i++) {
      sprintf(xcad,"%-6s = %1.9Lf",fun_disp.Nombre_parametros[i],fun_disp.P[i] );
      configura->ListBoxParametros->Items->Add(xcad);
   }
   ////////////////////////////////////////////////////////
   // Dimensiones
   ////////////////////////////////////////////////////////
   sprintf(xcad,"%Lf",Dim_Vtn.Xi);
   configura->EditHMin->Text = (AnsiString) xcad;
   sprintf(xcad,"%Lf",Dim_Vtn.Xf);
   configura->EditHMax->Text = (AnsiString) xcad;
   sprintf(xcad,"%Lf",Dim_Vtn.Yi);
   configura->EditVMin->Text = (AnsiString) xcad;
   sprintf(xcad,"%Lf",Dim_Vtn.Yf);
   configura->EditVMax->Text = (AnsiString) xcad;
   ////////////////////////////////////////////////////////
   // Visualizar
   ////////////////////////////////////////////////////////
   // Check Box
   // Colores
   configura->Panel9->Color = Color_fondo;
   ////////////////////////////////////////////////////////
   // Escenario
   ////////////////////////////////////////////////////////
   sprintf(xcad,"%Lf",Condicion_inicial.X);
   configura->Edit7->Text = (AnsiString) xcad;
   sprintf(xcad,"%u",Puntos_trazar);
   configura->Edit8->Text = (AnsiString) xcad;
   sprintf(xcad,"%u",Num_iteraciones);
   configura->Edit9->Text = (AnsiString) xcad;
   configura->RadioButton1->Checked = Tipo_integracion;   
   configura->RadioButton2->Checked = !Tipo_integracion;   
}

// Retorna los valores de configuración de la ventana de captura
void TFormaLenguas::RetornarValoresConfiguracion(void)
{
   if (!configura->Aceptar) return;
   ////////////////////////////////////////////////////////
   // Parámetros
   ////////////////////////////////////////////////////////
   for (int i = 0; i < fun_disp.Numero_parametros; i++) {
       unsigned int i1, i2;
       char xcad[100], xcad1[100];
       strcpy(xcad1,configura->ListBoxParametros->Items->Strings[i].c_str());
       // Valor del parámetro
       for (i2 = 0, i1 = 9; i1 < strlen(xcad1); i2++, i1++) xcad[i2] = xcad1[i1];
       xcad[i2] = 0;
       fun_disp.P[i] = _atold(xcad);
   }
   ////////////////////////////////////////////////////////
   // Dimensiones
   ////////////////////////////////////////////////////////
   Dim_Vtn.Xi = _atold(configura->EditHMin->Text.c_str());       
   Dim_Vtn.Xf = _atold(configura->EditHMax->Text.c_str());       
   Dim_Vtn.Yi = _atold(configura->EditVMin->Text.c_str());       
   Dim_Vtn.Yf = _atold(configura->EditVMax->Text.c_str());       
   ////////////////////////////////////////////////////////
   // Visualizar
   ////////////////////////////////////////////////////////
   Color_fondo      = configura->Panel9->Color;
   ////////////////////////////////////////////////////////
   // Escenario
   ////////////////////////////////////////////////////////
   Condicion_inicial.X = _atold(configura->Edit7->Text.c_str());       
   Puntos_trazar       = atoi(configura->Edit8->Text.c_str());       
   Num_iteraciones     = atoi(configura->Edit9->Text.c_str());       
   Tipo_integracion    = configura->RadioButton1->Checked;   
   /////////////////////////////////////////////////////////
   // Al terminar
   /////////////////////////////////////////////////////////
   pix[0].Cambia_dimension(Dim_Vtn);
   pix[1].Cambia_dimension(Dim_Vtn);
   pix[2].Cambia_dimension(Dim_Vtn);
   pix[3].Cambia_dimension(Dim_Vtn);
   FormResize(this);
}

void __fastcall TFormaLenguas::Timer1Timer(TObject *Sender)
{
   // Almacena la ventana activa
   if (Focused()) {
      Ventana_activa = this;
   }   
   // Revisa si es la ventana activa 
   if (Ventana_activa == this) {
      // Calcula el número de rotacion
      if (Calcular_numero_rotacion) {
          Calcular_numero_rotacion = false;
          MenuCalcularNumeroRotacionClick(this);
      }
      // Calcula la sincronización
      if (Calcular_sincronizaciones) {
          Calcular_sincronizaciones = false;
          MenuCalcularSincronizacinClick(this);
      }
      // Calcula el exponente de Luapunov
      if (Calcular_exponente_lyapunov) {
          Calcular_exponente_lyapunov = false;
          MenuCalcularExpLyapunovClick(this);
      }
      // Configura el escenario
      if (Configura_escenario) {
          Configura_escenario = false;
          MenuConfigurarParametrosClick(this);
      }
      // Calcula
      if (Calcula_escenario) {
          Calcula_escenario = false;
          MenuCalcularLevantamientosClick(this);
      }
      // Detener cálculo
      if (Detener_Calculo) {
          Detener_Calculo = false;
          MenuCalcularDetenerelcalculoClick(this);
      }
      // Limpia la ventana
      if (Limpiar_ventana) {
          Limpiar_ventana = false;
          MenuVentanaLimpiarClick(this);
      }
   }
   // Controla que no este calculando para cerrar la ventana
   if (Sw_cerrar_ventana && !Sw_Proceso_calculo) {
      Ventana_activa = NULL;
      Free();
   }
}

void __fastcall TFormaLenguas::MenuCalcularDetenerelcalculoClick(TObject *Sender)
{
   Detener_calculo = true;        
}

void __fastcall TFormaLenguas::VTLenguasPaint(TObject *Sender)
{
   // Grafica el contenido de la ventana
   Grafica(true);        
}

// OnHint
void  __fastcall TFormaLenguas::OnHint(TObject *Sender)
{
   BarraDeEstadosLenguas->SimpleText = Application->Hint;
}

void __fastcall TFormaLenguas::FormActivate(TObject *Sender)
{
   Application->OnHint = OnHint;
}

void __fastcall TFormaLenguas::FormDeactivate(TObject *Sender)
{
   Application->OnHint = NULL;
}



void __fastcall TFormaLenguas::MenuArchivoLoadFileofTonguesClick(TObject *Sender)
{
   if (!OpenDialogLenguas->Execute()) return;
   strcpy(Archivo_lenguas,OpenDialogLenguas->FileName.c_str());

   if (Encontrar_todas_sincronizaciones()) return;
   
   // Lectura del archivo de encabezado
   if (Leer_Encabezado()) return;

    //Det. la cantidad de sincros para un conj. de parametros especificos
    unsigned char Indice_sincronizaciones = 0;
   
    // Definicion del arreglo de sincronizaciones
    unsigned char Arreglo_Sincronizaciones_Q[MAYORSINCRONIZACION];
    unsigned char Arreglo_Sincronizaciones_P[MAYORSINCRONIZACION];

    //Parametros (A y B); LeeLongDb se utiliza para capturar valores de tipo long double
    float A, B;


    //Se lee la informacion correspondiente a cada uno de los valores de los parámetros
    //y sus posibles sincronizaciones
    unsigned int i, xi;
    int px, py;
    while (1)
    {
       //Lectura del Parametro A
       fread(&A, sizeof(A), 1, InField);
       //Condicion de que no se ha llegado al final del archivo
       if (A == FIN) break;
       //Lectura del Parametro B
       fread(&B, sizeof(B), 1, InField);
       //Lectura del Numero de Sincronizaciones
       fread(&Indice_sincronizaciones, sizeof(Indice_sincronizaciones), 1, InField);
       //Lectura de las Sincronizaciones
       for (i = 0; i < Indice_sincronizaciones; i++)
       {
          fread(&Arreglo_Sincronizaciones_Q[i], sizeof(Arreglo_Sincronizaciones_Q[i]), 1, InField);
          fread(&Arreglo_Sincronizaciones_P[i], sizeof(Arreglo_Sincronizaciones_P[i]), 1, InField);
          // Visualización de las lenguas
          for (xi = 0; xi < SizeTgs; xi++) {
             if (Tongues_P[xi] == Arreglo_Sincronizaciones_P[i] && Tongues_Q[xi] == Arreglo_Sincronizaciones_Q[i]) {
                pix[xi%16].Asigna_valor(A,B,true);
                px = (A - Dim_Vtn.Xi) * Escala.X;
                py = VTLenguas->Height - (((B - Dim_Vtn.Yi) * Escala.Y) + 1.0);
                VTLenguas->Canvas->Pixels[px][py] = Colores[xi%16];
                break; 
             }
          }
       }
    } //Termina while(1)
    //Cierra el Archivo que fue leido
    fclose(InField);
}
//---------------------------------------------------------------------------


// Lee el encabezado del archivo de lenguas
int TFormaLenguas::Leer_Encabezado(void)
{
    float MinX, MaxX, MinY, MaxY;

    unsigned int PtsX, PtsY;

    float LeeLongDb = 0.0;
    //Arreglo utilizado para capturar textos del archivo de Lectura
    char Outer[400];

    InField = fopen(Archivo_lenguas,"rb");
    if ( InField == NULL ) return 1;

    ///////////  Clave de Archivo
    fread(Outer, 8, 1, InField);
    Outer[8] = 0;
   
    // Comprueba si el archivo de Apertura cumple con los requerimientos
    if ( strcmp(CLAVE_ENCABEZADO, Outer) != 0) return 1;
   
    /////Nombre del Archivo
    fread(Outer, 30, 1, InField);
    Outer[30] = 0;

    ///////////Comentarios
    fread(Outer, 300, 1, InField);
    Outer[300] = 0;
     
    ////////////// Seccion de Parametros a Variar
    fread(Outer, 100, 1, InField);
    Outer[100] = 0;

    //////////////Clave Numero de Sincronizaciones: Tipo de Algorit.
    fread(Outer, 20, 1, InField);
    Outer[20] = 0;

    ////////// C O N F I G U R A C I O N //////////////////
    fread(Outer, 100, 1, InField);
    Outer[100] = 0;
     
    /////// Dimensiones en X e Y Reales
    fread(Outer, 100, 1, InField);
    Outer[100] = 0;

    fread(&MinX, sizeof(MinX), 1, InField);  //MinX
    fread(&MinY, sizeof(MinY), 1, InField);  //MinY
    fread(&MaxX, sizeof(MaxX), 1, InField);  //MaxX
    fread(&MaxY, sizeof(MaxY), 1, InField);  //MaxY

    /////// Cantidad de Pts en X e Y Fisicas
    fread(Outer, 100, 1, InField);
    Outer[100] = 0;

    fread(&PtsX, sizeof(PtsX), 1, InField);
    fread(&PtsY, sizeof(PtsY), 1, InField);
     
    /////// Longitud de Paso de Calculo
    fread(Outer, 50, 1, InField);
    Outer[50] = 0;

    fread(&LeeLongDb, sizeof(LeeLongDb), 1, InField);
    fread(&LeeLongDb, sizeof(LeeLongDb), 1, InField);
     
    /////// Ecuacion del Sistema
    fread(Outer, 100, 1, InField);
    Outer[100] = 0;
    
    //////// Formato de Almacenamiento de Sincronizaciones
    fread(Outer, 100, 1, InField);
    Outer[100] = 0;

   return 0;
}


int TFormaLenguas::Encontrar_todas_sincronizaciones(void)
{
   // Lectura del archivo de encabezado
   if (Leer_Encabezado()) return 1;

    //Det. la cantidad de sincros para un conj. de parametros especificos
    unsigned char Indice_sincronizaciones = 0;
   
    // Definicion del arreglo de sincronizaciones
    unsigned char Arreglo_Sincronizaciones_Q[MAYORSINCRONIZACION];
    unsigned char Arreglo_Sincronizaciones_P[MAYORSINCRONIZACION];

    unsigned int i;
    unsigned int *Back_T_Q = new unsigned int[MAX_ARREGLO];
    unsigned int *Back_T_P = new unsigned int[MAX_ARREGLO];
    float A, B;
    unsigned int Count;
    N_Sincro_encontradas = 0;

    //Inicializacion de los elementos del arreglo
    for (i = 0; i < MAX_ARREGLO; i++) Back_T_Q[i] = Back_T_P[i] = 0;
    
    while (1)
    {
       //Lectura del Parametro A
       fread(&A, sizeof(A), 1, InField);
       //Condicion de que no se ha llegado al final del archivo
       if (A == FIN) break;
       //Lectura del Parametro B
       fread(&B, sizeof(B), 1, InField);
       //Lectura del Numero de Sincronizaciones para los paramatros (A, B)
       fread(&Indice_sincronizaciones, sizeof(Indice_sincronizaciones), 1, InField);
       //Lectura de las Sincronizaciones para los parametros (A, B)
       
       for (i = 0; i < Indice_sincronizaciones; i++)
       {
          fread(&Arreglo_Sincronizaciones_Q[i], sizeof(Arreglo_Sincronizaciones_Q[i]), 1, InField);
          fread(&Arreglo_Sincronizaciones_P[i], sizeof(Arreglo_Sincronizaciones_P[i]), 1, InField);
       }

       for (i = 0; i < Indice_sincronizaciones; i++)
       {
          Count = 0;
          do
          {
             if ( (Arreglo_Sincronizaciones_Q[i] == Back_T_Q[Count]) && (Arreglo_Sincronizaciones_P[i] == Back_T_P[Count]) ) break;
             Count ++;
          } while( Count <= N_Sincro_encontradas);
          if ( Count > N_Sincro_encontradas)
          {
             Back_T_Q[N_Sincro_encontradas] = Arreglo_Sincronizaciones_Q[i];
             Back_T_P[N_Sincro_encontradas] = Arreglo_Sincronizaciones_P[i];
             N_Sincro_encontradas ++;
             Count = N_Sincro_encontradas+1;
          }
       }  // end para Indice_sincronizaciones
    } //Termina while(1)
    //Cierra el Archivo que fue leido
    fclose(InField);
    SizeTgs = N_Sincro_encontradas;
    //Proceso de Ordenacion en orden ascendente de Q
    if (SizeTgs) Ordenacion(Back_T_Q, Back_T_P);
    delete []Back_T_Q; 
    delete []Back_T_P;
    return 0;
}


// Rutina de ordenacion de Lenguas en Qs
void TFormaLenguas::Ordenacion(unsigned int *Back_T_Q, unsigned int *Back_T_P)
{
   unsigned int Natural_Q = 0, Natural_P = 0, Count = 0, sizeorbits = 0, i = 0;

   Tongues_P = new unsigned int[SizeTgs];
   Tongues_Q = new unsigned int[SizeTgs];

   // Encuentra la maxima orbita
   for (i = 0; i < SizeTgs; i++) {
      if (Back_T_Q[i] > sizeorbits) sizeorbits = Back_T_Q[i];
   }

   //Ordenacion de las Sincronizaciones
   for(Natural_Q = 1; Natural_Q < sizeorbits; Natural_Q++)
   {
      for(Natural_P = 0; Natural_P <= Natural_Q; Natural_P++)
      {
         for(i = 0; i < SizeTgs; i++)
         {
            if( (Natural_Q == Back_T_Q[i]) && (Natural_P == Back_T_P[i]) )
            {
               Tongues_Q[Count] = Back_T_Q[i];
               Tongues_P[Count] = Back_T_P[i];
               Count++;
            }
         }
      }
   }
}



// Lee las especificaciones del calculo
int TFormaLenguas::Leer_Especificaciones_Calculo(void)
{
  unsigned int *Back_T_P = NULL, *Back_T_Q = NULL; //Lenguas y Color Auxiliares
  float Resonancy[4];

  FILE *ApTongue;      //Apuntador al archivo de datos de sincronizaciones
  ApTongue = fopen("D:\\Lenguas\\Config.dat","r");
  if( ApTongue == NULL ) return 1;
   //Orden de Iterada de la Funcion
   Leer_Linea_Archivo(Resonancy, ApTongue);
   Iterated = int(Resonancy[0]);
    //Cantidad de Iteraciones a Realizar el Transitorio
   Leer_Linea_Archivo(Resonancy,ApTongue);
   ItsTrans = int(Resonancy[0]);
    //Cantidad de condciones iniciales
   Leer_Linea_Archivo(Resonancy,ApTongue);
   NCondInits = int(Resonancy[0]);

   //Min en X
   Leer_Linea_Archivo(Resonancy,ApTongue);
   MinX = Resonancy[0];

   //Min en Y
   Leer_Linea_Archivo(Resonancy,ApTongue);
   MinY = Resonancy[0];

   //Max en X
   Leer_Linea_Archivo(Resonancy,ApTongue);
   MaxX = Resonancy[0];
      
   //Max en Y
   Leer_Linea_Archivo(Resonancy,ApTongue);
   MaxY = Resonancy[0];

   //Puntos en X
   Leer_Linea_Archivo(Resonancy,ApTongue);
   PtsX = (unsigned int)Resonancy[0];
      
   //Puntos en Y
   Leer_Linea_Archivo(Resonancy,ApTongue);
   PtsY = (unsigned int)Resonancy[0];
      
    //Especificacion de si:
    //     0 = Se calcularan todas las sincronizaciones posibles
    //     1 = Se calcularan las sincronizaciones especificadas
   Leer_Linea_Archivo(Resonancy,ApTongue);
   SINCROS = (unsigned int)Resonancy[0];
   //Caso: Encontrar todas las sincronizaciones posibles
   if (SINCROS == DESACTIVADO)
   {
      Leer_Linea_Archivo(Resonancy,ApTongue);
      SizeOrbits = (unsigned int)Resonancy[0];
   } 
   //Caso: Encontrar todas las sincronizaciones especificadas
   else
   {   //las sincronizaciones son especificadas
       //SINCROS = ACTIVADO;
       //Inicializa la cantidad de lenguas a cero y posteriormente se calcula cuantas fueron
       //Lectura de la cantidad de sincronizaciones, para poder construir
       //los arreglos de Qs, Ps y Colores de las sincronizaciones
      
       //Construccion de los arreglos para los Qs, Ps y Colores
       Back_T_Q = new unsigned int[MAYORSINCRONIZACION];
       Back_T_P = new unsigned int[MAYORSINCRONIZACION];

       Intern = 0;
//       SizeTgs = 0;
       THE_END = DESACTIVADO;

       //Obtiene informacion de las sincronizaciones
       while(!THE_END)
       {  
          //Obtiene Informacion de las Sincronizaciones
         Leer_Linea_Archivo(Resonancy,ApTongue);
            
          //Verifica lasentradas de las Sincronizaciones en los arreglos temporales para Q y P
          if (!THE_END) {
             if (Analizar_Entrada(Resonancy, Back_T_Q, Back_T_P)) {
//                //Cierra el archivo de informacion de Sincronizaciones
//                fclose(ApTongue);  
//                delete[] Back_T_Q;
//                delete[] Back_T_P;
//                return 1;
             }
          }
       } //Termina while(!THE_END)
   } //Termina "else" para el Caso: Encontrar todas las sincronizaciones especificadas
  fclose(ApTongue);  //Cierra el archivo de informacion de Sincronizaciones
  // Ordenacion de las lenguas, considerando el periodo 
  if(SINCROS == ACTIVADO) Ordenacion(Back_T_Q, Back_T_P);
  delete[]Back_T_Q;
  delete[]Back_T_P;
  return 0;
}


//Analiza las entradas de la lectura del archivo de especificacion de Sincronizaciones
int TFormaLenguas::Analizar_Entrada(const float *Resonancy, unsigned int *Back_T_Q, unsigned int *Back_T_P)
{
   unsigned int Cuenta;
   unsigned int i;

   //Verifica que la informacion de las sincronizaciones sea correcta
   
   //Caso si existe sincronizacion o rango de sinc.
   if( ((unsigned int)Resonancy[0]!=0) || ((unsigned int)Resonancy[1]!=0) )
   {
       // caso cuando existe un rango de sincronizaciones
       if( ((unsigned int)Resonancy[2]!=0) || ((unsigned int)Resonancy[3]!=0) )
       {
           //Caso: Qs Fijos, Ps Varian
           if( (unsigned int)Resonancy[0] == (unsigned int)Resonancy[2] )
           {
               Cuenta = fabs( (unsigned int)Resonancy[3] - (unsigned int)Resonancy[1]) + 1;
               for (i = 0; i < Cuenta; i++)
               {
                   Back_T_Q[Intern] = (unsigned int)Resonancy[0];
                   Back_T_P[Intern] = (unsigned int)Resonancy[1] + i;
                   Intern++;   //Aumento en el indice de los arreglos
               }
               SizeTgs += Cuenta;
               Cuenta = 0;
           }
           else
           {
              //Caso: Ps Fijos, Qs Varian
              if( (unsigned int)Resonancy[1] == (unsigned int)Resonancy[3] )
              {
                   Cuenta = fabs( (unsigned int)Resonancy[2] - (unsigned int)Resonancy[0]) + 1;
                   for (i = 0; i < Cuenta; i++)
                   {
                       Back_T_Q[Intern]= (unsigned int)Resonancy[0] + i;
                       Back_T_P[Intern]= (unsigned int)Resonancy[1]; 

                       Intern++;   //Aumento en el indice de los arreglos
                   }
                   SizeTgs += Cuenta;
                   Cuenta = 0;
              }
           }
       }
       else 
       { 
          Back_T_Q[Intern] = (unsigned int)Resonancy[0];
          Back_T_P[Intern] = (unsigned int)Resonancy[1]; 
          
          Intern++;   //Aumento en el indice de los arreglos
          SizeTgs++;
       }
   }
   //Caso en que no existe sincronizacion o rango de sinc. 0:0
   else return 1;
   return 0;
}


// Función del calculo de Sincronizaciones Solicitadas   <<SINCROS == ACTIVADO>> 
void TFormaLenguas::Calcula_Lenguas_Solicitadas(const long double a, const long double b)
{
   // Utilizada para hacer el barrido sobre las Lenguas proporcionadas
   unsigned int verif, i;               
   unsigned int Posible_Q = 0, Posible_P = 0;

   // Almacena el primer valor de las iteraciones para buscar las resonancias
   long double x, Frac_x, Int_x = 0;

   // Almacena las iteraciones de la funcion de disparos
   long double New_x, FracNew_x, IntNew_x;

   // Auxiliar en las busquedas
   long double Ancla_x, FracAncla_x, IntAncla_x;

   // Contador y Controlador de ciclos (Artifio req. por la rutina)
   unsigned int K;
   // Utilizada para hacer el barrido sobre las cond. iniciales
   
   long double IncInits;    

   long double TOL = TOLERANCIA;  //Tolerancia solicitada

   Encontro = FALSO;

   //Det. la cantidad de sincros para un conj. de parametros especificos
   unsigned char Indice_sincronizaciones = 0;  
   
   // Definicion del arreglo de sincronizaciones
   unsigned char Arreglo_Sincronizaciones_Q[MAYORSINCRONIZACION];
   unsigned char Arreglo_Sincronizaciones_P[MAYORSINCRONIZACION];

   // Inicializa arreglo de sincronizaciones
   for (i = 0; i < MAYORSINCRONIZACION; i++)
   {
       Arreglo_Sincronizaciones_P[i] = 0;
       Arreglo_Sincronizaciones_Q[i] = 0;
   }
  
   //Barrido de Cond. Iniciales   
   for ( IncInits = 0.0; IncInits <= 1.0; IncInits += (1.0/((long double) NCondInits)) ) 
   {
      // Condicion inicial
      Frac_x = IncInits;   

      //  A partir de la Condicion Inicial se realiza un Transitorio de iteraciones sobre ella
      for(i = 0; i < ItsTrans; i++) 
      {  
          x = Frac_x;
          x = Siguiente_Disparo(x)+Int_x;
          Frac_x = modfl(x,&Int_x);
      }
      
      K = 0;
      New_x = x;
      FracNew_x = Frac_x;
      IntNew_x = Int_x;
      Ancla_x = Frac_x;

      //Busca una primera aproximación
      do {
             Posible_Q = 0;
            //Condicion para el caso en que se proporciona una lista de
            //sincronizaciones a calcular, con el fin de ahorrar iteraciones
            
            //Empieza considerando las orbitas de tamaño minimo solicitadas
            for ( i = 1 ; i <= Tongues_Q[0]; i++)
            {
               New_x = FracNew_x;
               New_x = Siguiente_Disparo(New_x) + IntNew_x;
               FracNew_x = modfl(New_x, &IntNew_x);
               //Almacena la posible longitud de la órbita periódica
               Posible_Q++;
            }
            //Condicion para det. si hay orbita
            if( (fabsl(Ancla_x - FracNew_x) < TOL) || (fabsl(fabsl(Ancla_x - FracNew_x)-1.0) < TOL) ) Encontro = VERDADERO;
            
            //busca la resonancia y halla una primera orbita periodica
            while( (Encontro == FALSO) && (Posible_Q <= SizeOrbits))
            {
               New_x = FracNew_x;
               New_x = Siguiente_Disparo(New_x) + IntNew_x;
               FracNew_x = modfl(New_x, &IntNew_x);
               //Almacena la posible longitud de la ¢rbita peri¢dica
               Posible_Q++;

               //Condicion para det. si hay órbita
               if ( (fabsl(Ancla_x - FracNew_x)<TOL) || (fabsl(fabsl(Ancla_x - FracNew_x)-1.0) < TOL) ) Encontro = VERDADERO;
            }
            if ( (Posible_Q > SizeOrbits) && (Encontro == FALSO) ) K++;
         } while ( (Encontro==FALSO) && (K <= 2) );

      //Inicia comprob.(Check) de la resonancia hallada
      if ((Encontro == VERDADERO))
      {
	       Encontro = FALSO;
          if ( (Posible_Q > 0) && (Posible_Q <= SizeOrbits) )
	       {
		        //New_x=New_x+(TOL/10); //Perturbacion ligera si se desea
		        Ancla_x = New_x;
              //Ciclo de check (long. de Posible_Q) desde 1 hasta Posible_Q, pues ahora solo se recorrá
		        //la orbita que se presume haber encontrado
              for ( i = 1; i <= Posible_Q; i++) 
              { 
                  FracNew_x = modfl(New_x,&IntNew_x);
                  New_x = Siguiente_Disparo(FracNew_x) + IntNew_x;
              }

              FracAncla_x = modfl(Ancla_x, &IntAncla_x);

              FracNew_x = modfl(New_x, &IntNew_x);
                              //Condicion para det. si hay órbita
              if ( (fabsl(FracAncla_x-FracNew_x) < (TOL/2.0)) ||
                   (fabsl(fabsl(FracAncla_x - FracNew_x) - 1.0) < (TOL / 2.0)) ) Encontro = VERDADERO;
                   
              // Se encontro resonancia y paso el check
              if ( (Encontro == VERDADERO) ) 
              {
                 // Determina la posible envolvencia asociada a la órbita encontrada
                 //Para "Posible_Q" este ya se encuentra almacenado
		           Posible_P = IntNew_x - IntAncla_x;
                 
                 //Barrido sobre las sincronizaciones solicitadas
			        for ( verif = 0; verif < SizeTgs; verif++)
			        {
			            // Comparacion de si la órbita encontrada es alguna de las solicitadas
			            if ( (Posible_Q == Tongues_Q[verif]) && (Posible_P == Tongues_P[verif]) )
			            {
				            //Opciones de Grabado para Multisincronizacion
                        if(Indice_sincronizaciones < MAYORSINCRONIZACION)
                        {
                           if (Indice_sincronizaciones > 0)
                           {
                              // Busca si ya esta la sincronización
                              for ( i = 0; i < Indice_sincronizaciones; i++)
                              {
                                  if (Arreglo_Sincronizaciones_Q[i] == Tongues_Q[verif] && Arreglo_Sincronizaciones_P[i] == Tongues_P[verif]) break;
                              }
                              // Sincronizacion no encontrada
                              if (i == Indice_sincronizaciones)
                              {
                                  Arreglo_Sincronizaciones_Q[Indice_sincronizaciones] = (unsigned char) Tongues_Q[verif];
                                  Arreglo_Sincronizaciones_P[Indice_sincronizaciones] = (unsigned char) Tongues_P[verif];
                                  Indice_sincronizaciones++;
                              }
                           }
                           else
                           {
                              Arreglo_Sincronizaciones_Q[Indice_sincronizaciones] = (unsigned char) Tongues_Q[verif];
                              Arreglo_Sincronizaciones_P[Indice_sincronizaciones] = (unsigned char) Tongues_P[verif];
                              Indice_sincronizaciones++;
                           }
                        }
			            } //end if para el for
			        } //End for "verif"
		        } // if de "Se encontro resonancia y paso el check"
          } //termina "if( (Posible_Q>0L) && (Posible_Q<=SizeOrbits) )"
       } //termina "if((Encontro==VERDADERO)) //Inicia comprob.(Check) de la resonancia hallada"
   } //Termina for de "IncInit"

   // Almacenamiento de los valores de los parametros y sus sincronizaciones
   int px, py;
   if (Indice_sincronizaciones > 0)
   {
      float xa = (float) a , xb = (float) b;
      fwrite(&xa, sizeof(xa), 1, OutField);
      fwrite(&xb, sizeof(xb), 1, OutField);
      // grabar Indice_sincronizaciones
      fwrite(&Indice_sincronizaciones, sizeof(Indice_sincronizaciones), 1, OutField);

      for (i = 0; i < Indice_sincronizaciones; i++)
      {
         fwrite(&Arreglo_Sincronizaciones_Q[i], sizeof(Arreglo_Sincronizaciones_Q[i]), 1, OutField);
         fwrite(&Arreglo_Sincronizaciones_P[i], sizeof(Arreglo_Sincronizaciones_P[i]), 1, OutField);
      }     
      pix[0].Asigna_valor(xa,xb,true);
      px = (xa - Dim_Vtn.Xi) * Escala.X;
      py = VTLenguas->Height - (((xb - Dim_Vtn.Yi) * Escala.Y) + 1.0);
      VTLenguas->Canvas->Pixels[px][py] = clBlack;
   }    
}


//  Función del calculo de Todas las Posibles Sincronizaciones  <<SINCROS == DESACTIVADO>> 
void TFormaLenguas::Calcula_Lenguas_Todas(const long double a, const long double b)
{
   unsigned int Posible_Q = 0, Posible_P = 0;
   unsigned int i;

   // Almacena el primer valor de las iteraciones para buscar las resonancias
   long double x, Frac_x, Int_x = 0.0;

   // Almacena las iteraciones de la funcion de disparos
   long double New_x, FracNew_x, IntNew_x;

   // Auxiliar en las busquedas
   long double Ancla_x, FracAncla_x, IntAncla_x;

   // Contador y Controlador de ciclos (Artifio req. por la rutina)
   unsigned int K;
   // Utilizada para hacer el barrido sobre las cond. iniciales
   
   long double IncInits;    

   long double TOL = TOLERANCIA;  //Tolerancia solicitada

   Encontro = FALSO;

   //Det. la cantidad de sincros para un conj. de parametros especificos
   unsigned char Indice_sincronizaciones = 0;  
   
   // Definicion del arreglo de sincronizaciones
   unsigned char Arreglo_Sincronizaciones_Q[MAYORSINCRONIZACION];
   unsigned char Arreglo_Sincronizaciones_P[MAYORSINCRONIZACION];

   // Inicializa arreglo de sincronizaciones
   for (i = 0; i < MAYORSINCRONIZACION; i++)
   {
       Arreglo_Sincronizaciones_Q[i] = 0;
       Arreglo_Sincronizaciones_P[i] = 0;
   }
  
   //Barrido de Cond. Iniciales   
   for ( IncInits = 0.0; IncInits <= 1.0; IncInits += (1.0/((long double) NCondInits)) ) 
   {
      // Condicion inicial
      Frac_x = IncInits;   

      //  A partir de la Condicion Inicial se realiza un Transitorio de iteraciones sobre ella
      for(i = 0; i < ItsTrans; i++) 
      {  
          x = Frac_x;
          x = Siguiente_Disparo(x)+Int_x;
          Frac_x = modfl(x,&Int_x);
      }
      
      K = 0;
      New_x = x;
      FracNew_x = Frac_x;
      IntNew_x = Int_x;
      Ancla_x = Frac_x;

      //Busca una primera aproximación
      do {
         Posible_Q = 0;
         //busca la resonancia y halla una primera orbita periodica
         while( (Encontro == FALSO) && (Posible_Q <= SizeOrbits))
         {
            New_x = FracNew_x;
            New_x = Siguiente_Disparo(New_x) + IntNew_x;
            FracNew_x = modfl(New_x, &IntNew_x);
            //Almacena la posible longitud de la órbita periódica
            Posible_Q++;
            //Condicion para det. si hay órbita
            if ( (fabsl(Ancla_x - FracNew_x) < TOL) || (fabsl(fabsl(Ancla_x - FracNew_x)-1.0) < TOL) ) Encontro = VERDADERO;
         }
         if ( (Posible_Q > SizeOrbits) && (Encontro == FALSO) ) K++;
      } while ( (Encontro==FALSO) && (K <= 2) );

      
      //Inicia comprob.(Check) de la resonancia hallada
      if ((Encontro == VERDADERO))
      {
          Encontro = FALSO;
          if ( (Posible_Q > 0) && (Posible_Q <= SizeOrbits) )
	  {
	      //New_x=New_x+(TOL/10); //Perturbacion ligera si se desea
	      Ancla_x = New_x;
              //Ciclo de check (long. de Posible_Q) desde 1 hasta Posible_Q, pues ahora solo se recorrá
	      //la orbita que se presume haber encontrado
              for ( i = 1; i <= Posible_Q; i++) 
              { 
                   FracNew_x = modfl(New_x,&IntNew_x);
                   New_x = Siguiente_Disparo(FracNew_x) + IntNew_x;
              }

              FracAncla_x = modfl(Ancla_x, &IntAncla_x);

              FracNew_x = modfl(New_x, &IntNew_x);
              //Condicion para det. si hay órbita
              if ( (fabsl(FracAncla_x - FracNew_x) < (TOL / 2.0)) || (fabsl(fabsl(FracAncla_x - FracNew_x) - 1.0) < (TOL / 2.0)) ) Encontro = VERDADERO;
                      
              // Se encontro resonancia y paso el check
              if ( (Encontro == VERDADERO) ) 
              {
                  // Determina la posible envolvencia asociada a la órbita encontrada
                  //Para "Posible_Q" este ya se encuentra almacenado
                  Posible_P = IntNew_x - IntAncla_x;

                  // Posible P no debera de excede a Posible Q
                  if (Posible_P <= Posible_Q) 
                  {

                     //Caso en que no se proporciona lista de sincronizaciones
                     //Opciones de Grabado para Multisincronizacion
                     if (Indice_sincronizaciones > 0)
                     {
                        for (i = 0; i < Indice_sincronizaciones; i++)
                        {
                           if (Arreglo_Sincronizaciones_Q[i] == Posible_Q && Arreglo_Sincronizaciones_P[i] == Posible_P) break;
                        }
                        if (i == Indice_sincronizaciones)
                        {
                            Arreglo_Sincronizaciones_Q[Indice_sincronizaciones] = (unsigned char) Posible_Q;
                            Arreglo_Sincronizaciones_P[Indice_sincronizaciones] = (unsigned char) Posible_P;
                            Indice_sincronizaciones++;
                        }
                     }
                     else
                     {
                         Arreglo_Sincronizaciones_Q[Indice_sincronizaciones] = (unsigned char) Posible_Q;
                         Arreglo_Sincronizaciones_P[Indice_sincronizaciones] = (unsigned char) Posible_P;
                         Indice_sincronizaciones++;
                     }
                  }
              } // if de "Se encontro resonancia y paso el check"
	  } //termina "if( (Posible_Q>0L) && (Posible_Q<=SizeOrbits) )"
      } //termina "if((Encontro==VERDADERO)) //Inicia comprob.(Check) de la resonancia hallada"
   } //Termina for de "IncInit"

   // Almacenamiento de los valores de los parametros y sus sincronizaciones
   int px, py;              
   if (Indice_sincronizaciones > 0)
   {
   
      float xa = (float) a , xb = (float) b;
      fwrite(&xa, sizeof(xa), 1, OutField);
      fwrite(&xb, sizeof(xb), 1, OutField);
      // grabar Indice_sincronizaciones
      fwrite(&Indice_sincronizaciones, sizeof(Indice_sincronizaciones), 1, OutField);

      for (i = 0; i < Indice_sincronizaciones; i++)
      {
         fwrite(&Arreglo_Sincronizaciones_Q[i], sizeof(Arreglo_Sincronizaciones_Q[i]), 1, OutField);
         fwrite(&Arreglo_Sincronizaciones_P[i], sizeof(Arreglo_Sincronizaciones_P[i]), 1, OutField);
      }     
      pix[0].Asigna_valor(xa,xb,true);
      px = (xa - Dim_Vtn.Xi) * Escala.X;
      py = VTLenguas->Height - (((xb - Dim_Vtn.Yi) * Escala.Y) + 1.0);
      VTLenguas->Canvas->Pixels[px][py] = clBlack;
   }    
}



//Calcula el Siguiente Disparo del Sistema
long double TFormaLenguas::Siguiente_Disparo(const long double x)
{
  long double val;
  val =  x+a+(b*sinl(2*M_PI*x));
  return val;
}

// Formato de Encabezado del Archivo
void TFormaLenguas::Grabar_encabezado_archivo(void)
{
   float Incx=0.0, Incy=0.0;
   
   Incx = (MaxX - MinX) / (PtsX);  //  ( C.R. / C.F.)

   Incy = (MaxY - MinY) / (PtsY);  //  ( C.R. / C.F.)

   char Outer[350];

   strcpy(Outer, CLAVE_ENCABEZADO);    ///////////Clave de Archivo
   fwrite(Outer, 8, 1, OutField);
   
   strcpy(Outer, "Nombre del Archivo:");   /////Nombre del Archivo
   fwrite(Outer, 30, 1, OutField);
   
   strcpy(Outer, "Seccion de Comentarios ..."); ///////////Comentarios
   fwrite(Outer, 300,1, OutField);
   
      ////////////// Seccion de Parametros a Variar
   strcpy(Outer, "Parametros: a  b");
   fwrite(Outer, 100, 1, OutField);
   
        //////////////Clave Numero de Sincronizaciones: Tipo de Algorit.
   strcpy(Outer, "Numero Definido");
   fwrite(Outer, 20,1, OutField);
   
          ////////// C O N F I G U R A C I O N //////////////////
   strcpy(Outer, "Oscilador Geometrico de Diente de Sierra");
   fwrite(Outer, 100,1, OutField);
   
          /////// Dimensiones en X e Y Reales
   strcpy(Outer, "Dimensiones (X-Y) Reales");
   fwrite(Outer, 100, 1, OutField);
   
   fwrite(&MinX, sizeof(MinX), 1, OutField);   // MinX
   fwrite(&MinY, sizeof(MinY), 1, OutField);   // MinY
   fwrite(&MaxX, sizeof(MaxX), 1, OutField);   // MaxX
   fwrite(&MaxY, sizeof(MaxY), 1, OutField);   // MaxY
   
          /////// Cantidad de Pts en X-Y
   strcpy(Outer, "Cantidad de Pts en X-Y");
   fwrite(Outer, 100, 1, OutField);
   
   fwrite(&PtsX, sizeof(PtsX), 1, OutField);   // PtsX
   fwrite(&PtsY, sizeof(PtsY), 1, OutField);   // PtsY

          /////// Longitud de Paso de Calculo
   strcpy(Outer, "Longitud de Paso de Calculo (X-Y)");
   fwrite(Outer, 50, 1, OutField);
   
   fwrite(&Incx, sizeof(Incx), 1, OutField);
   fwrite(&Incy, sizeof(Incy), 1, OutField);

          /////// Ecuacion del Sistema
   strcpy(Outer, "Ecuacion: f(x)=x+a+b*Sen(2*PI*x)");
   fwrite(Outer, 100, 1, OutField);

         //////// Formato de Almacenamiento de Sincronizaciones
   strcpy(Outer, "Par-X  Par-Y  #Sincros Valor-Qs  Valor-Ps");
   fwrite(Outer, 100, 1, OutField);
/////////////////////////////////////////////////////////////////////////////
// Falta grabar:
//   Lenguas solicitadas
//      # de lenguas solicitadas, P's , Q's,....
//   ......
/////////////////////////////////////////////////////////////////////////////
}


// Funcion de lectura para el archivo de lenguas.
void TFormaLenguas::Leer_Linea_Archivo(float *Resonancy, FILE *ApTongue)
{
   char entra[100], car;
   int i, END_LINE = DESACTIVADO, Indice = 0;

   //Inicializacion del arreglo de rango de sincronizaciones
   for (i = 0; i < 4; i++) Resonancy[i] = 0;
   i = 0;
   while ( (!THE_END) && (!END_LINE) )
   {
      car = fgetc(ApTongue);
      if (car == ' ') continue;
      if (car == '~') THE_END = ACTIVADO;
      if (car == '\n') END_LINE = ACTIVADO;
      if ( (car != ':') && (car != ',') && (car != '\n') ) entra[i++] = car;
      else 
      {
          entra[i] = 0;
	  if ( strcmp(entra, "...") )
	  {
	     if (!THE_END) Resonancy[Indice++] = atof(entra);
	     //Limpieza del buffer entra
             entra[0] = 0;
             i = 0;
	  }
          else
          {
             entra[0] = 0;
             i = 0;
          }
      }
   }
}













