using System;
using Hyperscan.Compilation;
using Hyperscan.Core;

namespace Hyperscan.Sample
{
    class Program
    {
        static void Main(string[] args)
        {
            IDisposable matchSubscription = null;
            using var engine = new HyperscanEngine((_, matchObservable) =>
            {
                matchSubscription = matchObservable
                    .Subscribe(match => Console.WriteLine($"New match (Id: {match.Id}) found: {match.Result}."),
                        ex => Console.WriteLine("Error: {0}", ex.Message),
                        () => Console.WriteLine("Scan completed."));

                return new Compiler(_, "^Blah");
            });

            engine.Scan("Blah blah hello Benjamin! blah");
            engine.Scan("Blah blah hello Benjamin! blah");
            engine.Scan("Blah blah hello Benjamin! blah");
            engine.Scan("Blah blah hello Benjamin! blah");
            matchSubscription.Dispose();
        }
    }
}