using Hyperscan.Compilation;

namespace Hyperscan.Extensions.Expressions
{
    /// <summary>
    /// Extensions for working with Hyperscan expressions
    /// </summary>
    public static class ExpressionExtensions
    {
        /// <summary>
        /// Check if expression is valid
        /// </summary>
        /// <param name="expression"><see cref="Expression"/></param>
        /// <returns>True if valid, false otherwise</returns>
        public static bool IsValid(this Expression expression)
        {
            return expression.TryGetInfo(out _);
        }
    }
}