using System.Threading.Tasks;
using FluentAssertions;
using Hyperscan.Compilation;
using Hyperscan.Core;
using Hyperscan.Databases;
using Xunit;

namespace Hyperscan.Tests
{
    public class DatabaseTests
    {
        [Fact]
        public async Task Database_Size_Should_Be_Valid()
        {
            var engineBuilder = new EngineBuilder();
            engineBuilder.WithDatabase(() => new Database());
            engineBuilder.WithCompiler(() => new SimpleCompiler(new Expression("", ExpressionFlag.HsFlagAllowempty), CompilerMode.HsModeBlock));
            var engine = engineBuilder.Build();
            engine.Database.Size.Should().BeGreaterThan(0);
            await engine.DisposeAsync();
        }

        [Fact]
        public async Task Database_Serialization_Should_Serialize()
        {
            var engineBuilder = new EngineBuilder();
            engineBuilder.WithDatabase(() => new Database());
            engineBuilder.WithCompiler(() => new SimpleCompiler(new Expression("", ExpressionFlag.HsFlagAllowempty), CompilerMode.HsModeBlock));
            var engine = engineBuilder.Build();
            var bytes = engine.Database.Serialize();
            bytes.Should().NotBeEmpty();

            var engineBuilder2 = new EngineBuilder();
            engineBuilder2.WithDatabase(() => new Database(bytes));
            engineBuilder2.WithCompiler(() => new SimpleCompiler(new Expression("", ExpressionFlag.HsFlagAllowempty), CompilerMode.HsModeBlock));
            var engine2 = engineBuilder.Build();
            engine2.Database.Size.Should().Be(engine.Database.Size);
            await engine.DisposeAsync();
            await engine2.DisposeAsync();
        }
    }
}
