CXX      = g++
CXXFLAGS = -std=c++1z -Wextra -Wall -pedantic -g -O2 
LDFLAGS  = -L /usr/local/lib -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -lpthread

SRCFILE = Sources
INCFILE = Includes
OBJFILE = Obj
EXEFILE = .

OUTPUTFILES = Output Output/Graphics Output/Map Output/Entity Output/Server Output/Movement Output/Master

DIRECTORIES = $(subst $(SRCFILE),$(OBJFILE),$(shell find $(SRCFILE) -type d))

EXENAME = test
SRC     = $(wildcard $(SRCFILE)/*.cpp) $(wildcard $(SRCFILE)/**/*.cpp)
INC     = $(wildcard $(SRCFILE)/*.hpp) $(wildcard $(SRCFILE)/**/*.hpp)
OBJ     = $(SRC:$(SRCFILE)/%.cpp=$(OBJFILE)/%.o)

ENDCOLOR    = \033[m

REDCOLOR	= \033[0;31m
GREENCOLOR  = \033[0;32m
YELLOWCOLOR = \033[0;33m
BLUECOLOR	= \033[0;34m
PURPLECOLOR = \033[0;35m
CYANCOLOR	= \033[0;36m
GREYCOLOR 	= \033[0;37m

LREDCOLOR	 = \033[1;31m
LGREENCOLOR	 = \033[1;32m
LYELLOWCOLOR = \033[1;33m
LBLUECOLOR   = \033[1;34m
LPURPLECOLOR = \033[1;35m
LCYANCOLOR	 = \033[1;36m
LGREYCOLOR	 = \033[1;37m

OKSTRING   = $(LGREENCOLOR)[SUCCES]$(ENDCOLOR)
WARSTRING  = $(LYELLOWCOLOR)[WARNING]$(ENDCOLOR)
ERRSTRING  = $(LREDCOLOR)[ERROR]$(ENDCOLOR)

all: $(EXENAME)

$(EXENAME): $(OBJ)
	@mkdir -p $(OUTPUTFILES)
	@mkdir -p $(EXEFILE)
	@echo "$(LGREENCOLOR)-------------------------------------------------------------------$(ENDCOLOR)"
	@echo "$(LGREENCOLOR)| Linking:    $(ENDCOLOR)$(LYELLOWCOLOR)$^$(ENDCOLOR)"
	@$(CXX) $^ -o $(EXEFILE)/$(EXENAME) $(LDFLAGS)
	@echo "$(LGREENCOLOR)-------------------------------------------------------------------$(ENDCOLOR)"
	@echo "$(LGREENCOLOR)| Executable: $(ENDCOLOR)$(LPURPLECOLOR)$(EXEFILE)/$(EXENAME)$(ENDCOLOR)"

$(OBJFILE)/%.o: $(SRCFILE)/%.cpp
	@mkdir -p $(DIRECTORIES)
	@printf "%-75b %s" "$(LGREENCOLOR)| Compiling:  $(ENDCOLOR)$(LCYANCOLOR)$<$(ENDCOLOR)"
	@-$(CXX) $(CXXFLAGS) -c $< -o $@ -I $(INCFILE)
	@$(eval COMPILRESULT := $(shell echo $$?))

ifneq ($(COMPILRESULT), 0)
ifneq ($(LOGFILE), "")
	@printf "%-20b" "$(LGREENCOLOR)[SUCCES]  |$(ENDCOLOR)\\n"
else
	@printf "%-20b" "$(LYELLOWCOLOR)[WARNING]|$(ENDCOLOR)\\n"
endif
else
	@printf "%-20b" "$(LREDCOLOR)[ERROR]  |$(ENDCOLOR)\\n"
endif

clean: 
	@rm -rf $(OBJFILE)
	@rm -f  $(EXEFILE)/$(EXENAME)