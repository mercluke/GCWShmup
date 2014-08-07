TARGET := bin/GCWShmup
OBJS := obj/main.o obj/clsPlayer.o obj/clsHealthBar.o obj/clsBullet.o obj/clsBackGround.o obj/clsAsteroid.o
OPK := opk/GCWShmup.opk
CXX := $(CROSS_COMPILE)g++

DEPENDENCIES := libini sdl SDL_ttf

SYSROOT := $(shell $(CXX) --print-sysroot)
PKGCONFIG := env PKG_CONFIG_SYSROOT_DIR=$(SYSROOT) PKG_CONFIG_LIBDIR=$(SYSROOT)/usr/lib/pkgconfig pkg-config
CPPFLAGS += $(shell $(PKGCONFIG) --cflags $(DEPENDENCIES))
LDFLAGS += $(shell $(PKGCONFIG) --libs $(DEPENDENCIES))

default: $(TARGET) 
ifdef CROSS_COMPILE
	mksquashfs bin $(OPK) -all-root -noappend -no-exports -no-xattrs 
endif

$(TARGET): $(OBJS)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $^ -o $@

obj/main.o: main.cpp main.h globalStuff.h clsPlayer.h clsBullet.h clsAsteroid.h clsHealthBar.h clsBackGround.h
	$(CXX) $(CPPFLAGS) -c -o obj/main.o main.cpp

obj/clsPlayer.o: clsPlayer.cpp clsPlayer.h globalStuff.h
	$(CXX) $(CPPFLAGS) -c -o obj/clsPlayer.o clsPlayer.cpp

obj/clsHealthBar.o: clsHealthBar.cpp clsHealthBar.h globalStuff.h
	$(CXX) $(CPPFLAGS) -c -o obj/clsHealthBar.o clsHealthBar.cpp

obj/clsBullet.o: clsBullet.cpp clsBullet.h globalStuff.h
	$(CXX) $(CPPFLAGS) -c -o obj/clsBullet.o clsBullet.cpp

obj/clsBackGround.o: clsBackGround.cpp clsBackGround.h globalStuff.h
	$(CXX) $(CPPFLAGS) -c -o obj/clsBackGround.o clsBackGround.cpp

obj/clsAsteroid.o: clsAsteroid.cpp clsAsteroid.h globalStuff.h
	$(CXX) $(CPPFLAGS) -c -o obj/clsAsteroid.o clsAsteroid.cpp

clean:
	rm -f $(TARGET) $(OBJS) $(OPK) bin/.GCWShmup
