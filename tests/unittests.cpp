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

#include <prox/digital.hpp>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

namespace digital = PROX_DIGITAL_NAMESPACE_NAME;
using namespace digital::unit_literals;

constexpr std::int64_t operator"" _i64(unsigned long long v) {
    return static_cast<std::int64_t>(v);
}

namespace doctest {
template <typename TRep, typename TRatio>
struct StringMaker<PROX_DIGITAL_NAMESPACE_NAME::unit<TRep, TRatio>> {
    static String convert(const PROX_DIGITAL_NAMESPACE_NAME::unit<TRep, TRatio>& value) {
        auto s = std::to_string(value.value());
        if constexpr (std::is_same_v<TRatio, PROX_DIGITAL_NAMESPACE_NAME::identity>) {
            s += " B";
        } else if constexpr (std::is_same_v<TRatio, PROX_DIGITAL_NAMESPACE_NAME::kilo>) {
            s += " KB";
        } else if constexpr (std::is_same_v<TRatio, PROX_DIGITAL_NAMESPACE_NAME::mega>) {
            s += " MB";
        } else if constexpr (std::is_same_v<TRatio, PROX_DIGITAL_NAMESPACE_NAME::giga>) {
            s += " GB";
        } else if constexpr (std::is_same_v<TRatio, PROX_DIGITAL_NAMESPACE_NAME::tera>) {
            s += " TB";
        } else if constexpr (std::is_same_v<TRatio, PROX_DIGITAL_NAMESPACE_NAME::peta>) {
            s += " PB";
        } else if constexpr (std::is_same_v<TRatio, PROX_DIGITAL_NAMESPACE_NAME::exa>) {
            s += " EB";
        } else if constexpr (std::is_same_v<TRatio, PROX_DIGITAL_NAMESPACE_NAME::kibi>) {
            s += " KiB";
        } else if constexpr (std::is_same_v<TRatio, PROX_DIGITAL_NAMESPACE_NAME::mebi>) {
            s += " MiB";
        } else if constexpr (std::is_same_v<TRatio, PROX_DIGITAL_NAMESPACE_NAME::gibi>) {
            s += " GiB";
        } else if constexpr (std::is_same_v<TRatio, PROX_DIGITAL_NAMESPACE_NAME::tebi>) {
            s += " TiB";
        } else if constexpr (std::is_same_v<TRatio, PROX_DIGITAL_NAMESPACE_NAME::pebi>) {
            s += " PiB";
        } else if constexpr (std::is_same_v<TRatio, PROX_DIGITAL_NAMESPACE_NAME::exbi>) {
            s += " EiB";
        } else {
            s += " ?B";
        }
        return String(s.c_str(), static_cast<String::size_type>(s.size()));
    }
};
} // namespace doctest

TEST_CASE("bytes") {
    CHECK((0_B).value() == 0_i64);
    CHECK(digital::unit_cast<digital::bytes>(1_B).value() == 1_i64);

    CHECK(digital::unit_cast<digital::bytes>(2_KB).value() == 2000_i64);
    CHECK(digital::unit_cast<digital::bytes>(4_MB).value() == 4'000'000_i64);
    CHECK(digital::unit_cast<digital::bytes>(8_GB).value() == 8'000'000'000_i64);

    CHECK(digital::unit_cast<digital::bytes>(1_TB).value() == 1'000'000'000'000_i64);
    CHECK(digital::unit_cast<digital::bytes>(1_PB).value() == 1'000'000'000'000'000_i64);
    CHECK(digital::unit_cast<digital::bytes>(1_EB).value() == 1'000'000'000'000'000'000_i64);

    CHECK(digital::unit_cast<digital::bytes>(2_KiB).value() == 2048_i64);
    CHECK(digital::unit_cast<digital::bytes>(4_MiB).value() == 4'194'304_i64);
    CHECK(digital::unit_cast<digital::bytes>(8_GiB).value() == 8'589'934'592_i64);

    CHECK(digital::unit_cast<digital::bytes>(1_TiB).value() == 1'099'511'627'776_i64);
    CHECK(digital::unit_cast<digital::bytes>(1_PiB).value() == 1'125'899'906'842'624_i64);
    CHECK(digital::unit_cast<digital::bytes>(1_EiB).value() == 1'152'921'504'606'846'976_i64);
}

TEST_CASE("kilobytes") {
    CHECK(digital::unit_cast<digital::kilobytes>(1_B).value() == 0_i64);

    CHECK(digital::unit_cast<digital::kilobytes>(2_KB).value() == 2_i64);
    CHECK(digital::unit_cast<digital::kilobytes>(4_MB).value() == 4'000_i64);
    CHECK(digital::unit_cast<digital::kilobytes>(8_GB).value() == 8'000'000_i64);

    CHECK(digital::unit_cast<digital::kilobytes>(1_TB).value() == 1'000'000'000_i64);
    CHECK(digital::unit_cast<digital::kilobytes>(1_PB).value() == 1'000'000'000'000_i64);
    CHECK(digital::unit_cast<digital::kilobytes>(1_EB).value() == 1'000'000'000'000'000_i64);

    CHECK(digital::unit_cast<digital::kilobytes>(2_KiB).value() == 2_i64);
    CHECK(digital::unit_cast<digital::kilobytes>(4_MiB).value() == 4'194_i64);
    CHECK(digital::unit_cast<digital::kilobytes>(8_GiB).value() == 8'589'934_i64);

    CHECK(digital::unit_cast<digital::kilobytes>(1_TiB).value() == 1'099'511'627_i64);
    CHECK(digital::unit_cast<digital::kilobytes>(1_PiB).value() == 1'125'899'906'842_i64);
    CHECK(digital::unit_cast<digital::kilobytes>(1_EiB).value() == 1'152'921'504'606'846_i64);
}

TEST_CASE("megabytes") {
    CHECK(digital::unit_cast<digital::megabytes>(1_B).value() == 0_i64);

    CHECK(digital::unit_cast<digital::megabytes>(2_KB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::megabytes>(4_MB).value() == 4_i64);
    CHECK(digital::unit_cast<digital::megabytes>(8_GB).value() == 8'000_i64);

    CHECK(digital::unit_cast<digital::megabytes>(1_TB).value() == 1'000'000_i64);
    CHECK(digital::unit_cast<digital::megabytes>(1_PB).value() == 1'000'000'000_i64);
    CHECK(digital::unit_cast<digital::megabytes>(1_EB).value() == 1'000'000'000'000_i64);

    CHECK(digital::unit_cast<digital::megabytes>(2_KiB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::megabytes>(4_MiB).value() == 4_i64);
    CHECK(digital::unit_cast<digital::megabytes>(8_GiB).value() == 8'589_i64);

    CHECK(digital::unit_cast<digital::megabytes>(1_TiB).value() == 1'099'511_i64);
    CHECK(digital::unit_cast<digital::megabytes>(1_PiB).value() == 1'125'899'906_i64);
    CHECK(digital::unit_cast<digital::megabytes>(1_EiB).value() == 1'152'921'504'606_i64);
}

TEST_CASE("gigabytes") {
    CHECK(digital::unit_cast<digital::gigabytes>(1_B).value() == 0_i64);

    CHECK(digital::unit_cast<digital::gigabytes>(2_KB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::gigabytes>(4_MB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::gigabytes>(8_GB).value() == 8_i64);

    CHECK(digital::unit_cast<digital::gigabytes>(1_TB).value() == 1'000_i64);
    CHECK(digital::unit_cast<digital::gigabytes>(1_PB).value() == 1'000'000_i64);
    CHECK(digital::unit_cast<digital::gigabytes>(1_EB).value() == 1'000'000'000_i64);

    CHECK(digital::unit_cast<digital::gigabytes>(2_KiB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::gigabytes>(4_MiB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::gigabytes>(8_GiB).value() == 8_i64);

    CHECK(digital::unit_cast<digital::gigabytes>(1_TiB).value() == 1'099_i64);
    CHECK(digital::unit_cast<digital::gigabytes>(1_PiB).value() == 1'125'899_i64);
    CHECK(digital::unit_cast<digital::gigabytes>(1_EiB).value() == 1'152'921'504_i64);
}

TEST_CASE("terabytes") {
    CHECK(digital::unit_cast<digital::terabytes>(1_B).value() == 0_i64);

    CHECK(digital::unit_cast<digital::terabytes>(2_KB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::terabytes>(4_MB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::terabytes>(8_GB).value() == 0_i64);

    CHECK(digital::unit_cast<digital::terabytes>(1_TB).value() == 1_i64);
    CHECK(digital::unit_cast<digital::terabytes>(1_PB).value() == 1'000_i64);
    CHECK(digital::unit_cast<digital::terabytes>(1_EB).value() == 1'000'000_i64);

    CHECK(digital::unit_cast<digital::terabytes>(2_KiB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::terabytes>(4_MiB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::terabytes>(8_GiB).value() == 0_i64);

    CHECK(digital::unit_cast<digital::terabytes>(1_TiB).value() == 1_i64);
    CHECK(digital::unit_cast<digital::terabytes>(1_PiB).value() == 1'125_i64);
    CHECK(digital::unit_cast<digital::terabytes>(1_EiB).value() == 1'152'921_i64);
}

TEST_CASE("petabytes") {
    CHECK(digital::unit_cast<digital::petabytes>(1_B).value() == 0_i64);

    CHECK(digital::unit_cast<digital::petabytes>(2_KB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::petabytes>(4_MB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::petabytes>(8_GB).value() == 0_i64);

    CHECK(digital::unit_cast<digital::petabytes>(1_TB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::petabytes>(1_PB).value() == 1_i64);
    CHECK(digital::unit_cast<digital::petabytes>(1_EB).value() == 1'000_i64);

    CHECK(digital::unit_cast<digital::petabytes>(2_KiB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::petabytes>(4_MiB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::petabytes>(8_GiB).value() == 0_i64);

    CHECK(digital::unit_cast<digital::petabytes>(1_TiB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::petabytes>(1_PiB).value() == 1_i64);
    CHECK(digital::unit_cast<digital::petabytes>(1_EiB).value() == 1'152_i64);
}

TEST_CASE("exabytes") {
    CHECK(digital::unit_cast<digital::exabytes>(1_B).value() == 0_i64);

    CHECK(digital::unit_cast<digital::exabytes>(2_KB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::exabytes>(4_MB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::exabytes>(8_GB).value() == 0_i64);

    CHECK(digital::unit_cast<digital::exabytes>(1_TB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::exabytes>(1_PB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::exabytes>(1_EB).value() == 1_i64);

    CHECK(digital::unit_cast<digital::exabytes>(2_KiB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::exabytes>(4_MiB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::exabytes>(8_GiB).value() == 0_i64);

    CHECK(digital::unit_cast<digital::exabytes>(1_TiB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::exabytes>(1_PiB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::exabytes>(1_EiB).value() == 1_i64);
}

TEST_CASE("kibibytes") {
    CHECK(digital::unit_cast<digital::kibibytes>(1_B).value() == 0_i64);

    CHECK(digital::unit_cast<digital::kibibytes>(2_KB).value() == 1_i64);
    CHECK(digital::unit_cast<digital::kibibytes>(4_MB).value() == 3'906_i64);
    CHECK(digital::unit_cast<digital::kibibytes>(8_GB).value() == 7'812'500_i64);

    CHECK(digital::unit_cast<digital::kibibytes>(1_TB).value() == 976'562'500_i64);
    CHECK(digital::unit_cast<digital::kibibytes>(1_PB).value() == 976'562'500'000_i64);
    CHECK(digital::unit_cast<digital::kibibytes>(1_EB).value() == 976'562'500'000'000_i64);

    CHECK(digital::unit_cast<digital::kibibytes>(2_KiB).value() == 2_i64);
    CHECK(digital::unit_cast<digital::kibibytes>(4_MiB).value() == 4'096_i64);
    CHECK(digital::unit_cast<digital::kibibytes>(8_GiB).value() == 8'388'608_i64);

    CHECK(digital::unit_cast<digital::kibibytes>(1_TiB).value() == 1'073'741'824_i64);
    CHECK(digital::unit_cast<digital::kibibytes>(1_PiB).value() == 1'099'511'627'776_i64);
    CHECK(digital::unit_cast<digital::kibibytes>(1_EiB).value() == 1'125'899'906'842'624_i64);
}

TEST_CASE("mebibytes") {
    CHECK(digital::unit_cast<digital::mebibytes>(1_B).value() == 0_i64);

    CHECK(digital::unit_cast<digital::mebibytes>(2_KB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::mebibytes>(4_MB).value() == 3_i64);
    CHECK(digital::unit_cast<digital::mebibytes>(8_GB).value() == 7'629_i64);

    CHECK(digital::unit_cast<digital::mebibytes>(1_TB).value() == 953'674_i64);
    CHECK(digital::unit_cast<digital::mebibytes>(1_PB).value() == 953'674'316_i64);
    CHECK(digital::unit_cast<digital::mebibytes>(1_EB).value() == 953'674'316'406_i64);

    CHECK(digital::unit_cast<digital::mebibytes>(2_KiB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::mebibytes>(4_MiB).value() == 4_i64);
    CHECK(digital::unit_cast<digital::mebibytes>(8_GiB).value() == 8'192_i64);

    CHECK(digital::unit_cast<digital::mebibytes>(1_TiB).value() == 1'048'576_i64);
    CHECK(digital::unit_cast<digital::mebibytes>(1_PiB).value() == 1'073'741'824_i64);
    CHECK(digital::unit_cast<digital::mebibytes>(1_EiB).value() == 1'099'511'627'776_i64);
}

TEST_CASE("gibibytes") {
    CHECK(digital::unit_cast<digital::gibibytes>(1_B).value() == 0_i64);

    CHECK(digital::unit_cast<digital::gibibytes>(2_KB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::gibibytes>(4_MB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::gibibytes>(8_GB).value() == 7_i64);

    CHECK(digital::unit_cast<digital::gibibytes>(1_TB).value() == 931_i64);
    CHECK(digital::unit_cast<digital::gibibytes>(1_PB).value() == 931'322_i64);
    CHECK(digital::unit_cast<digital::gibibytes>(1_EB).value() == 931'322'574_i64);

    CHECK(digital::unit_cast<digital::gibibytes>(2_KiB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::gibibytes>(4_MiB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::gibibytes>(8_GiB).value() == 8_i64);

    CHECK(digital::unit_cast<digital::gibibytes>(1_TiB).value() == 1'024_i64);
    CHECK(digital::unit_cast<digital::gibibytes>(1_PiB).value() == 1'048'576_i64);
    CHECK(digital::unit_cast<digital::gibibytes>(1_EiB).value() == 1'073'741'824_i64);
}

TEST_CASE("tebibytes") {
    CHECK(digital::unit_cast<digital::tebibytes>(1_B).value() == 0_i64);

    CHECK(digital::unit_cast<digital::tebibytes>(2_KB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::tebibytes>(4_MB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::tebibytes>(8_GB).value() == 0_i64);

    CHECK(digital::unit_cast<digital::tebibytes>(1_TB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::tebibytes>(1_PB).value() == 909_i64);
    CHECK(digital::unit_cast<digital::tebibytes>(1_EB).value() == 909'494_i64);

    CHECK(digital::unit_cast<digital::tebibytes>(2_KiB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::tebibytes>(4_MiB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::tebibytes>(8_GiB).value() == 0_i64);

    CHECK(digital::unit_cast<digital::tebibytes>(1_TiB).value() == 1_i64);
    CHECK(digital::unit_cast<digital::tebibytes>(1_PiB).value() == 1'024_i64);
    CHECK(digital::unit_cast<digital::tebibytes>(1_EiB).value() == 1'048'576_i64);
}

TEST_CASE("pebibytes") {
    CHECK(digital::unit_cast<digital::pebibytes>(1_B).value() == 0_i64);

    CHECK(digital::unit_cast<digital::pebibytes>(2_KB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::pebibytes>(4_MB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::pebibytes>(8_GB).value() == 0_i64);

    CHECK(digital::unit_cast<digital::pebibytes>(1_TB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::pebibytes>(1_PB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::pebibytes>(1_EB).value() == 888_i64);

    CHECK(digital::unit_cast<digital::pebibytes>(2_KiB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::pebibytes>(4_MiB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::pebibytes>(8_GiB).value() == 0_i64);

    CHECK(digital::unit_cast<digital::pebibytes>(1_TiB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::pebibytes>(1_PiB).value() == 1_i64);
    CHECK(digital::unit_cast<digital::pebibytes>(1_EiB).value() == 1'024_i64);
}

TEST_CASE("exbibytes") {
    CHECK(digital::unit_cast<digital::exbibytes>(1_B).value() == 0_i64);

    CHECK(digital::unit_cast<digital::exbibytes>(2_KB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::exbibytes>(4_MB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::exbibytes>(8_GB).value() == 0_i64);

    CHECK(digital::unit_cast<digital::exbibytes>(1_TB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::exbibytes>(1_PB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::exbibytes>(1_EB).value() == 0_i64);

    CHECK(digital::unit_cast<digital::exbibytes>(2_KiB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::exbibytes>(4_MiB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::exbibytes>(8_GiB).value() == 0_i64);

    CHECK(digital::unit_cast<digital::exbibytes>(1_TiB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::exbibytes>(1_PiB).value() == 0_i64);
    CHECK(digital::unit_cast<digital::exbibytes>(1_EiB).value() == 1_i64);
}

TEST_CASE("fractional") {
    CHECK(digital::unit_cast<digital::unit<float, digital::kibi>>(1_KiB).value() == doctest::Approx(1.0));
    CHECK(
        digital::unit_cast<digital::unit<float, digital::kibi>>(digital::unit<double, digital::kibi>(1))
            .value() == doctest::Approx(1.0)
    );
    CHECK(digital::unit_cast<digital::unit<float, digital::kilo>>(1_KiB).value() == doctest::Approx(1.024));
    CHECK(
        digital::unit_cast<digital::unit<float, digital::kibi>>(1_KB).value() == doctest::Approx(0.9765625)
    );
    CHECK(
        digital::unit_cast<digital::unit<float, digital::mebi>>(1_KiB).value() ==
        doctest::Approx(0.0009765625)
    );
    CHECK(digital::unit_cast<digital::unit<float, digital::kibi>>(1_MiB).value() == doctest::Approx(1024.0));
}

TEST_CASE("equality operator") {
    CHECK(123456789_B == 123456789.0_B);

    CHECK(-1_B == -1_B);
    CHECK(0_B == 0_B);
    CHECK(1_B == 1_B);

    CHECK(1_KiB == 1_KiB);
    CHECK(2_MiB == 2_MiB);
    CHECK(3_GiB == 3_GiB);
    CHECK(4_TiB == 4_TiB);
    CHECK(5_PiB == 5_PiB);
    CHECK(6_EiB == 6_EiB);

    CHECK(2_GiB == 2048_MiB);
    CHECK(2_GB == 2000_MB);

    CHECK(1_MiB == 1024_KiB);
    CHECK(1'048'576_B == 1_MiB);
    CHECK(1'048'576_B == 1024_KiB);

    CHECK(0.5_KiB == 512_B);
    CHECK(1.0_KiB == 1024_B);
    CHECK(1.5_KiB == 1'536_B);

    CHECK(digital::unit<std::uint64_t, digital::mebi>(42) == digital::unit<float, digital::mebi>(42.0f));
    CHECK(
        digital::unit<std::int64_t, digital::exbi>(9223372036854775807) ==
        digital::unit<std::int64_t, digital::exbi>(9223372036854775807)
    );
}

TEST_CASE("non-decimal base") {
    CHECK(0x123456789abcdef_B == 81'985'529'216'486'895_B);
    CHECK(0644_B == 420_B);
    CHECK(-0755_B == -493_B);
    CHECK(-010000_B == -4_KiB);
}

TEST_CASE("non-equality operator") {
    CHECK(0_B != 1_B);

    CHECK(1_KiB != -1_KB);
    CHECK(1_KiB != 0_KB);
    CHECK(1_KiB != 1_KB);
    CHECK(1_KiB != 2_KB);
    CHECK(1_KiB != 3_KB);

    CHECK(1_KiB != 1000_B);
    CHECK(1_KiB != 1023_B);
    CHECK(1_KiB != 1025_B);

    CHECK(8_GiB != 8_GB);

    CHECK(0.5_KiB != 511_B);
    CHECK(0.5_KiB != 513_B);
    CHECK(1.0_KiB != 1023_B);
    CHECK(1.0_KiB != 1025_B);
    CHECK(1.5_KiB != 1'535_B);
    CHECK(1.5_KiB != 1'537_B);

    CHECK(digital::unit<std::uint64_t, digital::mebi>(42) != digital::unit<float, digital::mebi>(42.01f));
}

TEST_CASE("less-than operator") {
    CHECK(0_B < 1_B);
    CHECK(-1_B < 0_B);
    CHECK(-2_B < -1_B);

    CHECK(0_B < 0.1_B);
    CHECK(0.5_B < 1_B);

    CHECK(1_KB < 1_KiB);
    CHECK(1_KiB < 1_MiB);
}

TEST_CASE("less-than-equal operator") {
    CHECK(0_B <= 1_B);
    CHECK(1.024_KB <= 1_KiB);
    CHECK(1_KiB <= 1024_B);
    CHECK(1024.0_KiB <= 1_MiB);
    CHECK(1_PiB <= 1_EiB);

    CHECK(1023.9_KiB <= 1_MiB);
    CHECK(1023_PiB <= 1_EiB);
    CHECK(1024_PiB <= 1_EiB);
    CHECK(1025_PiB <= 10_EiB);
}

TEST_CASE("greater-than operator") {
    CHECK(1_B > 0_B);
    CHECK(0_B > -1_B);
    CHECK(-1_B > -2_B);

    CHECK(0.1_B > 0_B);
    CHECK(1_B > 0.5_B);

    CHECK(1_KiB > 1_KB);
    CHECK(1_MiB > 1_KiB);

    CHECK(1_MiB > 1023.9_KiB);
}

TEST_CASE("greater-than-equal operator") {
    CHECK(1_B >= 0_B);
    CHECK(1_KiB >= 1.024_KB);
    CHECK(1024_B >= 1_KiB);
    CHECK(1_MiB >= 1024.0_KiB);
    CHECK(1_EiB >= 1023_PiB);
    CHECK(1_EiB >= 1024_PiB);
    CHECK(10_EiB >= 1025_PiB);
}

TEST_CASE("operator+") {
    CHECK((+42.0_GB).value() == 42.0);
    CHECK(+42.0_TB == 42_TB);
    CHECK(100_PB - +58.0_PB == 42.0_PB);
    CHECK(+42.0_TB == +42_TB);
    CHECK(30_EB + +12000.0_PB == 42.0_EB);
}

TEST_CASE("operator-") {
    CHECK((-42.0_TiB).value() == -42.0);
    CHECK(-42.0_PiB == -43008.0_TiB);
    CHECK(30_GiB - -12288.0_MiB == 42.0_GiB);
    CHECK(-30_EiB + -12288.0_PiB == -42.0_EiB);
}

TEST_CASE("pre-increment operator identity") {
    digital::bytes value = 512_B;
    auto newValue = ++value;
    CHECK(value == 513_B);
    CHECK(newValue == 513_B);

    value = 1_KiB;      // The 1 KiB will get converted to bytes
    newValue = ++value; // expecting to add 1 unit of bytes
    CHECK(value == 1025_B);
    CHECK(newValue == 1025_B);
}

TEST_CASE("pre-increment operator kibi") {
    digital::kibibytes value = 1_KiB;
    auto newValue = ++value;
    CHECK(value == 2_KiB);
    CHECK(newValue == 2_KiB);
}

TEST_CASE("post-increment operator identity") {
    digital::bytes value = 512_B;
    auto old = value++;
    CHECK(value == 513_B);
    CHECK(old == 512_B);

    value = 1_KiB; // The 1 KiB will get converted to bytes
    old = value++; // expecting to add 1 unit of bytes
    CHECK(value == 1025_B);
    CHECK(old == 1_KiB);
}

TEST_CASE("post-increment operator kibi") {
    digital::kibibytes value = 1_KiB;
    auto old = value++;
    CHECK(value == 2_KiB);
    CHECK(old == 1_KiB);
}

TEST_CASE("pre-decrement operator identity") {
    digital::bytes value = 512_B;
    auto newValue = --value;
    CHECK(value == 511_B);
    CHECK(newValue == 511_B);

    value = 1_KiB;      // The 1 KiB will get converted to bytes
    newValue = --value; // expecting to add 1 unit of bytes
    CHECK(value == 1023_B);
    CHECK(newValue == 1023_B);
}

TEST_CASE("pre-decrement operator kibi") {
    digital::kibibytes value = 2_KiB;
    auto newValue = --value;
    CHECK(value == 1_KiB);
    CHECK(newValue == 1_KiB);
}

TEST_CASE("post-decrement operator identity") {
    digital::bytes value = 512_B;
    auto old = value--;
    CHECK(value == 511_B);
    CHECK(old == 512_B);

    value = 1_KiB; // The 1 KiB will get converted to bytes
    old = value--; // expecting to add 1 unit of bytes
    CHECK(value == 1023_B);
    CHECK(old == 1_KiB);
}

TEST_CASE("post-decrement operator kibi") {
    digital::kibibytes value = 2_KiB;
    auto old = value--;
    CHECK(value == 1_KiB);
    CHECK(old == 2_KiB);
}

TEST_CASE("compound add-assign operator") {
    auto value = 510_B;
    value += 2_B;
    CHECK(value == 512_B);

    value += 1_KiB;
    CHECK(value == 1.5_KiB);

    value += 2_MiB;
    CHECK(value == 2049.5_KiB);
}

TEST_CASE("compound sub-assign operator") {
    auto value = digital::unit_cast<digital::bytes>(2001.5_KB);
    value -= 2_MB;
    CHECK(value == 1.5_KB);

    value -= 1_KB;
    CHECK(value == 500_B);

    value -= 2_B;
    CHECK(value == 498_B);
}

TEST_CASE("compound mul-assign operator identity") {
    auto value = 10_B;
    value *= 2;
    CHECK(value == 20_B);

    value *= 50;
    CHECK(value == 1_KB);
}

TEST_CASE("compound mul-assign operator mebi") {
    auto value = 10_MB;
    value *= 2;
    CHECK(value == 20_MB);

    value *= 50;
    CHECK(value == 1_GB);
}

TEST_CASE("compound div-assign operator identity") {
    auto value = 1000_B;
    value /= 50;
    CHECK(value == 20_B);

    value /= 2;
    CHECK(value == 10_B);
}

TEST_CASE("compound div-assign operator mebi") {
    auto value = 1000_MB;
    value /= 50;
    CHECK(value == 20_MB);

    value /= 2;
    CHECK(value == 10_MB);
}

TEST_CASE("compound mod-assign operator identity") {
    auto value = 11_B;
    value %= 3;
    CHECK(value == 2_B);
}

TEST_CASE("compound mod-assign operator tera") {
    auto value = 11_TB;
    value %= 3;
    CHECK(value == 2_TB);
}

TEST_CASE("compound mod-assign operator mix") {
    auto value = 11000_MB;
    value %= 3_GB;
    CHECK(value == 2_GB);
}

TEST_CASE("plus operator") {
    CHECK(1_B + 1_B == 2_B);
    CHECK(1_KiB + 512_B == 1536_B);
    CHECK(1.5_KiB + 512_B == 2_KiB);
}

TEST_CASE("minus operator") {
    CHECK(5_B - 2_B == 3_B);
    CHECK(1_KiB - 512_B == 512_B);
    CHECK(1.5_KiB - 512_B == 1_KiB);
}

TEST_CASE("mul operator") {
    CHECK(5_B * 2 == 10_B);
    CHECK(5 * 2_KiB == 10_KiB);

    CHECK(1_KiB * 4 == 4096_B);
    CHECK(4 * 1_KiB == 4096_B);

    CHECK(1.5_MB * 4 == 6_MB);
    CHECK(4 * 1.5_MB == 6_MB);
}

TEST_CASE("div operator") {
    CHECK(10_B / 2 == 5_B);
    CHECK(10_KiB / 5 == 2_KiB);
    CHECK(6_MB / 4.0 == 1.5_MB);

    CHECK(10_B / 5_B == 2);
    CHECK(10_MB / 5_KB == 2000);
    CHECK(1_KB / 1.0_MB == 0.001l);
}

TEST_CASE("mod operator") {
    CHECK(10_B % 3 == 1_B);
    CHECK(10_KiB % 3 == 1_KiB);

    CHECK(10_B % 3_B == 1_B);
    CHECK(10_MB % 3_KB == 1_KB);
}

TEST_CASE("zero min max") {
    CHECK(digital::tebibytes::zero() == 0_TiB);
    CHECK(digital::tebibytes::min() == digital::tebibytes(std::numeric_limits<std::int64_t>::lowest()));
    CHECK(digital::tebibytes::max() == digital::tebibytes(std::numeric_limits<std::int64_t>::max()));

    using megabytes_ld = digital::unit<long double, digital::mega>;
    CHECK((100.0_MB).zero() == 0.0_MiB);
    CHECK((100.0_MB).min() == megabytes_ld(std::numeric_limits<long double>::lowest()));
    CHECK((100.0_MB).max() == megabytes_ld(std::numeric_limits<long double>::max()));
}

TEST_CASE("abs") {
    CHECK(digital::abs(0_EiB) == 0_EiB);

    CHECK(digital::abs(1_EiB) == 1_EiB);
    CHECK(digital::abs(1024_EiB) == 1024_EiB);

    CHECK(digital::abs(-1_EiB) == 1_EiB);
    CHECK(digital::abs(-1024_EiB) == 1024_EiB);
}

TEST_CASE("floor") {
    CHECK(digital::floor<digital::kilobytes>(999_B) == 0_KB);
    CHECK(digital::floor<digital::kilobytes>(1000_B) == 1_KB);
    CHECK(digital::floor<digital::kilobytes>(1001_B) == 1_KB);
    CHECK(digital::floor<digital::kilobytes>(1999_B) == 1_KB);

    CHECK(digital::floor<digital::kilobytes>(-999_B) == -1_KB);
    CHECK(digital::floor<digital::kilobytes>(-1000_B) == -1_KB);
    CHECK(digital::floor<digital::kilobytes>(-1001_B) == -2_KB);
    CHECK(digital::floor<digital::kilobytes>(-1999_B) == -2_KB);
}

TEST_CASE("ceil") {
    CHECK(digital::ceil<digital::kilobytes>(999_B) == 1_KB);
    CHECK(digital::ceil<digital::kilobytes>(1000_B) == 1_KB);
    CHECK(digital::ceil<digital::kilobytes>(1001_B) == 2_KB);
    CHECK(digital::ceil<digital::kilobytes>(1999_B) == 2_KB);

    CHECK(digital::ceil<digital::kilobytes>(-999_B) == 0_KB);
    CHECK(digital::ceil<digital::kilobytes>(-1000_B) == -1_KB);
    CHECK(digital::ceil<digital::kilobytes>(-1001_B) == -1_KB);
    CHECK(digital::ceil<digital::kilobytes>(-1999_B) == -1_KB);
}

TEST_CASE("round") {
    CHECK(digital::round<digital::kilobytes>(0_B) == 0_KB);
    CHECK(digital::round<digital::kilobytes>(1_B) == 0_KB);
    CHECK(digital::round<digital::kilobytes>(499_B) == 0_KB);

    CHECK(digital::round<digital::kilobytes>(501_B) == 1_KB);
    CHECK(digital::round<digital::kilobytes>(999_B) == 1_KB);
    CHECK(digital::round<digital::kilobytes>(1000_B) == 1_KB);
    CHECK(digital::round<digital::kilobytes>(1001_B) == 1_KB);
    CHECK(digital::round<digital::kilobytes>(1499_B) == 1_KB);

    CHECK(digital::round<digital::kilobytes>(1999_B) == 2_KB);

    // Round half-even (bankers' rounding)
    CHECK(digital::round<digital::kilobytes>(500_B) == 0_KB);
    CHECK(digital::round<digital::kilobytes>(1500_B) == 2_KB);
    CHECK(digital::round<digital::kilobytes>(2500_B) == 2_KB);
    CHECK(digital::round<digital::kilobytes>(3500_B) == 4_KB);

    CHECK(digital::round<digital::kilobytes>(-1_B) == 0_KB);
    CHECK(digital::round<digital::kilobytes>(-499_B) == 0_KB);
    CHECK(digital::round<digital::kilobytes>(-500_B) == 0_KB);
    CHECK(digital::round<digital::kilobytes>(-501_B) == -1_KB);
    CHECK(digital::round<digital::kilobytes>(-1000_B) == -1_KB);
    CHECK(digital::round<digital::kilobytes>(-1499_B) == -1_KB);
    CHECK(digital::round<digital::kilobytes>(-1500_B) == -2_KB);
    CHECK(digital::round<digital::kilobytes>(-1999_B) == -2_KB);
}

TEST_CASE("hash") {
    CHECK(std::hash<digital::kibibytes>{}(1_KiB) == std::hash<std::int64_t>{}(1));
    CHECK(std::hash<digital::kibibytes>{}(1_KiB) != std::hash<digital::bytes>{}(1024_B));
}
