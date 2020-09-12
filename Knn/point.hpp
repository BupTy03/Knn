#pragma once
#include <cmath>


template<typename T>
struct point2
{
	constexpr point2() noexcept : x_{}, y_{} {}
	explicit constexpr point2(T x, T y) noexcept : x_{ x }, y_{ y } {}

	constexpr inline T x() const noexcept { return x_; }
	constexpr inline T y() const noexcept { return y_; }

	constexpr inline point2 with_x(T x) const noexcept { return point2{ x, y_ }; }
	constexpr inline point2 with_y(T y) const noexcept { return point2{ x_, y }; }

	constexpr inline point2 plus_x(T x) const noexcept { return point2{ x_ + x, y_ }; }
	constexpr inline point2 plus_y(T y) const noexcept { return point2{ x_, y_ + y }; }

	friend constexpr inline bool operator==(const point2& lhs, const point2& rhs) noexcept
	{
		return lhs.x() == rhs.x() && lhs.y() == rhs.y();
	}

	friend constexpr inline bool operator!=(const point2& lhs, const point2& rhs) noexcept
	{
		return !(lhs == rhs);
	}

	friend constexpr const point2 operator*(const point2& p, T mult) noexcept
	{
		return point2{
			p.x() * mult,
			p.y() * mult
		};
	}

	friend constexpr const point2 operator/(const point2& p, T divider) noexcept
	{
		return point2{
			p.x() / divider,
			p.y() / divider
		};
	}

	friend constexpr const point2 operator+(const point2& lhs, const point2& rhs) noexcept
	{
		return point2{
			lhs.x() + rhs.x(),
			lhs.y() + rhs.y()
		};
	}

	friend constexpr const point2 operator-(const point2& lhs, const point2& rhs) noexcept
	{
		return point2{
			static_cast<T>(lhs.x() - rhs.x()),
			static_cast<T>(lhs.y() - rhs.y())
		};
	}

private:
	T x_;
	T y_;
};


template<typename T>
constexpr inline point2<T> null_point() noexcept { return point2<T>{T{ 0 }, T{ 0 }}; }

template<typename T>
constexpr inline bool is_null(const point2<T>& p) noexcept { return p.x() == 0 && p.y() == 0; }

template<typename T>
constexpr inline point2<T> transposed(const point2<T>& p) noexcept { return point2<T>{p.y(), p.x()}; }

template<typename T>
constexpr inline auto dot_product(const point2<T>& lhs, const point2<T>& rhs) noexcept
{
	return lhs.x() * rhs.x() + lhs.y() * rhs.y();
}

template<typename T>
auto manhattan_length(const point2<T>& p) noexcept
{
	return std::sqrt(p.x() * p.x() + p.y() * p.y());
}

template<typename T>
bool is_left_turn(const point2<T>& a, const point2<T>& b, const point2<T>& c)
{
	const auto u = b - a;
	const auto v = c - b;

	return u.x() * v.y() - u.y() * v.x() >= 0;
};

template<typename T>
double distance(const point2<T>& a, const point2<T>& b)
{
	return std::sqrt(
		std::pow(static_cast<double>(b.x() - a.x()), 2.0) +
		std::pow(static_cast<double>(b.y() - a.y()), 2.0)
	);
}
