# if project is in External dir
EXTERN = yes

# if project if pure c code
C = yes

# if source path if different to ROOT/Src/PROJECT/
# specified with SRC_PATH (root path relative)
# SRC_PATH= 

# List of source file (SRC_PATH relative)
SRC= \
	src/SDL_framerate.c \
	src/SDL_gfxBlitFunc.c \
	src/SDL_gfxPrimitives.c \
	src/SDL_imageFilter.c \
	src/SDL_rotozoom.c \

# Option optionnal for the compilation
# OPTION = 

# List of include dir (ROOT relative)
INC_DIR = \
	External/SDL/include \

# Additionnal library for the final link
# (ROOT path relative)
# LIB_DEP= 
	
