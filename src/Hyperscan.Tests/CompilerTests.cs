using FluentAssertions;
using Hyperscan.Compilation;
using Xunit;

namespace Hyperscan.Tests
{
    public class CompilerTests
    {
        [Theory]
        [InlineData(CompilerMode.HsModeBlock)]
        [InlineData(CompilerMode.HsModeStream)]
        [InlineData(CompilerMode.HsModeVectored)]
        public void Compiler_Mode_Should_Be_Populated(CompilerMode mode)
        {
            var compiler = new SimpleCompiler(new Expression("", ExpressionFlag.HsFlagAllowempty), mode);
            compiler.Mode.Should().Be(mode);
        }
    }
}