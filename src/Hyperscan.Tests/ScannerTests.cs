using System.Collections.Generic;
using System.Reactive.Linq;
using System.Reactive.Threading.Tasks;
using System.Threading;
using System.Threading.Tasks;
using FluentAssertions;
using Hyperscan.Compilation;
using Hyperscan.Core;
using Hyperscan.Databases;
using Hyperscan.Extensions.Utils;
using Hyperscan.Scanning;
using Microsoft.Reactive.Testing;
using Xunit;

namespace Hyperscan.Tests
{
    public class ScannerTests
    {
        [Fact]
        public async Task Engine_With_Simple_Compiler_Should_Match_Pattern()
        {
            var engineBuilder = new EngineBuilder();
            engineBuilder.WithDatabase(() => new Database());
            engineBuilder.WithCompiler(() => new SimpleCompiler(new Expression("foo(?i)bar(?-i)baz", ExpressionFlag.HsFlagUtf8), CompilerMode.HsModeBlock));
            var engine = engineBuilder.Build();
            var onMatch = engine.OnMatch.FirstAsync().ToTask();
            await engine.ScanAsync("foofoobarbazbazbaz", CancellationToken.None);
            var match = await onMatch;
            match.Should().NotBeNull();
            match.Expression.Flag.Should().Be(ExpressionFlag.HsFlagUtf8);
            match.Expression.Id.Should().Be(0);
            match.Expression.TryGetInfo(out var info).Should().BeTrue();
            info.CompilationErrorMessage.Should().BeEmpty();
            match.Input.Read().Should().Be("foofoobarbazbazbaz");
            match.Expression.Pattern.Should().Be("foo(?i)bar(?-i)baz");
        }

        [Fact]
        public async Task Engine_With_Multiple_Compiler_Should_Match_Patterns()
        {
            var engineBuilder = new EngineBuilder();
            engineBuilder.WithDatabase(() => new Database());
            engineBuilder.WithCompiler(() => new MultipleCompiler(new List<Expression>
            {
                new Expression("foo(?i)bar(?-i)baz", ExpressionFlag.HsFlagCaseless),
                new Expression("foo", ExpressionFlag.HsFlagCaseless | ExpressionFlag.HsFlagUtf8),
                new Expression("foo(?i)bar", ExpressionFlag.HsFlagCaseless | ExpressionFlag.HsFlagDotall)
            }, CompilerMode.HsModeBlock));
            var engine = engineBuilder.Build();
            var observer = new TestScheduler().CreateObserver<Match>();
            using var onMatch = engine.OnMatch.Subscribe(observer);
            await engine.ScanAsync("foofoobarbazbazbaz", CancellationToken.None);
            await Task.Delay(100);
            observer.Messages.Count.Should().Be(4);
            observer.Messages.Should().Contain(message => message.Value.Value.FullMatch == "foo");
            observer.Messages.Should().Contain(message => message.Value.Value.FullMatch == "foofoo");
            observer.Messages.Should().Contain(message => message.Value.Value.FullMatch == "foofoobar");
            observer.Messages.Should().Contain(message => message.Value.Value.FullMatch == "foofoobarbaz");
        }
    }
}