# if project is in External dir
# EXTERN = yes

# if project if pure c code
# C = yes

# if source path if different to ROOT/Src/PROJECT/
# specified with SRC_PATH (root path relative)
# SRC_PATH= 

# List of source file (SRC_PATH relative)
SRC= \
	Action/IBActionDef_DropObject.cpp \
	Action/IBActionDef_FindPath.cpp \
	Action/IBActionDef_FollowPath.cpp \
	Action/IBActionDef_PickObject.cpp \
	Action/IBActionDef_PushProp.cpp \
	Action/IBActionDef_UnblockProp.cpp \
	BLApp.cpp \
	BLBot.cpp \
	BLGoalMenu.cpp \
	BLWorld.cpp \
	Fact/IBFactDef_BotAtPos.cpp \
	Fact/IBFactDef_BotHasObject.cpp \
	Fact/IBFactDef_BotIsEmpty.cpp \
	Fact/IBFactDef_BotNearPos.cpp \
	Fact/IBFactDef_HasValidPath.cpp \
	Fact/IBFactDef_ObjectAtPos.cpp \
	Fact/IBFactDef_PosIsFree.cpp \
	Fact/IBFactDef_PropIsUnblock.cpp \
	Fact/IBFactDef_PropIsPickable.cpp \
	Fact/IBFactDef_PropIsMovable.cpp \
	IBPlanner_BL.cpp \
	Main.cpp \
	Map/BLMap.cpp \
	Map/BLSquare.cpp \
	Map/BLTiles.cpp \
	MapViewApp.cpp \
	SpriteViewApp.cpp \
	TilesViewApp.cpp \
	World/BLDoor.cpp \
	World/BLHeavyProp.cpp \
	World/BLLightProp.cpp \
	World/BLObject.cpp \
	World/BLProp.cpp \
	World/BLProp_FB.cpp \
	World/BLProp_SI.cpp \
	World/IBPath.cpp \

# Option optionnal for the compilation
# OPTION = 

# List of include dir (ROOT relative)
INC_DIR = Src/Common Src/Graphics Src/IBot Src/Navigation Src/Graphics_SDL

# Additionnal library for the final link
# (ROOT path relative)
# LIB_DEP= 


