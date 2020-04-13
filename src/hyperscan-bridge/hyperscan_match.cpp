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

#include "hyperscan_match.h"

using namespace Hyperscan::Scanning;

Match::Match(int id, String^ fullMatch, Compilation::Expression^ expression, ReadOnlySequence<Byte>^ input) {
	this->m_id_ = id;
	this->m_full_match_ = fullMatch;
	this->m_expression_ = expression;
	this->m_input_ = input;
}

int Match::Id::get() {
	return this->m_id_;
}

String^ Match::FullMatch::get() {
	return this->m_full_match_;
}

Expression^ Match::Expression::get() {
	return this->m_expression_;
}

ReadOnlySequence<Byte> Match::Input::get() {
	return *this->m_input_;
}