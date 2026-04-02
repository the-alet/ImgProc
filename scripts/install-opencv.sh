#!/bin/bash
OS="$(uname -s)"
case "$OS" in
    Linux*)
        if command -v apt &> /dev/null; then
            sudo apt update && sudo apt install -y libopencv-dev
        elif command -v dnf &> /dev/null; then
            sudo dnf install -y opencv-devel
        elif command -v pacman &> /dev/null; then
            sudo pacman -S --noconfirm opencv
        fi
        ;;
esac