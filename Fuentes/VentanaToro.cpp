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
#include "VentanaToro.h"
#include "Sincronizaciones.hpp"
#include "NumeroRotacion.hpp"
#include "ExponenteLyapunov.hpp"
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
// Objetos globales del sistema IyD
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


// Al cerrar la forma
void __fastcall TFormaToro::FormClose(TObject *Sender, TCloseAction &Action)
{
   Ventana_activa = NULL;
   Free();        
}


// Al solicitar cerrar la ventana ...
void __fastcall TFormaToro::FormCloseQuery(TObject *Sender, bool &CanClose)
{
   if (MessageBox(Handle,"Do you wish to close this window?","Torus scenery",MB_YESNO + MB_ICONQUESTION)  == IDYES) CanClose = true;
    else CanClose = false;
}

// Al cambiar de tamaño ...
void __fastcall TFormaToro::FormResize(TObject *Sender)
{
   // Calcula la escala de la ventana de visualizacion
   Escala.X = (VTToro->Width -1) / (Dim_Vtn.Xf - Dim_Vtn.Xi);
   Escala.Y = (VTToro->Height -1) / (long double) (Dim_Vtn.Yf - Dim_Vtn.Yi);
   // Grafica el contenido de la ventana
   Grafica(true);        
}

///////////////////////////////////////////////////////////////////////////////
//  Definición de Comportamientos del Menu 
///////////////////////////////////////////////////////////////////////////////

// Menu->Archivo->Cerrar
void __fastcall TFormaToro::MenuArchivoCerrarClick(TObject *Sender)
{
   Close();        
}

// Menu->Archivo->Grabar BMP
void __fastcall TFormaToro::ManuArchivoGrabarBMPClick(TObject *Sender)
{
   TRect   xRect = Rect(0,0,VTToro->Width,VTToro->Height);
   Graphics::TBitmap *Bitmap = new Graphics::TBitmap;
   Bitmap->Width = VTToro->Width;
   Bitmap->Height = VTToro->Height;
   Bitmap->Canvas->CopyRect(xRect, VTToro->Canvas, xRect);
   SaveDialog->Title = "Save as ...";
   if (SaveDialog->Execute()) {
      Bitmap->SaveToFile(SaveDialog->FileName);           
   }
   VTToro->Canvas->Draw(0,0,Bitmap);
   delete Bitmap;
}

// Menu->Archivo->Imprimir      
void __fastcall TFormaToro::MenuArchivoImprimirClick(TObject *Sender)
{
   TRect   xRect = Rect(0,0,VTToro->Width,VTToro->Height);
   Graphics::TBitmap *Bitmap = new Graphics::TBitmap;
   Bitmap->Width = VTToro->Width;
   Bitmap->Height = VTToro->Height;
   Bitmap->Canvas->CopyRect(xRect, VTToro->Canvas, xRect);
   VTToro->Canvas->Draw(0,0,Bitmap);
   Printer()->BeginDoc();
   Printer()->Canvas->StretchDraw(Rect(50,50,Printer()->PageWidth-50,Printer()->PageWidth-50),Bitmap);
   Printer()->EndDoc();
   delete Bitmap;
}


// Menu->Calcular->Iteraciones en el Toro
void __fastcall TFormaToro::MenuCalcularIteracionesenToroClick(TObject *Sender)
{
   Calcula_lineas_toro();
}

// Menu->Calcular->Toro
void __fastcall TFormaToro::MenuCalcularToroClick(TObject *Sender)
{
   Calcula_toro();
}

// MenuCalcular->Numero de Rotación
void __fastcall TFormaToro::MenuCalcularNumRotacionClick(TObject *Sender)
{
   TCursor antcursor = Cursor;
   // Cambia el cursor del mouse
   Cursor = crHourGlass;
   long double p[NUM_MAX_PARAMETROS], rot;
   BarraDeEstadosToro->SimpleText = (AnsiString) "Calculating rotation number (this process may last several seconds).";
   // Recupera los parámetros por omisión
   fun_disp.RetornaParametros(p);
   // Cambiar parámetros
   num_rot.AsignaParametros(p);
   rot = num_rot.Calcula(Tipo_integracion);
   char xcad[200];
   sprintf(xcad,"Rotation: %Lf",rot);
   MessageBox(NULL,xcad,"Torus scenery",MB_OK+MB_ICONINFORMATION);
   BarraDeEstadosToro->SimpleText = (AnsiString) " ";
   // Cambia el cursor del mouse
   Cursor = antcursor;
}

// Menu->Calcular->Sincronización
void __fastcall TFormaToro::MenuCalcularSincronizacionClick(TObject *Sender)
{
   TCursor antcursor = Cursor;
   // Cambia el cursor del mouse
   Cursor = crHourGlass;
   long double p[NUM_MAX_PARAMETROS];
   unsigned int xp, xq;
   BarraDeEstadosToro->SimpleText = (AnsiString) "Calculating synchronization (this process may last several seconds).";
   // Recupera los parámetros por omisión
   fun_disp.RetornaParametros(p);
   // Cambiar parámetros
   sincro.AsignaParametros(p);
   sincro.Calcula(Tipo_integracion, xp, xq);
   char xcad[200];
   sprintf(xcad,"Synchronization: %u /%u ",xp,xq);
   MessageBox(NULL,xcad,"Torus scenery",MB_OK+MB_ICONINFORMATION);
   BarraDeEstadosToro->SimpleText = (AnsiString) " ";
   // Cambia el cursor del mouse
   Cursor = antcursor;
}

// Menu->Calcular->Exponente de Lyapunov
void __fastcall TFormaToro::MenuCalcularExpLyapunovClick(TObject *Sender)
{
   TCursor antcursor = Cursor;
   // Cambia el cursor del mouse
   Cursor = crHourGlass;
   long double p[NUM_MAX_PARAMETROS], rot;
   BarraDeEstadosToro->SimpleText = (AnsiString) "Calculating Lyapunov exponent (this process may last several seconds).";
   // Recupera los parámetros por omisión
   fun_disp.RetornaParametros(p);
   // Cambiar parámetros
   exp_lyap.AsignaParametros(p);
   rot = exp_lyap.Calcula(Tipo_integracion);
   char xcad[200];
   sprintf(xcad,"Lyapunov exponent: %Lf",rot);
   MessageBox(NULL,xcad,"Torus scenery",MB_OK+MB_ICONINFORMATION);
   BarraDeEstadosToro->SimpleText = (AnsiString) " ";
   // Cambia el cursor del mouse
   Cursor = antcursor;
}

// Menu->Ventana->Limpiar ventana
void __fastcall TFormaToro::MenuVentanaLimpiarClick(TObject *Sender)
{
   Limpia_matriz_pixeles();
   Grafica(true);
}


//Menu->Configurar->Parametros
void __fastcall TFormaToro::MenuConfigurarParametrosClick(TObject *Sender)
{
   configura = new TVCap_Toro(this);
   if (configura) {
      PasarValoresConfiguracion();
      configura->TabbedNotebook1->PageIndex = 0;
      configura->ShowModal();
      RetornarValoresConfiguracion();
      delete configura;
   }
}

//Menu->Configurar->Dimensiones//Menu->Configurar->Visualizar
void __fastcall TFormaToro::MenuConfigurarVisualizarClick(TObject *Sender)
{
   configura = new TVCap_Toro(this);
   if (configura) {
      PasarValoresConfiguracion();
      configura->TabbedNotebook1->PageIndex = 1;
      configura->ShowModal();
      RetornarValoresConfiguracion();
      delete configura;
   }
}

//Menu->Configurar->Escenario
void __fastcall TFormaToro::MenuConfigurarCalculoClick(TObject *Sender)
{
   configura = new TVCap_Toro(this);
   if (configura) {
      PasarValoresConfiguracion();
      configura->TabbedNotebook1->PageIndex = 2;
      configura->ShowModal();
      RetornarValoresConfiguracion();
      delete configura;
   }
}


// Menu->Ayuda->Acerca de ...
void __fastcall TFormaToro::MenuAyudaAcercadeClick(TObject *Sender)
{
   TVAcercaDe *Acercade = new TVAcercaDe(this);
   if (Acercade) {
      Acercade->ShowModal();
      delete Acercade;
   }
}

// Menu->Ayuda->Toro
void __fastcall TFormaToro::MenuAyudaToroClick(TObject *Sender)
{
   TAyudaForm *Ayuda = new TAyudaForm(this);
   if (Ayuda) {
      Ayuda->Abrir_archivo("Torus scenery","Toro.hlp");
      Ayuda->Show();
   }
}


///////////////////////////////////////////////////////////////////////////////
//  Definición de Comportamientos de Toro 
///////////////////////////////////////////////////////////////////////////////
// Constructor de la clase
__fastcall TFormaToro::TFormaToro(TComponent* Owner) : TForm(Owner)
{
   Detener_calculo = false;
   // Dimenciones de la ventana
   Dim_Vtn.Xi = 0.0;
   Dim_Vtn.Xf = 1.0;
   Dim_Vtn.Yi = 0.0;
   Dim_Vtn.Yf = 1.0;
   // longitud de la ventana de pixeles
   Pix_x = 1024;
   Pix_y = 768;
   // Inicializa la ventana de pixeles
   pix[0].Inicializa(Pix_x,Pix_y, false, Dim_Vtn);   // Referencia
   pix[1].Inicializa(Pix_x,Pix_y, false, Dim_Vtn);   // Toro
   pix[2].Inicializa(Pix_x,Pix_y, false, Dim_Vtn);   // Iteraciones
   // Color de los graficos
   Color_grafica[0] = clWhite;    // Referencia
   Color_grafica[1] = clAqua;     // Toro
   Color_grafica[2] = clGray;     // Iteraciones
   Color_fondo = clSilver;        // Fondo
   // indica que graficos estaran activos
   Sw_Visualiza_referencia = true;
   Sw_Visualiza_toro = true;
   Sw_Visualiza_linea = true;
   // Puntos a trazar en la curva
   Puntos_trazar = Pix_x;
   // Tipo de integración
   Tipo_integracion = ADELANTE;
   // Valores para calculo de iteraciones
   Num_iteraciones = 1;
   Num_trazos = 10;
   // Condiciones iniciales
   Condicion_inicial.X = 0.0; 
   Condicion_inicial.Y = 0.0;
   // Calcula la referencia 
   Calcula_referencia();
}

// Calcula el toro
void TFormaToro::Calcula_toro(void) 
{
   TCursor antcursor = Cursor;
   // Cambia el cursor del mouse
   Cursor = crHourGlass;
   unsigned int xi;
   long double y , t, aux, paso;
   int px, py;

   Detener_calculo = false;
   BarraDeEstadosToro->SimpleText = (AnsiString) "Calculating torus (this process may last several seconds).";
   pix[1].Asigna_todo_array(false);
   t = Dim_Vtn.Xi;
   paso = (Dim_Vtn.Xf - Dim_Vtn.Xi) / (long double) Puntos_trazar;
   while(t <= Dim_Vtn.Xf) {
      // Termina el ciclo si se solicito 
      Application->ProcessMessages();
      if(Detener_calculo) break;
      y = t;
      for(xi = 0; xi < Num_iteraciones; xi ++) {
          y = fun_disp.Calcula(y,Tipo_integracion);
          y = modfl(y,&aux);
          if(y < 0.0) y += 1.0;
      }
      if(!fun_disp.Error_calculo) {
         pix[1].Asigna_valor(t, y, true);
         px = (t - Dim_Vtn.Xi) * Escala.X;
         py = VTToro->Height - (((y - Dim_Vtn.Yi) * Escala.Y) + 1.0);
         if (Sw_Visualiza_toro) {
            if (px >= 0 && px < VTToro->Width && py >= 0 && py < VTToro->Height) VTToro->Canvas->Pixels[px][py] = Color_grafica[1];      
         }   
      }
      t += paso;
   }
   BarraDeEstadosToro->SimpleText = (AnsiString) "";
   // Cambia el cursor del mouse
   Cursor = antcursor;
}

// Calcula las lineas en el toro
void TFormaToro::Calcula_lineas_toro(void) 
{
   TCursor antcursor = Cursor;
   // Cambia el cursor del mouse
   Cursor = crHourGlass;
   unsigned int xi;
   unsigned int n_t = 0;
   long double y , t, aux;

   Detener_calculo = false;
   BarraDeEstadosToro->SimpleText=(AnsiString) "Calculating iterations (this process may last several seconds).";
   t = Condicion_inicial.X;
   while(n_t < Num_trazos) {
      // Termina el ciclo si se solicito 
      Application->ProcessMessages();
      if(Detener_calculo) break;
      y = t;
      for(xi = 0; xi < Num_iteraciones; xi ++) {
          y = fun_disp.Calcula(y,Tipo_integracion);
          y = modfl(y,&aux);
          if(y < 0.0) y += 1.0;
      }
      pix[2].Asigna_linea(Condicion_inicial.X,Condicion_inicial.Y,Condicion_inicial.X,y,true);
      pix[2].Asigna_linea(Condicion_inicial.X,y,y,y,true);

      t = y;
      Condicion_inicial.X = y; 
      Condicion_inicial.Y = t; 
      n_t ++;
      Grafica(false);
   }
   BarraDeEstadosToro->SimpleText=(AnsiString) " ";   
   // Cambia el cursor del mouse
   Cursor = antcursor;
}


// Grafica la referencia de la ventana
void TFormaToro::Calcula_referencia(void)
{
   pix[0].Asigna_linea(Dim_Vtn.Xi,Dim_Vtn.Yi,Dim_Vtn.Xf,Dim_Vtn.Yf,true);
}

// Grafica las curvas calculadas
void TFormaToro::Grafica(bool limpia)
{
   unsigned int x,y,i;
   C_2D escala;

   if(limpia) Limpiar_vantana();
   // Calcula la escala de la ventana de visualizacion con respecto a la ventana de pixeles
   escala.X = VTToro->Width / (long double) Pix_x;
   escala.Y = VTToro->Height / (long double) Pix_y;
   for(i = 0; i < 3; i++) {
      if(i == 0 && !Sw_Visualiza_referencia) i++;
      if(i == 1 && !Sw_Visualiza_toro) i++;
      if(i == 2 && !Sw_Visualiza_linea) break;
      for(y = 0; y < Pix_y; y++) {
          for(x = 0; x < Pix_x; x++) {
              if(pix[i].Retorna_valor(x, y)) VTToro->Canvas->Pixels[x * escala.X][y * escala.Y] = Color_grafica[i];
          }
      }
   }
}

// Limpia la ventana de graficacion
void TFormaToro::Limpiar_vantana(void)
{
   VTToro->Canvas->Pen->Color = Color_fondo;
   VTToro->Canvas->Brush->Color = Color_fondo;
   VTToro->Canvas->Rectangle(0, 0, VTToro->Width, VTToro->Height);
}




//#error Si se solicita cerrar ventana cancelar calculo y visualización







// Muestra la posición del mouse en coordenadas reales
void __fastcall TFormaToro::VTToroMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
   Vs.Xf = X, Vs.Yf = Y;
   Vs.Xi = Vs.Xf / Escala.X + Dim_Vtn.Xi;
   Vs.Yi = (-(Vs.Yf - VTToro->Height) / Escala.Y) + Dim_Vtn.Yi;

   sprintf(Msg,"Mouse position: (%3.8Lf, %3.8Lf)", Vs.Xi, Vs.Yi);
   BarraDeEstadosToro->SimpleText = (AnsiString) Msg;
}

// Fija la condición inicial
void __fastcall TFormaToro::FijarCondicIninicialClick(TObject *Sender)
{
   Condicion_inicial.X = Vs.Xi; 
   Condicion_inicial.Y = 0.0;
}


// Pasa los valores de configuración de la ventana de captura
void TFormaToro::PasarValoresConfiguracion(void)
{
   ////////////////////////////////////////////////////////
   // Parámetros
   ////////////////////////////////////////////////////////
   configura->ListBoxParametros->Items->Clear();
   for ( int i = 0; i < fun_disp.Numero_parametros; i++) {
       sprintf(xcad,"%-6s = %1.9Lf",fun_disp.Nombre_parametros[i],fun_disp.P[i] );
       configura->ListBoxParametros->Items->Add(xcad);
   }
   ////////////////////////////////////////////////////////
   // Visualizar
   ////////////////////////////////////////////////////////
   // Check Box
   configura->CheckBox1->Checked = Sw_Visualiza_referencia;
   configura->CheckBox2->Checked = Sw_Visualiza_toro;
   configura->CheckBox3->Checked = Sw_Visualiza_linea;
   // Colores
   configura->Panel5->Color = Color_grafica[0];
   configura->Panel6->Color = Color_grafica[1];
   configura->Panel7->Color = Color_grafica[2];
   configura->Panel8->Color = Color_fondo;
   ////////////////////////////////////////////////////////
   // Escenario
   ////////////////////////////////////////////////////////
   sprintf(xcad,"%Lf",Condicion_inicial.X);
   configura->Edit8->Text = (AnsiString) xcad;
   sprintf(xcad,"%u",Num_trazos);
   configura->Edit9->Text = (AnsiString) xcad;
   sprintf(xcad,"%u",Num_iteraciones);
   configura->Edit10->Text = (AnsiString) xcad;
   configura->RadioButton1->Checked = Tipo_integracion;   
   configura->RadioButton2->Checked = !Tipo_integracion;   
}

// Retorna los valores de configuración de la ventana de captura
void TFormaToro::RetornarValoresConfiguracion(void)
{
   if (!configura->Aceptar) return;
   ////////////////////////////////////////////////////////
   // Parámetros
   ////////////////////////////////////////////////////////
   bool sw = false;
   long double temp;
   for (int i = 0; i < fun_disp.Numero_parametros; i++) {
       unsigned int i1, i2;
       char xcad[100], xcad1[100];
       strcpy(xcad1,configura->ListBoxParametros->Items->Strings[i].c_str());
       // Valor del parámetro
       for (i2 = 0, i1 = 9; i1 < strlen(xcad1); i2++, i1++) xcad[i2] = xcad1[i1];
       xcad[i2] = 0;
       temp = _atold(xcad);
       if (fun_disp.P[i] != temp) sw = true;
       fun_disp.P[i] = temp;
   }
   if (sw) {
      pix[1].Asigna_todo_array(false);
      pix[2].Asigna_todo_array(false);
   }
   ////////////////////////////////////////////////////////
   // Visualizar
   ////////////////////////////////////////////////////////
   // Check Box
   Sw_Visualiza_referencia = configura->CheckBox1->Checked;
   Sw_Visualiza_toro       = configura->CheckBox2->Checked;
   Sw_Visualiza_linea      = configura->CheckBox3->Checked;
   // Colores
   Color_grafica[0] = configura->Panel5->Color;
   Color_grafica[1] = configura->Panel6->Color;
   Color_grafica[2] = configura->Panel7->Color;
   Color_fondo      = configura->Panel8->Color;
   ////////////////////////////////////////////////////////
   // Escenario
   ////////////////////////////////////////////////////////
   Condicion_inicial.X = _atold(configura->Edit8->Text.c_str());       
   Num_trazos          = atoi(configura->Edit9->Text.c_str());       
   Num_iteraciones     = atoi(configura->Edit10->Text.c_str());       
   Tipo_integracion    = configura->RadioButton1->Checked;   
   /////////////////////////////////////////////////////////
   // Al terminar
   /////////////////////////////////////////////////////////
   Grafica(true);
}



void __fastcall TFormaToro::Timer1Timer(TObject *Sender)
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
          MenuCalcularNumRotacionClick(this);
      }
      // Calcula la sincronización
      if (Calcular_sincronizaciones) {
          Calcular_sincronizaciones = false;
          MenuCalcularSincronizacionClick(this);
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
          MenuCalcularIteracionesenToroClick(this);
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
//---------------------------------------------------------------------------




void __fastcall TFormaToro::MenuCalcularDetenerelcalculoClick(TObject *Sender)
{
   Detener_calculo = true;        
}
//---------------------------------------------------------------------------

void __fastcall TFormaToro::VTToroPaint(TObject *Sender)
{
   Grafica(true);        
}


// OnHint
void  __fastcall TFormaToro::OnHint(TObject *Sender)
{
   BarraDeEstadosToro->SimpleText = Application->Hint;
}

void __fastcall TFormaToro::FormActivate(TObject *Sender)
{
   Application->OnHint = OnHint;
}

void __fastcall TFormaToro::FormDeactivate(TObject *Sender)
{
   Application->OnHint = NULL;
}

