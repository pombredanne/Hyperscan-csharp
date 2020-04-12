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
// SOFTWARE

#include "pch.h"

#include "hyperscan_expression_info.h"

using namespace Hyperscan::Compilation;

ExpressionInfo::ExpressionInfo(unsigned int minWidth, unsigned int maxWidth, bool unorderedMatches, bool matchesAtEod, bool matchesOnlyAtEod, String^ compilationErrorMessage) {
	this->m_min_width_ = minWidth;
	this->m_max_width_ = maxWidth;
	this->m_unordered_matches_ = unorderedMatches;
	this->m_matches_at_eod_width_ = matchesAtEod;
	this->m_matches_only_at_eod_ = matchesOnlyAtEod;
	this->m_compilation_error_message_ = compilationErrorMessage;
}

unsigned int ExpressionInfo::MinWidth::get() {
	return this->m_min_width_;
}

unsigned int ExpressionInfo::MaxWidth::get() {
	return this->m_max_width_;
}

bool ExpressionInfo::UnorderedMatches::get() {
	return this->m_unordered_matches_;
}

bool ExpressionInfo::MatchesAtEod::get() {
	return this->m_matches_at_eod_width_;
}

bool ExpressionInfo::MatchesOnlyAtEod::get() {
	return this->m_matches_only_at_eod_;
}

String^ ExpressionInfo::CompilationErrorMessage::get() {
	return this->m_compilation_error_message_;
}