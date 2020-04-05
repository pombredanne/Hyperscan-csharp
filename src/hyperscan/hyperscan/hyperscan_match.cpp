#include "pch.h"

#include "hyperscan_match.h"

using namespace Hyperscan::Scanning;

Match::Match(int id, System::String^ result) {
	this->m_Id = id;
	this->m_Result = result;
}

int Match::Id::get() {
	return this->m_Id;
}

System::String^ Match::Result::get() {
	return this->m_Result;
}