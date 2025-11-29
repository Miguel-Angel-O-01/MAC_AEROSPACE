#pragma once

// Parches de compatibilidad OCCT
#pragma warning(push)
#pragma warning(disable: 4996) 
#pragma warning(disable: 4251) 

#ifdef MAC_AEROSPACE_CORE_EXPORTS
#define MAC_CORE_API __declspec(dllexport)
#else
#define MAC_CORE_API __declspec(dllimport)
#endif

#include <AIS_InteractiveContext.hxx>
#include <V3d_View.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <WNT_Window.hxx> 

class MAC_CORE_API MotorDeIngenieria {
public:
    MotorDeIngenieria();

    bool InicializarVentana(void* windowHandle);
    void Redimensionar();
    void DibujarCuboPrueba();

    // --- NUEVAS FUNCIONES DE MOUSE (Faltaban aquí) ---
    void MoverMouse(int x, int y);
    void IniciarRotacion(int x, int y);
    void Rotar(int x, int y);
    void Zoom(int x, int y);
    void Pan(int x, int y);

private:
    Handle(V3d_Viewer) m_viewer;
    Handle(V3d_View) m_view;
    Handle(AIS_InteractiveContext) m_context;
    Handle(OpenGl_GraphicDriver) m_graphicDriver;
};

#pragma warning(pop)