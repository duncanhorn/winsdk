# winsdk
This project is an attempt to provide a smaller, more separated, and more standards conformant version of the Windows SDK. Some of its goals are:

* Separate functionality into separate includes, to improve build time
* Purge the use of macros (e.g. min, max, etc.) in favor of constants/inline functions
* Replace use of "Windows typedefs" with clearer, more consise types (e.g. `DWORD` -> `std::uint32_t`)
* Remove uses of SAL and hungarian
* Improve conformance, so that it builds with Clang _without_ `ms-compatability`

## Type mappings
Here's a (likely incomplete) list of the mapping between "Windows types" and their equivalent type(s) used in this project:

|Windows Type|Actual Type|
|------------|-----------|
|`HANDLE`|`void*` (or `handle_t`)
|`BOOL`|`std::int32_t` (or `bool_t`)
|`WORD`|`std::uint16_t`|
|`DWORD`|`std::uint32_t`|
|`PSTR`|`char*`|
|`PCSTR`|`const char*`|
|`PWSTR`|`wchar_t*`|
|`PCWSTR`|`const wchar_t*`|
|`PVOID`|`void*`|

## Namespace and Linking
All function declarations are placed in the `winsdk::` namespace. This is primarily to avoid conflicts if the actual Windows SDK headers are included somewhere (e.g. in a small subset of a project). Since these functions are declared as `extern "C"`, their linkage will be done against the same name with the namespace removed (e.g. `winsdk::CreateFileA` will link against `::CreateFileA`).
