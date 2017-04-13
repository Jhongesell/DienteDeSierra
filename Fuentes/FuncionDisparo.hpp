// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV5
// Direcci�n: Amsterdam 312 col. Hip�dromo Condesa
// Tel�fono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr�mite
// Revisi�n  1.0-A


#ifndef __FUNCIONDISPARO_HPP__
#define __FUNCIONDISPARO_HPP__


#include "DefinicionEcuacion.hpp"

// Indica el m�todo num�rico de integraci�n activo
#define RUNGE-KUTTA


////////////////////////////////////////////////////////////////////////////////////////////////////
//      Clase que contiene los metodos numericos de integracion de ecuaciones diferenciales       //
////////////////////////////////////////////////////////////////////////////////////////////////////


class FuncionDisparo: public DefinicionEcuacion
{
   private:
                             
      long double            Y, Yn, T1, Cota;    // Variables temporales para la funci�n de disparo

   public:

      ////////////////////////////////////////////////////////////////////////
      // Funci�n de disparo
      ////////////////////////////////////////////////////////////////////////
        
                             // Indica el error en calculo (si este existe)
      unsigned int           Error_calculo;

                             // Constructor de la clase
                             FuncionDisparo(void);

                             // C�lculo de la funci�n de disparo
      long double            Calcula(const long double T, const bool FI);
};

#endif

