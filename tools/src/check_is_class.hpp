// ***********************************************************************
// Filename         : check_is_class.hpp
// Author           : LIZHENG
// Created          : 2014-06-09
// Description      : �ж�һ�������Ƿ��������ͣ�ע�⣬std::is_class���Ǹù���
//
// Last Modified By : LIZHENG
// Last Modified On : 2014-06-09
// 
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef ZL_CHECKISCLASS_H
#define ZL_CHECKISCLASS_H

namespace ZL
{
	template <typename T>
	class is_class
	{
		typedef char one;
		typedef struct { char a[2]; } two;

		template <typename C>
		static one test(int C::*);

		template <typename C>
		static two test(...);
	public:
		enum { value = sizeof(test<T>(0)) == sizeof(one) };
	};

} /* namespace ZL */

#endif /* ZL_CHECKISCLASS_H */