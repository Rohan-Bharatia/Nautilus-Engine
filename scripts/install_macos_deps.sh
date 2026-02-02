#!/bin/bash

# List of packages to install
PACKAGES=(git cmake ninja tbb)

# Function to install dependencies
install_deps() {
    echo "Installing development tools..."

    # Install Xcode Command Line Tools
    if ! xcode-select -p &>/dev/null; then
        echo "Installing Xcode Command Line Tools..."
        xcode-select --install
        echo "Please complete the installation before rerunning this script."
        exit 1
    else
        echo "Xcode Command Line Tools already installed."
    fi

    # Install packages via Homebrew
    for pkg in "${PACKAGES[@]}"; do
        if ! brew list --formula | grep -q "^${pkg}$"; then
            echo "Installing $pkg..."
            brew install "$pkg"
        else
            echo "$pkg is already installed."
        fi
    done

    echo "All tools have been installed."
}

# Check for Homebrew
if ! command -v brew &>/dev/null; then
    echo "Homebrew not found. Installing Homebrew..."
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

    # Add brew to PATH (especially for Apple Silicon Macs)
    if [[ $(uname -m) == "arm64" ]]; then
        echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >>~/.zprofile
        eval "$(/opt/homebrew/bin/brew shellenv)"
    else
        echo 'eval "$(/usr/local/bin/brew shellenv)"' >>~/.bash_profile
        eval "$(/usr/local/bin/brew shellenv)"
    fi
fi

# Now install the tools
install_deps
