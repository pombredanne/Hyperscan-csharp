using System;
using Hyperscan.Compilation;
using Hyperscan.Databases;
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
            return new Engine(_logger ?? NullLogger.Instance, _databaseFactory, _compilerFactory);
        }
    }
}
