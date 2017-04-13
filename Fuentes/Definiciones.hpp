// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV5
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#ifndef __DEFINICIONES_HPP__
#define __DEFINICIONES_HPP__

struct Dimencion_Ventana {
    long double Xi;
    long double Xf;
    long double Yi;
    long double Yf;
    long double Zi;
    long double Zf;
};

struct Definicion_Ventana {
    int Xi;
    int Xf;
    int Yi;
    int Yf;
};


struct C_2D {
    long double X;
    long double Y;
};

struct C_3D {
    long double x;
    long double y;
    long double z;
};

// Cordenadas triples en formato entero
struct C_3I {
   int x;
   int y;
   int z;
};
   
// Cordenadas dobles en formato entero
struct C_2I {
   int x;
   int y;
};


#endif
