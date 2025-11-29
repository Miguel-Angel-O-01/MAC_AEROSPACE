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

class MAC_CORE_API CadKermelSession {
public:
    CadKermelSession();

    bool InitViewerHandle(void* windowHandle);
    void ResizeController();
    void RenderTestContext();

    // --- NUEVAS FUNCIONES DE MOUSE (Faltaban aquí) ---
    void OnMouseMove(int x, int y);
    void StartRotation(int x, int y);
    void DoRotation(int x, int y);
    void DoZoom(int x, int y);
    void DoPan(int x, int y);

private:
    Handle(V3d_Viewer) m_viewer;
    Handle(V3d_View) m_view;
    Handle(AIS_InteractiveContext) m_context;
    Handle(OpenGl_GraphicDriver) m_graphicDriver;
};

#pragma warning(pop)