
[CmdletBinding()]
Param (
    [Parameter(Mandatory=$True)]
    [string]$File,

    [int]$StartLine,

    [int]$EndLine
)

$text = Get-Content $File
if (!$StartLine) { $StartLine = 0 }
if (!$EndLine) { $EndLine = $text.Length }

for ($i = $StartLine; $i -lt $EndLine; ++$i)
{
    $text[$i] = $text[$i] -replace "STDMETHOD\((\w+)\)","virtual std::int32_t __stdcall `$1"
    $text[$i] = $text[$i] -replace "STDMETHODV\((\w+)\)","virtual std::int32_t __cdecl `$1"
    $text[$i] = $text[$i] -replace " PURE;", " noexcept = 0;"

    $text[$i] = $text[$i] -replace "_In\w* +",""
    $text[$i] = $text[$i] -replace "_In\w*\([^\)]+\) +",""
    $text[$i] = $text[$i] -replace "_Out_\w* +",""
    $text[$i] = $text[$i] -replace "_Out_\w*\([^\)]+\) +",""
    $text[$i] = $text[$i] -replace "_Reserved_ +",""

    $text[$i] = $text[$i] -replace "_t A","_t a"
    $text[$i] = $text[$i] -replace "_t B","_t b"
    $text[$i] = $text[$i] -replace "_t C","_t c"
    $text[$i] = $text[$i] -replace "_t D","_t d"
    $text[$i] = $text[$i] -replace "_t E","_t e"
    $text[$i] = $text[$i] -replace "_t F","_t f"
    $text[$i] = $text[$i] -replace "_t G","_t g"
    $text[$i] = $text[$i] -replace "_t H","_t h"
    $text[$i] = $text[$i] -replace "_t I","_t i"
    $text[$i] = $text[$i] -replace "_t J","_t j"
    $text[$i] = $text[$i] -replace "_t K","_t k"
    $text[$i] = $text[$i] -replace "_t L","_t l"
    $text[$i] = $text[$i] -replace "_t M","_t m"
    $text[$i] = $text[$i] -replace "_t N","_t n"
    $text[$i] = $text[$i] -replace "_t O","_t o"
    $text[$i] = $text[$i] -replace "_t P","_t p"
    $text[$i] = $text[$i] -replace "_t Q","_t q"
    $text[$i] = $text[$i] -replace "_t R","_t r"
    $text[$i] = $text[$i] -replace "_t S","_t s"
    $text[$i] = $text[$i] -replace "_t T","_t t"
    $text[$i] = $text[$i] -replace "_t U","_t u"
    $text[$i] = $text[$i] -replace "_t V","_t v"
    $text[$i] = $text[$i] -replace "_t W","_t w"
    $text[$i] = $text[$i] -replace "_t X","_t x"
    $text[$i] = $text[$i] -replace "_t Y","_t y"
    $text[$i] = $text[$i] -replace "_t Z","_t z"

    $text[$i] = $text[$i] -replace "\* A","* a"
    $text[$i] = $text[$i] -replace "\* B","* b"
    $text[$i] = $text[$i] -replace "\* C","* c"
    $text[$i] = $text[$i] -replace "\* D","* d"
    $text[$i] = $text[$i] -replace "\* E","* e"
    $text[$i] = $text[$i] -replace "\* F","* f"
    $text[$i] = $text[$i] -replace "\* G","* g"
    $text[$i] = $text[$i] -replace "\* H","* h"
    $text[$i] = $text[$i] -replace "\* I","* i"
    $text[$i] = $text[$i] -replace "\* J","* j"
    $text[$i] = $text[$i] -replace "\* K","* k"
    $text[$i] = $text[$i] -replace "\* L","* l"
    $text[$i] = $text[$i] -replace "\* M","* m"
    $text[$i] = $text[$i] -replace "\* N","* n"
    $text[$i] = $text[$i] -replace "\* O","* o"
    $text[$i] = $text[$i] -replace "\* P","* p"
    $text[$i] = $text[$i] -replace "\* Q","* q"
    $text[$i] = $text[$i] -replace "\* R","* r"
    $text[$i] = $text[$i] -replace "\* S","* s"
    $text[$i] = $text[$i] -replace "\* T","* t"
    $text[$i] = $text[$i] -replace "\* U","* u"
    $text[$i] = $text[$i] -replace "\* V","* v"
    $text[$i] = $text[$i] -replace "\* W","* w"
    $text[$i] = $text[$i] -replace "\* X","* x"
    $text[$i] = $text[$i] -replace "\* Y","* y"
    $text[$i] = $text[$i] -replace "\* Z","* z"

    # for ($i = 0; $i -lt 26; ++$i)
    # {
    #     $upper = [string][char](65 + $i)
    #     $lower = [string][char](97 + $i)
    #     $text[$i] = $text[$i] -replace "_t $upper","_t $lower"
    # }
}

$text | Out-File $File -Encoding utf8
