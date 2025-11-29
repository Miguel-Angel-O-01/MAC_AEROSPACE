#include "OcctProxy.h"

namespace MacAerospace {
    namespace Wrapper {

        // Constructor
        OcctProxy::OcctProxy() {
            m_nativeEngine = new MotorDeIngenieria();
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
            return m_nativeEngine->InicializarVentana(windowHandle.ToPointer());
        }

        void OcctProxy::Resize() {
            if (m_nativeEngine) m_nativeEngine->Redimensionar();
        }

        void OcctProxy::DrawCube() {
            if (m_nativeEngine) m_nativeEngine->DibujarCuboPrueba();
        }

        // --- MÉTODOS DE INPUT (MOUSE) ---

        void OcctProxy::MoveTo(int x, int y) {
            if (m_nativeEngine) m_nativeEngine->MoverMouse(x, y);
        }

        void OcctProxy::StartRotation(int x, int y) {
            if (m_nativeEngine) m_nativeEngine->IniciarRotacion(x, y);
        }

        void OcctProxy::Rotation(int x, int y) {
            if (m_nativeEngine) m_nativeEngine->Rotar(x, y);
        }

        void OcctProxy::Zoom(int x, int y) {
            if (m_nativeEngine) m_nativeEngine->Zoom(x, y);
        }

        void OcctProxy::Pan(int x, int y) {
            if (m_nativeEngine) m_nativeEngine->Pan(x, y);
        }
    }
}