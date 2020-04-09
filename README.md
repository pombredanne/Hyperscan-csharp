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

## Building the Repository

| Windows                    |
|----------------------------|
| [Instructions][bd-windows] |

[bd-windows]: https://github.com/bbougot/Hyperscan-csharp/blob/master/docs/building/windows-core.md

## Legal and Licensing

Hyperscan - C# is licensed under the [MIT license][].

[MIT license]: https://github.com/bbougot/Hyperscan-csharp/blob/master/LICENSE