using System;
using System.Threading;
using System.Threading.Tasks;
using Hyperscan.Queuing;
using Microsoft.Extensions.Logging;

namespace Hyperscan.Scanning
{
    internal class InputConsumer : IDisposable
    {
        private readonly ILogger _logger;
        private readonly Consumer<string> _consumer;

        public InputConsumer(ILogger logger, Consumer<string> consumer, Scanner scanner)
        {
            _logger = logger;
            _consumer = consumer;
            Scanner = scanner;
        }

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

        internal Scanner Scanner { get; }

        public void Dispose()
        {
            Scanner?.Dispose();
        }
    }
}