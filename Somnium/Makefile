CC := clang++ -fprofile-instr-generate -fcoverage-mapping -DDEBUG_MODE -DENABLE_DEBUG_CAMERA
WEBCC := emcc -O3 --memory-init-file 0 -DWEB_BUILD -s FULL_ES3=1 -s USE_GLFW=3 -s USE_FREETYPE=1
OSXLDFLAGS:= -framework OpenGL -l glfw -l GLEW -L Dependencies/portAudio/lib -l portaudio
LDFLAGS:= -lgcov -l GL -pthread -l glfw -l GLEW -l freetype -L Dependencies/portAudio/lib
CPPFLAGS := -Wall -g -std=c++11 -pthread -lm
PKGFLAGS := -Wextra `pkg-config --cflags glfw3 glew freetype2`
CXXFLAGS:=  -I Dependencies/GLEW/include -I Dependencies/GLFW/include -I Dependencies/portsf/include -I Dependencies/portAudio/include -I Dependencies/freetype/include
WEBFLAGS:=  -I Dependencies/GLEW/include -I Dependencies/GLFW/include -I Dependencies/portsf/include -I Dependencies/portAudio/include
SRC_DIR:=.
OBJ_DIR:=Objects
OBJ_DIR_WEB:=Objects
SUB_DIRS := $(shell find $(SRC_DIR) -type d | sed 's|^./||; s|\.||')
TARGET := SOMNIUM_BUILD
TARGETOSX := SOMNIUMOSX
TARGETWEB := SOMNIUM_web.html

SRCS := $(shell find $(SRC_DIR) -name "*.cpp")
OBJS:=$(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))
WEBOBJS:=$(patsubst %.cpp,$(OBJ_DIR)/%.bc,$(SRCS))

Debugx64:all

all: pre-build main-build

osx: pre-build main-build-OSX

web: pre-build main-build-web

pre-build:
	mkdir -p $(OBJ_DIR) $(addprefix $(OBJ_DIR)/,$(SUB_DIRS))

main-build:$(TARGET)

main-build-OSX:$(TARGETOSX)

main-build-web:$(TARGETWEB)

$(TARGETOSX):$(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(OSXLDFLAGS)

$(TARGETWEB):$(WEBOBJS)
	$(WEBCC) $(WEBOBJS) -o $(TARGET).html --preload-file Resources

$(TARGET):$(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o:%.cpp
	$(CC) $(CPPFLAGS) $(PKGFLAGS) $< -c -o $@ $(CXXFLAGS)

$(OBJ_DIR)/%.bc:%.cpp
	$(WEBCC) $(CPPFLAGS) $< -o $@ $(WEBFLAGS)

CXXFLAGS += -MMD
-include $(OBJS:.o=.d)


clean:
	rm SOMNIUM_BUILD* &
	rm -r $(OBJ_DIR)
