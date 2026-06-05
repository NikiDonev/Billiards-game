#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <math.h>
#include <initializer_list>

#pragma region constructors and indexing

template <typename T, size_t N>
struct vec {
	T data[N]{};
	
	vec<T, N>() {};
	vec<T, N>(const std::initializer_list<T>& list) {
		size_t i = 0;
		for (const auto& item : list) {
			if (i == N) break;
			data[i++] = item;
		}
	}
	T& operator[](size_t i) { return data[i]; }
	const T& operator[](size_t i) const { return data[i]; }
};

template <typename T>
struct vec<T, 2> {
	T x{}, y{};

	vec<T, 2>() {};
	vec<T, 2>(T X, T Y) : x(X), y(Y) {}
	T& operator[](size_t i) { return (i == 0) ? x : y; }
	const T& operator[](size_t i) const { return (i == 0) ? x : y; }

};

template <typename T>
struct vec<T, 3> {
	T x{}, y{}, z{};

	vec<T, 3>() {};
	vec<T, 3>(T X, T Y, T Z) : x(X), y(Y) , z(Z) {}
	T& operator[](size_t i) {
		if (i == 0) return x;
		if (i == 1) return y;
		return z;
	}
	const T& operator[](size_t i) const {
		if (i == 0) return x;
		if (i == 1) return y;
		return z;
	}
};
#pragma endregion

#pragma region +-*/ overloads

template <typename T,size_t N>
vec<T, N>& operator+= (vec<T, N>& left, const vec<T, N>& right) {
	for (size_t i = 0; i < N; ++i) left[i] += right[i];
	return left;
}

template <typename T, size_t N>
vec<T, N>& operator-= (vec<T, N>& left, const vec<T, N>& right) {
	for (size_t i = 0; i < N; ++i) left[i] -= right[i];
	return left;
}

template <typename T, size_t N>
vec<T, N> operator+ (const vec<T, N>& left, const vec<T, N>& right) {
	vec<T, N>res = left;
	res += right;
	return res;
}

template <typename T, size_t N>
vec<T, N> operator- (const vec<T, N>& left, const vec<T, N>& right) {
	vec<T, N>res = left;
	res -= right;
	return res;
}
template <typename T, size_t N>
vec<T, N>& operator*=(vec<T, N>& left, const vec<T, N>& right) {
	for (size_t i = 0; i < N; ++i) left[i] *= right[i];
	return left;
}
template <typename T, size_t N>
vec<T, N> operator*(const vec<T, N>& left, const vec<T, N>& right) {
	vec<T, N> res = left;
	res *= right;
	return res;
}

template <typename T, size_t N>
vec<T, N>& operator*= (vec<T, N>& v, T scalar) {
	for (size_t i = 0; i < N; ++i) v[i] *= scalar;
	return v;
}

template <typename T, size_t N>
vec<T, N> operator* (const vec<T, N>& v, T scalar) {
	vec<T, N>res = v;
	res *= scalar;
	return res;
}

template <typename T, size_t N>
vec<T, N> operator* (T scalar, const vec<T, N>& v) {
	return v * scalar;
}

template <typename T, size_t N>
vec<T, N>& operator/= (vec<T, N>& v, T scalar) {
	v *= (1 / scalar);
	return v;
}

template <typename T, size_t N>
vec<T, N> operator/ (const vec<T, N>& v, T scalar) {
	vec<T, N>res = v;
	res *= (1 / scalar);
	return res;
}

template <typename T, size_t N>
vec<T, N> operator/ (T scalar, const vec<T, N>& v) {
	vec<T, N>res = v;
	res *= (1 / scalar);
	return res;
}
#pragma endregion

#pragma region vector math
template <typename T, size_t N>
T dot(const vec<T, N>& left, const vec<T, N>& right) {
	T product{};
	for (size_t i = 0; i < N; ++i) product += left[i] * right[i];
	return product;
}

template <typename T, size_t N>
T operator| (const vec<T, N>& left,const vec<T, N>& right) {
	return dot(left, right);
}

template <typename T>
T cross(const vec<T, 2>& left, const vec<T, 2>& right) {
	return left.x * right.y - left.y * right.x;
}
template <typename T>
vec<T, 3> cross(const vec<T, 3>& a, const vec<T, 3>& b) {
	return vec<T, 3>{
		a.y* b.z - a.z * b.y,
			a.z* b.x - a.x * b.z,
			a.x* b.y - a.y * b.x
	};
}

template <typename T>
T operator^(const vec<T, 2>& left, const vec<T, 2>& right) {
	return cross(left, right);
}
template <typename T>
vec<T, 3> operator^(const vec<T, 3>& left, const vec<T, 3>& right) {
	return cross(left, right);
}

template <typename T, size_t N>
double length(const vec<T, N>& v) {
	double len{};
	for (size_t i = 0; i < N; ++i) len += v[i] * v[i];
	return std::sqrt(len);
}
template <typename T, size_t N>
double length_sq(const vec<T, N>& v) {
	double len{};
	for (size_t i = 0; i < N; ++i) len += v[i] * v[i];
	return len;
}

template <typename T, size_t N>
double operator! (const vec<T, N>& v) {
	return length(v);
}

template <typename T, size_t N>
vec<T, N> normalized(const vec<T, N>& v) {
	T len = length(v);
	if (len == 0) return v;
	return v * (static_cast<T>(1) / len);
}
template <typename T, size_t N>
vec<T, N>normalize(vec<T, N>& v) {
	return v = normalized(v);
}

template <typename T, size_t N>
double dist(const vec<T, N>& v1, const vec<T, N>& v2) {
	return !(v1 - v2);
}

template <typename T>
double angleRad(const vec<T, 2>& v) {
	return atan2(v.y, v.x);
}
template <typename T>
double angleDeg(const vec<T, 2>& v) {
	return angleRad(v) * 180.0 / M_PI;
}

template <typename T>
vec<T, 2> rotateRad(vec<T, 2>& v, double a) {
	return v = { static_cast<T>(v.x * cos(a) - v.y * sin(a)), 
				 static_cast<T>(v.x * sin(a) + v.y * cos(a)) };
}
template <typename T>
vec<T, 2> rotateDeg(vec<T, 2>& v, double a) {
	a *= (M_PI / 180.0);
	return v = { static_cast<T>(v.x * cos(a) - v.y * sin(a)), 
				 static_cast<T>(v.x * sin(a) + v.y * cos(a)) };
}

template <typename T, size_t N, typename U>
vec<T, N> lerp(const vec<T, N>& start, const vec<T, N>& end, U t) {
	return start + (end - start) * t;
}

template <typename T, size_t N>
vec<T, N> reflect(const vec<T, N>& incident, const vec<T, N>& normal) {
	return incident - 2 * (incident | normal) * normal;
}

#pragma endregion

#pragma region printing and comparing

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& os, const vec<T, N>& v) {
	os << "[";
	for (size_t i = 0; i < N; ++i) {
		os << v[i] << (i < N - 1 ? ", " : "");
	}
	os << "]";
	return os;
}

template <typename T, size_t N>
void print(const vec<T, N>& v) {
	std::cout << v << std::endl;
}


template <typename T, size_t N>
bool operator== (const vec<T, N>& left, const vec<T, N>& right) {
	T epsilon = static_cast<T>(0.00001);
	for (size_t i = 0; i < N; ++i) 
		if (std::abs(left[i] - right[i]) > epsilon) return false;
	return true;
}
template <typename T, size_t N>
bool operator!= (const vec<T, N>& left, const vec<T, N>& right) {
	return !(left == right);
}
#pragma endregion

using vec2f = vec<float, 2>;
using vec2i = vec<int, 2>;
using vec2d = vec<double, 2>;

using vec3f = vec<float, 3>;
using vec3i = vec<int, 3>;
using vec3d = vec<double, 3>;