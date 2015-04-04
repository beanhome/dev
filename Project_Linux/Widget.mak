# if source path if different to ROOT/Src/PROJECT/
# specified with SRC_PATH (root path relative)
# SRC_PATH= 

# List of source file (SRC_PATH relative)
SRC= \
	Component/WBackground.cpp \
	Component/WButton.cpp \
	Component/WDebug.cpp \
	Component/WEditBox.cpp \
	Component/WEditText.cpp \
	Component/WImage.cpp \
	Component/WSimpleWindow.cpp \
	Component/WText.cpp \
	Component/WWindow.cpp \
	Widget.cpp \
	WidgetSide.cpp \

# Option optionnal for the compilation
OPTION = -std=c++11

# List of include dir (ROOT relative)
INC_DIR = Src/Common Src/Graphics

# Additionnal library for the final link
# LIB_DEP= 

