// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV5
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A




   // Arreglo que contiene el nombre de las constantes usas y su valor numerico correspondiente
   char *Constantes[] = {
      "M_PI",         "3.14159265358979",  // Pi
      "M_PI_2",       "3.14159265358979",  // Pi/2
      "M_PI_4",       "3.14159265358979",  // Pi/4
      "M_1_PI",       "3.14159265358979",  // 1/Pi
      "M_2_PI",       "3.14159265358979",  // 2/Pi
      "M_1_SQRTPI",   "3.14159265358979",  // 1/sqrt(Pi)
      "M_2_SQRTPI",   "3.14159265358979",  // 2/sqrt(Pi)
      "M_E",          "2.71828182845904",  // e
      "M_LOG2E",      "2.71828182845904",  // log(e)
      "M_LOG10E",     "2.71828182845904",  // log10(e)
      "M_LN2",        "2.71828182845904",  // ln(2)
      "M_LN10",       "2.71828182845904",  // ln(10)
      "",""
   };

//////////////////////////////////////////////////////////////////////////////////////////
// Estas son usadas por los programas Analiza expresion y calculadora en notación polaca   
//////////////////////////////////////////////////////////////////////////////////////////

   // Arreglo que contiene el nombre de las funciones permitidas y su numero de parametros
   char *Funciones[] = {
      "sinl",   "1",                    // seno
      "cosl",   "1",                    // coseno
      "tanl",   "1",                    // tangente
      "asinl",  "1",                    // arco seno
      "acosl",  "1",                    // arco coseno
      "atanl",  "1",                    // arco tangente
      "sinhl",  "1",                    // seno hiperbolico
      "coshl",  "1",                    // coseno hiperbolico
      "tanhl",  "1",                    // tangente hiperbolico
      "fabsl",  "1",                    // valor absoluto
      "floorl", "1",                    // El mayor entero menor o igual a
      "fmodl",  "2",                    // Calcula el modulo de X/Y
      "expl",   "1",                    // exponencia e a la x
      "ldexpl", "2",                    // Calcula X  por 2 exponente a la Y
      "logl",   "1",                    // logaritmo natural
      "log10l", "1",                    // logaritmo base 10
      "sqrtl",  "1",                    // raiz cuadrada
      "powl",   "2",                    // x a la y
      "pow10l", "1",                    // 10 a la X
//////////////////////////////////////////////////////////////////////////////////
// Funciones agregadas para el evaluador de expresiones no son propias de       //
// Borland.                                                                     //
//                                                                              //
      "factl",  "1",                    // Factorial de x
      "invl",   "1",                    // Inverso de x
      "sigl",   "1",                    // Signo de X (1 si X > 0, -1 si X < 0 y 0 si X es cero)
      "sqrl",   "1",                    // Cuadrado de X
      "trcl",   "1",                    // Parte entera de X
      "decl",   "1",                    // Parte decimal de X
      "maxl",   "2",                    // Maximo entre X e Y
      "minl",   "2",                    // Minimo entre X e Y
//      "gra",   "0",                    // funciones trigonometricas en gradianes
//      "rad",   "0",                    // funciones trigonometricas en radianes
//      "deg",   "0",                    // funciones trigonometricas en grados
      "F",     "1",                    // Se usara para funciones auxiliares unicamente
//                                                                               //
/////////////////////////////////////////////////////////////////////////////////
      "",""
   };
