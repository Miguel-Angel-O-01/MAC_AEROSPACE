#nullable disable
using System;
using System.Runtime.InteropServices;
using System.Windows.Interop;
using System.Windows;
using System.Windows.Input; // Necesario para MouseEventArgs
using MacAerospace.Wrapper;

namespace MAC_AEROSPACE.App
{
    public class OcctViewHost : HwndHost
    {
        private OcctProxy _proxy;
        private IntPtr _hWnd;

        // Variable para guardar la posición del mouse
        private Point _lastPos;

        private const int WS_CHILD = 0x40000000;
        private const int WS_VISIBLE = 0x10000000;
        private const int WS_CLIPCHILDREN = 0x02000000;

        public OcctViewHost() { }

        protected override HandleRef BuildWindowCore(HandleRef hwndParent)
        {
            try
            {
                _hWnd = CreateWindowEx(0, "static", "",
                    WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
                    0, 0, (int)ActualWidth, (int)ActualHeight,
                    hwndParent.Handle, IntPtr.Zero, IntPtr.Zero, IntPtr.Zero);

                if (_proxy == null)
                {
                    _proxy = new OcctProxy();
                    _proxy.InitViewer(_hWnd);
                    _proxy.DrawCube();
                }
                return new HandleRef(this, _hWnd);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error crítico:\n" + ex.ToString());
                return new HandleRef(this, IntPtr.Zero);
            }
        }

        protected override void DestroyWindowCore(HandleRef hwnd)
        {
            if (_proxy != null) { _proxy.Dispose(); _proxy = null; }
            DestroyWindow(hwnd.Handle);
        }

        protected override void OnRenderSizeChanged(System.Windows.SizeChangedInfo sizeInfo)
        {
            base.OnRenderSizeChanged(sizeInfo);
            if (_proxy != null) _proxy.Resize();
        }

        protected override IntPtr WndProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            const int WM_PAINT = 0x000F;
            const int WM_SIZE = 0x0005;
            const int WM_ERASEBKGND = 0x0014;

            switch (msg)
            {
                case WM_PAINT:
                case WM_SIZE:
                    if (_proxy != null) _proxy.Resize();
                    break;
                case WM_ERASEBKGND:
                    handled = true;
                    return IntPtr.Zero;
            }
            return base.WndProc(hwnd, msg, wParam, lParam, ref handled);
        }

        // --- MÉTODOS DE INPUT (DENTRO DE LA CLASE) ---

        protected override void OnMouseDown(MouseButtonEventArgs e)
        {
            base.OnMouseDown(e);
            _lastPos = e.GetPosition(this);

            if (e.ChangedButton == MouseButton.Right)
            {
                if (_proxy != null) _proxy.StartRotation((int)_lastPos.X, (int)_lastPos.Y);
            }
        }

        protected override void OnMouseMove(MouseEventArgs e)
        {
            base.OnMouseMove(e);
            var pos = e.GetPosition(this);

            if (_proxy == null) return;

            if (e.RightButton == MouseButtonState.Pressed)
            {
                _proxy.Rotation((int)pos.X, (int)pos.Y);
            }
            else
            {
                _proxy.MoveTo((int)pos.X, (int)pos.Y);
            }
        }

        // --- P/INVOKE ---
        [DllImport("user32.dll", EntryPoint = "CreateWindowEx", CharSet = CharSet.Auto)]
        private static extern IntPtr CreateWindowEx(int dwExStyle, string lpszClassName, string lpszWindowName, int style, int x, int y, int width, int height, IntPtr hwndParent, IntPtr hMenu, IntPtr hInst, IntPtr pvParam);

        [DllImport("user32.dll", EntryPoint = "DestroyWindow", CharSet = CharSet.Auto)]
        private static extern bool DestroyWindow(IntPtr hwnd);

    } // <--- CIERRE DE LA CLASE
} // <--- CIERRE DEL NAMESPACE