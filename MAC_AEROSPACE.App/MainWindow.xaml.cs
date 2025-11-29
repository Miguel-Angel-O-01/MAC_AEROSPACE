using System.Windows;

namespace MAC_AEROSPACE.App
{
    // ESTA ES LA VENTANA PRINCIPAL (SOLO CONTROLA LA UI GENERAL)
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        // Evento temporal del botón (luego moveremos esto a un Command en MVVM)
        private void BtnCargar_Click(object sender, RoutedEventArgs e)
        {
            // Forzar repintado si es necesario
            if (View3D != null)
            {
                View3D.Width = View3D.ActualWidth + 0.1;
                View3D.Width = View3D.ActualWidth - 0.1;
            }
        }
    }
}