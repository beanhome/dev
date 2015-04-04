# if source path if different to ROOT/Src/PROJECT/
# specified with SRC_PATH (root path relative)
# SRC_PATH= 

# List of source file (SRC_PATH relative)
SRC= \
	Event_SDL.cpp \
	FontResource_SDL.cpp \
	GEngine_SDL.cpp \
	ImageResource_SDL.cpp \

# List of include dir (ROOT relative)
INC_DIR = \
	Src/Common \
	Src/Graphics \
	/usr/include/SDL \

# Option optionnal for the compilation
OPTION = -std=c++11

# Additionnal library for the final link
LIB_DEP= \
	-lSDL \
	-lSDL_ttf \
	-lSDL_image \
	-lSDL_gfx \

