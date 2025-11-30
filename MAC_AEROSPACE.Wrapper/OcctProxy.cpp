#include <Windows.h>
#include "OcctProxy.h"
#include <string>
#include <iostream>
using namespace System;
using namespace System::Runtime::InteropServices;


namespace MAC_AEROSPACE {
    namespace Interop {

        // Constructor
        CadSessionProxy::CadSessionProxy() {
            m_nativeEngine = new CadKermelSession();
        }

        // Destructor
        CadSessionProxy::~CadSessionProxy() {
            this->!CadSessionProxy();
        }

        // Finalizador
        CadSessionProxy::!CadSessionProxy() {
            if (m_nativeEngine != nullptr) {
                delete m_nativeEngine;
                m_nativeEngine = nullptr;
            }
        }

        // --- MÉTODOS EXISTENTES ---

        bool CadSessionProxy::InitViewer(IntPtr windowHandle) {
            if (!m_nativeEngine) return false;
            return m_nativeEngine->InitViewerHandle(windowHandle.ToPointer());
        }

        void CadSessionProxy::Resize() {
            if (m_nativeEngine) m_nativeEngine->ResizeController();
        }

        void CadSessionProxy::DrawCube() {
            if (m_nativeEngine) m_nativeEngine->RenderTestContext();
        }

        // --- MÉTODOS DE INPUT (MOUSE) ---

        void CadSessionProxy::OnMouseMove(int x, int y) {
            if (m_nativeEngine) m_nativeEngine->OnMouseMove(x, y);
        }

        void CadSessionProxy::StartRotation(int x, int y) {
            if (m_nativeEngine) m_nativeEngine->StartRotation(x, y);
        }

        void CadSessionProxy::DoRotation(int x, int y) {
            if (m_nativeEngine) m_nativeEngine->DoRotation(x, y);
        }

        void CadSessionProxy::Zoom(int x, int y) {
            if (m_nativeEngine) m_nativeEngine->DoZoom(x, y);
        }

        void CadSessionProxy::Pan(int x, int y) {
            if (m_nativeEngine) m_nativeEngine->DoPan(x, y);
        }

        bool CadSessionProxy::ImportStep(System::String^ path) {
            if (!m_nativeEngine) return false;

            // Conversión manual segura de .NET String a std::string
            const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(path)).ToPointer();
            std::string stdPath = chars;
            Marshal::FreeHGlobal(IntPtr((void*)chars)); // Liberar memoria

            return m_nativeEngine->ImportStepFile(stdPath.c_str());
        }
    }
}