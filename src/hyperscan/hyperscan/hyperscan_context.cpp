#include "pch.h"

#include "hyperscan_context.h"

using namespace System::Runtime::InteropServices;
using namespace Hyperscan::Core;

HyperscanContext::HyperscanContext() {

}

HyperscanContext::~HyperscanContext() {
	this->!HyperscanContext();
}

HyperscanContext::!HyperscanContext() {
	hs_free_scratch(this->m_Scratch);
	hs_free_database(this->m_Database);
}