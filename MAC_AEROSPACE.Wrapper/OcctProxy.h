#pragma once
#include "MacCoreAPI.h" // Enlace con el Core

using namespace System;

namespace MAC_AEROSPACE {
    namespace Interop {

        public ref class CadSessionProxy
        {
        public:
            CadSessionProxy();
            ~CadSessionProxy();
            !CadSessionProxy();

            bool InitViewer(IntPtr windowHandle);
            void Resize();
            void DrawCube();

            // --- NUEVAS FUNCIONES DE MOUSE PARA C# ---
            void OnMouseMove(int x, int y);
            void StartRotation(int x, int y);
            void DoRotation(int x, int y);
            void Zoom(int x, int y);
            void Pan(int x, int y);

        private:
            CadKermelSession* m_nativeEngine;
        };
    }
}
