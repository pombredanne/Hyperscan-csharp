using System;
using System.Buffers;
using System.Text;

namespace Hyperscan.Sample
{
    public static class StringBuilderExtensions
    {
        public static void AppendChars(this StringBuilder stringBuilder, ReadOnlySpan<byte> span, Decoder decoder, int charCount, bool isLast)
        {
            Span<char> buffer = stackalloc char[charCount];
            decoder.GetChars(span, buffer, isLast);
            stringBuilder.Append(buffer);
        }
    }

    public static class ReadOnlySequenceExtensions
    {
        public static string Read(this ReadOnlySequence<byte> bytes)
        {
            var decoder = Encoding.UTF8.GetDecoder();
            var stringBuilder = new StringBuilder();
            var processed = 0L;
            var total = bytes.Length;
            foreach (var i in bytes)
            {
                processed += i.Length;
                var isLast = processed == total;
                var span = i.Span;
                var charCount = decoder.GetCharCount(span, isLast);
                stringBuilder.AppendChars(span, decoder, charCount, isLast);
            }

            return stringBuilder.ToString();
        }
    }
}