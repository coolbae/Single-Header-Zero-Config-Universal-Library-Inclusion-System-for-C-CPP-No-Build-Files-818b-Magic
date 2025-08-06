#pragma once
#ifdef __cplusplus
#define _ls_inline inline
#define _ls_auto_type auto
#else
#define _ls_inline static
#define _ls_auto_type __typeof__
#endif

#define lib_sub_include(p)\
_Pragma("GCC system_header")\
_Pragma("GCC diagnostic ignored \"-Wunused-variable\"")\
_Pragma("GCC diagnostic ignored \"-Wunused-function\"")\
_ls_auto_type _ls_dummy;\
__LIB_SUB_INCLUDE__(p)

#ifdef _MSC_VER
#undef _ls_auto_type
#define _ls_auto_type decltype(auto)
#pragma section(".CRT$XCU", read)
#define _ls_init \
static void __cdecl _ls_init_fn(); \
__declspec(allocate(".CRT$XCU")) void(__cdecl*_ls_init_)(void) = _ls_init_fn; \
static void __cdecl _ls_init_fn()
#undef lib_sub_include
#define lib_sub_include(p) \
__pragma(warning(disable:4505 4101)) \
_ls_init { __LIB_SUB_INCLUDE__(p); } \
_ls_auto_type _ls_dummy
#endif