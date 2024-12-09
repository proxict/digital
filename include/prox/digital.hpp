/******************************************************************************
MIT License

Copyright (c) 2024 proxict

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/

#ifndef PROX_DIGITAL_HPP_
#define PROX_DIGITAL_HPP_

#include <cstdint>
#include <limits>
#include <ratio>

#ifndef PROX_DIGITAL_NAMESPACE_NAME
#define PROX_DIGITAL_NAMESPACE_NAME prox::digital
#endif

namespace PROX_DIGITAL_NAMESPACE_NAME {

template <typename TRep, typename TRatio = std::ratio<1>>
class unit;

namespace detail {

    template <typename T, T TValue, std::size_t TExp>
    struct pow;

    template <typename T, T TValue>
    struct pow<T, TValue, 1> {
        static constexpr T value = TValue;
    };

    template <typename T, T TValue>
    struct pow<T, TValue, 0> {
        static constexpr T value = 1;
    };

    template <typename T, T TValue, std::size_t TExp>
    struct pow {
        static constexpr T value = TValue * pow<T, TValue, TExp - 1>::value;
    };

    namespace aux {
        template <class T, template <class...> class TPrimary>
        struct is_specialization_of : std::false_type {};

        template <template <class...> class TPrimary, class... TArgs>
        struct is_specialization_of<TPrimary<TArgs...>, TPrimary> : std::true_type {};
    } // namespace aux

    template <class T, template <class...> class TPrimary>
    inline constexpr bool is_specialization_of_v = aux::is_specialization_of<T, TPrimary>::value;

    // number literals parsing - inspired by GNU
    namespace literal {
        namespace aux {
            namespace impl {
                template <unsigned TBase, unsigned TVal>
                struct digit : std::integral_constant<unsigned, TVal> {
                    static_assert(TVal < TBase, "digit outside of base range");
                    using valid = std::true_type;
                };
            } // namespace impl

            template <unsigned TBase, char TDig>
            struct digit;

            template <unsigned TBase>
            struct digit<TBase, '0'> : impl::digit<TBase, 0> {};

            template <unsigned TBase>
            struct digit<TBase, '1'> : impl::digit<TBase, 1> {};

            template <unsigned TBase>
            struct digit<TBase, '2'> : impl::digit<TBase, 2> {};

            template <unsigned TBase>
            struct digit<TBase, '3'> : impl::digit<TBase, 3> {};

            template <unsigned TBase>
            struct digit<TBase, '4'> : impl::digit<TBase, 4> {};

            template <unsigned TBase>
            struct digit<TBase, '5'> : impl::digit<TBase, 5> {};

            template <unsigned TBase>
            struct digit<TBase, '6'> : impl::digit<TBase, 6> {};

            template <unsigned TBase>
            struct digit<TBase, '7'> : impl::digit<TBase, 7> {};

            template <unsigned TBase>
            struct digit<TBase, '8'> : impl::digit<TBase, 8> {};

            template <unsigned TBase>
            struct digit<TBase, '9'> : impl::digit<TBase, 9> {};

            template <unsigned TBase>
            struct digit<TBase, 'a'> : impl::digit<TBase, 0xa> {};

            template <unsigned TBase>
            struct digit<TBase, 'A'> : impl::digit<TBase, 0xa> {};

            template <unsigned TBase>
            struct digit<TBase, 'b'> : impl::digit<TBase, 0xb> {};

            template <unsigned TBase>
            struct digit<TBase, 'B'> : impl::digit<TBase, 0xb> {};

            template <unsigned TBase>
            struct digit<TBase, 'c'> : impl::digit<TBase, 0xc> {};

            template <unsigned TBase>
            struct digit<TBase, 'C'> : impl::digit<TBase, 0xc> {};

            template <unsigned TBase>
            struct digit<TBase, 'd'> : impl::digit<TBase, 0xd> {};

            template <unsigned TBase>
            struct digit<TBase, 'D'> : impl::digit<TBase, 0xd> {};

            template <unsigned TBase>
            struct digit<TBase, 'e'> : impl::digit<TBase, 0xe> {};

            template <unsigned TBase>
            struct digit<TBase, 'E'> : impl::digit<TBase, 0xe> {};

            template <unsigned TBase>
            struct digit<TBase, 'f'> : impl::digit<TBase, 0xf> {};

            template <unsigned TBase>
            struct digit<TBase, 'F'> : impl::digit<TBase, 0xf> {};

            // digit separator (1'000'000)
            template <unsigned TBase>
            struct digit<TBase, '\''> : std::integral_constant<unsigned, 0> {
                using valid = std::false_type;
            };

            template <unsigned TBase, char TDig>
            inline constexpr bool is_valid_digit_v = digit<TBase, TDig>::valid::value;

            template <unsigned long long TVal>
            using ull_constant = std::integral_constant<unsigned long long, TVal>;

            // https://en.wikipedia.org/wiki/Positional_notation
            namespace impl {
                template <unsigned TBase, char TDig, char... TDigs>
                struct positional_notation {
                    using next = typename positional_notation<TBase, TDigs...>::type;
                    using type = ull_constant<next::value*(is_valid_digit_v<TBase, TDig> ? TBase : 1ULL)>;
                };

                template <unsigned TBase, char TDig>
                struct positional_notation<TBase, TDig> {
                    using type = ull_constant<is_valid_digit_v<TBase, TDig>>;
                };
            } // namespace impl

            template <unsigned TBase, char... TDigs>
            struct positional_notation : impl::positional_notation<TBase, TDigs...>::type {};

            template <unsigned TBase>
            struct positional_notation<TBase> : ull_constant<0> {};

            namespace impl {
                template <unsigned TBase, unsigned long long TPow, char TDig, char... TDigs>
                struct number {
                    static constexpr auto value = aux::digit<TBase, TDig>::value;
                    using next = number<TBase, is_valid_digit_v<TBase, TDig> ? TPow / TBase : TPow, TDigs...>;
                    using type = ull_constant<TPow * value + next::type::value>;
                    static_assert(
                        (type::value / TPow) == value,
                        "Integer literal does not fit in unsigned long long"
                    );
                };

                template <unsigned TBase, unsigned long long TPow, char TDig, char... TDigs>
                struct number<TBase, TPow, '\'', TDig, TDigs...> : number<TBase, TPow, TDig, TDigs...> {};

                template <unsigned TBase, char TDig>
                struct number<TBase, 1ULL, TDig> {
                    using type = ull_constant<aux::digit<TBase, TDig>::value>;
                };
            } // namespace impl

            template <unsigned TBase, char... TDigs>
            struct number : impl::number<TBase, positional_notation<TBase, TDigs...>::value, TDigs...>::type {
            };

            template <unsigned TBase>
            struct number<TBase> : ull_constant<0> {};

            template <char... TDigs>
            struct int_parser;

            template <char... TDigs>
            struct int_parser<'0', 'b', TDigs...> : number<2U, TDigs...>::type {};

            template <char... TDigs>
            struct int_parser<'0', 'B', TDigs...> : number<2U, TDigs...>::type {};

            template <char... TDigs>
            struct int_parser<'0', 'x', TDigs...> : number<16U, TDigs...>::type {};

            template <char... TDigs>
            struct int_parser<'0', 'X', TDigs...> : number<16U, TDigs...>::type {};

            template <char... TDigs>
            struct int_parser<'0', TDigs...> : number<8U, TDigs...>::type {};

            template <char... TDigs>
            struct int_parser : number<10U, TDigs...>::type {};

            template <typename R, typename T>
            constexpr bool in_range(T value) noexcept {
                constexpr R kMin = std::numeric_limits<R>::min();
                constexpr R kMax = std::numeric_limits<R>::max();

                if constexpr (std::is_signed_v<T> == std::is_signed_v<R>) {
                    return value >= kMin && value <= kMax;
                } else if constexpr (std::is_signed_v<T>) {
                    return value >= 0 && std::make_unsigned_t<T>(value) <= kMax;
                } else {
                    return value <= std::make_unsigned_t<R>(kMax);
                }
            }
        } // namespace aux

        template <typename TUnit, char... TDigits, auto TValue = aux::int_parser<TDigits...>::value>
        constexpr TUnit parse() {
            using UnitType = typename TUnit::rep;
            using aux::in_range;
            // clang-format off
            static_assert(in_range<UnitType>(TValue), "This value is out of range of the unit's representation type");
            // clang-format on
            return TUnit(TValue);
        }
    } // namespace literal

    namespace aux {
        template <std::int64_t TValue>
        struct abs : std::integral_constant<std::int64_t, (TValue < 0 ? -TValue : TValue)> {};

        template <std::int64_t TA, std::int64_t TB>
        struct gcd : gcd<TB, (TA % TB)> {};

        template <std::int64_t TA>
        struct gcd<TA, 0> : std::integral_constant<std::int64_t, abs<TA>::value> {};

        template <std::int64_t TB>
        struct gcd<0, TB> : std::integral_constant<std::int64_t, abs<TB>::value> {};

        template <
            typename TRatio1,
            typename TRatio2,
            std::int64_t TGcd1 = gcd<TRatio1::num, TRatio2::num>::value,
            std::int64_t TGcd2 = gcd<TRatio1::den, TRatio2::den>::value>
        using divide = std::ratio<
            (TRatio1::num / TGcd1) * (TRatio2::den / TGcd2),
            (TRatio1::den / TGcd2) * (TRatio2::num / TGcd1)>;
    } // namespace aux

    template <typename TRep, typename TRatio1, typename TRatio2, typename = void>
    struct unit_common_type {};

    template <typename TRep, typename TRatio1, typename TRatio2>
    struct unit_common_type<TRep, TRatio1, TRatio2, std::void_t<typename TRep::type>> {
    private:
        using GcdNum = aux::gcd<TRatio1::num, TRatio2::num>;
        using GcdDen = aux::gcd<TRatio1::den, TRatio2::den>;
        using TCommonRep = typename TRep::type;
        using TCommonRatio =
            typename std::ratio<GcdNum::value, (TRatio1::den / GcdDen::value) * TRatio2::den>::type;

    public:
        using type = unit<TCommonRep, TCommonRatio>;
    };

    template <typename TRatio1, typename TRatio2>
    using is_harmonic = std::bool_constant<aux::divide<TRatio2, TRatio1>::den == 1>;

    template <typename TRep1, typename TRep2, typename TCRep = std::common_type_t<TRep1, TRep2>>
    using common_rep = std::enable_if_t<std::is_convertible_v<const TRep2&, TCRep>, TCRep>;

    template <
        typename TTo,
        typename TDivide,
        typename TCommonRep,
        bool TNumIsOne = false,
        bool TDenIsOne = false>
    struct unit_cast {
        template <typename TRep, typename TRatio>
        constexpr TTo operator()(const unit<TRep, TRatio>& from) const {
            return TTo(static_cast<typename TTo::rep>(
                static_cast<TCommonRep>(from.value()) * static_cast<TCommonRep>(TDivide::num) /
                static_cast<TCommonRep>(TDivide::den)
            ));
        }
    };

    template <typename TTo, typename TDivide, typename TCommonRep>
    struct unit_cast<TTo, TDivide, TCommonRep, true, true> {
        template <typename TRep, typename TRatio>
        constexpr TTo operator()(const unit<TRep, TRatio>& from) const {
            return TTo(static_cast<typename TTo::rep>(from.value()));
        }
    };

    template <typename TTo, typename TDivide, typename TCommonRep>
    struct unit_cast<TTo, TDivide, TCommonRep, true, false> {
        template <typename TRep, typename TRatio>
        constexpr TTo operator()(const unit<TRep, TRatio>& from) const {
            return TTo(static_cast<typename TTo::rep>(
                static_cast<TCommonRep>(from.value()) / static_cast<TCommonRep>(TDivide::den)
            ));
        }
    };

    template <typename TTo, typename TDivide, typename TCommonRep>
    struct unit_cast<TTo, TDivide, TCommonRep, false, true> {
        template <typename TRep, typename TRatio>
        constexpr TTo operator()(const unit<TRep, TRatio>& from) const {
            return TTo(static_cast<typename TTo::rep>(
                static_cast<TCommonRep>(from.value()) * static_cast<TCommonRep>(TDivide::num)
            ));
        }
    };
} // namespace detail

using identity = std::ratio<1>;

using kilo = std::ratio<detail::pow<std::int64_t, 1000, 1>::value>;
using mega = std::ratio<detail::pow<std::int64_t, 1000, 2>::value>;
using giga = std::ratio<detail::pow<std::int64_t, 1000, 3>::value>;
using tera = std::ratio<detail::pow<std::int64_t, 1000, 4>::value>;
using peta = std::ratio<detail::pow<std::int64_t, 1000, 5>::value>;
using exa = std::ratio<detail::pow<std::int64_t, 1000, 6>::value>;

using kibi = std::ratio<detail::pow<std::int64_t, 1024, 1>::value>;
using mebi = std::ratio<detail::pow<std::int64_t, 1024, 2>::value>;
using gibi = std::ratio<detail::pow<std::int64_t, 1024, 3>::value>;
using tebi = std::ratio<detail::pow<std::int64_t, 1024, 4>::value>;
using pebi = std::ratio<detail::pow<std::int64_t, 1024, 5>::value>;
using exbi = std::ratio<detail::pow<std::int64_t, 1024, 6>::value>;

using bytes = unit<std::int64_t, identity>;
using kilobytes = unit<std::int64_t, kilo>;
using megabytes = unit<std::int64_t, mega>;
using gigabytes = unit<std::int64_t, giga>;
using terabytes = unit<std::int64_t, tera>;
using petabytes = unit<std::int64_t, peta>;
using exabytes = unit<std::int64_t, exa>;

using kibibytes = unit<std::int64_t, kibi>;
using mebibytes = unit<std::int64_t, mebi>;
using gibibytes = unit<std::int64_t, gibi>;
using tebibytes = unit<std::int64_t, tebi>;
using pebibytes = unit<std::int64_t, pebi>;
using exbibytes = unit<std::int64_t, exbi>;

template <typename TTo, typename TRep, typename TRatio>
constexpr auto unit_cast(unit<TRep, TRatio> from
) -> std::enable_if_t<detail::is_specialization_of_v<TTo, unit>, TTo> {
    if constexpr (std::is_same_v<TTo, unit<TRep, TRatio>>) {
        return from;
    } else {
        using TDivide = std::ratio_divide<TRatio, typename TTo::ratio>;
        using TCommonRep = std::common_type_t<typename TTo::rep, TRep, std::int64_t>;
        return detail::unit_cast<TTo, TDivide, TCommonRep, TDivide::num == 1, TDivide::den == 1>{}(from);
    }
}

template <typename TRep, typename TRatio>
class unit final {
public:
    using rep = TRep;
    using ratio = TRatio;

    static constexpr TRep zero() { return TRep(0); }
    static constexpr TRep min() { return std::numeric_limits<TRep>::lowest(); }
    static constexpr TRep max() { return std::numeric_limits<TRep>::max(); }

    constexpr unit() = default;

    template <
        typename TRep2,
        std::enable_if_t<
            std::is_convertible_v<const TRep2&, TRep> &&
                (std::is_floating_point_v<TRep> || !std::is_floating_point_v<TRep2>),
            bool> = true>
    constexpr explicit unit(const TRep2& other)
        : mValue(static_cast<TRep>(other)) {}

    template <
        typename TRep2,
        typename TRatio2,
        std::enable_if_t<
            std::is_convertible_v<const TRep2&, TRep> &&
                (std::is_floating_point_v<TRep> ||
                 (detail::is_harmonic<TRatio, TRatio2>::value && !std::is_floating_point_v<TRep2>)),
            bool> = true>
    constexpr unit(const unit<TRep2, TRatio2>& v)
        : mValue(unit_cast<unit>(v).value()) {}

    unit(const unit&) = default;

    unit& operator=(const unit&) = default;

    ~unit() = default;

    constexpr TRep value() const { return mValue; }

    constexpr auto operator+() const { return unit(mValue); }

    constexpr auto operator-() const { return unit(-mValue); }

    constexpr unit& operator++() {
        ++mValue;
        return *this;
    }

    constexpr unit operator++(int) { return unit(mValue++); }

    constexpr unit& operator--() {
        --mValue;
        return *this;
    }

    constexpr unit operator--(int) { return unit(mValue--); }

    constexpr unit& operator+=(const unit& rhs) {
        mValue += rhs.mValue;
        return *this;
    }

    constexpr unit& operator-=(const unit& rhs) {
        mValue -= rhs.mValue;
        return *this;
    }

    constexpr unit& operator*=(const TRep& rhs) {
        mValue *= rhs;
        return *this;
    }

    constexpr unit& operator/=(const TRep& rhs) {
        mValue /= rhs;
        return *this;
    }

    template <typename TRep2 = TRep>
    constexpr auto operator%=(const TRep& rhs) -> std::enable_if_t<!std::is_floating_point_v<TRep2>, unit&> {
        mValue %= rhs;
        return *this;
    }

    template <typename TRep2 = TRep>
    constexpr auto operator%=(const unit& rhs) -> std::enable_if_t<!std::is_floating_point_v<TRep2>, unit&> {
        mValue %= rhs.mValue;
        return *this;
    }

private:
    TRep mValue;
};

/// Comparison operators
template <typename TRep1, typename TRatio1, typename TRep2, typename TRatio2>
constexpr bool operator==(
    const PROX_DIGITAL_NAMESPACE_NAME::unit<TRep1, TRatio1>& lhs,
    const PROX_DIGITAL_NAMESPACE_NAME::unit<TRep2, TRatio2>& rhs
) {
    using TCT = std::common_type_t<decltype(lhs), decltype(rhs)>;
    if constexpr (std::is_same_v<TRatio1, TRatio2>) {
        return TCT(lhs).value() == TCT(rhs).value();
    } else {
        return unit_cast<TCT>(lhs).value() == unit_cast<TCT>(rhs).value();
    }
}

template <typename TRep1, typename TRatio1, typename TRep2, typename TRatio2>
constexpr bool operator!=(
    const PROX_DIGITAL_NAMESPACE_NAME::unit<TRep1, TRatio1>& lhs,
    const PROX_DIGITAL_NAMESPACE_NAME::unit<TRep2, TRatio2>& rhs
) {
    return !(rhs == lhs);
}

template <typename TRep1, typename TRatio1, typename TRep2, typename TRatio2>
constexpr bool operator<(
    const PROX_DIGITAL_NAMESPACE_NAME::unit<TRep1, TRatio1>& lhs,
    const PROX_DIGITAL_NAMESPACE_NAME::unit<TRep2, TRatio2>& rhs
) {
    using TCT = std::common_type_t<decltype(lhs), decltype(rhs)>;
    if constexpr (std::is_same<TRatio1, TRatio2>::value) {
        return TCT(lhs).value() < TCT(rhs).value();
    } else {
        return unit_cast<TCT>(lhs).value() < unit_cast<TCT>(rhs).value();
    }
}

template <typename TRep1, typename TRatio1, typename TRep2, typename TRatio2>
constexpr bool operator<=(
    const PROX_DIGITAL_NAMESPACE_NAME::unit<TRep1, TRatio1>& lhs,
    const PROX_DIGITAL_NAMESPACE_NAME::unit<TRep2, TRatio2>& rhs
) {
    return !(rhs < lhs);
}

template <typename TRep1, typename TRatio1, typename TRep2, typename TRatio2>
constexpr bool operator>(
    const PROX_DIGITAL_NAMESPACE_NAME::unit<TRep1, TRatio1>& lhs,
    const PROX_DIGITAL_NAMESPACE_NAME::unit<TRep2, TRatio2>& rhs
) {
    return rhs < lhs;
}

template <typename TRep1, typename TRatio1, typename TRep2, typename TRatio2>
constexpr bool operator>=(
    const PROX_DIGITAL_NAMESPACE_NAME::unit<TRep1, TRatio1>& lhs,
    const PROX_DIGITAL_NAMESPACE_NAME::unit<TRep2, TRatio2>& rhs
) {
    return !(lhs < rhs);
}

/// Arithmetic operators
template <typename TRep1, typename TRatio1, typename TRep2, typename TRatio2>
constexpr auto operator+(const unit<TRep1, TRatio1>& lhs, const unit<TRep2, TRatio2>& rhs)
    -> std::common_type_t<unit<TRep1, TRatio1>, unit<TRep2, TRatio2>> {
    using TCT = std::common_type_t<decltype(lhs), decltype(rhs)>;
    return TCT(TCT(lhs).value() + TCT(rhs).value());
}

template <typename TRep1, typename TRatio1, typename TRep2, typename TRatio2>
constexpr auto operator-(const unit<TRep1, TRatio1>& lhs, const unit<TRep2, TRatio2>& rhs)
    -> std::common_type_t<unit<TRep1, TRatio1>, unit<TRep2, TRatio2>> {
    using TCT = std::common_type_t<decltype(lhs), decltype(rhs)>;
    return TCT(TCT(lhs).value() - TCT(rhs).value());
}

template <typename TRep1, typename TRatio, typename TRep2>
constexpr unit<detail::common_rep<TRep1, TRep2>, TRatio> operator*(
    const unit<TRep1, TRatio>& lhs,
    const TRep2& rhs
) {
    using TCT = unit<std::common_type_t<TRep1, TRep2>, TRatio>;
    return TCT(TCT(lhs).value() * rhs);
}

template <typename TRep1, typename TRep2, typename TRatio>
constexpr unit<detail::common_rep<TRep2, TRep1>, TRatio> operator*(
    const TRep1& lhs,
    const unit<TRep2, TRatio>& rhs
) {
    return rhs * lhs;
}

template <typename TRep1, typename TRatio, typename TRep2>
constexpr unit<
    detail::common_rep<TRep1, std::enable_if_t<!detail::is_specialization_of_v<TRep2, unit>, TRep2>>,
    TRatio>
operator/(const unit<TRep1, TRatio>& lhs, const TRep2& rhs) {
    using TCT = unit<std::common_type_t<TRep1, TRep2>, TRatio>;
    return TCT(TCT(lhs).value() / rhs);
}

template <typename TRep1, typename TRatio1, typename TRep2, typename TRatio2>
constexpr auto operator/(const unit<TRep1, TRatio1>& lhs, const unit<TRep2, TRatio2>& rhs)
    -> std::common_type_t<TRep1, TRep2> {
    using TCT = std::common_type_t<decltype(lhs), decltype(rhs)>;
    return TCT(lhs).value() / TCT(rhs).value();
}

template <typename TRep1, typename TRatio, typename TRep2>
constexpr unit<
    detail::common_rep<TRep1, std::enable_if_t<!detail::is_specialization_of_v<TRep2, unit>, TRep2>>,
    TRatio>
operator%(const unit<TRep1, TRatio>& lhs, const TRep2& rhs) {
    using TCT = unit<std::common_type_t<TRep1, TRep2>, TRatio>;
    return TCT(TCT(lhs).value() % rhs);
}

template <typename TRep1, typename TRatio1, typename TRep2, typename TRatio2>
constexpr std::common_type_t<unit<TRep1, TRatio1>, unit<TRep2, TRatio2>> operator%(
    const unit<TRep1, TRatio1>& lhs,
    const unit<TRep2, TRatio2>& rhs
) {
    using TCT = std::common_type_t<decltype(lhs), decltype(rhs)>;
    return TCT(TCT(lhs).value() % TCT(rhs).value());
}

inline namespace literals {
    inline namespace unit_literals {
        // Technically, we could easily get away with:
        // `constexpr auto operator""_B(unsigned long long v);`
        // But parsing the literal manually allows us to handle overflows during compile-time.

        // power-10, integral
        template <char... TDigits>
        constexpr auto operator""_B() {
            return detail::literal::parse<bytes, TDigits...>();
        }

        template <char... TDigits>
        constexpr auto operator""_KB() {
            return detail::literal::parse<kilobytes, TDigits...>();
        }

        template <char... TDigits>
        constexpr auto operator""_MB() {
            return detail::literal::parse<megabytes, TDigits...>();
        }

        template <char... TDigits>
        constexpr auto operator""_GB() {
            return detail::literal::parse<gigabytes, TDigits...>();
        }

        template <char... TDigits>
        constexpr auto operator""_TB() {
            return detail::literal::parse<terabytes, TDigits...>();
        }

        template <char... TDigits>
        constexpr auto operator""_PB() {
            return detail::literal::parse<petabytes, TDigits...>();
        }

        template <char... TDigits>
        constexpr auto operator""_EB() {
            return detail::literal::parse<exabytes, TDigits...>();
        }

        // power-2, integral
        template <char... TDigits>
        constexpr auto operator""_KiB() {
            return detail::literal::parse<kibibytes, TDigits...>();
        }

        template <char... TDigits>
        constexpr auto operator""_MiB() {
            return detail::literal::parse<mebibytes, TDigits...>();
        }

        template <char... TDigits>
        constexpr auto operator""_GiB() {
            return detail::literal::parse<gibibytes, TDigits...>();
        }

        template <char... TDigits>
        constexpr auto operator""_TiB() {
            return detail::literal::parse<tebibytes, TDigits...>();
        }

        template <char... TDigits>
        constexpr auto operator""_PiB() {
            return detail::literal::parse<pebibytes, TDigits...>();
        }

        template <char... TDigits>
        constexpr auto operator""_EiB() {
            return detail::literal::parse<exbibytes, TDigits...>();
        }

        // power-10, floating
        constexpr auto operator""_B(long double x) {
            return unit<long double, identity>(x);
        }

        constexpr auto operator""_KB(long double x) {
            return unit<long double, kilo>(x);
        }

        constexpr auto operator""_MB(long double x) {
            return unit<long double, mega>(x);
        }

        constexpr auto operator""_GB(long double x) {
            return unit<long double, giga>(x);
        }

        constexpr auto operator""_TB(long double x) {
            return unit<long double, tera>(x);
        }

        constexpr auto operator""_PB(long double x) {
            return unit<long double, peta>(x);
        }

        constexpr auto operator""_EB(long double x) {
            return unit<long double, exa>(x);
        }

        // power-2, floating
        constexpr auto operator""_KiB(long double x) {
            return unit<long double, kibi>(x);
        }

        constexpr auto operator""_MiB(long double x) {
            return unit<long double, mebi>(x);
        }

        constexpr auto operator""_GiB(long double x) {
            return unit<long double, gibi>(x);
        }

        constexpr auto operator""_TiB(long double x) {
            return unit<long double, tebi>(x);
        }

        constexpr auto operator""_PiB(long double x) {
            return unit<long double, pebi>(x);
        }

        constexpr auto operator""_EiB(long double x) {
            return unit<long double, exbi>(x);
        }
    } // namespace unit_literals
} // namespace literals
} // namespace PROX_DIGITAL_NAMESPACE_NAME

namespace std {
template <typename TRep1, typename TRatio1, typename TRep2, typename TRatio2>
struct common_type<
    PROX_DIGITAL_NAMESPACE_NAME::unit<TRep1, TRatio1>,
    PROX_DIGITAL_NAMESPACE_NAME::unit<TRep2, TRatio2>>
    : PROX_DIGITAL_NAMESPACE_NAME::detail::
          unit_common_type<common_type<TRep1, TRep2>, typename TRatio1::type, typename TRatio2::type> {};

template <typename TRep, typename TRatio>
struct common_type<
    PROX_DIGITAL_NAMESPACE_NAME::unit<TRep, TRatio>,
    PROX_DIGITAL_NAMESPACE_NAME::unit<TRep, TRatio>> {
    using type = PROX_DIGITAL_NAMESPACE_NAME::unit<typename common_type<TRep>::type, typename TRatio::type>;
};

template <typename TRep, typename TRatio>
struct common_type<PROX_DIGITAL_NAMESPACE_NAME::unit<TRep, TRatio>> {
    using type = PROX_DIGITAL_NAMESPACE_NAME::unit<typename common_type<TRep>::type, typename TRatio::type>;
};

template <typename T>
struct hash;

template <typename TRep, typename TRatio>
struct hash<PROX_DIGITAL_NAMESPACE_NAME::unit<TRep, TRatio>> {
    constexpr std::size_t operator()(const PROX_DIGITAL_NAMESPACE_NAME::unit<TRep, TRatio>& u) const {
        return std::hash<TRep>{}(u.value());
    }
};
} // namespace std

#endif // PROX_DIGITAL_HPP_
