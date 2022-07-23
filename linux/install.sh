#!/bin/bash
BINARY=$1
RUBY_VER=$2

MODSHOT_PREFIX=$(uname -m)
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
RUBY_LIB_DIR="$DIR/build-${MODSHOT_PREFIX}/lib/ruby"

EXCLUDELIST=https://raw.githubusercontent.com/AppImage/pkg2appimage/master/excludelist
SO_BLACKLIST="$(curl -sL $EXCLUDELIST | grep -o '^[^ #]*')"
SO_PROCESSED=""

function fail() {
    echo "$1"
    echo "Please beat the crap out of rkevin until he fixes this issue."
    exit 1
}

function copy_dependencies() {
    if [[ $SO_BLACKLIST =~ $1 ]]; then
        return
    fi
    if [[ $SO_PROCESSED =~ $1 ]]; then
        return
    fi
    [[ ! $1 =~ ^[a-zA-Z0-9+\._-]*$ ]] && fail "The library $1 has weird characters!"

    SO_PROCESSED="$SO_PROCESSED $1"
    cp "$2" "$DESTDIR/$1"
    patchelf --set-rpath '$ORIGIN' "$DESTDIR/$1"
    ldd "$2" | while read -ra line; do
        if [[ ${line[0]} == 'linux-vdso.so.1' ]] || [[ ${line[0]} =~ 'ld-linux-x86-64.so.2' ]]; then
            continue
        fi
        [[ ${line[1]} != '=>' ]] && echo ${line[*]} && fail "ldd's output isn't what this script expected!"
        [[ ! ${line[3]} =~ ^\(0x[0-9a-f]*\)$ ]] && echo ${line[*]} && fail "ldd's output isn't what this script expected!"
        copy_dependencies "${line[0]}" "${line[2]}"
    done
}

shopt -s dotglob

DESTDIR="${MESON_INSTALL_PREFIX}/lib"
mkdir -p $DESTDIR
copy_dependencies $BINARY $BINARY

echo "Copying standard library..."
cp -ar "$RUBY_LIB_DIR/$RUBY_VER.0" "$DESTDIR/ruby"
echo "Downloading cacert.pem..."
curl -o "$DESTDIR/cacert.pem" https://curl.se/ca/cacert.pem
echo "Sym-linking modshot..."
ln -sf "$DESTDIR/lmodshot" $BINARY
echo "Done!"
