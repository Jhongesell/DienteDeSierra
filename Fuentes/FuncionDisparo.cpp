// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV5
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#include "FuncionDisparo.hpp"
#include <math.h>


// Constructor de la clase
FuncionDisparo::FuncionDisparo(void)
{
   // Variable para controlar el error numerico
   Error_calculo = 0;
}


// Función que encuentra el siguiente disparo
long double FuncionDisparo::Calcula(const long double T, const bool FI)
{
   Error_calculo = 0;
   return (Ecuacion(T,FI));
}


/*
long double FuncionDisparo::Calcula(const long double p1, const long double p2, const long double p3, const long double T, const bool FI)
{
   Error_calculo = 0;

//   return (T + p2 + p1*sinl(2.0 * M_PI * T));

   bool sw, sw1;
   long double KT8, R, x1, x2, Y, T1;
   long cont = 0;

  T1 = T;
  if (FI) Y = 0.0, Cota = 1.0;
   else  Y = 1.0, Cota = 0.0;
   
  if (FI) {
      while ((Y < Cota) && ((T1 - T) < Dis_Tiempo_maximo)) {
         sw = true;
         while (sw) {
            sw1 = false;
            KT8 = Dis_Paso_integracion * 0.25;
            x2  = Dis_Paso_integracion * 0.5;
            K1 = x2 * Ecuacion(p1,p2,p3,Y,T1);
            K2 = x2 * Ecuacion(p1,p2,p3,Y + K1 * 0.5,T1 + KT8);
            K3 = x2 * Ecuacion(p1,p2,p3,Y + K2 * 0.5,T1 + KT8);
            K4 = x2 * Ecuacion(p1,p2,p3,Y + K3,T1 + x2);
            x1 = ((K1 + (2.0 * K2) + (2.0 * K3) + K4) / 6.0) + Y;

            KT8 = Dis_Paso_integracion * 0.75;
            K1 = x2 * Ecuacion(p1,p2,p3,x1,T1+x2);
            K2 = x2 * Ecuacion(p1,p2,p3,x1 + K1 * 0.5,T1 + KT8);
            K3 = x2 * Ecuacion(p1,p2,p3,x1 + K2 * 0.5,T1 + KT8);
            K4 = x2 * Ecuacion(p1,p2,p3,x1 + K3,T1 + Dis_Paso_integracion);
            Kt = ((K1 + (2.0 * K2) + (2.0 * K3) + K4) / 6.0) + x1;

            KT8 = Dis_Paso_integracion * 0.5;
            K1 = - Dis_Paso_integracion * Ecuacion(p1,p2,p3,Kt,T1 + Dis_Paso_integracion);
            K2 = - Dis_Paso_integracion * Ecuacion(p1,p2,p3,Kt + K1 * 0.5,T1 + KT8);
            K3 = - Dis_Paso_integracion * Ecuacion(p1,p2,p3,Kt + K2 * 0.5,T1 + KT8);
            K4 = - Dis_Paso_integracion * Ecuacion(p1,p2,p3,Kt + K3,T1);
            R = ((K1 + (2.0 * K2) + (2.0 * K3) + K4) / 6.0) + Kt;

            if (fabsl(Y - R) < Dis_Tolerancia_metodo) sw = false;
             else sw1 = true;
            if (sw == false) {
               if (Kt > Cota) sw1 = true;
            }
            if (sw1) {
               Dis_Paso_integracion *= 0.7;
//               if (Dis_Paso_integracion > 0.005) Dis_Paso_integracion *= 0.7;
//                else sw = false;
            }   
            cont ++;
         }
         if (cont < 2) {
            if (fabsl(Y - R) < (Dis_Tolerancia_metodo * 0.8)) {
               Dis_Paso_integracion *= 1.1;
               if (fabs(Dis_Paso_integracion) > Dis_Paso_maximo)  Dis_Paso_integracion = Dis_Paso_maximo;
            }
         }
         cont = 0;
         Y = Kt;
         T1 += Dis_Paso_integracion;
      }
      if (Y < Cota) Error_calculo = 1;  // Excesivo tiempo de integracion
   } else {
      while ((Y > Cota) && ((T1 - T) < Dis_Tiempo_maximo)) {
//         Yn = Y;
//         Y = Integra(p1,p2,p3,Y,T1,-Paso);
         T1 -= Paso;
      }
      if (Y > Cota) Error_calculo = 1;  // Excesivo tiempo de integracion
  }

  return T1;
  
}
*/


