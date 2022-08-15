ARCH := $(shell uname -m)

RUBY_FLAGS := ${RUBY_FLAGS}
RUBY_VER ?= "3.1"
RUBY_BRANCH = $(subst .,_,$(RUBY_VER))

BUILD_PREFIX := ${PWD}/build-$(ARCH)
LIBDIR := $(BUILD_PREFIX)/lib
INCLUDEDIR := $(BUILD_PREFIX)/include
DOWNLOADS := ${PWD}/downloads/$(ARCH)
NPROC := $(shell nproc)
CFLAGS := -I$(INCLUDEDIR) -flax-vector-conversions -O3
LDFLAGS := -L$(LIBDIR)
CC      := gcc
PKG_CONFIG_LIBDIR := $(BUILD_PREFIX)/lib/pkgconfig
GIT := git
CLONE := $(GIT) clone -q
GITHUB := https://github.com

CONFIGURE_ENV := \
	PKG_CONFIG_LIBDIR=$(PKG_CONFIG_LIBDIR) \
	CC="$(CC)" CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)"

CONFIGURE_ARGS := --prefix="$(BUILD_PREFIX)"

CMAKE_ARGS := \
	-DCMAKE_INSTALL_PREFIX="$(BUILD_PREFIX)" \
	-DCMAKE_C_FLAGS="$(CFLAGS)"

RUBY_CONFIGURE_ARGS := \
	--disable-install-doc \
	--enable-shared 

CONFIGURE := $(CONFIGURE_ENV) ./configure $(CONFIGURE_ARGS)
AUTOGEN   := $(CONFIGURE_ENV) ./autogen.sh $(CONFIGURE_ARGS)
CMAKE     := $(CONFIGURE_ENV) cmake .. $(CMAKE_ARGS)

default: everything

# iconv
iconv: init_dirs $(LIBDIR)/libiconv.a

$(LIBDIR)/libiconv.a: $(DOWNLOADS)/iconv/Makefile
	cd $(DOWNLOADS)/iconv; make; make install

$(DOWNLOADS)/iconv/Makefile: $(DOWNLOADS)/iconv/configure
	cd $(DOWNLOADS)/iconv; \
	$(CONFIGURE) --enable-static=true --enable-shared=false

$(DOWNLOADS)/iconv/configure: $(DOWNLOADS)/libiconv-1.16.tar.gz
	cd $(DOWNLOADS); \
	tar -xzf libiconv-1.16.tar.gz; \
	mv libiconv-1.16 iconv

$(DOWNLOADS)/libiconv-1.16.tar.gz:
	wget https://ftp.gnu.org/pub/gnu/libiconv/libiconv-1.16.tar.gz -P $(DOWNLOADS)

# SDL_sound
sdlsound: init_dirs $(LIBDIR)/libSDL2_sound.a

$(LIBDIR)/libSDL2_sound.a: $(DOWNLOADS)/sdl_sound/cmakebuild/Makefile
	cd $(DOWNLOADS)/sdl_sound/cmakebuild; \
	make -j$(NPROC); make install

$(DOWNLOADS)/sdl_sound/cmakebuild/Makefile: $(DOWNLOADS)/sdl_sound/CMakeLists.txt
	cd $(DOWNLOADS)/sdl_sound; mkdir -p cmakebuild; cd cmakebuild; \
	$(CMAKE) \
	-DSDLSOUND_BUILD_TEST=false

$(DOWNLOADS)/sdl_sound/CMakeLists.txt:
	$(CLONE) $(GITHUB)/icculus/SDL_sound $(DOWNLOADS)/sdl_sound

# Standard ruby
ruby: init_dirs $(BUILD_PREFIX)/libruby.so.$(RUBY_VER)

$(BUILD_PREFIX)/libruby.so.$(RUBY_VER): $(DOWNLOADS)/ruby/Makefile
	cd $(DOWNLOADS)/ruby; \
	make -j$(NPROC); make install

$(DOWNLOADS)/ruby/Makefile: $(DOWNLOADS)/ruby/configure
	cd $(DOWNLOADS)/ruby; \
	$(CONFIGURE) $(RUBY_CONFIGURE_ARGS) $(RUBY_FLAGS)

$(DOWNLOADS)/ruby/configure: $(DOWNLOADS)/ruby/*.c
	cd $(DOWNLOADS)/ruby; autoreconf -i

$(DOWNLOADS)/ruby/*.c:
	$(CLONE) $(GITHUB)/ruby/ruby $(DOWNLOADS)/ruby -b ruby_$(RUBY_BRANCH);

libnsgif: init_dirs ${LIBDIR}/libnsgif.so

$(LIBDIR)/libnsgif.so: $(DOWNLOADS)/libnsgif/Makefile
	cd $(DOWNLOADS)/libnsgif; \
	make -j$(NPROC); make install

$(DOWNLOADS)/libnsgif/Makefile: $(DOWNLOADS)/libnsgif/configure
	cd $(DOWNLOADS)/libnsgif; \
	$(CONFIGURE)

$(DOWNLOADS)/libnsgif/configure: $(DOWNLOADS)/libnsgif/autogen.sh
	cd $(DOWNLOADS)/libnsgif; ./autogen.sh

$(DOWNLOADS)/libnsgif/autogen.sh:
	$(CLONE) $(GITHUB)/jcupitt/libnsgif-autotools $(DOWNLOADS)/libnsgif

# ====
init_dirs:
	@mkdir -p $(LIBDIR) $(INCLUDEDIR)

powerwash: clean-downloads

clean-downloads:
	-rm -rf downloads

deps-core: sdlsound iconv libnsgif
everything: deps-core ruby
