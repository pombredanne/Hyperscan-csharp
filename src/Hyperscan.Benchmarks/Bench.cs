using BenchmarkDotNet.Attributes;
using BenchmarkDotNet.Configs;
using BenchmarkDotNet.Exporters;
using BenchmarkDotNet.Exporters.Csv;
using BenchmarkDotNet.Order;

namespace Hyperscan.Benchmarks
{
    [Orderer(SummaryOrderPolicy.FastestToSlowest)]
    [ShortRunJob]
    [Config(typeof(Config))]
    [MemoryDiagnoser]
    internal class Bench
    {
        private class Config : ManualConfig
        {
            public Config()
            {
                AddExporter(CsvMeasurementsExporter.Default);
                AddExporter(RPlotExporter.Default);
                Options |= ConfigOptions.DisableOptimizationsValidator;
            }
        }

        [GlobalSetup]
        public void Setup()
        {
        }

        [Benchmark(Baseline = true, Description = "Some bench")]
        public void Some_Bench()
        {
        }
    }
}