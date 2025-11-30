#include "MacCoreAPI.h" 

// Includes Geometría
#include <BRepPrimAPI_MakeBox.hxx>
#include <AIS_Shape.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <Aspect_Handle.hxx>

// Includes STEP
#include <STEPControl_Reader.hxx>
#include <TopoDS_Shape.hxx>
#include <Interface_Static.hxx>
#include <Quantity_NameOfColor.hxx> // For colors

// --- CONSTRUCTOR ---
CadKernelSession::CadKernelSession() {
    // Vacío
}

// --- INICIALIZAR ---
bool CadKernelSession::InitViewerHandle(void* windowHandle) {
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

        m_view->SetBackgroundColor(Quantity_TOC_RGB, 0.2, 0.2, 0.25);
        m_view->MustBeResized();
        return true;
    }
    catch (...) { return false; }
}

// --- REDIMENSIONAR ---
void CadKernelSession::ResizeController() {
    if (!m_view.IsNull()) {
        m_view->MustBeResized();
        m_view->Redraw();
    }
}

// --- DIBUJAR CUBO ---
void CadKernelSession::RenderTestContext() {
    if (m_context.IsNull()) return;
    TopoDS_Shape caja = BRepPrimAPI_MakeBox(100.0, 100.0, 100.0).Shape();
    Handle(AIS_Shape) cajaVis = new AIS_Shape(caja);

    cajaVis->SetMaterial(Graphic3d_NOM_GOLD);

    m_context->Display(cajaVis, Standard_True);
    m_view->FitAll();
}

// --- IMPORTAR STEP ---
bool CadKernelSession::ImportStepFile(const char* path) {
    STEPControl_Reader reader;

    IFSelect_ReturnStatus status = reader.ReadFile(path);

    if (status == IFSelect_RetDone) {
        reader.TransferRoots();
        TopoDS_Shape shape = reader.OneShape();

        Handle(AIS_Shape) newShape = new AIS_Shape(shape);
        newShape->SetDisplayMode(1);
        newShape->SetColor(Quantity_NOC_GREEN);

        m_context->RemoveAll(Standard_False);
        m_context->Display(newShape, Standard_False);

        m_view->FitAll();
        m_view->Redraw();

        return true;
    }
    return false;
}

// --- INPUT ---
void CadKernelSession::OnMouseMove(int x, int y) {
    if (!m_context.IsNull()) m_context->MoveTo(x, y, m_view, Standard_True);
}

void CadKernelSession::StartRotation(int x, int y) {
    if (!m_view.IsNull()) m_view->StartRotation(x, y);
}

void CadKernelSession::DoRotation(int x, int y) {
    if (!m_view.IsNull()) {
        m_view->Rotation(x, y);
        m_view->Redraw();
    }
}

void CadKernelSession::DoZoom(int x, int y) {
    if (!m_view.IsNull()) {
        m_view->Zoom(0, 0, x, y);
        m_view->Redraw();
    }
}

void CadKernelSession::DoPan(int x, int y) {
    if (!m_view.IsNull()) {
        m_view->Pan(x, y);
        m_view->Redraw();
    }
}