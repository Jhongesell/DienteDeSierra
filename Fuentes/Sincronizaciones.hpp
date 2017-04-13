// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV5
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A



#ifndef __SINCRONIZACIONES_HPP__
#define __SINCRONIZACIONES_HPP__


#include "FuncionDisparo.hpp"
#include <stdlib.h>


//////////////////////////////////////////////////////////////////////////////////
//      Clase que contiene las rutinas para el calculo de sincronizaciones      //
//////////////////////////////////////////////////////////////////////////////////


class Sincronizaciones: public FuncionDisparo 
{
   public:
        
      unsigned int           Res_Long_max_ciclo ;
      unsigned int           Res_Max_num_ciclos;
      unsigned int           Res_Long_transitorios;
      long double            Res_Tolerancia;
      long double            Res_Condicion_Inicial;
      bool                   Res_sw_Cond_inicial_aleatoria;

                             // Constructor de la clase
                             Sincronizaciones(void)
                             {
                                // Valores por omision para el calculo de resonancias
                                Res_Long_max_ciclo            = 40;
                                Res_Max_num_ciclos            = 10;
                                Res_Long_transitorios         = 150;
                                Res_Tolerancia                = 0.001;
                                Res_Condicion_Inicial         = 0.0;
                                Res_sw_Cond_inicial_aleatoria = true;

                                // Variable para controlar el error numerico
                                Error_calculo = 0;

                             }
                             // Retorna el numero de resonancias
      int                    Calcula(const bool  t_i, unsigned int &p, unsigned int &q);
};

#endif

