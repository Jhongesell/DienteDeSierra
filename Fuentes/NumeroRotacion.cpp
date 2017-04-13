// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV5
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#include "NumeroRotacion.hpp"


// Retorna el numero de rotacion
long double NumeroRotacion::Calcula(const bool  t_i)
{
   long double aux, Temp1;  
   unsigned int N;     
   // Condicion inicial
   if(Rot_sw_Cond_inicial_aleatoria) Temp1 = random(10000) / 10000;   // Condicion inicial aleatoria
    else Temp1 = Rot_sw_Cond_inicial_aleatoria;
                       
   N = 1;
   while ((N <= Rot_Num_iteraciones) && !Error_calculo) {
      Temp1 = modfl(Temp1,&aux);
      Temp1 = FuncionDisparo::Calcula(Temp1, t_i) + aux;
      N++;
   }
   if (!Error_calculo) {
      if (Temp1 >= 0.0) Temp1 = modfl(Temp1 / (long double) Rot_Num_iteraciones,&aux);
       else Temp1 = modfl((Temp1 /(long double) Rot_Num_iteraciones),&aux) + 1.0;
   } else Temp1 = -10.0;
   return (Temp1);
}


