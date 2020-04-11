﻿using System;
using System.Collections.Generic;
using System.Reactive.Concurrency;
using System.Reactive.Linq;
using System.Threading;
using System.Threading.Tasks;
using Hyperscan.Compilation;
using Hyperscan.Core;
using Hyperscan.Databases;
using Hyperscan.Extensions.Utils;

namespace Hyperscan.Sample
{
    class Program
    {
        static async Task Main(string[] args)
        {
            var engineBuilder = new EngineBuilder();
            //engineBuilder.WithDatabase(() => new Database(@"PATH_TO_SERIALIZED_DB"));
            engineBuilder.WithDatabase(() => new Database());
            engineBuilder.WithCompiler(() => new SimpleCompiler(new Expression(0, "foo(?i)bar(?-i)baz", ExpressionFlag.HsFlagUtf8 | ExpressionFlag.HsFlagDotall), CompilerMode.HsModeBlock));
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
                    ex => Console.WriteLine("Error: {0}", ex.Message),
                    () => Console.WriteLine("Scan completed."));
            //await engine.Database.SerializeToFileAsync(@"PATH_TO_SERIALIZED_DB");
            while (true)
            {
                await engine.ScanAsync("foobarbazbazbaz", CancellationToken.None);
                await Task.Delay(1);
            }
        }
    }
}