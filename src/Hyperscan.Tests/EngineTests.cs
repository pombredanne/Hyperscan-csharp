using System.Threading.Tasks;
using FluentAssertions;
using Hyperscan.Compilation;
using Hyperscan.Core;
using Hyperscan.Core.Exceptions;
using Hyperscan.Databases;
using Hyperscan.Tests.XUnit;
using Xunit;
using Xunit.Abstractions;

namespace Hyperscan.Tests
{
    public class EngineTests
    {
        private readonly ITestOutputHelper _testOutputHelper;

        public EngineTests(ITestOutputHelper testOutputHelper)
        {
            _testOutputHelper = testOutputHelper;
        }

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
        public async Task Engine_Should_Have_Valid_Version()
        {
            var loggerProvider = new XunitLoggerProvider(_testOutputHelper);
            var engineBuilder = new EngineBuilder();
            engineBuilder.WithLogger(loggerProvider.CreateLogger("Hyperscan"));
            engineBuilder.WithDatabase(() => new Database());
            engineBuilder.WithCompiler(() => new SimpleCompiler(new Expression("", ExpressionFlag.HsFlagAllowempty), CompilerMode.HsModeBlock));
            var engine = engineBuilder.Build();
            engine.Version.Should().NotBeNullOrEmpty();
            await engine.DisposeAsync();
        }

        [Fact]
        public async Task Platform_Should_Be_Valid()
        {
            var loggerProvider = new XunitLoggerProvider(_testOutputHelper);
            var engineBuilder = new EngineBuilder();
            engineBuilder.WithLogger(loggerProvider.CreateLogger("Hyperscan"));
            engineBuilder.WithDatabase(() => new Database());
            engineBuilder.WithCompiler(() => new SimpleCompiler(new Expression("", ExpressionFlag.HsFlagAllowempty), CompilerMode.HsModeBlock));
            var engine = engineBuilder.Build();
            engine.PlatformInfo.Should().NotBeNull();
            engine.PlatformInfo.IsPlatformValid.Should().BeTrue();
            await engine.DisposeAsync();
        }

        [Fact]
        public async Task Logger_Should_Log_Traces()
        {
            var loggerProvider = new XunitLoggerProvider(_testOutputHelper);
            var engineBuilder = new EngineBuilder();
            engineBuilder.WithLogger(loggerProvider.CreateLogger("Hyperscan"));
            engineBuilder.WithDatabase(() => new Database());
            engineBuilder.WithCompiler(() => new SimpleCompiler(new Expression("foo(?i)bar(?-i)baz", ExpressionFlag.HsFlagUtf8), CompilerMode.HsModeBlock));
            var engine = engineBuilder.Build();
            var traces = loggerProvider.GetTraces();
            traces.Should().ContainMatch("*1 expression(s) compiled*");
            await engine.DisposeAsync();
        }
    }
}