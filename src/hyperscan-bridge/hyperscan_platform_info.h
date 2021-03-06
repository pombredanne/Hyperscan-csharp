// MIT License
// Copyright(c) 2020 Benjamin Bougot
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include "hyperscan_exception.h"
#include "hyperscan_platform_cpu_feature.h"

using namespace System;

using namespace Hyperscan::Core::Exceptions;

namespace Hyperscan {
	namespace Platform {
		/// <summary>
		/// Exposes platform information such as CPU features, ...
		/// </summary>
		public ref class PlatformInfo sealed {
		public:
			/// <summary>
			/// Construct a platform info
			/// </summary>
			PlatformInfo();

			/// <summary>
			/// Finalizer
			/// </summary>
			~PlatformInfo();

			/// <summary>
			/// Destructor
			/// </summary>
			!PlatformInfo();

			/// <summary>
			/// Check if the hardware platform is supported
			/// </summary>
			property bool IsPlatformValid {
				bool get();
			}

			/// <summary>
			/// Get the CPU features
			/// </summary>
			property CpuFeature CpuFeature {
				Platform::CpuFeature get();
			}
		internal:
			hs_platform_info* m_platform_info;
		};
	}
}