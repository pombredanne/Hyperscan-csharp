using System;
using System.Threading;
using System.Threading.Tasks;
using Hyperscan.Queuing;
using Microsoft.Extensions.Logging;

namespace Hyperscan.Scanning
{
    /// <summary>
    /// The consumer
    /// </summary>
    internal class InputConsumer : IDisposable
    {
        private bool _disposed;
        private readonly ILogger _logger;
        private readonly Consumer<string> _consumer;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="logger"><see cref="ILogger{TCategoryName}"/></param>
        /// <param name="consumer"><see cref="Consumer{T}"/></param>
        /// <param name="scanner"><see cref="Scanner"/></param>
        public InputConsumer(ILogger logger, Consumer<string> consumer, Scanner scanner)
        {
            _logger = logger;
            _consumer = consumer;
            Scanner = scanner;
        }

        /// <summary>
        /// Consume the channel
        /// </summary>
        /// <param name="cancellationToken"></param>
        public void Consume(CancellationToken cancellationToken)
        {
            var loopTask = Task.Run(async () =>
            {
                try
                {
                    await foreach (var message in _consumer.ReadMessagesAsync(cancellationToken))
                    {
                        try
                        {
                            if (!Scanner.Scan(message))
                            {
                                _logger.LogWarning("Scan has been terminated");
                            }
                        }
                        catch (Exception ex)
                        {
                            _logger.LogError(ex, "An error has occurred while scanning.");
                        }
                    }
                }
                catch (OperationCanceledException)
                {
                }
            }, CancellationToken.None);

            loopTask.ContinueWith(
                task => _logger.LogError(task?.Exception?.GetBaseException(), "An error has occurred."),
                TaskContinuationOptions.ExecuteSynchronously |
                TaskContinuationOptions.OnlyOnFaulted);
        }

        /// <summary>
        /// The internal scanner
        /// </summary>
        internal Scanner Scanner { get; }

        /// <summary>
        /// Dispose pattern
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
        }

        /// <summary>
        /// Dispose
        /// </summary>
        /// <param name="disposing">If disposing</param>
        protected virtual void Dispose(bool disposing)
        {
            if (_disposed)
                return;

            if (disposing)
            {
                Scanner?.Dispose();
            }

            _disposed = true;
        }
    }
}