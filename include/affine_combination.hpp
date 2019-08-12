#ifndef AFFINE_COMBINATION_HPP
#define AFFINE_COMBINATION_HPP

#include "affine_types.hpp"
#include <ratio>

namespace affine
{

template <typename T, typename Tag, typename Weight>
class weighted_position : public value<T>
{
public:
	using value<T>::value;
};

template <typename T, typename Tag, typename Weight1, typename Weight2>
auto operator+(const weighted_position<T, Tag, Weight1>& lh, const weighted_position<T, Tag, Weight2>& rh)
AFFINE_TYPE_THRICE(weighted_position<T, Tag, std::ratio_add<Weight1, Weight2>::type>{ value_of(lh) + value_of(rh) })

template <typename T, typename Tag>
class weighted_position<T, Tag, std::ratio<1>> : public value<T>
{
public:
	using value<T>::value;
	operator position<T, Tag>() const noexcept(std::is_nothrow_copy_constructible_v<T>)
	{
		return position<T, Tag>{ value_of(*this) };
	}
};

template <typename T, typename Tag>
class weighted_position<T, Tag, std::ratio<0>> : public value<T>
{
public:
	using value<T>::value;
	operator displacement<T, Tag>() const noexcept(std::is_nothrow_copy_constructible_v<T>)
	{
		return displacement<T, Tag>{ value_of(*this) };
	}
};

template <typename Weight, typename T, typename Tag>
auto weighted(const position<T, Tag>& p)
AFFINE_TYPE_THRICE(weighted_position<T, Tag, Weight>{ value_of(p) * Weight::num / static_cast<double>(Weight::den) })

}

#endif // AFFINE_COMBINATION_HPP
