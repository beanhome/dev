# Solution.mak
# Called from a .sol.mak file
# who define
# - MAIN (the project containing the main function)
# - PROJECT (list of the project, depend sorted)
# - PLATFORM (the platform)
# - VERSION (Debug or other)
# - ROOT (The root path)
#
# Each Project has his own .mak who define
# - EXTERN (the project is in External dir)
# - C (the project is pure c code)
# - SRC_PATH (the source path if different of default one)
# - SRC (the source files list)
# - OPTION (project compilator option)
# - INC_DIR (the list of include directory)
# - LIB_DEP (list of static library needed at the link)
#
# Each project .mak is converted to prefix the variable name with the project name
#

PROJECT += $(MAIN)

# function reverse
reverse = $(if $(wordlist 2,2,$(1)),$(call reverse,$(wordlist 2,$(words $(1)),$(1))) $(firstword $(1)),$(1))

# define compilator
CC= gcc
CPPC = g++
AR = ar -rc
LD= $(CPPC)

#define version from goal
ifeq ($(MAKECMDGOALS),debug)
VERSION=Debug
endif
ifeq ($(MAKECMDGOALS),release)
VERSION=Release
endif

#define some name complement and option
ifeq ($(VERSION),Debug)
LIB_POSTFIX=_d
OPTION=-g -D_DEBUG
endif
ifeq ($(PLATFORM), Win32)
EXE_EXT=.exe
LIB_EXT=.lib
else
EXE_EXT=
LIB_PREFIX=lib
LIB_EXT=.a
endif


# define path
BUILD_PATH = $(ROOT)Build/$(PLATFORM)/
EXE_PATH = $(BUILD_PATH)exe/$(VERSION)/
EXE = $(EXE_PATH)$(MAIN)$(EXE_EXT)

# All the generated mak
PROJ_MAK=$(foreach p,$(PROJECT),$(BUILD_PATH)mak/$(p).mak)

# General rule
all: $(EXE) $(PROJ_MAK) $(PROJECT)
exe: $(EXE) 

debug: all
release: all

# Copy the project makefile with specific name
$(BUILD_PATH)mak/%.mak: $(ROOT)Project_$(PLATFORM)/%.mak
	@echo 'Generate $*.mak'
	@mkdir -p $(dir $@)
	@sed -e 's/\([_A-Za-z]\+\) *=/$*_\1=/' $^ > $@

ifneq ($(MAKECMDGOALS),clean)
-include $(PROJ_MAK)
endif

# Generate the first var of each project
define PROJECT_var
$(1)_MAK= $(BUILD_PATH)mak/$(1).mak
$(1)_LIB= $(BUILD_PATH)lib/$(LIB_PREFIX)$(1)$(LIB_POSTFIX)$(LIB_EXT)
$(1)_DEP_PATH= $(BUILD_PATH)dep/$(1)/$(VERSION)/
$(1)_OBJ_PATH= $(BUILD_PATH)obj/$(1)/$(VERSION)/
$(1)_SRC_PATH= $(if $($(1)_SRC_PATH), $(ROOT)$($(1)_SRC_PATH), $(if $($(1)_EXTERN), $(ROOT)External/$(1)/, $(ROOT)Src/$(1)/))
$(1)_SRCEXT = $(if $($(1)_C), c, cpp)
$(1)_CC= $(if $($(1)_C), $(CC), $(CPPC))
endef

# Generate the other var of each project
define PROJECT_var2
$(1)_INC= -I $($(1)_SRC_PATH) $(foreach i,$($(1)_INC_DIR), -I $(if $(realpath $i),$i,$(ROOT)$i)) 
$(1)_OBJS= $(foreach f,$($(1)_SRC),$($(1)_OBJ_PATH)$(basename $f).o)
ALL_LIB+= $($(1)_LIB)
OTHER_LIB += $($(1)_LIB_DEP)
endef

# Some Test to eject the generation
define PROJECT_test
$(if $(wildcard $(ROOT)Project_$(PLATFORM)/$(1).mak), , $(error $(ROOT)Project_$(PLATFORM)/$(1).mak no exist))
endef

# Project rules
define PROJECT_rules
$(1): $($(1)_MAK) $($(1)_LIB)
$($(1)_LIB): $($(1)_OBJS) $($(1)_MAK) 
	@echo 'Generate static lib of $(1)'
	@mkdir -p $$(dir $$@)
	@$(AR) $$@ $($(1)_OBJS) 2> /dev/null

$($(1)_OBJ_PATH)%.o: $($(1)_SRC_PATH)%.$($(1)_SRCEXT)
	@echo 'Generate obj of $$<'
	@mkdir -p $$(dir $$@)
	@$($(1)_CC) $(OPTION) $($(1)_OPTION) -c $$< -o $$@ $($(1)_INC)

$($(1)_DEP_PATH)%.dep: $($(1)_SRC_PATH)%.$($(1)_SRCEXT)
	@echo 'Generate dep of $$<'
	@mkdir -p $$(dir $$@)
	@$($(1)_CC) $(OPTION) $($(1)_OPTION) -MM -MT $($(1)_OBJ_PATH)$$*.o $$< -MF $$@ $($(1)_INC)
endef

# include the dep of each project
define PROJECT_include
-include $(foreach f,$($(1)_SRC),$($(1)_DEP_PATH)$(basename $f).dep)
endef

# call Source target
define PROJECT_SOURCE_rules
$(foreach f,$($(1)_SRC), $(eval $(call SOURCE_rules,$(1),$(f))))
endef

# insert rule dor each source file
define SOURCE_rules
.PHONY: $(2) $(notdir $(2)) $(notdir $(basename $(2)))
$(2): $($(1)_SRC_PATH)$(2)
$(notdir $(2)): $($(1)_SRC_PATH)$(2)
$(notdir $(basename $(2))): $($(1)_SRC_PATH)$(2)
endef

# Call Project Rules
$(foreach p,$(PROJECT),$(eval $(call PROJECT_var,$(p))))
$(foreach p, $(PROJECT), $(eval $(call PROJECT_var2,$(p))))
$(foreach p, $(PROJECT), $(eval $(call PROJECT_test,$(p))))
$(foreach p, $(PROJECT), $(eval $(call PROJECT_rules,$(p))))
ifneq ($(MAKECMDGOALS),clean)
$(foreach p, $(PROJECT), $(eval $(call PROJECT_include,$(p))))
endif
$(foreach p, $(PROJECT), $(eval $(call PROJECT_SOURCE_rules,$(p))))

# exe rule
$(EXE): $(ALL_LIB)
	@mkdir -p $(dir $@)
	@echo 'Generate exe'
	@$(LD) $(OPTION) -o $(EXE) $(call reverse,$(ALL_LIB)) $(OTHER_LIB)

# Clean
.PHONY: clean
clean:
	@rm -rf $(BUILD_PATH)




