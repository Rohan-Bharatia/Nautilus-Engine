#!/bin/bash

# Function to detect distro
detect_distro() {
    if [ -f /etc/os-release ]; then
        . /etc/os-release
        DISTRO=$ID
    else
        echo "Cannot detect Linux distribution."
        exit 1
    fi
}

# Function to install dependencies
install_deps() {
    echo "Detected Linux distribution: $DISTRO"

    case "$DISTRO" in
        ubuntu|debian)
            sudo apt update
            sudo apt install -y git cmake ninja-build build-essential
            ;;

        fedora)
            sudo dnf install -y git cmake ninja-build @development-tools
            ;;

        arch)
            sudo pacman -Sy --noconfirm git cmake ninja base-devel
            ;;

        *)
            echo "Unsupported distribution: $DISTRO"
            echo "Please install the required dependencies manually."
            exit 1
            ;;
    esac

    echo "All development tools have been installed."
}

# Main
detect_distro
install_deps
