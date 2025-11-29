#nullable disable
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using MAC_AEROSPACE.App.Services;
using System.Threading.Tasks;
using System.Windows; 

namespace MAC_AEROSPACE.App.ViewModels
{
    // Heredamos de ObservableObject para que la UI se entere de los cambios
    public partial class MainViewModel : ObservableObject
    {
        // Inyección de Dependencia: El servicio CAD llega aquí automáticamente
        private readonly ICadService _cadService;

        // Propiedad para el título de la ventana
        [ObservableProperty]
        private string _windowTitle = "MAC AEROSPACE - Engineering Suite (Alpha)";

        // Constructor: Aquí recibimos el servicio
        public MainViewModel(ICadService cadService)
        {
            _cadService = cadService;
        }

        // Comando para el botón "Cargar Geometría"
        [RelayCommand]
        private void LoadGeometry()
        {
            // 1. Dibujar
            _cadService.RenderTest();

            // 2. Forzar redimensionado/repintado
            _cadService.Resize();

            MessageBox.Show("Motor Gráfico Inicializado y Cubo Renderizado.", "Status", MessageBoxButton.OK, MessageBoxImage.Information);
        }

        // Comando para "Análisis Estructural"
        [RelayCommand]
        private void RunAnalysis()
        {
            MessageBox.Show("Módulo de Análisis Estructural (FEA) - Próximamente", "Work in Progress");
        }
    }
}
