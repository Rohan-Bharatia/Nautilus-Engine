#!/bin/bash

# Function to detect distro
detect_distro() {
    if [ -f /etc/os-release ]; then
        . /etc/os-release
        DISTRO=$ID
        DISTRO_LIKE=$ID_LIKE
    else
        echo "Cannot detect Linux distribution."
        exit 1
    fi
}

# Function to install dependencies
install_native_deps() {
    echo "Detected Linux distribution: $DISTRO"

    case "$DISTRO" in
    ubuntu | debian | linuxmint | pop)
        sudo apt update
        sudo apt install -y \
            git cmake ninja-build build-essential \
            libtbb-dev libfreetype6-dev \
            libx11-dev libxcursor-dev libxrandr-dev libxi-dev libxinerama-dev \
            libwayland-dev wayland-protocols libxkbcommon-dev
        ;;

    fedora)
        sudo dnf install -y \
            git cmake ninja-build @development-tools \
            tbb-devel freetype-devel \
            libX11-devel libXcursor-devel libXrandr-devel libXi-devel libXinerama-devel \
            wayland-devel wayland-protocols-devel libxkbcommon-devel
        ;;

    arch)
        sudo pacman -Sy --noconfirm \
            git cmake ninja base-devel \
            tbb freetype2 \
            libx11 libxcursor libxrandr libxi libxinerama \
            wayland wayland-protocols libxkbcommon
        ;;

    opensuse* | suse)
        sudo zypper install -y \
            git cmake ninja gcc-c++ make \
            libtbb-devel freetype2-devel \
            libX11-devel libXcursor-devel libXrandr-devel libXi-devel libXinerama-devel \
            wayland-devel wayland-protocols-devel libxkbcommon-devel
        ;;

    alpine)
        sudo apk add --no-cache \
            git cmake ninja build-base \
            tbb-dev freetype-dev \
            libx11-dev libxcursor-dev libxrandr-dev libxi-dev libxinerama-dev \
            wayland-dev wayland-protocols libxkbcommon-dev
        ;;

    nixos)
        nix-env -iA \
            nixpkgs.git nixpkgs.cmake nixpkgs.ninja nixpkgs.gcc nixpkgs.gnumake \
            nixpkgs.tbb nixpkgs.freetype \
            nixpkgs.xorg.libX11 nixpkgs.xorg.libXcursor nixpkgs.xorg.libXrandr nixpkgs.xorg.libXi nixpkgs.xorg.libXinerama \
            nixpkgs.wayland nixpkgs.wayland-protocols nixpkgs.libxkbcommon
        ;;

    *)
        echo "Unsupported distribution: $DISTRO"
        echo "Please install the required dependencies manually."
        exit 1
        ;;
    esac
}

# Main
detect_distro
install_native_deps
