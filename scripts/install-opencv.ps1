$vcpkgRoot = "..\addons\vcpkg"
$vcpkgExe = Join-Path $vcpkgRoot "vcpkg.exe"
if (-not (Test-Path $vcpkgExe)) {
    git clone https://github.com/Microsoft/vcpkg.git $vcpkgRoot
    & "$vcpkgRoot\bootstrap-vcpkg.bat"
}
& $vcpkgExe install opencv:x64-windows
& $vcpkgExe integrate install