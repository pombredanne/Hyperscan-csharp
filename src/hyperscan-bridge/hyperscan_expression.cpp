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

#include "hyperscan_expression.h"

using namespace Hyperscan::Compilation;

Expression::Expression(String^ pattern, const ExpressionFlag expressionFlag) {
	const auto rand_string_generator = gcnew Random();
	this->m_id_ = rand_string_generator->Next();
	this->m_pattern_ = pattern;
	this->m_expression_flag_ = expressionFlag;
}

bool Expression::TryGetInfo([Out] ExpressionInfo^% info)
{
	hs_expr_info_t* expr_info = nullptr;
	hs_compile_error_t* compilation_error = nullptr;
	try {
		const auto expression_error = hs_expression_info(StringUtils::to_unmanaged(this->Pattern), static_cast<unsigned int>(this->Flag), &expr_info, &compilation_error);
		if (expression_error != HS_SUCCESS) {
			const auto compilation_error_message = gcnew String(compilation_error->message);
			info = gcnew ExpressionInfo(0, 0, false, false, false, compilation_error_message);
			return false;
		}

		info = gcnew ExpressionInfo(expr_info->min_width, expr_info->max_width, expr_info->unordered_matches, expr_info->matches_at_eod, expr_info->matches_only_at_eod, gcnew String(""));
		return true;
	}
	finally
	{
		free(expr_info);
		hs_free_compile_error(compilation_error);
	}
}

int Expression::Id::get() {
	return this->m_id_;
}

String^ Expression::Pattern::get() {
	return this->m_pattern_;
}

ExpressionFlag Expression::Flag::get() {
	return this->m_expression_flag_;
}