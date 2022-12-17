# Building for Linux/WSL
## Installing packages
**Automated (Ubuntu, Arch, RedHat, or derivatives)** — Just running `setup.sh` should be enough if you have access to `sudo`.

Otherwise, install these packages manually:
- Ubuntu&nbsp; — &nbsp;`make cmake vim ruby bison doxygen meson libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libopenal-dev libphysfs-dev libpixman-1-dev libwebp-dev libbz2-dev libvorbis-dev libogg-dev libsodium-dev libboost-dev libpng-dev libjpeg-dev libtiff-dev libsigc++-2.0-dev libgtk-3-dev libxfconf-0-dev libfreetype-dev libharfbuzz-de`
- Arch&nbsp; — &nbsp;`make cmake ruby bison doxygen sdl2 openal pixman libwebp bzip2 libvorbis libogg libsodium libpng libjpeg libtiff zeromq mm-common base-devel gtk3`
- RedHat&nbsp; — &nbsp;`make cmake m4 bison doxygen ruby meson mm-common SDL2 SDL2-devel SDL2_image SDL2_tff SDL2_ttf-devel SDL2_image-devel bzip2-devel libwebp libwebp-devel libvorbis libvorbis-devel libpng libpng-devel libjpeg-turbo libjpeg-turbo-devel libogg libogg-devel libtiff libtiff-devel libsodium libsodium-devel zeromq zeromq-devel physfs physfs-devel pixman pixman-devel bzip2 openal-soft speex speex-devel libmodplug libmodplug-devel boost boost-devel openal-soft-devel xfconf xfconf-devel gtk3 gtk3-devel libsigc++-devel harfbuzz-devel`

> ❗&nbsp; You will also need to install a C compiler alongside those packages. I recommend using Clang (`clang` in all distributions) as it compiles faster and has no known issues with ModShot. If you don't want to use Clang, install GCC (`gcc` in all distributions).


### Installing packages for `_______`
You only need them if you are planning to build `_______`

- Ubuntu&nbsp; — &nbsp;`python3 python3-pyqt5`
- Arch&nbsp; — &nbsp;`python python-pyqt5`
- RedHat&nbsp; — &nbsp;`python3 PyQt5`
- Gentoo&nbsp; — &nbsp;`python PyQt5`
- Nix&nbsp; — &nbsp;`python39 python3.9-PyQt5`

## Cloning repository
 **With `git`**&nbsp; — &nbsp;`git clone https://github.com/Astrabit-ST/ModShot-Core ModShot-Core-master --depth=1`
 
**With `wget`**&nbsp; — &nbsp;`wget -O - https://github.com/Astrabit-ST/ModShot-Core | tar xz`

**With `curl`**&nbsp; — &nbsp;`curl https://github.com/Astrabit-ST/ModShot-Core | tar xz`

## Building

> 💡&nbsp; It's advised to read the comments to understand what's going on.

```sh
# Uncomment the following lines if using Clang!
# export CC=clang
# export CXX=clang++
cd ModShot-Core-master/linux

make # Build extra dependencies (like Ruby)
source vars.sh

# Build ModShot itself!
cd ..; meson build --prefix="$PWD/build.out" --bindir=.
cd build && ninja install
```

Your ModShot has been built and is in `../build.out/modshot`. If you launch it, it should throw an error saying something like "Unable to find Data/xScripts.rxdata". That's completely normal and means you did everything right!

## Copying assets
**Step 1: Find your assets** — They are in `~/.steam/debian-installation/steamapps/common/OneShot/` on Debian-based distributions (if you are using Steam, of course). Replace `[assets]` in the commands below with it.

**Step 2: Find the game path** — Run ModShot with `../build.out/modshot` and then close it. Look for a line saying "Game path: ...". Replace `[game path]` in all the commands below with it.

**Step 3: Copy assets** — Run `cp -r [assets]/[A-Z]*[a-z] [assets]/images/ ../build.out/lib/ "[game path]"; cp  ../assets/journal.png [game path]/_______.png`. This will copy ModShot and assets into your game path.

**Step 4: Download `_______`** — Download `https://raw.githubusercontent.com/hunternet93/OneShot-Journal/master/journal.py` into your game path. Open it with any text editor and add `#!/usr/bin/env python3` in the start. Add a newline after it. Save the file. Run `chmod +x [game path]/journal.py`.

> **You are ready to go!** Launch OneShot with `[game path]/lib/modshot` now.
