#include "stdafx.h"

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <deque>
#include <map>
#include <set>
#include <cctype>

#include <numeric>
#include <utility>

#include <assert.h>

/*
Tuple sum

Your task is to implement a function that adds all tuple elements that are numbers.

For this kata chars are not considered numbers.

*/

#include <tuple>

template <typename T, typename... Ts>
auto head(std::tuple<T, Ts...> t) {
	return std::get<0>(t);
}

template <std::size_t... Ns, typename... Ts>
auto tail_impl(std::index_sequence<Ns...>, std::tuple<Ts...> t) {
	return std::make_tuple(std::get<Ns + 1u>(t)...);
}

template <typename... Ts>
auto tail(std::tuple<Ts...> t) {
	return tail_impl(std::make_index_sequence<sizeof...(Ts)-1u>(), t);
}

template <typename... T>
std::size_t get_tuple_size(std::tuple<T...> const &)
{
	return sizeof...(T);
}

//template <typename... Ts>
//double tuple_sum(const std::tuple<Ts...>& tpl) {
//	size_t elementsCount = get_tuple_size(tpl);
//	if (0 == elementsCount)
//		return 0.0;
//
//	double sum = num(std::get<0>(tpl)).get();
//
//	auto tplTail = tail(tpl);
//	sum += tuple_sum_impl(tplTail);
//
//	return sum;
//}

struct num {
	num(int v) { m_data = v; }
	num(double v) { m_data = v; }
	num(unsigned v) { m_data = v; }

	template <typename T>
	num(T t) { m_data = 0; }

	double get() { return m_data; }

private:
	double m_data;
};

template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), double>::type
tumpl_sum_impl(std::tuple<Tp...> const& t)
{
	return 0.0;
}

template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), double>::type
tumpl_sum_impl(std::tuple<Tp...> const& t)
{
	return num(std::get<I>(t)).get() + tumpl_sum_impl<I + 1, Tp...>(t);
}

template <typename... Ts>
double tuple_sum(const std::tuple<Ts...>& tpl) {
	return tumpl_sum_impl(tpl);
}


using namespace std::string_literals;

int main() {
	std::cout << tuple_sum(std::make_tuple(3.14, 42, 'a', "Hello", "World"s, std::vector<int>{1, 2, 3}));
	//test1(std::make_tuple(3.14, 42, 'a', "Hello", "World"s, std::vector<int>{1, 2, 3}));

	//auto sum = tuple_sum(std::make_tuple(3.14, 42, 'a', "Hello", "World"s, std::vector<int>{1, 2, 3}));
	//assert( (sum <= 45.14 + 0.001) && (sum >= 45.14 - 0.001) );
}

