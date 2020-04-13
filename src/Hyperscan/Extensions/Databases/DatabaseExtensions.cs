using System.IO;
using System.Threading.Tasks;
using Hyperscan.Databases;

namespace Hyperscan.Extensions.Databases
{
    /// <summary>
    /// Extensions for working with Hyperscan database
    /// </summary>
    public static class DatabaseExtensions
    {
        /// <summary>
        /// Serialize database to a file
        /// </summary>
        /// <param name="database"><see cref="Database"/></param>
        /// <param name="path">Path to the file</param>
        /// <returns><see cref="Task"/></returns>
        public static Task SerializeToFileAsync(this Database database, string path)
        {
            var serializedDatabase = database.Serialize();
            return File.WriteAllBytesAsync(path, serializedDatabase);
        }
    }
}
