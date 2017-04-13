// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV5
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#include "Sincronizaciones.hpp"

// Retorna el numero de sincronizacion
int Sincronizaciones::Calcula(const bool  t_i, unsigned int &p, unsigned int &q)
{
  long double aux, X, X0, X1;     
  unsigned int K, J = 0, I = 0;
  int Found = 0;        
  p = 0, q = 0;
  // Condicion inicial
  if(Res_sw_Cond_inicial_aleatoria) X0 = random(10000) / 10000;   // Condicion inicial aleatoria
   else X0 = Res_sw_Cond_inicial_aleatoria;
  ///////////////////////////////////////////////////////////////////////////////////
  // Transitorios
  do {  
    X0 = modfl(X0,&aux);
    X0 = FuncionDisparo::Calcula(X0,t_i) + aux;
    I++;
  } while ((I < Res_Long_transitorios) && !Error_calculo);
  ///////////////////////////////////////////////////////////////////////////////////
  K = 0;
  X = X0;
  X1 = modfl(X0,&aux);
  do {  // Comienza otro ciclo
     do { // Busca una primera aproximacion
        I = 0;
        // Busca la resonancia y halla una primera orbita periodica
        while (!Found && (I < Res_Long_max_ciclo) && !Error_calculo) {
           X = modfl(X,&aux);
           X = FuncionDisparo::Calcula(X,t_i) + aux;
           Found = ((fabsl(X1 - modfl(X,&aux)) <= Res_Tolerancia) || (fabsl(fabsl(X1 - modfl(X,&aux)) - 1.0) <= Res_Tolerancia));
           I++;
        }
        if ((I >= Res_Long_max_ciclo) && !Found) K++;
     } while (!Found && ( K < Res_Max_num_ciclos) && !Error_calculo);

     // Comienza comprobacion de la resonancia hallada
     if (Found) {
        Found = 0;
        if ((I > 0) && (I < Res_Long_max_ciclo) &&  !Error_calculo) {
           X0 = X;
           // Ciclo del revisión
           for (J = 0; J < I && !Error_calculo; J++) {
                X = modfl(X,&aux);
                X = FuncionDisparo::Calcula(X,t_i) + aux;
           }
           Found = ((fabsl(modfl(X0,&aux) - modfl(X,&aux)) < Res_Tolerancia) || (fabs(fabsl(modfl(X0,&aux) - modfl(X,&aux)) -1.0) <= Res_Tolerancia));
           // Se encontro resonancia
           if (Found) {
              modfl(X,&aux);
              J = aux;
              modfl(X0,&aux);
              J -= aux;
              p = J;
              q = I;
              return (Found);
           }
        }
     }
     X1 = X; // Si no detecto periodicidad toma otro punto mas avanzado de una probable orbita y lo utiliza al volver a entrar al loop
     K++;
  } while (!Found && (K < Res_Max_num_ciclos) && (I < Res_Long_max_ciclo) && (J < Res_Long_max_ciclo) && !Error_calculo);   

  // Revisa si fue encontrada o no la resonancia
  if (!Found) {                
      // No encontro resonancia en el punto
      p = 0;
      q = 0;
  }
  return (Found);
}

