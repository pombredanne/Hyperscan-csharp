using System;
using System.Threading;
using System.Threading.Tasks;
using Hyperscan.Databases;
using Hyperscan.Platform;
using Hyperscan.Scanning;

namespace Hyperscan.Core
{
    public interface IEngine : IAsyncDisposable
    {
        string Version { get; }
        PlatformInfo PlatformInfo { get; }
        Database Database { get; }
        IObservable<Match> OnMatch { get; }
        ValueTask ScanAsync(string input, CancellationToken cancellationToken);
    }
}