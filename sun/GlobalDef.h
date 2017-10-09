#pragma once

/* endian */
//#define ARCH_BIG_ENDIAN
#define ARCH_LITTLE_ENDIAN


/* namespace */
#define _SUN_BEGIN namespace sun {
#define _SUN_END	}
#define _USING_SUN using namespace sun;

#define _DETAIL_BEGIN namespace detail {
#define _DETAIL_END }
#define _USING_DETAIL using namespace detail;

#define _ANON_BEGIN namespace {
#define _ANON_END }


/* delete pointer macros */
#define deletePtr(ptr) \
	if (nullptr != ptr) { \
		delete ptr; \
		ptr = nullptr; \
	}

#define deleteContainerPtrs(c) \
	for (auto &ptr : c) { \
		DeletePtr(ptr) \
		c.clear(); \
	}


/* assert */
#ifdef NOASSERT
#	define assert_s(expr)
#else
#	define assert_s(expr) assert(expr)
#endif // NOASSERT


/* size */
const unsigned int KB = 1024;
const unsigned int MB = 1024 * KB;
const unsigned int GB = 1024 * MB;