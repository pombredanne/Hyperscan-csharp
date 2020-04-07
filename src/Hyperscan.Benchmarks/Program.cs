using BenchmarkDotNet.Running;

namespace Hyperscan.Benchmarks
{
    class Program
    {
        static void Main(string[] args)
        {
            BenchmarkRunner.Run<Bench>();
        }
    }
}
