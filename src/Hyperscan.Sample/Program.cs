using System.Threading.Tasks;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace Hyperscan.Sample
{
    class Program
    {
        static async Task Main(string[] args)
        {
            using var host = Host.CreateDefaultBuilder(args)
                .ConfigureLogging(config => { config.AddConsole(); })
                .ConfigureServices((hostBuilderContext, services) => { services.AddHostedService<HyperscanService>(); })
                .UseConsoleLifetime(opt => opt.SuppressStatusMessages = true)
                .Build();
            await host.RunAsync();
        }
    }
}