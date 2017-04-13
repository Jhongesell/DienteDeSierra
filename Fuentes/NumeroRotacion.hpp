// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV5
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A



#ifndef __NUMEROROTACION_HPP__
#define __NUMEROROTACION_HPP__


#include "FuncionDisparo.hpp"
#include <stdlib.h>


////////////////////////////////////////////////////////////////////////////////////////
//         Clase que contiene la rutina para el calculo del numero de Rotación        //
////////////////////////////////////////////////////////////////////////////////////////


class NumeroRotacion: public FuncionDisparo 
{
   public:

                             // Indica el error en calculo (si este existe)
      unsigned int           Error_calculo;
      unsigned int           Rot_Num_iteraciones;
      long double            Rot_Condicion_Inicial;
      bool                   Rot_sw_Cond_inicial_aleatoria;

  
                             // Constructor de la clase
                             NumeroRotacion(void)
                             {
                                // Valores por omision para el calculo del rotacional
                                Rot_Num_iteraciones           = 200;
                                Error_calculo                 = 0;
                                Rot_Condicion_Inicial         = 0.0;
                                Rot_sw_Cond_inicial_aleatoria = true;
                             }
                             
                             // Retorna el numero de rotacional
      long double            Calcula(const bool  t_i);
};

#endif

