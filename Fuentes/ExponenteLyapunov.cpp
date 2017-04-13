// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV5
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#include "ExponenteLyapunov.hpp"
#include <stdlib.h>


////////////////////////////////////////////////////////////////////////////////////////////
// Calcula el exponente de Lyapunov mediante el cálculo de la derivada usando 4 puntos
// Rutina revisada por: C. Dr. Miguel Angel Mendoza
// Fecha de Modificación: 22 de Noviembre del 2000
////////////////////////////////////////////////////////////////////////////////////////////

// Retorna el exponente de Lyapunov
long double ExponenteLyapunov::Calcula(const bool FI)
{
   long double IAux;
   long double Suma = 0.0;
   long double Temp = 1.0;
   long double T;
   long double TAux;
   long double TAux2;
   long double Y = -1000.0;
   long double aux1, aux2, aux3, aux4;
   int i = 0;

   Error_calculo = 0;
   if (Sw_cond_inicial_aleatoria) T = random(1000) / 1000.0;   // Condicion inicial aleatoria
    else T = Condicion_inicial; // Condicion inicial fija

   while ((i < Max_num_iteraciones) && (Temp > Epsilon)) {
     aux1 = FuncionDisparo::Calcula(T-2.0*Paso_derivada,FI);
     if (Error_calculo) break;
     aux2 = FuncionDisparo::Calcula(T-Paso_derivada,FI);
     if (Error_calculo) break;
     aux3 = FuncionDisparo::Calcula(T+Paso_derivada,FI);
     if (Error_calculo) break;
     aux4 = FuncionDisparo::Calcula(T+2.0*Paso_derivada,FI);
     if (Error_calculo) break;
     TAux2 = fabsl((aux1 - 8.0*aux2 + 8.0*aux3 - aux4) / (12.0*Paso_derivada));
     if ((TAux2 > 0.0) && (TAux2 < 1.0E100)) Suma += logl(TAux2);
      else {              
         Error_calculo = 1;
         break;
     }
     T = modfl(T,&IAux);
     if (FI) T = FuncionDisparo::Calcula(T,FI) + IAux;
     i ++;
     TAux = 1.0 / ((long double) i) * Suma;
     Temp = fabsl(TAux - Y);
     Y = TAux;
   } 
   if (Error_calculo) Y = 0.0;
   Error_calculo = 0;
   return (Y);
}


