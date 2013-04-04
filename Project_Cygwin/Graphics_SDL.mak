# if source path if different to ROOT/Src/PROJECT/
# specified with SRC_PATH (root path relative)
# SRC_PATH= 

# List of source file (SRC_PATH relative)
SRC= \
	FontResource_SDL.cpp \
	GEngine_SDL.cpp \
	ImageResource_SDL.cpp \
	InputEvent_SDL.cpp \

# List of include dir (ROOT relative)
INC_DIR = \
	Src/Common \
	Src/Graphics \
	External/SDL_image-1.2.10-lib/include \
	External/SDL_ttf/include \
	External/SDL_gfx/src \
	External/SDL_Draw/src \
	External/SDL/include \

# Option optionnal for the compilation
# OPTION = 

# Additionnal library for the final link
# (ROOT path relative)
LIB_DEP= \
	External/SDL_image-1.2.10-lib/lib/SDL_image.lib \
	External/SDL_ttf/lib/SDL_ttf.lib \
	External/SDL/lib/SDLmain.lib \
	External/SDL/lib/SDL.lib
	
