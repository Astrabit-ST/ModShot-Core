#!/bin/bash

BINARY=$1
SHIM_BINARY=$2
RUBY_VER=$3

MODSHOT_PREFIX=$(ruby -e "puts ENV[\"MSYSTEM\"].downcase")
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
RUBY_LIB_DIR="$DIR/build-${MODSHOT_PREFIX}/lib/ruby"

function fail() {
    echo "$1"
    echo "Please beat the crap out of Pancakes until he fixes this issue."
    exit 1
}

function copy_dependencies() {
    if [[ ${2@L} = /c/windows/* ]]; then
        return
    fi
    echo "Copying $1..."

    [[ ! $1 =~ ^[a-zA-Z0-9+\._-]*$ ]] && fail "The library $1 has weird characters!"

    cp "$2" "$DESTDIR/$1" -f
    ldd "$2" | while read -ra line; do
        [[ ${line[1]} != '=>' ]] && echo ${line[*]} && fail "ldd's output isn't what this script expected!"
        [[ ! ${line[3]} =~ ^\(0x[0-9a-f]*\)$ ]] && echo ${line[*]} && fail "ldd's output isn't what this script expected!"
        copy_dependencies "${line[0]}" "${line[2]}"
    done
}

shopt -s dotglob

echo "Relocating dependencies..."
DESTDIR="${MESON_INSTALL_PREFIX}/lib"
rm -r $DESTDIR
mkdir -p $DESTDIR
copy_dependencies $BINARY $BINARY

echo "Copying standard library..."
cp -ar "$RUBY_LIB_DIR/$RUBY_VER.0" "$DESTDIR/ruby"
echo "Downloading cacert.pem..."
curl -o "$DESTDIR/cacert.pem" https://curl.se/ca/cacert.pem
echo "Moving shim..."
cp $SHIM_BINARY "$DESTDIR/../$BINARY"
echo "Done!"
