@echo off

setlocal EnableDelayedExpansion

:: List of packages to install
set PACKAGES=Microsoft.VisualStudio.2022.BuildTools git cmake ninja Intel.oneTBB

:: Function to install all dependencies
:install_deps
@echo Installing development tools with winget...
for %%P in (%PACKAGES%) do (
    @echo Installing %%P...
    winget install --id=%%P --source=winget --accept-source-agreements --accept-package-agreements -e
)
@echo All tools have been installed.
goto :eof

:: Check if winget is available
where winget >nul 2>nul
if %errorlevel%==0 (
    @echo Winget is installed.
    call :install_deps
) else (
    @echo Winget is not installed.
    @echo.
    @echo Please install App Installer from the Microsoft Store to enable 'winget'.
    @echo Opening Microsoft Store page...
    start ms-windows-store://pdp/?productid=9NBLGGH4NNS1
    @echo After installing winget, re-run this script.
    pause
)
endlocal
