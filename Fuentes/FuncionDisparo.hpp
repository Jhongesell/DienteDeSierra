// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV5
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#ifndef __FUNCIONDISPARO_HPP__
#define __FUNCIONDISPARO_HPP__


#include "DefinicionEcuacion.hpp"

// Indica el método numérico de integración activo
#define RUNGE-KUTTA


////////////////////////////////////////////////////////////////////////////////////////////////////
//      Clase que contiene los metodos numericos de integracion de ecuaciones diferenciales       //
////////////////////////////////////////////////////////////////////////////////////////////////////


class FuncionDisparo: public DefinicionEcuacion
{
   private:
                             
      long double            Y, Yn, T1, Cota;    // Variables temporales para la función de disparo

   public:

      ////////////////////////////////////////////////////////////////////////
      // Función de disparo
      ////////////////////////////////////////////////////////////////////////
        
                             // Indica el error en calculo (si este existe)
      unsigned int           Error_calculo;

                             // Constructor de la clase
                             FuncionDisparo(void);

                             // Cálculo de la función de disparo
      long double            Calcula(const long double T, const bool FI);
};

#endif

