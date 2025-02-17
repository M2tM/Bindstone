#ifndef _MV_EXACT_TYPE_HPP_
#define _MV_EXACT_TYPE_HPP_

#include <type_traits>

namespace MV {
	//useful to disambiguate bool and a lambda with no captures [](){}
	template<class T>
	struct ExactType {
		T t;
		template<class U, typename std::enable_if< std::is_same<T, typename std::decay<U>::type>{}, int>::type = 0 >
		ExactType(U&& u) :t(std::forward<U>(u)) {}
		ExactType() :t() {}
		ExactType(ExactType&&) = default;
		ExactType(ExactType const&) = default;

		operator T() const& { return t; }
		operator T() && { return std::move(t); }
		T& get()& { return t; }
		T const& get() const& { return t; }
		T get() && { return std::move(t); }
	};
}

#endif