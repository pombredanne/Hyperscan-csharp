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
#include "hyperscan_utils.h"

using namespace System;

using namespace Hyperscan::Core::Exceptions;
using namespace Hyperscan::Utils;

namespace Hyperscan {
	namespace Databases {
		/// <summary>
		/// Hyperscan database which stores compiled expressions
		/// </summary>
		public ref class Database sealed {
		public:
			/// <summary>
			/// Construct a default database
			/// </summary>
			Database();

			/// <summary>
			/// Construct a database from a previously serialized database from a file
			/// </summary>
			explicit Database(String^ filePath);

			/// <summary>
			/// Construct a database from a previously serialized database from a byte array
			/// </summary>
			explicit Database(array<Byte>^ serializedDatabase);

			/// <summary>
			/// Finalizer
			/// </summary>
			~Database();

			/// <summary>
			/// Destructor
			/// </summary>
			!Database();

			/// <summary>
			/// The size of the database in bytes
			/// </summary>
			property int Size
			{
				int get();
			}

			/// <summary>
			/// Serialize the database as a byte array
			/// </summary>
			array<Byte>^ Serialize();
		internal:
			hs_database_t* m_database;
		};
	}
}
