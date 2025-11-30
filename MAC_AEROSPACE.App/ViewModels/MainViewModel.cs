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

        [RelayCommand]
        private void LoadGeometry()
        {
            // Usamos el diálogo de archivos de Microsoft
            var openFileDialog = new Microsoft.Win32.OpenFileDialog
            {
                Filter = "STEP Files (*.stp;*.step)|*.stp;*.step|All files (*.*)|*.*",
                Title = "Importar Geometría Aeroespacial"
            };

            if (openFileDialog.ShowDialog() == true)
            {
                string path = openFileDialog.FileName;
                bool success = _cadService.LoadStep(path);

                if (success)
                    MessageBox.Show("Modelo importado correctamente.", "Éxito", MessageBoxButton.OK, MessageBoxImage.Information);
                else
                    MessageBox.Show("Error al leer el archivo STEP.", "Falla Crítica", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
            // Comando para "Análisis Estructural"
        [RelayCommand]
        private void RunAnalysis()
        {
            MessageBox.Show("Módulo de Análisis Estructural (FEA) - Próximamente", "Work in Progress");
        }
    }
}
