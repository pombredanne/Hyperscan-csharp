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

#include "pch.h"

#include "hyperscan_database.h"
#include "hyperscan_exception.h"

using namespace Hyperscan::Databases;

Database::Database()
{
	this->m_database = nullptr;
}

Database::Database(String^ path)
{
	const auto file_stream = gcnew IO::FileStream(path, IO::FileMode::Open, IO::FileAccess::Read, IO::FileShare::Read);
	const auto binary_reader = gcnew IO::BinaryReader(file_stream);
	try
	{
		const auto file_info = gcnew IO::FileInfo(path);
		const auto total_bytes = file_info->Length;
		const auto buffer = binary_reader->ReadBytes(safe_cast<Int32>(total_bytes));
		this->Database::Database(buffer);
	}
	finally
	{
		file_stream->Close();
		delete file_stream;
		binary_reader->Close();
	}
}

Database::Database(array<Byte>^ serializedDatabase)
{
	const pin_ptr<Byte> serialized_database = &serializedDatabase[0];
	const auto serialized_database_ptr = reinterpret_cast<char*>(serialized_database);
	const pin_ptr<hs_database*> database = &this->m_database;
	const auto deserialize_database_error = hs_deserialize_database(serialized_database_ptr, serializedDatabase->Length, database);
	if (deserialize_database_error != HS_SUCCESS)
	{
		throw gcnew HyperscanException(String::Format("Unable to deserialize database: {0}", deserialize_database_error));
	}
}


Database::~Database()
{
	this->!Database();
}

Database::!Database()
{
	hs_free_database(this->m_database);
}

int Database::Size::get()
{
	size_t database_size = 0;
	const auto database_size_error = hs_database_size(this->m_database, &database_size);
	if(database_size_error != HS_SUCCESS)
	{
		throw gcnew HyperscanException(String::Format("Unable to get database size: {0}", database_size_error));
	}

	return static_cast<int>(database_size);
}

array<Byte>^ Database::Serialize()
{
	const auto database_size = new size_t[1];
	char* serialized_database = nullptr;
	try
	{
		const auto database_serialize_error = hs_serialize_database(this->m_database, &serialized_database, database_size);
		if (database_serialize_error != HS_SUCCESS)
		{
			throw gcnew HyperscanException(String::Format("Unable to serialize database: {0}", database_serialize_error));
		}

		return StringUtils::to_managed_array(serialized_database, static_cast<int>(*database_size));
	}
	finally
	{
		delete[] database_size;
		delete[] serialized_database;
	}
}