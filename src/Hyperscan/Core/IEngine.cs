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
        /// <summary>
        /// Hyperscan version
        /// </summary>
        string Version { get; }

        /// <summary>
        /// <see cref="PlatformInfo"/>
        /// </summary>
        PlatformInfo PlatformInfo { get; }

        /// <summary>
        /// <see cref="Database"/>
        /// </summary>
        Database Database { get; }

        /// <summary>
        /// Subscribe to observe new match
        /// </summary>
        IObservable<Match> OnMatch { get; }

        /// <summary>
        /// Trigger a scan on the engine
        /// </summary>
        /// <param name="input">Input to match</param>
        /// <param name="cancellationToken"><see cref="CancellationToken"/></param>
        /// <returns><see cref="ValueTask"/></returns>
        ValueTask ScanAsync(string input, CancellationToken cancellationToken);
    }
}