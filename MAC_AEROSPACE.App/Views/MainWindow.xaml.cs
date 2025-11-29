#nullable disable
using System.Windows;
using MAC_AEROSPACE.App.ViewModels; // Asegúrate de importar esto

namespace MAC_AEROSPACE.App.Views
{
    public partial class MainWindow : Window
    {
        // Constructor con INYECCIÓN DE DEPENDENCIAS
        // El contenedor nos pasa el ViewModel automáticamente al crear la ventana
        public MainWindow(MainViewModel viewModel)
        {
            InitializeComponent();

            // CONEXIÓN CLAVE: Asignamos el ViewModel como contexto de datos
            DataContext = viewModel;
        }
    }
}