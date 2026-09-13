/** @file SIMD DATA TYPES HEADER FILE FOR GNU COMPILERS
 * @date Started creation at 13/09/2026 18:27 GMT
 * @note This will strictly use GCC's compiler intristics which will not be supported on other C++ Compilers so do not use this -
 * if you are not using the GNU Compiler for you're C++ project.
 * */

#include <cstdint>

#if __cplusplus <= 201101L
#define _SIOUD_ABLE_TO_USING
#endif

#ifndef _STANDARD_TEMPLATED_LIBARY_SIMD_INTRISTICS_DATA_TYPES
#define _STANDARD_TEMPLATED_LIBARY_SIMD_INTRISTICS_DATA_TYPES

namespace stl {
    /// @typedef Type definitions of SIMD dTypes

    // Single-Precision Floats
#ifdef _SIOUD_ABLE_TO_USING
    using FMD64 = float [[gnu::aligned(4), gnu::vector_size(8)]];
    using FMD128 = float [[gnu::aligned(4), gnu::vector_size(16)]];
#else
    typedef float FMD64 [[gnu::aligned(4), gnu::vector_size(8)]];
    typedef float FMD128 [[gnu::aligned(4), gnu::vector_size(16)]];
#endif
    // Double-Precision Floats
#ifdef _SIOUD_ABLE_TO_USING
    using DMD128 = double [[gnu::aligned(8), gnu::vector_size(16)]];
    using DMD256 = double [[gnu::aligned(8), gnu::vector_size(32)]];
#else
    typedef double DMD128 [[gnu::aligned(8), gnu::vector_size(16]];
    typedef double DMD256 [[gnu::aligned(8), gnu::vector_size(32)]];
#endif

    // 32-Bit Signed Integers
#ifdef _SIOUD_ABLE_TO_USING
    using IMD64 = std::uint32_t [[gnu::aligned(4), gnu::vector_size(8)]];
    using IMD128 = std::uint32_t [[gnu::aligned(4), gnu::vector_size(16)]];
#else
    typedef std::uint32_t IMD64 [[gnu::aligned(4), gnu::vector_size(8)]];
    typedef std::uint32_t IMD128 [[gnu::aligned(4), gnu::vector_size(16)]];
#endif

    // 64-Bit Signed Integers
#ifdef _SIOUD_ABLE_TO_USING
    using IMD128 = std::uint64_t [[gnu::aligned(8), gnu::vector_size(16)]];
    using IMD256 = std::uint64_t [[gnu::aligned(8), gnu::vector_size(32)]];
#else
    typedef std::uint64_t IMD128 [[gnu::aligned(8), gnu::vector_size(16)]];
    typedef std::uint64_t IMD256 [[gnu::aligned(8), gnu::vector_size(32)]];
#endif


    // @defgroup  Functions
    namespace md {
	#if defined(__X86_64__) || defined(_M_X64)
#ifdef __cpp_constexpr
      #define CPP_CONSTEXPR constexpr
#else
      #define CPP_CONSTEXPR
#endif

#define CPU_COMPILER_INSTRICS [[gnu::always_inline, gnu::optimize("O3")]]

CPU_COMPILER_INSTRICS CPP_CONSTEXPR inline static FMD64 add_fmd64(
    FMD64 vector1,
    FMD64 vector2
) {
    return vector1 + vector2;
}

CPU_COMPILER_INSTRICS CPP_CONSTEXPR inline static void padd_fmd64(
    FMD64& result,
    FMD64 const& from
) {
    result += from;
}

	#endif
    }
}

#endif
