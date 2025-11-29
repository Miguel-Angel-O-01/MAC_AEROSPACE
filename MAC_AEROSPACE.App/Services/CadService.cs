#nullable disable

using System;
using MAC_AEROSPACE.Interop; // Nuestro Wrapper C++/CLI

namespace MAC_AEROSPACE.App.Services
{
    public class CadService : ICadService, IDisposable
    {
        private CadSessionProxy _proxy;

        public CadService()
        {
            _proxy = new CadSessionProxy(); // Aquí nace el motor C++
        }

        public bool InitializeViewer(IntPtr windowHandle)
        {
            return _proxy.InitViewer(windowHandle);
        }

        public void Resize() => _proxy.Resize();
        public void RenderTest() => _proxy.DrawCube();

        public void OnMouseMove(int x, int y) => _proxy.OnMouseMove(x, y);
        public void StartRotation(int x, int y) => _proxy.StartRotation(x, y);
        public void DoRotation(int x, int y) => _proxy.DoRotation(x, y);

        public void Dispose()
        {
            _proxy?.Dispose();
            _proxy = null;
        }
    }
}