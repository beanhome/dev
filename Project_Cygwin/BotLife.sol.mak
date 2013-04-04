# PROJECT containing main function
MAIN = BotLife

# List of all the project
# (dependency orderer)
PROJECT = \
	Common \
	Navigation \
	SDL_Draw \
	SDL_gfx \
	Graphics \
	IBot \
	IBot_Graph \
	Graphics_SDL \


# platform
PLATFORM = Cygwin

# version
VERSION = Debug

# Root dir
ROOT = ../

include Solution.mak

