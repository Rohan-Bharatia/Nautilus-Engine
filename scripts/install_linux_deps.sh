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

    if command -v nix-env >/dev/null 2>&1; then
        HAS_NIX=1
    else
        HAS_NIX=0
    fi

    if [ -n "$WAYLAND_DISPLAY" ]; then
        DISPLAY_SERVER="wayland"
    elif [ -n "$DISPLAY" ]; then
        DISPLAY_SERVER="x11"
    else
        DISPLAY_SERVER="unknown"
    fi

    echo "Detected display server: $DISPLAY_SERVER"
}

# Function to install dependencies
install_native_deps() {
    echo "Detected Linux distribution: $DISTRO"

    case "$DISTRO" in
    ubuntu | debian | linuxmint | pop)
        sudo apt update
        sudo apt install -y \
            git cmake ninja-build build-essential \
            libtbb-dev \
            libx11-dev libxcursor-dev libxrandr-dev libxi-dev libxinerama-dev \
            libwayland-dev wayland-protocols libxkbcommon-dev
        ;;

    fedora)
        sudo dnf install -y \
            git cmake ninja-build @development-tools \
            tbb-devel \
            libX11-devel libXcursor-devel libXrandr-devel libXi-devel libXinerama-devel \
            wayland-devel wayland-protocols-devel libxkbcommon-devel
        ;;

    arch)
        sudo pacman -Sy --noconfirm \
            git cmake ninja base-devel \
            tbb \
            libx11 libxcursor libxrandr libxi libxinerama \
            wayland wayland-protocols libxkbcommon
        ;;

    opensuse* | suse)
        sudo zypper install -y \
            git cmake ninja gcc-c++ make \
            libtbb-devel \
            libX11-devel libXcursor-devel libXrandr-devel libXi-devel libXinerama-devel \
            wayland-devel wayland-protocols-devel libxkbcommon-devel
        ;;

    alpine)
        sudo apk add --no-cache \
            git cmake ninja build-base \
            tbb-dev \
            libx11-dev libxcursor-dev libxrandr-dev libxi-dev libxinerama-dev \
            wayland-dev wayland-protocols libxkbcommon-dev
        ;;

    nixos)
        echo "NixOS detected — skipping native install"
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
if [ "$DISTRO" = "nixos" ] || [ "$HAS_NIX" -eq 1 ]; then
    install_nix_deps
else
    install_native_deps
fi
