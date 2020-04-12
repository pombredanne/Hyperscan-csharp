using FluentAssertions;
using Hyperscan.Compilation;
using Hyperscan.Extensions.Expressions;
using Xunit;

namespace Hyperscan.Tests
{
    public class ExpressionTests
    {
        [Fact]
        public void Incorrect_Expression_Should_Not_Be_Valid()
        {
            var expression = new Expression("(((", ExpressionFlag.HsFlagDotall);
            expression.IsValid().Should().BeFalse();
        }

        [Fact]
        public void Correct_Expression_Should_Not_Be_Valid()
        {
            var expression = new Expression("foo(?i)bar(?-i)baz", ExpressionFlag.HsFlagDotall);
            expression.IsValid().Should().BeTrue();
        }
    }
}
