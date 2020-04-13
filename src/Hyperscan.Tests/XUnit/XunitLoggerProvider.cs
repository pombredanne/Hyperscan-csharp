using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Extensions.Logging;
using Xunit.Abstractions;

namespace Hyperscan.Tests.XUnit
{
    public class XunitLoggerProvider : ILoggerProvider
    {
        private readonly TraceObserver traceObserver;
        private readonly ITestOutputHelper testOutputHelper;
        private readonly Stack<string> traces;

        public XunitLoggerProvider(ITestOutputHelper testOutputHelper)
        {
            this.testOutputHelper = testOutputHelper;
            this.traces = new Stack<string>();
            traceObserver = new TraceObserver(this.traces);
        }

        public ILogger CreateLogger(string categoryName)
            => new XunitLogger(traceObserver, testOutputHelper, categoryName);

        public IEnumerable<string> GetTraces() => traceObserver.Traces;

        public void Dispose()
        {
        }
    }

    public class TraceObserver : IObserver<string>
    {
        private readonly Stack<string> traces;

        public TraceObserver(Stack<string> traces)
        {
            this.traces = traces;
        }

        public IEnumerable<string> Traces => traces.ToList();

        public void OnCompleted()
        {
            throw new NotImplementedException();
        }

        public void OnError(Exception error)
        {
            throw new NotImplementedException();
        }

        public void OnNext(string trace)
        {
            this.traces.Push(trace);
        }
    }

    public class XunitLogger : ILogger
    {
        private readonly TraceObserver traceObserver;
        private readonly ITestOutputHelper testOutputHelper;
        private readonly string categoryName;

        public XunitLogger(TraceObserver traceObserver, ITestOutputHelper testOutputHelper, string categoryName)
        {
            this.traceObserver = traceObserver;
            this.testOutputHelper = testOutputHelper;
            this.categoryName = categoryName;
        }

        public IDisposable BeginScope<TState>(TState state)
            => NoopDisposable.Instance;

        public bool IsEnabled(LogLevel logLevel)
            => true;

        public void Log<TState>(LogLevel logLevel, EventId eventId, TState state, Exception exception,
            Func<TState, Exception, string> formatter)
        {
            var trace = $"{categoryName} [{eventId}] {formatter(state, exception)}";
            traceObserver.OnNext(trace);
            testOutputHelper.WriteLine(trace);
            if (exception != null)
                testOutputHelper.WriteLine(exception.ToString());
        }

        private class NoopDisposable : IDisposable
        {
            public static readonly NoopDisposable Instance = new NoopDisposable();

            public void Dispose()
            {
            }
        }
    }
}