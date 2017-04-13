//---------------------------------------------------------------------------
#ifndef EnviarCorreoH
#define EnviarCorreoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <NMsmtp.hpp>
#include <Psock.hpp>
#include <string.h>
//---------------------------------------------------------------------------
class TFormaEnviarCorreo : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TButton *Button1;
        TRichEdit *Editor;
        TStaticText *StaticText1;
        TNMSMTP *NMSMTP1;
        TEdit *EditFrom;
        TStaticText *StaticText2;
        TRichEdit *EditorAux;
        void __fastcall NMSMTP1Connect(TObject *Sender);
        void __fastcall NMSMTP1Failure(TObject *Sender);
        void __fastcall NMSMTP1Success(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall NMSMTP1ConnectionFailed(TObject *Sender);
private:	// User declarations
        char       To[200];
        char       Subject[200];
        int        Numero_archivos;
        char     **Nombres_archivos;
public:		// User declarations
        __fastcall TFormaEnviarCorreo(TComponent* Owner);
        
        __fastcall ~TFormaEnviarCorreo()
                   {
                      if (!Nombres_archivos) return;
                      for (int xi = 0; xi < Numero_archivos; xi++) delete[] Nombres_archivos[xi];
                      delete[] Nombres_archivos;
                   }
                   
        void       Parametros(const char *from, const char *to, const char *subject)
                   {
                      strcpy(To,to);
                      strcpy(Subject,subject);
                      EditFrom->Text = from;
                   }
                   
        void       Fija_numero_archivos(const int num)
                   {
                      Numero_archivos = num;
                      Nombres_archivos = new char *[num];
                   }
                   
        void       Asigna_nombre_archivo(const int ind, const char *nombre)
                   {
                      Nombres_archivos[ind-1] = new char[strlen(nombre)+1];
                      strcpy(Nombres_archivos[ind-1],nombre);
                   }
          
};
//---------------------------------------------------------------------------
extern PACKAGE TFormaEnviarCorreo *FormaEnviarCorreo;
//---------------------------------------------------------------------------
#endif
