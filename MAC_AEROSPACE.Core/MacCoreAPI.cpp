#include "MacCoreAPI.h"
#include <BRepPrimAPI_MakeBox.hxx>
#include <AIS_Shape.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <Aspect_Handle.hxx>

// --- CONSTRUCTOR ---
MotorDeIngenieria::MotorDeIngenieria() {
    // Vacío
}

// --- INICIALIZAR ---
bool MotorDeIngenieria::InicializarVentana(void* windowHandle) {
    try {
        Handle(Aspect_DisplayConnection) dConnection = new Aspect_DisplayConnection();
        m_graphicDriver = new OpenGl_GraphicDriver(dConnection);

        m_viewer = new V3d_Viewer(m_graphicDriver);
        m_viewer->SetDefaultLights();
        m_viewer->SetLightOn();

        m_context = new AIS_InteractiveContext(m_viewer);
        m_view = m_viewer->CreateView();

        Aspect_Handle hWindow = (Aspect_Handle)windowHandle;
        Handle(WNT_Window) wntWindow = new WNT_Window(hWindow);

        m_view->SetWindow(wntWindow);
        if (!wntWindow->IsMapped()) wntWindow->Map();

        m_view->SetBackgroundColor(Quantity_TOC_RGB, 0.2, 0.2, 0.2); // Gris oscuro
        m_view->MustBeResized();
        return true;
    }
    catch (...) { return false; }
}

// --- REDIMENSIONAR ---
void MotorDeIngenieria::Redimensionar() {
    if (!m_view.IsNull()) {
        m_view->MustBeResized();
        m_view->Redraw();
    }
}

// --- DIBUJAR CUBO ---
void MotorDeIngenieria::DibujarCuboPrueba() {
    if (m_context.IsNull()) return;
    TopoDS_Shape caja = BRepPrimAPI_MakeBox(100.0, 100.0, 100.0).Shape();
    Handle(AIS_Shape) cajaVis = new AIS_Shape(caja);

    cajaVis->SetMaterial(Graphic3d_NOM_GOLD);

    m_context->Display(cajaVis, Standard_True);
    m_view->FitAll();
}

// --- AQUÍ EMPIEZAN LAS FUNCIONES NUEVAS (FUERA DE LAS ANTERIORES) ---

void MotorDeIngenieria::MoverMouse(int x, int y) {
    if (!m_context.IsNull()) {
        m_context->MoveTo(x, y, m_view, Standard_True);
    }
}

void MotorDeIngenieria::IniciarRotacion(int x, int y) {
    if (!m_view.IsNull()) {
        m_view->StartRotation(x, y);
    }
}

void MotorDeIngenieria::Rotar(int x, int y) {
    if (!m_view.IsNull()) {
        m_view->Rotation(x, y);
    }
}

void MotorDeIngenieria::Zoom(int x, int y) {
    if (!m_view.IsNull()) {
        m_view->Zoom(0, 0, x, y);
    }
}

void MotorDeIngenieria::Pan(int x, int y) {
    if (!m_view.IsNull()) {
        m_view->Pan(x, y);
    }
}