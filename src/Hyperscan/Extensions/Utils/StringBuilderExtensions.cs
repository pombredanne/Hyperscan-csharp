using System;
using System.Text;

namespace Hyperscan.Extensions.Utils
{
    internal static class StringBuilderExtensions
    {
        /// <summary>
        /// Append chars to the <see cref="StringBuilder"/>
        /// </summary>
        /// <param name="stringBuilder"><see cref="StringBuilder"/></param>
        /// <param name="span"><see cref="ReadOnlySpan{T}"/></param>
        /// <param name="decoder"><see cref="Decoder"/></param>
        /// <param name="charCount">The char count</param>
        /// <param name="isLast">True if last char</param>
        internal static void AppendChars(this StringBuilder stringBuilder, ReadOnlySpan<byte> span, Decoder decoder, int charCount, bool isLast)
        {
            Span<char> buffer = stackalloc char[charCount];
            decoder.GetChars(span, buffer, isLast);
            stringBuilder.Append(buffer);
        }
    }
}
