using System;
using System.Linq;
using Hyperscan.Compilation;
using Hyperscan.Core.Exceptions;
using Hyperscan.Databases;
using Hyperscan.Extensions.Expressions;
using Hyperscan.Platform;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Logging.Abstractions;

namespace Hyperscan.Core
{
    /// <summary>
    /// Builder pattern to create an Hyperscan engine
    /// </summary>
    public class EngineBuilder
    {
        private Func<Database> _databaseFactory;
        private Func<Compiler> _compilerFactory;
        private ILogger _logger;

        /// <summary>
        /// Create the Hyperscan engine builder
        /// </summary>
        public EngineBuilder()
        {
            _logger = NullLogger.Instance;
        }

        /// <summary>
        /// Link a database factory for Hyperscan engine
        /// </summary>
        /// <param name="databaseFactory">The database factory</param>
        public void WithDatabase(Func<Database> databaseFactory)
        {
            _databaseFactory = databaseFactory;
        }

        /// <summary>
        /// Link a compiler factory for Hyperscan engine
        /// </summary>
        /// <param name="compilerFactory">The compiler factory</param>
        public void WithCompiler(Func<Compiler> compilerFactory)
        {
            _compilerFactory = compilerFactory;
        }

        /// <summary>
        /// Link a logger the Hyperscan engine
        /// </summary>
        /// <param name="logger"><see cref="ILogger{TCategoryName}"/></param>
        public void WithLogger(ILogger logger)
        {
            _logger = logger;
        }

        /// <summary>
        /// Build the Hyperscan engine
        /// </summary>
        /// <returns></returns>
        public IEngine Build()
        {
            if (_databaseFactory == default)
            {
                throw new HyperscanException($"{nameof(WithDatabase)} should be called.");
            }

            if (_compilerFactory == default)
            {
                throw new HyperscanException($"{nameof(WithCompiler)} should be called.");
            }

            var engine = new Engine(_logger, _databaseFactory, _compilerFactory);
            if (!engine.PlatformInfo.IsPlatformValid)
            {
                _logger.LogWarning("Platform not supported, Hyperscan may not run properly.");
            }

            var hyperscanVersion = engine.Version;
            string mode;
            switch (engine.Compiler.Mode)
            {
                case CompilerMode.HsModeBlock:
                    mode = "block mode (non-streaming)";
                    break;
                case CompilerMode.HsModeStream:
                    mode = "streaming mode";
                    break;
                case CompilerMode.HsModeVectored:
                    mode = "vector mode";
                    break;
                default:
                    mode = string.Empty;
                    break;
            }

            _logger.LogInformation($@"
    __  __                                          
   / / / /_  ______  ___  ___________________ _____ 
  / /_/ / / / / __ \/ _ \/ ___/ ___/ ___/ __ `/ __ \
 / __  / /_/ / /_/ /  __/ /  (__  ) /__/ /_/ / / / /
/_/ /_/\__, / .___/\___/_/  /____/\___/\__,_/_/ /_/ 
      /____/_/                                      

Version {hyperscanVersion}
========================
CPU-enabled intrinsics: {(engine.PlatformInfo.CpuFeature == CpuFeature.HsCpuFeatureAvx2 ? "AVX2" : "none")}
{engine.InputConsumers.Count} multi-threaded scanners initialized with a total of {engine.InputConsumers.Sum(consumer => consumer.Scanner.ScratchSize)} bytes of scratch allocation.
{engine.Compiler.ExpressionsById.Count} expression(s) compiled.
Database size is {engine.Database.Size} bytes.
Engine compiler running in {mode}...
");
            if (engine.Compiler.ExpressionsById.Any(expression => !expression.Value.IsValid()))
            {
                foreach (var (_, value) in engine.Compiler.ExpressionsById.Where(expression => !expression.Value.IsValid()))
                {
                    _logger.LogWarning($"Expression Id='{value.Id}' (Pattern='{value.Pattern}') is not valid.");
                }
            }

            return engine;
        }
    }
}