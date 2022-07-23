#!/bin/bash

# ModShot dependencies installer

if [[ $OSTYPE == msys ]]; then 
    echo " * MSYS2 detected"
    echo " * Installing pactoys..."
    pacman -S pactoys --needed --noconfirm
    echo " * Installing dependencies..."
    pacboy -S git: vim: libtool: autoconf: automake: gcc:p make:p cmake:p \
    ruby:p bison: doxygen:p SDL2:p SDL2_image:p SDL2_ttf:p openal:p \
    freetype:p physfs:p pixman:p libwebp:p zlib:p meson:p clang:p bzip2:p \
    libvorbis:p libogg:p zeromq:p libsigc++:p boost:p libpng:p \
    libjpeg-turbo:p libtiff:p harfbuzz:p --needed --noconfirm
else 
    if [[ "$(cat /etc/issue)" == Debian* || "$(cat /etc/issue)" == Ubuntu* ]];
    then
        echo " * Debian Linux detected"
        echo " * Installing dependencies..."
        sudo apt install -y gcc make cmake vim ruby bison doxygen meson \
        libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libopenal-dev \
        libphysfs-dev libpixman-1-dev libwebp-dev libbz2-dev libvorbis-dev \
        libogg-dev libsodium-dev libboost-dev libpng-dev libjpeg-dev \
        libtiff-dev libsigc++-2.0-dev libgtk-3-dev libxfconf-0-dev \
        libfreetype-dev libharfbuzz-dev
    fi

    if [[ "$(cat /etc/issue)" == Manjaro* ]];
    then
        echo " * Manjaro detected"
        echo " * Installing dependencies..."
        sudo pacman -S --noconfirm --needed vim gcc make cmake ruby bison \
        doxygen sdl2 openal pixman libwebp bzip2 libvorbis libogg libsodium \
        libpng libjpeg libtiff zeromq mm-common base-devel gtk3
        echo " * Installing dependencies with pamac..."
        sudo pamac install sdl2_image sdl2_ttf physfs boost boost-libs \
        libsigc++ sdl_sound m4 meson freetype harfbuzz --no-confirm
    fi

    if [[ $(cat /etc/redhat-release) ]];
    then
        echo " * RedHat/Fedora Linux detected"
        echo " * Installing dependencies..."
        sudo dnf install vim gcc make cmake m4 bison doxygen ruby meson \
        mm-common SDL2 SDL2-devel SDL2_image SDL2_tff SDL2_ttf-devel \
        SDL2_image-devel bzip2-devel libwebp libwebp-devel libvorbis \
        libvorbis-devel libpng libpng-devel libjpeg-turbo \
        libjpeg-turbo-devel libogg libogg-devel libtiff libtiff-devel \
        libsodium libsodium-devel zeromq zeromq-devel physfs physfs-devel \
        pixman pixman-devel bzip2 openal-soft speex speex-devel libmodplug \
        libmodplug-devel boost boost-devel openal-soft-devel xfconf \
        xfconf-devel gtk3 gtk3-devel libsigc++-devel harfbuzz-devel
    fi
fi

if [ $? -ne 0 ];
then
    echo " * Finished with errors."
else
    echo " * Done! All dependencies was installed."
fi
