using System.Collections.Generic;
using System.Runtime.CompilerServices;
using System.Threading;
using System.Threading.Channels;

namespace Hyperscan.Extensions.Utils
{
    /// <summary>
    /// Channel extensions
    /// </summary>
    public static class ChannelReaderExtensions
    {
        /// <summary>
        /// Converts a <see cref="ChannelReader{T}"/> to a <see cref="IAsyncEnumerable{T}"/>
        /// </summary>
        /// <typeparam name="T">The entity</typeparam>
        /// <param name="reader"><see cref="ChannelReader{T}"/></param>
        /// <param name="cancellationToken"><see cref="CancellationToken"/></param>
        /// <returns><see cref="IAsyncEnumerable{T}"/></returns>
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