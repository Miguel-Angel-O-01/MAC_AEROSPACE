#pragma once
#include "MacCoreAPI.h" // Enlace con el Core

using namespace System;

namespace MacAerospace {
    namespace Interop {

        public ref class OcctProxy
        {
        public:
            OcctProxy();
            ~OcctProxy();
            !OcctProxy();

            bool InitViewer(IntPtr windowHandle);
            void Resize();
            void DrawCube();

            // --- NUEVAS FUNCIONES DE MOUSE PARA C# ---
            void MoveTo(int x, int y);
            void StartRotation(int x, int y);
            void Rotation(int x, int y);
            void Zoom(int x, int y);
            void Pan(int x, int y);

        private:
            CadKermelSession* m_nativeEngine;
        };
    }
}
