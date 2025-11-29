#nullable disable
using MAC_AEROSPACE.App.Views;
using MAC_AEROSPACE.App.Services;
using MAC_AEROSPACE.App.ViewModels;
using Microsoft.Extensions.DependencyInjection;
using System.Windows;

namespace MAC_AEROSPACE.App
{
    public partial class App : Application
    {
        // El contenedor de servicios (nuestra caja de herramientas global)
        public static IServiceProvider CurrentServiceProvider { get; private set; }

        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            // 1. Configurar los servicios
            var serviceCollection = new ServiceCollection();
            ConfigureServices(serviceCollection);

            // 2. Construir el proveedor
            CurrentServiceProvider = serviceCollection.BuildServiceProvider();

            // 3. Arrancar la ventana principal manualmente
            // El contenedor se encarga de crearla e inyectarle lo que necesite
            var mainWindow = CurrentServiceProvider.GetRequiredService<MAC_AEROSPACE.App.Views.MainWindow>();
            mainWindow.Show();
        }

        private void ConfigureServices(IServiceCollection services)
        {
            // --- CAPA DE SERVICIOS (Infraestructura) ---
            // Registramos CadService como "Singleton" (una única instancia para toda la app)
            // porque solo podemos tener un motor gráfico corriendo a la vez.
            services.AddSingleton<ICadService, CadService>();

            // --- CAPA DE VIEWMODELS (Lógica) ---
            // Registramos el ViewModel principal
            services.AddTransient<MainViewModel>();

            // --- CAPA DE VISTAS (UI) ---
            // Registramos la ventana principal
            services.AddTransient<MAC_AEROSPACE.App.Views.MainWindow>();
        }

        protected override void OnExit(ExitEventArgs e)
        {
            // Limpieza final al cerrar la app
            if (CurrentServiceProvider is IDisposable disposable)
            {
                disposable.Dispose();
            }
            base.OnExit(e);
        }
    }
}
