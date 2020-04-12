# Hyperscan - C#
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/bbougot/Hyperscan-csharp/blob/master/LICENSE) [![Nuget](https://img.shields.io/nuget/v/Hyperscan)](https://www.nuget.org/packages/Hyperscan/) [![Nuget](https://img.shields.io/nuget/dt/Hyperscan)](https://www.nuget.org/packages/Hyperscan/)

[hyperscan](https://github.com/intel/hyperscan) is a high-performance multiple regex matching library.

It uses hybrid automata techniques to allow simultaneous matching of large numbers (up to tens of thousands) of regular expressions and for the matching of regular expressions across streams of data.

This project is a third-party developed using C++/CLI for the [hyperscan](https://github.com/intel/hyperscan) project to enable developers to integrate hyperscan in their .NET Core based projects.

## Build status

| Github CI (Windows)                                | Code Coverage Status     |
| :------------------------------------------------- | :----------------------- |
| [![ci-image][]][ci-site]                   | [![cc-image][]][cc-site] |

[ci-image]: https://github.com/bbougot/Hyperscan-csharp/workflows/Build%20%26%20Test/badge.svg
[ci-site]: https://github.com/bbougot/Hyperscan-csharp/actions?query=workflow%3A%22Build+%26+Test%22
[cc-image]: https://codecov.io/gh/bbougot/Hyperscan-csharp/branch/master/graph/badge.svg
[cc-site]: https://codecov.io/gh/bbougot/Hyperscan-csharp

## Installing from NuGet

To install **Hyperscan**, run the following command in the **Package Manager Console**

```
Install-Package Hyperscan
```

More details available [here](https://www.nuget.org/packages/Hyperscan/).

## Usage

[<img src="assets/sample.png" width="650"/>](sample.png)

*More to come.*

## Structure
* **hyperscan** is a git *subtree* taken from master branch of https://github.com/intel/hyperscan. It is used by the C++/CLI wrapper located in src/hyperscan-bridge.
* **src** is the root folder of the Hyperscan - C# project which contains:
  * hyperscan-bridge: C++/CLI wrapper targeting .NET Core 3.1 which exposes the hyperscan API to the .NET world.
  * Hyperscan: .NET Core 3.1 layer on top of hyperscan-bridge which provides utilities, helpers and extension methods to easier the usage of the hyperscan API.
  * Hyperscan.Sample: .NET Core 3.1 console application to demonstrate simple usage of the API.
  * Hyperscan.Tests: Unit tests powered by xUnit.
  * Hyperscan.Benchmarks: Benchmark powered by BenchmarkDotNet.

## Building the Repository

| Windows                    |
|----------------------------|
| [Instructions][bd-windows] |

[bd-windows]: https://github.com/bbougot/Hyperscan-csharp/blob/master/docs/building/windows-core.md

## Supported platforms
Hyperscan - C# supports only Windows 8/8.1/10/Server 2016/2019 x64 with .NET Core >= 3.1, while support for 32-bit platform-only is **not** provided.

Using Hyperscan - C# is only available through .NET Core 3.1 applications, hence referencing `netcoreapp3.1` within your csproj. The chosen platform must also be **x64** exclusively, x86 or AnyCPU targets are not supported due to native bindings from hyperscan being x64.

Those requirements are driven by the following statements:
* [hyperscan](https://github.com/intel/hyperscan) supports Windows 8+ as explained [here](http://intel.github.io/hyperscan/dev-reference/getting_started.html#software).
* C++/CLI does support .NET Core >= 3.1 and only on Windows, as stated [here](https://devblogs.microsoft.com/cppblog/the-future-of-cpp-cli-and-dotnet-core-3/).
* 32-bit platform-only usage is marginal, especially on memory-intensive environment such as servers.

## Contributing
Feel free to raise issues or submit a pull request.

## Credits
Original project implementation comes from Intel®.

## Legal and Licensing

Hyperscan - C# is licensed under the [MIT license][].

[MIT license]: https://github.com/bbougot/Hyperscan-csharp/blob/master/LICENSE