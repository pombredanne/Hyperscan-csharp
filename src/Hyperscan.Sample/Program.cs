﻿using System;
using System.Collections.Generic;
using System.Reactive.Linq;
using Hyperscan.Compilation;
using Hyperscan.Core;
using Hyperscan.Databases;
using Hyperscan.Extensions;

namespace Hyperscan.Sample
{
    class Program
    {
        static void Main(string[] args)
        {
            using var engine = new HyperscanEngine(() => new Database(), () => new Compiler("foo(?i)bar(?-i)baz"));
            using var matchSubscription = engine.OnMatch
                .Do(match =>
                {
                    var input = match.Input.Read();
                    Console.Write($"New match for input \"{input}\" with pattern \"{match.Pattern}\": ");
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

            engine.Scan("foobarbazbazbaz");
        }
    }
}