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
#include "VentanaLevantamientos.h"
#include "Sincronizaciones.hpp"
#include "NumeroRotacion.hpp"
#include "ExponenteLyapunov.hpp"
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
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

// Al cerrar la forma ...
void __fastcall TFormaLevantamientos::FormClose(TObject *Sender,TCloseAction &Action)
{
   Ventana_activa = NULL;
   Free();     
}

// Al solicitar cerrar la ventana ...
void __fastcall TFormaLevantamientos::FormCloseQuery(TObject *Sender, bool &CanClose)
{
   if (MessageBox(Handle,"Do you wish to close this window?","Lifts scenery",MB_YESNO + MB_ICONQUESTION)  == IDYES) CanClose = true;
    else CanClose = false;
}

// Al dibujar la forma ...// Al cambiar de tamaño ...
void __fastcall TFormaLevantamientos::FormResize(TObject *Sender)
{
   // Calcula la escala de la ventana de visualizacion
   Escala.X = (VTLevantamientos->Width -1) / (long double) (Dim_Vtn.Xf - Dim_Vtn.Xi);
   Escala.Y = (VTLevantamientos->Height -1) / (long double) (Dim_Vtn.Yf - Dim_Vtn.Yi);
   // Grafica el contenido de la ventana
   Grafica(true);        
}


///////////////////////////////////////////////////////////////////////////////
//  Definición de Comportamientos del Menu 
///////////////////////////////////////////////////////////////////////////////

// Menu Archivo->Cerrar
void __fastcall TFormaLevantamientos::MenuArchivoCerrarClick(TObject *Sender)
{
   Close();        
}

// Menu->Archivo->Grabar BMP
void __fastcall TFormaLevantamientos::MenuArchivoGrabarBMPClick(TObject *Sender)
{
   TRect   xRect = Rect(0,0,VTLevantamientos->Width,VTLevantamientos->Height);
   Graphics::TBitmap *Bitmap = new Graphics::TBitmap;
   Bitmap->Width = VTLevantamientos->Width;
   Bitmap->Height = VTLevantamientos->Height;
   Bitmap->Canvas->CopyRect(xRect, VTLevantamientos->Canvas, xRect);
   SaveDialog->Title = "Save as ...";
   if (SaveDialog->Execute()) {
      Bitmap->SaveToFile(SaveDialog->FileName);           
   }
   VTLevantamientos->Canvas->Draw(0,0,Bitmap);
   delete Bitmap;
}

// Menu->Archivo->Imprimir
void __fastcall TFormaLevantamientos::MenuArchivoImprimirClick(TObject *Sender)
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
void __fastcall TFormaLevantamientos::MenuCalcularLevantamientosClick(TObject *Sender)
{
   Calcula_Levantamiento();
}

// Menu->Calcular->Calcular lineas sobre levantamientos
void __fastcall TFormaLevantamientos::MenuCalcularIteracionesClick(TObject *Sender)
{
   Calcula_lineas_levantamientos();
}


// Menu->Calcular->Numero de Rotación
void __fastcall TFormaLevantamientos::MenuCalcularNumeroRotacionClick(TObject *Sender)
{
   TCursor antcursor = Cursor;
   // Cambia el cursor del mouse
   Cursor = crHourGlass;
   long double p[NUM_MAX_PARAMETROS], rot;
   BarraDeEstadosLevantamientos->SimpleText = (AnsiString) "Calculating rotation number (this process may last several seconds).";
   // Recupera los parámetros por omisión
   fun_disp.RetornaParametros(p);
   // Cambiar parámetros
   num_rot.AsignaParametros(p);
   rot = num_rot.Calcula(Tipo_integracion);
   char xcad[200];
   sprintf(xcad,"Rotation number: %Lf",rot);
   MessageBox(NULL,xcad,"Lifts scenery",MB_OK+MB_ICONINFORMATION);
   BarraDeEstadosLevantamientos->SimpleText = (AnsiString) " ";
   // Cambia el cursor del mouse
   Cursor = antcursor;
}

// Menu->Calcular->Sincronización
void __fastcall TFormaLevantamientos::MenuCalcularSincronizacinClick(TObject *Sender)
{
   TCursor antcursor = Cursor;
   // Cambia el cursor del mouse
   Cursor = crHourGlass;
   long double p[NUM_MAX_PARAMETROS];
   unsigned int xp, xq;
   BarraDeEstadosLevantamientos->SimpleText = (AnsiString) "Calculating synchronization (this process may last several seconds).";
   // Recupera los parámetros por omisión
   fun_disp.RetornaParametros(p);
   // Cambiar parámetros
   sincro.AsignaParametros(p);
   sincro.Calcula(Tipo_integracion, xp, xq);
   char xcad[200];
   sprintf(xcad,"Synchronization: %u /%u ",xp,xq);
   MessageBox(NULL,xcad,"Lifts scenery",MB_OK+MB_ICONINFORMATION);
   BarraDeEstadosLevantamientos->SimpleText = (AnsiString) " ";
   // Cambia el cursor del mouse
   Cursor = antcursor;
}

// Menu->Calcular->Exponente de Lyapunov
void __fastcall TFormaLevantamientos::MenuCalcularExpLyapunovClick(TObject *Sender)
{
   TCursor antcursor = Cursor;
   // Cambia el cursor del mouse
   Cursor = crHourGlass;
   // Cambia el cursor del mouse
   Cursor = antcursor;
   long double p[NUM_MAX_PARAMETROS], rot;
   BarraDeEstadosLevantamientos->SimpleText = (AnsiString) "Calculating Lyapunov exponent (this process may last several seconds).";
   // Recupera los parámetros por omisión
   fun_disp.RetornaParametros(p);
   // Cambiar parámetros
   exp_lyap.AsignaParametros(p);
   rot = exp_lyap.Calcula(Tipo_integracion);
   char xcad[200];
   sprintf(xcad,"Lyapunov exponent: %Lf",rot);
   MessageBox(NULL,xcad,"Lifts scenery",MB_OK+MB_ICONINFORMATION);
   BarraDeEstadosLevantamientos->SimpleText = (AnsiString) " ";
   // Cambia el cursor del mouse
   Cursor = antcursor;
}

// Menu->ventana->limpiar
void __fastcall TFormaLevantamientos::MenuVentanaLimpiarClick(TObject *Sender)
{
   Limpia_matriz_pixeles();
   Grafica(true);
}

// Menu->Configurar->Parametros
void __fastcall TFormaLevantamientos::MenuConfigurarParametrosClick(TObject *Sender)
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
void __fastcall TFormaLevantamientos::MenuConfigurarDimensionesClick(TObject *Sender)
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
void __fastcall TFormaLevantamientos::MenuConfigurarVisualizarClick(TObject *Sender)
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
void __fastcall TFormaLevantamientos::MenuConfigurarCalculoClick(TObject *Sender)
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
void __fastcall TFormaLevantamientos::MenuAyudaAcercadeClick(TObject *Sender)
{
   TVAcercaDe *Acercade = new TVAcercaDe(this);
   if (Acercade) {
      Acercade->ShowModal();
      delete Acercade;
   }
}

// Ayuda de TFormaLevantamientos
void __fastcall TFormaLevantamientos::MenuAyudaLevantamientosClick(TObject *Sender)
{
   TAyudaForm *Ayuda = new TAyudaForm(this);
   if (Ayuda) {
      Ayuda->Abrir_archivo("Lifts scenery","Levantamientos.hlp");
      Ayuda->Show();
   }
}



///////////////////////////////////////////////////////////////////////////////
//  Definición de Comportamientos de TFormaLevantamientos 
///////////////////////////////////////////////////////////////////////////////

// Constructor de la clase
__fastcall TFormaLevantamientos::TFormaLevantamientos(TComponent* Owner) : TForm(Owner)
{
   Detener_calculo = false;
   // Dimenciones de la ventana
   Dim_Vtn.Xi = 0.0;
   Dim_Vtn.Xf = 4.0;
   Dim_Vtn.Yi = 0.0;
   Dim_Vtn.Yf = 4.0;
   // Longitud de la ventana de pixeles
   Pix_x = 1024;
   Pix_y = 768;
   // Inicializa la ventana de pixeles
   pix[0].Inicializa(Pix_x, Pix_y, false,Dim_Vtn);
   pix[1].Inicializa(Pix_x, Pix_y, false,Dim_Vtn);
   pix[2].Inicializa(Pix_x, Pix_y, false,Dim_Vtn);
   pix[3].Inicializa(Pix_x, Pix_y, false,Dim_Vtn);
   
   // Condición inicial
   Condicion_inicial.X = 0.0; 
   Condicion_inicial.Y = 0.0;
   // Configuracion de lineas en el levantamiento
   Num_iteraciones = 1;
   // Color de los graficos
   Color_grafica[0] = clMaroon;     // Referencia
   Color_grafica[1] = clWhite;   // Identidad
   Color_grafica[2] = clAqua;    // Grafico
   Color_grafica[3] = clGray;  // Lineas
   Color_fondo = clSilver;
   // Indica que graficos estaran activos
   Sw_Visualiza_grafico = true;
   Sw_Visualiza_identidad = true;
   Sw_Visualiza_referencia = true;
   Sw_Visualiza_linea = true;

   // Puntos a trazar en la curva
   Puntos_trazar = Pix_x;
   // Tipo de inegración en este escenario
   Tipo_integracion = ADELANTE;
   // Calcula la referencia
   Calcula_referencia();
}

// Calcula el levantamiento
void TFormaLevantamientos::Calcula_Levantamiento(void) 
{
   TCursor antcursor = Cursor;
   // Cambia el cursor del mouse
   Cursor = crHourGlass;
   long double y ,t, paso;
   int px, py;
   
   BarraDeEstadosLevantamientos->SimpleText = (AnsiString) "Calculating lifts (this process may last several seconds).";
   t = Dim_Vtn.Xi;
   paso = (Dim_Vtn.Xf - Dim_Vtn.Xi) / (long double) Puntos_trazar;
   // Inicializa la variable de cancelacion del calculo
   Detener_calculo = false;
   while(t <= Dim_Vtn.Xf) {
      // Termina el ciclo si se solicito 
      Application->ProcessMessages();
      if(Detener_calculo) break;
      y = fun_disp.Calcula(t,Tipo_integracion);
      if(!fun_disp.Error_calculo) {
         pix[2].Asigna_valor(t,y,true);
         px = (t - Dim_Vtn.Xi) * Escala.X;
         py = VTLevantamientos->Height - (((y - Dim_Vtn.Yi) * Escala.Y) + 1.0);
         if (Sw_Visualiza_grafico) {
            if (px >= 0 && px < VTLevantamientos->Width && py >= 0 && py < VTLevantamientos->Height) VTLevantamientos->Canvas->Pixels[px][py] = Color_grafica[2];
         }   
      }
      t += paso;
   }
   BarraDeEstadosLevantamientos->SimpleText = (AnsiString) " ";
   // Cambia el cursor del mouse
   Cursor = antcursor;
}


void TFormaLevantamientos::Calcula_lineas_levantamientos(void)
{
   TCursor antcursor = Cursor;
   // Cambia el cursor del mouse
   Cursor = crHourGlass;
   unsigned int xi;
   bool sw = false;
   long double y , t;
   C_2D xCondicion_inicial = Condicion_inicial;   

   BarraDeEstadosLevantamientos->SimpleText = (AnsiString) "Calculating iterations (this process may last several seconds).";
   // Inicializa la variable de cancelacion del calculo
   Detener_calculo = false;
  
   t = xCondicion_inicial.X;
   while(t <= Dim_Vtn.Yf) {
      // Termina el ciclo si se solicito 
      Application->ProcessMessages();
      if(Detener_calculo) break;
      y = t;
      for(xi = 0; xi < Num_iteraciones; xi ++) y = fun_disp.Calcula(y,Tipo_integracion);
      // Se ajusta el valor de Y para poder trazar la linea
      if (y > Dim_Vtn.Yf) y = Dim_Vtn.Yf, sw = true;
      pix[3].Asigna_linea(xCondicion_inicial.X,xCondicion_inicial.Y,xCondicion_inicial.X,y,true);
      // Si el valor de Y no fue ajustado visualiza la linea horizontal
      if (!sw) pix[3].Asigna_linea(xCondicion_inicial.X,y,y,y,true);
      t = y;
      xCondicion_inicial.X = y; 
      xCondicion_inicial.Y = t; 
      Grafica(false);
      // Si el valor de Y fue ajustado termina el ciclo
      if (sw) break;
   }
   BarraDeEstadosLevantamientos->SimpleText = (AnsiString) " ";
   // Cambia el cursor del mouse
   Cursor = antcursor;
}


// Grafica la referencia de la ventana
void TFormaLevantamientos::Calcula_referencia(void)
{
   long double x;
   // Lineas verticales
   for(x = Dim_Vtn.Xi; x <= Dim_Vtn.Xf; x += 1.0) pix[0].Asigna_linea(x,Dim_Vtn.Yi,x,Dim_Vtn.Yf,true);
   // Lineas horizontales
   for(x = Dim_Vtn.Yi; x <= Dim_Vtn.Yf; x += 1.0) pix[0].Asigna_linea(Dim_Vtn.Xi,x,Dim_Vtn.Xf,x,true);
   // Identidad
   pix[1].Asigna_linea(Dim_Vtn.Xi,Dim_Vtn.Yi,Dim_Vtn.Xf,Dim_Vtn.Yf,true);
}

// Grafica el mapa de pixeles
void TFormaLevantamientos::Grafica(bool limpia)
{
   unsigned int x, y, i;
   // Calcula la escala de la ventana de visualizacion con respecto a la ventana de pixeles
   C_2D esc;
   
   if (limpia) Limpiar_vantana();
   esc.X = VTLevantamientos->Width / (long double) Pix_x;
   esc.Y = VTLevantamientos->Height / (long double) Pix_y;
   // Visualiza la ventana de pixeles
   for(i = 0; i < 4; i++) {
      if(i == 0 && !Sw_Visualiza_referencia) i++;
      if(i == 1 && !Sw_Visualiza_identidad) i++;
      if(i == 2 && !Sw_Visualiza_grafico) i++;
      if(i == 3 && !Sw_Visualiza_linea) break;
      for(y = 0; y < Pix_y; y++) {
          for(x = 0; x < Pix_x; x++) {
              if(pix[i].Retorna_valor(x, y)) VTLevantamientos->Canvas->Pixels[x * esc.X][y * esc.Y] = Color_grafica[i];
          }
      }
   } 
}

// Limpia la ventana de graficacion
void TFormaLevantamientos::Limpiar_vantana(void)
{
   VTLevantamientos->Canvas->Pen->Color = Color_fondo;
   VTLevantamientos->Canvas->Brush->Color = Color_fondo;
   VTLevantamientos->Canvas->Rectangle(0, 0, VTLevantamientos->Width, VTLevantamientos->Height);
}

//#error Si se solicita cerrar ventana cancelar calculo y visualización


void __fastcall TFormaLevantamientos::VTLevantamientosMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
   Vs.Xf = X, Vs.Yf = Y;
   Vs.Xi = Vs.Xf / Escala.X + Dim_Vtn.Xi;
   Vs.Yi = (-(Vs.Yf - VTLevantamientos->Height) / Escala.Y) + Dim_Vtn.Yi;

   sprintf(Msg,"Mouse position: (%3.8Lf, %3.8Lf)", Vs.Xi, Vs.Yi);
   BarraDeEstadosLevantamientos->SimpleText = (AnsiString) Msg;
}


void __fastcall TFormaLevantamientos::FijarCondicIninicialClick(TObject *Sender)
{
   Condicion_inicial.X = Vs.Xi; 
   Condicion_inicial.Y = 0.0;
}

// Pasa los valores de configuración de la ventana de captura
void TFormaLevantamientos::PasarValoresConfiguracion(void)
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
   configura->CheckBox1->Checked = Sw_Visualiza_grafico;
   configura->CheckBox2->Checked = Sw_Visualiza_referencia;
   configura->CheckBox3->Checked = Sw_Visualiza_identidad;
   configura->CheckBox4->Checked = Sw_Visualiza_linea;
   // Colores
   configura->Panel5->Color = Color_grafica[2];
   configura->Panel6->Color = Color_grafica[0];
   configura->Panel7->Color = Color_grafica[1];
   configura->Panel8->Color = Color_grafica[3];
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
void TFormaLevantamientos::RetornarValoresConfiguracion(void)
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
   // Check Box
   Sw_Visualiza_grafico    = configura->CheckBox1->Checked;
   Sw_Visualiza_referencia = configura->CheckBox2->Checked;
   Sw_Visualiza_identidad  = configura->CheckBox3->Checked;
   Sw_Visualiza_linea      = configura->CheckBox4->Checked;
   // Colores
   Color_grafica[2] = configura->Panel5->Color;
   Color_grafica[0] = configura->Panel6->Color;
   Color_grafica[1] = configura->Panel7->Color;
   Color_grafica[3] = configura->Panel8->Color;
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
   Calcula_referencia();
   FormResize(this);
}

void __fastcall TFormaLevantamientos::Timer1Timer(TObject *Sender)
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
          MenuCalcularIteracionesClick(this);
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
}

void __fastcall TFormaLevantamientos::MenuCalcularDetenerelcalculoClick(TObject *Sender)
{
   Detener_calculo = true;        
}

void __fastcall TFormaLevantamientos::VTLevantamientosPaint(TObject *Sender)
{
   // Grafica el contenido de la ventana
   Grafica(true);        
}

// OnHint
void  __fastcall TFormaLevantamientos::OnHint(TObject *Sender)
{
   BarraDeEstadosLevantamientos->SimpleText = Application->Hint;
}

void __fastcall TFormaLevantamientos::FormActivate(TObject *Sender)
{
   Application->OnHint = OnHint;
}

void __fastcall TFormaLevantamientos::FormDeactivate(TObject *Sender)
{
   Application->OnHint = NULL;
}

