# Build Hyperscan - C# on Windows for .NET Core

This guide will walk you through building Hyperscan - C# on Windows, targeting .NET Core.
We'll start by showing how to set up your environment from scratch.

## Environment

These instructions are tested on Windows 10, though they should work anywhere the dependencies work.

### Git Setup

This guide assumes that you have recursively cloned the repository and `cd`ed into it.

### Visual Studio

You will need to install an edition of Visual Studio 2019 (2017 also works) (Community, Enterprise, or Professional) with the optional feature 'C++/CLI support for v142 build tools' installed.
You also need the workload '.NET Core cross-platform development'.
The free Community edition of Visual Studio 2019 can be downloaded [here](https://www.visualstudio.com/visual-studio-community-vs/).

### .NET Core

Ensure you have at least .NET Core 3.1, by querying .NET CLI: `dotnet --version`

## Build hyperscan

### Environment
Hyperscan uses the cross-platform tool CMake to compile, test, and package itself. CMake generates independent configuration files for building on all supported operating systems, for example, UNIX makefiles on Linux* and Microsoft Visual Studio Solution files on Windows. To do a build, Hyperscan uses:

* The [Ragel](http://www.colm.net/open-source/ragel/) state machine compiler to generate the regular expression parser.
* The [Boost](https://www.boost.org/) library to create the nondeterministic finite automaton (NFA) graph.
* The [Perl Compatible Regular Expressions](https://www.pcre.org/) (PCRE) library as a backup to provide complete grammar support for regular expressions.
* [SQLite](https://www.sqlite.org/index.html) to store the corpus.
* [Python](https://www.python.org/) to record CMake build time.

### Step-by-Step Instructions
To easier the installation of the dependencies, get [chocolatey](https://chocolatey.org/install).
Then, install the following requirements:

`choco install cygwin`
`choco install cmake --installargs 'ADD_CMAKE_TO_PATH=System'`

Add Cygwin to **PATH** environment variable: `C:\cygwin64\bin`
Once it's done, launch cygwin and get the following packages:
`gcc-core,gcc-g++,wget,make`

Go to Hyperscan-csharp root folder, where you cloned the repository, and using Cygwin bash:
* Download Ragel
`wget http://www.colm.net/files/ragel/ragel-6.10.tar.gz`
`tar xzvf ragel-6.10.tar.gz && rm ragel-6.10.tar.gz`
* Configure and build Ragel
`cd ragel-6.10`
`bash -c ./configure`
`make`
`make install`

 In the hyperscan folder (`cd hyperscan`), and using Cygwin bash:
 * Download Boost
`wget https://dl.bintray.com/boostorg/release/1.72.0/source/boost_1_72_0.tar.gz`
`tar xzvf boost_1_72_0.tar.gz && rm boost_1_72_0.tar.gz`

In the hyperscan folder (`cd hyperscan`), and using Cygwin bash:
* Download PCRE
`wget ftp://ftp.pcre.org/pub/pcre/pcre-8.41.tar.gz`
`tar xzvf pcre-8.41.tar.gz && rm pcre-8.41.tar.gz`

In the hyperscan folder (`cd hyperscan`), and using Cygwin bash:
* Download SQLite
`wget https://www.sqlite.org/2020/sqlite-autoconf-3310100.tar.gz`
`tar xzvf sqlite-autoconf-3310100.tar.gz && rm sqlite-autoconf-3310100.tar.gz`
`mv sqlite-autoconf-3310100 sqlite3`

In the hyperscan folder (`cd hyperscan`), and using CMD:
* Make hyperscan
`mkdir build`
`cd build`
`cmake -G "Visual Studio 16 2019" -D BOOST_ROOT=%cd%/../boost_1_72_0/ -DHAVE_AVX2=true ..` 

In the hyperscan build folder (`cd hyperscan\build`), and using CMD:
* Build hyperscan
`MsBuild.exe ALL_BUILD.vcxproj /t:build /p:Configuration=Release`

In the Hyperscan - C# src folder (`cd src`)
* Build Hyperscan
Launch Hyperscan.sln and build (x64/Release)

You'll find the binaries located in `Hyperscan-csharp\src\Hyperscan\bin\x64\Release\netcoreapp3.1`

### Using binaries
When compilation is done, you can reference them from any .NET Core 3.1 application.
Beware that you need:
* hyperscan-bridge.dll => The C++/CLI wrapper
* Hyperscan.dll => The .NET Core 3.1 layer on top of hyperscan-bridge
* Ijwhost.dll => The required hosting library to run any C++/CLI binary
* When using your application outside of a development environment, the VC++ redistributables x64 associated to the version of Visual Studio you used to build Hyperscan - C# (see [here](https://support.microsoft.com/fr-fr/help/2977003/the-latest-supported-visual-c-downloads))