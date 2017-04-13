//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "EnviarCorreo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormaEnviarCorreo *FormaEnviarCorreo;
//---------------------------------------------------------------------------
__fastcall TFormaEnviarCorreo::TFormaEnviarCorreo(TComponent* Owner) : TForm(Owner)
{
   To[0] = 0;
   Subject[0] = 0;
   Numero_archivos = 0;
   Nombres_archivos = NULL;
}


// Al conectarse intenta enviar el mensage
void __fastcall TFormaEnviarCorreo::NMSMTP1Connect(TObject *Sender)
{
   NMSMTP1->PostMessage->FromAddress = EditFrom->Text;
   NMSMTP1->PostMessage->ToAddress->Add(To);
   NMSMTP1->PostMessage->Subject = Subject;
   int i, xi;
   for (i = 0; i < Editor->Lines->Count; i++) NMSMTP1->PostMessage->Body->Add(Editor->Lines->Strings[i]);
   for (i = 0; i < Numero_archivos; i++) {
      NMSMTP1->PostMessage->Body->Add("//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
      NMSMTP1->PostMessage->Body->Add("//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
      EditorAux->Lines->LoadFromFile(Nombres_archivos[i]);
      for (xi = 0; xi < EditorAux->Lines->Count; xi++) NMSMTP1->PostMessage->Body->Add(EditorAux->Lines->Strings[xi]);
   }   
   NMSMTP1->SendMail();
}


// Si la conenxion falla
void __fastcall TFormaEnviarCorreo::NMSMTP1Failure(TObject *Sender)
{
   NMSMTP1->Disconnect();     
}

// Si la conexxion falla
void __fastcall TFormaEnviarCorreo::NMSMTP1ConnectionFailed(TObject *Sender)
{
   NMSMTP1->Disconnect();     
}

// El mensaje se envio correctamente
void __fastcall TFormaEnviarCorreo::NMSMTP1Success(TObject *Sender)
{
   ShowMessage("Mail Send OK");
   Close();
}

// Intentar enviatr el mensage
void __fastcall TFormaEnviarCorreo::Button1Click(TObject *Sender)
{
   if (Editor->Lines->Count == 0) return;
   Button1->Enabled = false;
   NMSMTP1->Host = "www.dynamics.unam.edu";
   NMSMTP1->Port = 25;
   NMSMTP1->UserID = "dinamica";
   NMSMTP1->TimeOut = 5000;
   NMSMTP1->Connect();
}

// Forma de uso
/*

   TFormaEnviarCorreo *vent = new TFormaEnviarCorreo(this);
   if (vent) {
       vent->Parametros("acl@hp.fciencias.unam.mx",Application->Title.c_str());
       vent->ShowModal();
       delete vent;
   }

*/

