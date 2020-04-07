using System;
using System.Text;

namespace Hyperscan.Extensions
{
    internal static class StringBuilderExtensions
    {
        public static void AppendChars(this StringBuilder stringBuilder, ReadOnlySpan<byte> span, Decoder decoder, int charCount, bool isLast)
        {
            Span<char> buffer = stackalloc char[charCount];
            decoder.GetChars(span, buffer, isLast);
            stringBuilder.Append(buffer);
        }
    }
}
