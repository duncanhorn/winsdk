
[CmdletBinding()]
Param (
    [Parameter(Mandatory=$True)]
    [string]$File,

    [int]$StartLine,

    [int]$EndLine
)

function ReplaceTypeName($line, $fromType, $toType)
{
    return $line -replace "(\s)$fromType([\s\*])","`$1$toType`$2"
}

$text = Get-Content $File
if (!$StartLine) { $StartLine = 0 }
if (!$EndLine) { $EndLine = $text.Length }

for ($i = $StartLine; $i -lt $EndLine; ++$i)
{
    $text[$i] = (ReplaceTypeName $text[$i] "HANDLE" "handle_t")
    $text[$i] = (ReplaceTypeName $text[$i] "BOOL" "bool_t")
    $text[$i] = (ReplaceTypeName $text[$i] "PBOOL" "bool_t*")

    $text[$i] = (ReplaceTypeName $text[$i] "BYTE" "std::uint8_t")
    $text[$i] = (ReplaceTypeName $text[$i] "UCHAR" "std::uint8_t")
    $text[$i] = (ReplaceTypeName $text[$i] "WORD" "std::uint16_t")
    $text[$i] = (ReplaceTypeName $text[$i] "USHORT" "std::uint16_t")
    $text[$i] = (ReplaceTypeName $text[$i] "DWORD" "std::uint32_t")
    $text[$i] = (ReplaceTypeName $text[$i] "DWORD64" "std::uint64_t")
    $text[$i] = (ReplaceTypeName $text[$i] "LONG" "std::int32_t")
    $text[$i] = (ReplaceTypeName $text[$i] "ULONG" "std::uint32_t")
    $text[$i] = (ReplaceTypeName $text[$i] "PULONG" "std::uint32_t*")
    $text[$i] = (ReplaceTypeName $text[$i] "LONG64" "std::int64_t")
    $text[$i] = (ReplaceTypeName $text[$i] "ULONG64" "std::uint64_t")
    $text[$i] = (ReplaceTypeName $text[$i] "PULONG64" "std::uint64_t*")
    $text[$i] = (ReplaceTypeName $text[$i] "LONGLONG" "std::int64_t")
    $text[$i] = (ReplaceTypeName $text[$i] "ULONGLONG" "std::uint64_t")
    $text[$i] = (ReplaceTypeName $text[$i] "SIZE_T" "std::size_t")
    $text[$i] = (ReplaceTypeName $text[$i] "ULONG_PTR" "std::uintptr_t")
    $text[$i] = (ReplaceTypeName $text[$i] "HRESULT" "std::int32_t")

    $text[$i] = (ReplaceTypeName $text[$i] "PSTR" "char*")
    $text[$i] = (ReplaceTypeName $text[$i] "LPSTR" "char*")
    $text[$i] = (ReplaceTypeName $text[$i] "PCSTR" "const char*")
    $text[$i] = (ReplaceTypeName $text[$i] "LPCSTR" "const char*")
    $text[$i] = (ReplaceTypeName $text[$i] "PWSTR" "wchar_t*")
    $text[$i] = (ReplaceTypeName $text[$i] "LPWSTR" "wchar_t*")
    $text[$i] = (ReplaceTypeName $text[$i] "PCWSTR" "const wchar_t*")
    $text[$i] = (ReplaceTypeName $text[$i] "LPCWSTR" "const wchar_t*")

    $text[$i] = (ReplaceTypeName $text[$i] "VOID" "void")
    $text[$i] = (ReplaceTypeName $text[$i] "PVOID" "void*")
    $text[$i] = (ReplaceTypeName $text[$i] "LPVOID" "void*")
    $text[$i] = (ReplaceTypeName $text[$i] "LPCVOID" "const void*")

    $text[$i] = (ReplaceTypeName $text[$i] "LPSECURITY_ATTRIBUTES" "security_attributes*")
}

$text | Out-File $File -Encoding utf8
