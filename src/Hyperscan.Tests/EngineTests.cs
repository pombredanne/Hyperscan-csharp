using FluentAssertions;
using Hyperscan.Compilation;
using Hyperscan.Core;
using Hyperscan.Core.Exceptions;
using Hyperscan.Databases;
using Xunit;

namespace Hyperscan.Tests
{
    public class EngineTests
    {
        [Fact]
        public void Compiler_Not_Configured_With_Engine_Builder_Should_Throw_Exception()
        {
            var engineBuilder = new EngineBuilder();
            engineBuilder.WithDatabase(() => new Database());
            FluentActions.Invoking(() => engineBuilder.Build()).Should().Throw<HyperscanException>();
        }

        [Fact]
        public void Database_Not_Configured_With_Engine_Builder_Should_Throw_Exception()
        {
            var engineBuilder = new EngineBuilder();
            engineBuilder.WithCompiler(() => new SimpleCompiler(new Expression("", ExpressionFlag.HsFlagAllowempty), CompilerMode.HsModeBlock));
            FluentActions.Invoking(() => engineBuilder.Build()).Should().Throw<HyperscanException>();
        }

        [Fact]
        public void Engine_Should_Have_Valid_Version()
        {
            var engineBuilder = new EngineBuilder();
            engineBuilder.WithDatabase(() => new Database());
            engineBuilder.WithCompiler(() => new SimpleCompiler(new Expression("", ExpressionFlag.HsFlagAllowempty), CompilerMode.HsModeBlock));
            var engine = engineBuilder.Build();
            engine.Version.Should().NotBeNullOrEmpty();
        }

        [Fact]
        public void Platform_Should_Be_Valid()
        {
            var engineBuilder = new EngineBuilder();
            engineBuilder.WithDatabase(() => new Database());
            engineBuilder.WithCompiler(() => new SimpleCompiler(new Expression("", ExpressionFlag.HsFlagAllowempty), CompilerMode.HsModeBlock));
            var engine = engineBuilder.Build();
            engine.PlatformInfo.Should().NotBeNull();
            engine.PlatformInfo.IsPlatformValid.Should().BeTrue();
        }
    }
}