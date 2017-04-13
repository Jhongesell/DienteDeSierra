// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV5
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A

#ifndef __BITACORA__ 
#define __BITACORA__


class Bitacora {
   private:
      char sep[4];      
      
   public:

            // Constructor de la clase
            Bitacora(void)
            {
               sep[0] = 13;
               sep[1] = 10;
               sep[2] = 0;
            }
            // Revisa y en su caso reinicializa la bitacora si esta saturada
      void  Revisa_llenado_bitacora(void);
            // Graba la bitacora del sistema
      void  Adiciona(const char *txt1, const char *txt2 = "", const char *txt3 = "");
};

#endif





