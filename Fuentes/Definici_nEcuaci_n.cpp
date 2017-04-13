// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en trámite 1999-2000
// Revisión  1.1-A


#include "DefinicionEcuacion.hpp"

// Constructor de la clase
DefinicionEcuacion::DefinicionEcuacion(void)
{
   // Nombre del sistema   
   Nombre_sistema       = "Arnold's Classical Maps of Circunference";
   // Número de parámetros
   Numero_parametros          = 6;
   Numero_parametros_bifurcar = 4;
   // Nombre de los parámetros (si el nombre de el parámetro excede de 6 letras
   // hay que indicar el tamaño maximo de este en captura de parámetros en cada escenario)
   Nombre_parametros[0] = "a";
   Nombre_parametros[1] = "b";
   Nombre_parametros[2] = "c";
   Nombre_parametros[3] = "d";
   Nombre_parametros[4] = "n";
   Nombre_parametros[5] = "m";
   
   // Valores por omisión de los parametros
   P[0] = 0.65;
   P[1] = 0.45;
   P[2] = 1.0;
   P[3] = 0.0;
   P[4] = 1.0;
   P[5] = 1.0;
   // Ecuación en formato texto
   Ecuacion_texto = "c = x + a + b * pow(sin(2.0 * M_PI * x),n) + d * pow(cos(2.0 * M_PI * x),m)";
}



// Asigna valor a los parámetros
void DefinicionEcuacion::AsignaParametros(const long double parm[NUM_MAX_PARAMETROS])
{
   for (int i = 0; i < Numero_parametros; i++) P[i] = parm[i];
}

// Retorna el valor de los parámetros
void DefinicionEcuacion::RetornaParametros(long double *parm)
{
   for (int i = 0; i < Numero_parametros; i++) parm[i] = P[i];
}


