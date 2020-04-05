#include "pch.h"

#include "hyperscan_match_event_handler.h"

using namespace Hyperscan::Scanning;
using namespace Hyperscan::Scanning::Event;
using namespace Hyperscan::Utils;

MatchEventHandler::MatchEventHandler(MatchObservable^ matchObservable) {
	this->m_MatchObservable = matchObservable;
	this->m_Callback = gcnew OnMatchManagedCallback(this, &MatchEventHandler::OnMatch);
	this->m_Callback_Handle = GCHandle::Alloc(this->m_Callback);
	this->m_Callback_Ptr = Marshal::GetFunctionPointerForDelegate(this->m_Callback);
	this->m_Handler = static_cast<match_event_handler>(this->m_Callback_Ptr.ToPointer());
}

MatchEventHandler::~MatchEventHandler() {
	this->!MatchEventHandler();
}

MatchEventHandler::!MatchEventHandler() {
	this->m_Callback_Handle.Free();
}

int MatchEventHandler::OnMatch(unsigned int id, unsigned long long from, unsigned long long to, unsigned int flags, void* context) {
	this->m_MatchObservable->OnMatch(gcnew Match(id, gcnew System::String(StringUtils::Substring((char*)context, from, to))));
	return 0;
}