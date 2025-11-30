using System;

namespace MAC_AEROSPACE.App.Services
{
    // Esta interfaz define QUÉ puede hacer el motor CAD, sin importar CÓMO lo hace.
    public interface ICadService
    {
        bool InitializeViewer(IntPtr windowHandle);
        bool LoadStep(string path);
        void Resize();
        void RenderTest();

        // Input
        void OnMouseMove(int x, int y);
        void StartRotation(int x, int y);
        void DoRotation(int x, int y);
        // ... aquí irán LoadStep, etc.
    }
}
