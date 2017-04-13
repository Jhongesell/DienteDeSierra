// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en trámite 1999-2000
// Revisión  1.1-A


//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("Sawtooth.res");
USEFORM("VentanaPrincipal.cpp", FormaPrincipal);
USEUNIT("FuncionDisparo.cpp");
USEUNIT("DefiniciónEcuación.cpp");
USEUNIT("Sincronizaciones.cpp");
USEUNIT("NumeroRotacion.cpp");
USEUNIT("ExponenteLyapunov.cpp");
USEFORM("VentanaBifurcaciones.cpp", FormaBifurcaciones);
USEFORM("VentanaCirculo.cpp", FormaCirculo);
USEFORM("VentanaToro.cpp", FormaToro);
USEFORM("VentanaCurvasIntegrales.cpp", FormaCurvasIntegrales);
USEFORM("VentanaLevantamientos.cpp", FormaLevantamientos);
USEFORM("Acecade.cpp", VAcercaDe);
USEFORM("ParamBifurcaciones.cpp", VCap_Bifurcaciones);
USEFORM("ParamToro.cpp", VCap_Toro);
USEFORM("ParamCurvasIntegrales.cpp", VCap_CIntegrales);
USEFORM("ParamLevantamientos.cpp", VCap_Levantamientos);
USEFORM("ParamCirculo.cpp", VCap_Circunferencia);
USEFORM("ParamGlobales.cpp", VCap_General);
USEUNIT("..\Libreria\V_pixel.cpp");
USEFORM("..\Libreria\FORMAS\Ayuda.cpp", AyudaForm);
USEFORM("..\Libreria\FORMAS\Editor.cpp", EditorForm);
USEUNIT("..\Libreria\ctrl_l_a.cpp");
USEUNIT("..\Libreria\Cadenas.cpp");
USEUNIT("..\Libreria\Fechas.cpp");
USEUNIT("..\Libreria\fechora.cpp");
USEUNIT("..\Libreria\Man_arch.cpp");
USEUNIT("..\Libreria\Tiempo.cpp");
USEFORM("VentanaLenguas.cpp", FormaLenguas);
USEFORM("..\Libreria\FORMAS\ACX-WebBrowser.cpp", FormaWebBrowzer);
USEFORM("..\Libreria\FORMAS\EnviarCorreo.cpp", FormaEnviarCorreo);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "";
                 Application->CreateForm(__classid(TFormaPrincipal), &FormaPrincipal);
                 Application->CreateForm(__classid(TFormaEnviarCorreo), &FormaEnviarCorreo);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------

