TARGET := bin/GCWShmup
OBJS := OBJ/main.o OBJ/clsPlayer.o OBJ/clsHealthBar.o OBJ/clsBullet.o OBJ/clsBackGround.o OBJ/clsAsteroid.o
OPK := bin/GCWShmup.opk
CXX := $(CROSS_COMPILE)g++

DEPENDENCIES := sdl SDL_image

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

OBJ/main.o: main.cpp main.h globalConstants.h clsPlayer.h clsBullet.h clsAsteroid.h clsHealthBar.h clsBackGround.h
	$(CXX) $(CPPFLAGS) -c -o OBJ/main.o main.cpp

OBJ/clsPlayer.o: clsPlayer.cpp clsPlayer.h globalConstants.h
	$(CXX) $(CPPFLAGS) -c -o OBJ/clsPlayer.o clsPlayer.cpp

OBJ/clsHealthBar.o: clsHealthBar.cpp clsHealthBar.h globalConstants.h
	$(CXX) $(CPPFLAGS) -c -o OBJ/clsHealthBar.o clsHealthBar.cpp

OBJ/clsBullet.o: clsBullet.cpp clsBullet.h globalConstants.h
	$(CXX) $(CPPFLAGS) -c -o OBJ/clsBullet.o clsBullet.cpp

OBJ/clsBackGround.o: clsBackGround.cpp clsBackGround.h globalConstants.h
	$(CXX) $(CPPFLAGS) -c -o OBJ/clsBackGround.o clsBackGround.cpp

OBJ/clsAsteroid.o: clsAsteroid.cpp clsAsteroid.h globalConstants.h
	$(CXX) $(CPPFLAGS) -c -o OBJ/clsAsteroid.o clsAsteroid.cpp

clean:
	rm -f $(TARGET) OBJ/$(OBJS) $(OPK)
