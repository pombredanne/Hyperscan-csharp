using System;
using System.Linq;
using Hyperscan.Compilation;
using Hyperscan.Databases;
using Hyperscan.Platform;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Logging.Abstractions;

namespace Hyperscan.Core
{
    public class EngineBuilder
    {
        private Func<Database> _databaseFactory;
        private Func<Compiler> _compilerFactory;
        private ILogger _logger;

        public void WithDatabase(Func<Database> databaseFactory)
        {
            _databaseFactory = databaseFactory;
        }

        public void WithCompiler(Func<Compiler> compilerFactory)
        {
            _compilerFactory = compilerFactory;
        }

        public void WithLogger(ILogger logger)
        {
            _logger = logger;
        }

        public IEngine Build()
        {
            var engine = new Engine(_logger ?? NullLogger.Instance, _databaseFactory, _compilerFactory);
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
            return engine;
        }
    }
}