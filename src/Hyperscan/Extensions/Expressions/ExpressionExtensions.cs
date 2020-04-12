using Hyperscan.Compilation;

namespace Hyperscan.Extensions.Expressions
{
    public static class ExpressionExtensions
    {
        public static bool IsValid(this Expression expression)
        {
            return expression.TryGetInfo(out var _);
        }
    }
}