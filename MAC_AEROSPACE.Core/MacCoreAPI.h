#pragma once

// Parches de compatibilidad para evitar advertencias molestas
#pragma warning(push)
#pragma warning(disable: 4996) 
#pragma warning(disable: 4251) 

// Macro de Exportación (Vital para que C# lo vea)
#ifdef MAC_AEROSPACE_CORE_EXPORTS
#define MAC_CORE_API __declspec(dllexport)
#else
#define MAC_CORE_API __declspec(dllimport)
#endif

// Includes de Open CASCADE
#include <AIS_InteractiveContext.hxx>
#include <V3d_View.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <WNT_Window.hxx> 

// La Clase Principal
class MAC_CORE_API CadKernelSession {
public:
    CadKernelSession(); // Constructor

    // Funciones del Sistema
    bool InitViewerHandle(void* windowHandle);
    void ResizeController();
    void RenderTestContext();

    // Función de Importación (¡Fíjate en el punto y coma final!)
    bool ImportStepFile(const char* path);

    // Funciones de Mouse
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