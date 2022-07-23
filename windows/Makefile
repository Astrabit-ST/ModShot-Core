ARCH := $(shell ruby -e "puts ENV[\"MSYSTEM\"].downcase")
RB_PREFIX := $(shell ruby -e "case '$(ARCH)'; \
							  when 'mingw64'; \
							  	puts 'x64-msvcrt'; \
							  when 'mingw32'; \
							    puts 'msvcrt'; \
							  when 'ucrt64', 'clang64'; \
							  	puts 'x64-ucrt'; \
							  when 'clang32'; \
							  	puts 'ucrt'; \
							  end \
							")
RUBY_VER ?= "3.1"
RUBY_BRANCH = $(subst .,_,$(RUBY_VER))
RUBY_DLL_VER = $(subst .,,$(RUBY_VER))

RUBY_FLAGS := ${RUBY_FLAGS}

BUILD_PREFIX := ${PWD}/build-$(ARCH)
LIBDIR := $(BUILD_PREFIX)/lib
INCLUDEDIR := $(BUILD_PREFIX)/include
DOWNLOADS := ${PWD}/downloads/$(ARCH)
NPROC := $(shell nproc)
CFLAGS := -I$(INCLUDEDIR)
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
	-DCMAKE_C_FLAGS="$(CFLAGS)" \
	-G "MSYS Makefiles"

RUBY_CONFIGURE_ARGS := \
	--prefix="$(shell cygpath -m ${BUILD_PREFIX})" \
	--disable-install-doc \
	--enable-shared

CONFIGURE := $(CONFIGURE_ENV) ./configure $(CONFIGURE_ARGS)
AUTOGEN   := $(CONFIGURE_ENV) ./autogen.sh $(CONFIGURE_ARGS)
CMAKE     := $(CONFIGURE_ENV) cmake .. $(CMAKE_ARGS)

default: everything

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
ruby: init_dirs $(BUILD_PREFIX)/$(RB_PREFIX)-ruby$(RUBY_DLL_VER).dll

$(BUILD_PREFIX)/$(RB_PREFIX)-ruby$(RUBY_DLL_VER).dll: $(DOWNLOADS)/ruby/Makefile
	cd $(DOWNLOADS)/ruby; \
	make -j$(NPROC); make install -j$(NPROC)

$(DOWNLOADS)/ruby/Makefile: $(DOWNLOADS)/ruby/configure
	cd $(DOWNLOADS)/ruby; \
	$(CONFIGURE) $(RUBY_CONFIGURE_ARGS) $(RUBY_FLAGS)

$(DOWNLOADS)/ruby/configure: $(DOWNLOADS)/ruby/*.c
	cd $(DOWNLOADS)/ruby; autoreconf -i

$(DOWNLOADS)/ruby/*.c:
	$(CLONE) $(GITHUB)/ruby/ruby $(DOWNLOADS)/ruby -b ruby_$(RUBY_BRANCH);

libnsgif: init_dirs ${LIBDIR}/libnsgif.dll

$(LIBDIR)/libnsgif.dll: $(DOWNLOADS)/libnsgif/Makefile
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

deps-core: sdlsound libnsgif
everything: deps-core ruby
