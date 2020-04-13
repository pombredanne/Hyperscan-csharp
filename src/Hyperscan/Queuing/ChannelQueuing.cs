using System.Collections.Generic;
using System.Runtime.CompilerServices;
using System.Threading;
using System.Threading.Channels;
using System.Threading.Tasks;
using Hyperscan.Extensions.Utils;

namespace Hyperscan.Queuing
{
    internal class ChannelQueuing<T>
    {
        public ChannelQueuing(BoundedChannelOptions options)
        {
            var channel = Channel.CreateBounded<T>(options);
            Producer = new Producer<T>(channel.Writer);
            Consumer = new Consumer<T>(channel.Reader);
        }

        public Producer<T> Producer { get; }
        public Consumer<T> Consumer { get; }
    }

    internal class Producer<T>
    {
        private readonly ChannelWriter<T> _writer;

        public Producer(ChannelWriter<T> writer)
        {
            _writer = writer;
        }

        public ValueTask ProduceAsync(T message, CancellationToken cancellationToken)
        {
            return _writer.TryWrite(message)
                ? default
                : ProcessAsynchronously(message, cancellationToken);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private async ValueTask ProcessAsynchronously(T deferredMessage, CancellationToken cancellationToken)
        {
            while (await _writer.WaitToWriteAsync(cancellationToken))
            {
                if (_writer.TryWrite(deferredMessage)) return;
            }
        }
    }

    internal class Consumer<T>
    {
        private readonly ChannelReader<T> _reader;

        public Consumer(ChannelReader<T> reader)
        {
            _reader = reader;
        }

        public IAsyncEnumerable<T> ReadMessagesAsync(CancellationToken cancellationToken)
        {
            return _reader.ToAsyncEnumerable(cancellationToken);
        }
    }
}