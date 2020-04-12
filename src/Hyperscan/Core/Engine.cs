using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Channels;
using System.Threading.Tasks;
using Hyperscan.Compilation;
using Hyperscan.Databases;
using Hyperscan.Queuing;
using Hyperscan.Scanning;
using Microsoft.Extensions.Logging;

namespace Hyperscan.Core
{
    public class Engine : HyperscanEngine, IEngine
    {
        private bool _disposed;
        private readonly ChannelQueuing<string> _queuing;
        private readonly CancellationTokenSource _cancellationTokenSource = new CancellationTokenSource();
        private readonly ILogger _logger;

        internal Engine(ILogger logger, Func<Database> databaseFactory, Func<Compiler> compilerFactory) : base(databaseFactory, compilerFactory)
        {
            _logger = logger;
            InputConsumers = new HashSet<InputConsumer>();
            _queuing = new ChannelQueuing<string>(new BoundedChannelOptions(Environment.ProcessorCount));
            foreach (var _ in Enumerable.Range(0, Environment.ProcessorCount))
            {
                var scanner = CreateScanner();
                var inputConsumer = new InputConsumer(_logger, _queuing.Consumer, scanner);
                inputConsumer.Consume(_cancellationTokenSource.Token);
                InputConsumers.Add(inputConsumer);
            }
        }

        internal ISet<InputConsumer> InputConsumers { get; }

        public ValueTask ScanAsync(string input, CancellationToken cancellationToken)
        {
            return _queuing.Producer.ProduceAsync(input, cancellationToken);
        }

        public ValueTask DisposeAsync()
        {
            return DisposeAsync(true);
        }

        protected virtual ValueTask DisposeAsync(bool disposing)
        {
            if (_disposed)
                return new ValueTask();

            if (disposing)
            {
                _cancellationTokenSource.Cancel();
                foreach (var inputConsumer in InputConsumers)
                {
                    inputConsumer.Dispose();
                }

                base.Dispose();
            }

            _disposed = true;
            return new ValueTask();
        }
    }
}