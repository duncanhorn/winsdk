
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

    $text[$i] = (ReplaceTypeName $text[$i] "WORD" "std::uint16_t")
    $text[$i] = (ReplaceTypeName $text[$i] "DWORD" "std::uint32_t")

    $text[$i] = (ReplaceTypeName $text[$i] "PSTR" "char*")
    $text[$i] = (ReplaceTypeName $text[$i] "PCSTR" "const char*")
    $text[$i] = (ReplaceTypeName $text[$i] "PWSTR" "wchar_t*")
    $text[$i] = (ReplaceTypeName $text[$i] "PCWSTR" "const wchar_t*")

    $text[$i] = (ReplaceTypeName $text[$i] "PVOID" "void*")
}

$text | Out-File $File
