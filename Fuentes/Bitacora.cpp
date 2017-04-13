// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV5
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A

#include <fstream.h>
#include <mmsystem.h>
#include <string.h>
#include <dir.h>
#include "man_arch.hpp"
#include "Fechora.hpp"
#include "bitacora.hpp"
#pragma hdrstop

const char *TXT01 = "BITACORA REINICIALIZADA";

extern char *ARCH_BITACORA;


void Bitacora::Revisa_llenado_bitacora(void)
{
   ifstream rev(ARCH_BITACORA,ios::binary);
   rev.seekg(0,ifstream::end);
   long lg = rev.tellg();
   rev.close();
   if (lg > 64000L) {
      Manipulador_archivos ma;
      char xarch[MAXPATH];
      
      ma.Cambia_ext_path(ARCH_BITACORA, "OLD", xarch);
      ma.Copia_archivo(ARCH_BITACORA, xarch);
      
      ofstream vac(ARCH_BITACORA,ios::binary|ios::trunc);
      vac.close();
      Adiciona(TXT01);
   }
}


// Adiciona una entrada más a la bitacora
void Bitacora::Adiciona(const char *txt1, const char *txt2, const char *txt3)
{
   char fecha[30], cad[300];
   Fechas_Horas   fh;

   fh.Fecha_y_hora(fecha, 2, 0);
   ofstream grab(ARCH_BITACORA,ios::binary|ios::app);
   if (grab) {
      sprintf(cad,"%s %s %s %s %s",fecha,txt1,txt2,txt3,sep);
      grab.write(cad,strlen(cad));
      grab.close();
   }
}

