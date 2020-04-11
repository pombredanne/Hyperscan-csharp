using System.Collections.Generic;
using System.Runtime.CompilerServices;
using System.Threading;
using System.Threading.Channels;

namespace Hyperscan.Extensions.Utils
{
    public static class ChannelReaderExtensions
    {
        public static async IAsyncEnumerable<T> ToAsyncEnumerable<T>(this ChannelReader<T> reader,
            [EnumeratorCancellation] CancellationToken cancellationToken)
        {
            while (await reader.WaitToReadAsync(cancellationToken))
            {
                while (reader.TryRead(out var message))
                {
                    yield return message;
                }
            }
        }
    }
}