using System;
using System.Collections.Generic;
using System.Reactive.Concurrency;
using System.Reactive.Linq;
using System.Threading;
using System.Threading.Tasks;
using Hyperscan.Compilation;
using Hyperscan.Core;
using Hyperscan.Databases;
using Hyperscan.Extensions.Utils;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace Hyperscan.Sample
{
    internal class HyperscanService : BackgroundService
    {
        private readonly ILoggerFactory _loggerFactory;

        public HyperscanService(ILoggerFactory loggerFactory)
        {
            _loggerFactory = loggerFactory;
        }

        protected override async Task ExecuteAsync(CancellationToken stoppingToken)
        {
            var engineBuilder = new EngineBuilder();
            engineBuilder.WithLogger(_loggerFactory.CreateLogger("Hyperscan"));
            engineBuilder.WithDatabase(() => new Database());
            engineBuilder.WithCompiler(() => new MultipleCompiler(new List<Expression>
            {
                new Expression("foo(?i)bar(?-i)baz", ExpressionFlag.HsFlagCaseless),
                new Expression("foo", ExpressionFlag.HsFlagCaseless | ExpressionFlag.HsFlagUtf8),
                new Expression("foo(?i)bar", ExpressionFlag.HsFlagCaseless | ExpressionFlag.HsFlagDotall)
            }, CompilerMode.HsModeBlock));
            await using var engine = engineBuilder.Build();
            using var matchSubscription = engine.OnMatch
                .ObserveOn(new EventLoopScheduler())
                .Do(match =>
                {
                    var input = match.Input.Read();
                    Console.Write($"New match for input \"{input}\" with pattern \"{match.Expression.Pattern}\": ");
                    var matchQueue = new Queue<char>();
                    Console.BackgroundColor = ConsoleColor.Green;
                    foreach (var c in match.FullMatch)
                    {
                        matchQueue.Enqueue(c);
                        Console.Write(c);
                    }

                    Console.BackgroundColor = ConsoleColor.Red;
                    foreach (var current in input)
                    {
                        if (matchQueue.TryPeek(out var matched) && matched == current)
                        {
                            matchQueue.Dequeue();
                            continue;
                        }

                        Console.Write(current);
                    }

                    matchQueue.Clear();
                    Console.ResetColor();
                    Console.Write(Environment.NewLine);
                })
                .Subscribe(match => { },
                    ex => { },
                    () => { });
            await engine.ScanAsync("foofoobarbazbazbaz", stoppingToken);
            await Task.Delay(-1, stoppingToken);
        }
    }
}