// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en trámite 1999-2000
// Revisión  1.1-A


#ifndef __DefinicionEcuacion_HPP__
#define __DefinicionEcuacion_HPP__




extern "C" {
   #include <math.h>
}

#define NUM_MAX_PARAMETROS 15


/////////////////////////////////////////////////////////////////////////////////
//         Clase que contiene la definicion de la ecuación del sistema         //
/////////////////////////////////////////////////////////////////////////////////

class DefinicionEcuacion {

   public:
                           // Nombre del sistema
      char                *Nombre_sistema;                  
                           // Número de parámetros
      char                 Numero_parametros;               
                           // Número de parámetros a bifurcar
      char                 Numero_parametros_bifurcar;               
                           // Nombre de parámetros
      char                *Nombre_parametros[NUM_MAX_PARAMETROS];            
                           // Ecuación en formato texto
      char                *Ecuacion_texto;
                           // Parámetros del sistema
      long double          P[NUM_MAX_PARAMETROS];


      
                           // Constructor de la clase
                           DefinicionEcuacion(void);
                           // Asigna valor a los parámetros
      void                 AsignaParametros(const long double parm[NUM_MAX_PARAMETROS]);
                           // Retorna el valor de los parámetros
      void                 RetornaParametros(long double *parm);
      
                           // Ecuacion del sistema 
      long double          Ecuacion(const long double x, const long double t)
                           { 
                              return ( (P[2] * x) + P[0] + (P[1] * powl(sinl(2.0 * M_PI * x),P[4])) + (P[3] * powl(cosl(2.0 * M_PI * x),P[5])));
                           } 
                           // Curva de extremos
      long double          G(const long double t)
                           {
                              return (0.0);
                           }
                           
};

#endif







