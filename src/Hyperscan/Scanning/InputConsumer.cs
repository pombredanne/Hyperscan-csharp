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
        private readonly Scanner _scanner;

        public InputConsumer(ILogger logger, Consumer<string> consumer, Scanner scanner)
        {
            _logger = logger;
            _consumer = consumer;
            _scanner = scanner;
        }

        public void Consume(CancellationToken cancellationToken)
        {
            var loopTask = Task.Run(async () =>
            {
                try
                {
                    await foreach (var message in _consumer.ReadMessagesAsync(cancellationToken))
                    {
                        _scanner.Scan(message);
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

        public void Dispose()
        {
            _scanner?.Dispose();
        }
    }
}