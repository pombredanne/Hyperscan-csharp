using System.IO;
using System.Threading.Tasks;
using Hyperscan.Databases;

namespace Hyperscan.Extensions.Databases
{
    public static class DatabaseExtensions
    {
        public static Task SerializeToFileAsync(this Database database, string path)
        {
            var serializedDatabase = database.Serialize();
            return File.WriteAllBytesAsync(path, serializedDatabase);
        }
    }
}
