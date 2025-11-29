#include "OcctProxy.h"

namespace MacAerospace {
    namespace Interop {

        // Constructor
        OcctProxy::OcctProxy() {
            m_nativeEngine = new CadKermelSession();
        }

        // Destructor
        OcctProxy::~OcctProxy() {
            this->!OcctProxy();
        }

        // Finalizador
        OcctProxy::!OcctProxy() {
            if (m_nativeEngine != nullptr) {
                delete m_nativeEngine;
                m_nativeEngine = nullptr;
            }
        }

        // --- MÉTODOS EXISTENTES ---

        bool OcctProxy::InitViewer(IntPtr windowHandle) {
            if (!m_nativeEngine) return false;
            return m_nativeEngine->InitViewerHandle(windowHandle.ToPointer());
        }

        void OcctProxy::Resize() {
            if (m_nativeEngine) m_nativeEngine->ResizeController();
        }

        void OcctProxy::DrawCube() {
            if (m_nativeEngine) m_nativeEngine->RenderTestContext();
        }

        // --- MÉTODOS DE INPUT (MOUSE) ---

        void OcctProxy::MoveTo(int x, int y) {
            if (m_nativeEngine) m_nativeEngine->OnMouseMove(x, y);
        }

        void OcctProxy::StartRotation(int x, int y) {
            if (m_nativeEngine) m_nativeEngine->StartRotation(x, y);
        }

        void OcctProxy::Rotation(int x, int y) {
            if (m_nativeEngine) m_nativeEngine->DoRotation(x, y);
        }

        void OcctProxy::Zoom(int x, int y) {
            if (m_nativeEngine) m_nativeEngine->DoZoom(x, y);
        }

        void OcctProxy::Pan(int x, int y) {
            if (m_nativeEngine) m_nativeEngine->DoPan(x, y);
        }
    }
}