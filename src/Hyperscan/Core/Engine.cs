using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Channels;
using System.Threading.Tasks;
using Hyperscan.Compilation;
using Hyperscan.Databases;
using Hyperscan.Logging;
using Hyperscan.Queuing;
using Hyperscan.Scanning;
using Microsoft.Extensions.Logging;

namespace Hyperscan.Core
{
    /// <summary>
    /// Hyperscan engine
    /// </summary>
    public class Engine : HyperscanEngine, IEngine
    {
        private bool _disposed;
        private readonly ChannelQueuing<string> _queuing;
        private readonly CancellationTokenSource _cancellationTokenSource = new CancellationTokenSource();
        private readonly ILogger _logger;

        /// <summary>
        /// Contructor
        /// </summary>
        /// <param name="logger"><see cref="ILogger{TCategoryName}"/></param>
        /// <param name="databaseFactory">The database factory</param>
        /// <param name="compilerFactory">The compiler factory</param>
        internal Engine(ILogger logger, Func<Database> databaseFactory, Func<Compiler> compilerFactory) : base(new Logger(trace => logger.LogTrace(trace), debug => logger.LogDebug(debug), info => logger.LogInformation(info), warning => logger.LogWarning(warning), error => logger.LogError(error), critical => logger.LogCritical(critical)), databaseFactory, compilerFactory)
        {
            _logger = logger;
            _queuing = new ChannelQueuing<string>(new BoundedChannelOptions(Environment.ProcessorCount));
            InputConsumers = new HashSet<InputConsumer>();
            foreach (var _ in Enumerable.Range(0, Environment.ProcessorCount))
            {
                var scanner = CreateScanner();
                var inputConsumer = new InputConsumer(_logger, _queuing.Consumer, scanner);
                inputConsumer.Consume(_cancellationTokenSource.Token);
                InputConsumers.Add(inputConsumer);
            }
        }

        /// <summary>
        /// Get the internal consumers
        /// </summary>
        internal ISet<InputConsumer> InputConsumers { get; }

        /// <summary>
        /// Trigger the scan of an input asynchronously
        /// </summary>
        /// <param name="input">The input</param>
        /// <param name="cancellationToken"><see cref="CancellationToken"/></param>
        /// <returns><see cref="ValueTask"/></returns>
        public ValueTask ScanAsync(string input, CancellationToken cancellationToken)
        {
            return _queuing.Producer.ProduceAsync(input, cancellationToken);
        }

        /// <summary>
        /// Dispose pattern
        /// </summary>
        /// <returns><see cref="ValueTask"/></returns>
        public ValueTask DisposeAsync()
        {
            return DisposeAsync(true);
        }

        /// <summary>
        /// Dispose
        /// </summary>
        /// <param name="disposing">If disposing</param>
        /// <returns><see cref="ValueTask"/></returns>
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