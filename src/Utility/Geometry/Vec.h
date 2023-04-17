#pragma once

#include <cmath>
#include <cstdint>
#include <type_traits>

template<class From, class To>
struct vector_conversion_allowed : std::false_type {};

#define MM_ALLOW_VECTOR_CONVERSION(FROM, TO) \
template<> \
struct vector_conversion_allowed<FROM, TO> : std::true_type {};

MM_ALLOW_VECTOR_CONVERSION(int16_t, int32_t)
MM_ALLOW_VECTOR_CONVERSION(int16_t, int64_t)
MM_ALLOW_VECTOR_CONVERSION(int32_t, int64_t)

template <class T>
struct Vec2 {
    T x = 0;
    T y = 0;

    Vec2() = default;
    Vec2(T a, T b) : x(a), y(b) {}

    [[nodiscard]] auto lengthSqr() const {
        // Note that auto return type is important because this way Vec2s::LengthSqr returns int.
        return x * x + y * y;
    }

    friend Vec2 operator+(const Vec2 &l, const Vec2 &r) {
        return Vec2(l.x + r.x, l.y + r.y);
    }

    friend Vec2 operator-(const Vec2 &l, const Vec2 &r) {
        return Vec2(l.x - r.x, l.y - r.y);
    }

    friend Vec2 operator/(const Vec2 &l, T r) {
        return Vec2(l.x / r, l.y / r);
    }

    friend Vec2 operator*(const Vec2 &l, T r) {
        return Vec2(l.x * r, l.y * r);
    }

    friend Vec2 operator*(T l, const Vec2 &r) {
        return r * l;
    }

    Vec2 &operator+=(const Vec2 &v) {
        *this = *this + v;
        return *this;
    }

    Vec2 &operator-=(const Vec2 &v) {
        *this = *this - v;
        return *this;
    }

    friend T dot(const Vec2 &l, const Vec2 &r) {
        return l.x * r.x + l.y * r.y;
    }
};

using Vec2i = Vec2<int32_t>;
using Vec2f = Vec2<float>;

static_assert(sizeof(Vec2i) == 8);
static_assert(sizeof(Vec2f) == 8);


template <class T>
struct Vec3 {
    T x = 0;
    T y = 0;
    T z = 0;

    Vec3() = default;
    Vec3(const Vec3 &other) = default;

    template<class OtherT> requires vector_conversion_allowed<OtherT, T>::value
    Vec3(const Vec3<OtherT> &other) : x(other.x), y(other.y), z(other.z) {}

    Vec3(T a, T b, T c) : x(a), y(b), z(c) {}

    Vec2<T> getXY() {
        return Vec2<T>(x, y);
    }

    static void rotate(T sDepth, T yaw, T pitch, Vec3<T> v, T *outx, T *outy, T *outz) {
        float cosf_x = cos(M_PI * pitch / 1024.0f);
        float sinf_x = sin(M_PI * pitch / 1024.0f);
        float cosf_y = cos(M_PI * yaw / 1024.0f);
        float sinf_y = sin(M_PI * yaw / 1024.0f);

        *outx = v.x + (int)(sinf_y * cosf_x * (float)(sDepth /*>> 16*/));
        *outy = v.y + (int)(cosf_y * cosf_x * (float)(sDepth /*>> 16*/));
        *outz = v.z + (int)(sinf_x * (float)(sDepth /*>> 16*/));
    }

    void normalize() requires std::is_floating_point_v<T> {
        T denom = static_cast<T>(1.0) / this->length();
        x *= denom;
        y *= denom;
        z *= denom;
    }

    [[nodiscard]] Vec3<short> toShort() const requires std::is_floating_point_v<T> {
        return Vec3<short>(std::round(x), std::round(y), std::round(z));
    }

    [[nodiscard]] Vec3<int> toInt() const requires std::is_floating_point_v<T> {
        return Vec3<int>(std::round(x), std::round(y), std::round(z));
    }

    // TODO(captainurist): we introduced this one because we couldn't easily retrace old traces, but now we can. Drop!
    [[nodiscard]] Vec3<int> toIntTrunc() const requires std::is_floating_point_v<T> {
        return Vec3<int>(std::trunc(x), std::trunc(y), std::trunc(z));
    }

    [[nodiscard]] Vec3<int> toFixpoint() const requires std::is_floating_point_v<T> {
        return Vec3<int>(std::round(x * 65536.0), std::round(y * 65536.0), std::round(z * 65536.0));
    }

    [[nodiscard]] Vec3<float> toFloat() const requires std::is_integral_v<T> {
        return Vec3<float>(x, y, z);
    }

    [[nodiscard]] Vec3<float> toFloatFromFixpoint() const requires std::is_integral_v<T> {
        return Vec3<float>(x / 65536.0, y / 65536.0, z / 65536.0);
    }

    [[nodiscard]] auto lengthSqr() const {
        // Note that auto return type is important because this way Vec3s::LengthSqr returns int.
        return x * x + y * y + z * z;
    }

    [[nodiscard]] T length() const {
        return std::sqrt(lengthSqr());
    }

    friend Vec3 operator+(const Vec3 &l, const Vec3 &r) {
        return Vec3(l.x + r.x, l.y + r.y, l.z + r.z);
    }

    friend Vec3 operator-(const Vec3 &l, const Vec3 &r) {
        return Vec3(l.x - r.x, l.y - r.y, l.z - r.z);
    }

    friend Vec3 operator/(const Vec3 &l, T r) {
        return Vec3(l.x / r, l.y / r, l.z / r);
    }

    friend Vec3 operator*(const Vec3 &l, T r) {
        return Vec3(l.x * r, l.y * r, l.z * r);
    }

    friend Vec3 operator*(T l, const Vec3 &r) {
        return r * l;
    }

    Vec3 &operator+=(const Vec3 &v) {
        *this = *this + v;
        return *this;
    }

    Vec3 &operator-=(const Vec3 &v) {
        *this = *this - v;
        return *this;
    }

    friend Vec3 cross(const Vec3 &l, const Vec3 &r) {
        return Vec3(l.y * r.z - l.z * r.y, l.z * r.x - l.x * r.z, l.x * r.y - l.y * r.x);
    }

    friend T dot(const Vec3 &l, const Vec3 &r) {
        return l.x * r.x + l.y * r.y + l.z * r.z;
    }
};

using Vec3s = Vec3<int16_t>;
using Vec3i = Vec3<int32_t>;
using Vec3f = Vec3<float>;

static_assert(sizeof(Vec3s) == 6);
static_assert(sizeof(Vec3i) == 12);
static_assert(sizeof(Vec3f) == 12);
