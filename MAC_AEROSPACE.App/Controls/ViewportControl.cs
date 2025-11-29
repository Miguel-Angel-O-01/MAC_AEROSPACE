#nullable disable
using MAC_AEROSPACE.Interop;
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Input; // Necesario para MouseEventArgs
using System.Windows.Interop;

namespace MAC_AEROSPACE.App.Controls
{
    public class ViewportControl : HwndHost
    {
        private CadSessionProxy _proxy;
        private nint _hWnd;

        // Variable para guardar la posición del mouse
        private Point _lastPos;

        private const int WS_CHILD = 0x40000000;
        private const int WS_VISIBLE = 0x10000000;
        private const int WS_CLIPCHILDREN = 0x02000000;

        public ViewportControl() { }

        protected override HandleRef BuildWindowCore(HandleRef hwndParent)
        {
            try
            {
                _hWnd = CreateWindowEx(0, "static", "",
                    WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
                    0, 0, (int)ActualWidth, (int)ActualHeight,
                    hwndParent.Handle, nint.Zero, nint.Zero, nint.Zero);

                if (_proxy == null)
                {
                    _proxy = new CadSessionProxy();
                    _proxy.InitViewer(_hWnd);
                    _proxy.DrawCube();
                }
                return new HandleRef(this, _hWnd);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error crítico:\n" + ex.ToString());
                return new HandleRef(this, nint.Zero);
            }
        }

        protected override void DestroyWindowCore(HandleRef hwnd)
        {
            if (_proxy != null) { _proxy.Dispose(); _proxy = null; }
            DestroyWindow(hwnd.Handle);
        }

        protected override void OnRenderSizeChanged(SizeChangedInfo sizeInfo)
        {
            base.OnRenderSizeChanged(sizeInfo);
            if (_proxy != null) _proxy.Resize();
        }

        protected override IntPtr WndProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            // --- Constantes Win32 ---
            const int WM_PAINT = 0x000F;
            const int WM_SIZE = 0x0005;
            const int WM_ERASEBKGND = 0x0014;
            const int WM_NCHITTEST = 0x0084; // <--- EL MENSAJE CLAVE
            const int WM_RBUTTONDOWN = 0x0204;
            const int WM_MOUSEMOVE = 0x0200;

            // Constantes de retorno
            const int HTCLIENT = 1; // "Estoy en el área del cliente"

            // --- LÓGICA ---
            switch (msg)
            {
                case WM_NCHITTEST:
                    // Truco Maestro: Le decimos a Windows "El mouse está sobre mí".
                    // Esto obliga a que se generen los eventos de MouseMove y Click.
                    handled = true;
                    return (IntPtr)HTCLIENT;

                case WM_PAINT:
                    if (_proxy != null) _proxy.Resize();
                    ValidateRect(hwnd, IntPtr.Zero);
                    handled = true;
                    break;

                case WM_SIZE:
                    if (_proxy != null) _proxy.Resize();
                    break;

                case WM_ERASEBKGND:
                    handled = true; // Evita parpadeo
                    return IntPtr.Zero;

                // --- INPUT ---

                case WM_RBUTTONDOWN:
                    // Extraemos coordenadas (Safe x64)
                    long paramDown = lParam.ToInt64();
                    int xDown = (short)(paramDown & 0xFFFF);
                    int yDown = (short)((paramDown >> 16) & 0xFFFF);

                    if (_proxy != null) _proxy.StartRotation(xDown, yDown);

                    // Importante: Capturar el mouse para no perder el arrastre si te sales de la ventana
                    // (Podemos implementarlo después con SetCapture, pero por ahora esto basta)
                    break;

                case WM_MOUSEMOVE:
                    // Verificamos si el botón derecho está presionado (Máscara 0x0002)
                    if ((wParam.ToInt64() & 0x0002) != 0)
                    {
                        long paramMove = lParam.ToInt64();
                        int xMove = (short)(paramMove & 0xFFFF);
                        int yMove = (short)((paramMove >> 16) & 0xFFFF);

                        if (_proxy != null) _proxy.DoRotation(xMove, yMove);
                    }
                    break;
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
                _proxy.DoRotation((int)pos.X, (int)pos.Y);
            }
            else
            {
                _proxy.OnMouseMove((int)pos.X, (int)pos.Y);
            }
        }

        // --- P/INVOKE ---
        [DllImport("user32.dll", EntryPoint = "CreateWindowEx", CharSet = CharSet.Auto)]
        private static extern nint CreateWindowEx(int dwExStyle, string lpszClassName, string lpszWindowName, int style, int x, int y, int width, int height, nint hwndParent, nint hMenu, nint hInst, nint pvParam);

        [DllImport("user32.dll", EntryPoint = "DestroyWindow", CharSet = CharSet.Auto)]
        private static extern bool DestroyWindow(nint hwnd);
        [DllImport("user32.dll")]
        private static extern bool ValidateRect(IntPtr hwnd, IntPtr lpRect);

    } 
} 