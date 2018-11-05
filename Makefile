# Makefile built using template from: https://github.com/LaurentTreguier/Makefile


#===== User defined variables =====#

DIR_SRC:=src/
DIR_INC:=inc/
DIR_OBJ:=obj/
# Source, header and object files directories.
# The object files directory also serves for dependency files.
# All directories must end with a slash ("/") or else the makefile won't work !

CC:=g++
EXT:=cc
TARGET:=main.exe
# The target executable file.

CFLAGS=$(COMMONFLAGS) -std=c11
CXXFLAGS=$(COMMONFLAGS) -std=c++11
LIBDIRS = -L/usr/lib64
INCDIRS = -I/usr/include
LDLIBS =  -lglut -lGL -lGLU -lX11 -lm


# Flags added to the compilation.
LINUXLIBS:=$(COMMONLIBS)
# Libraries needed to link the TARGET executable, for windows and for linux.

#===== Functions =====#

# All directories used in the functions must end with a slash ("/") or else they won't work !

search-dir=$(filter-out $1,$(dir $(wildcard $1*/)))
# Returns the list of subdirectories in Arg1 directory.
search-dir-all=$(strip $(call search-dir,$1) $(foreach DIR,$(call search-dir,$1),$(call search-dir-all,$(DIR))))
# Returns the list of directories and subdirectories in Arg1.
search-file=$(foreach DIR,$1,$(wildcard $(DIR)*.$(EXT)))
# Returns the list of files in Arg1 directories and their subdirectories.

#===== Variables =====#

DIR_SRC_ALL:=$(DIR_SRC) $(call search-dir-all,$(DIR_SRC))
DIR_INC_ALL:=$(DIR_INC) $(call search-dir-all,$(DIR_INC))
# List of all directories and subdirectories that can contain source and header files.
SRC:=$(notdir $(call search-file,$(DIR_SRC_ALL)))
# List of all source files in the main source directory and its subdirectories.
OBJ:=$(SRC:.$(EXT)=.o)
# List of all object files.
I_SRC:=$(addprefix -I,$(DIR_SRC_ALL))
I_INC:=$(addprefix -I,$(DIR_INC_ALL))
# The list of all -I for finding source and header files during the compilation.

VPATH:=$(DIR_SRC_ALL) $(DIR_OBJ)
# The VPATH variable contains all the source, header, object and dependency files directories.
# This is the variable Make uses to know where the targets and prerequisites are.

COMMONFLAGS+=$(I_SRC) $(I_INC) -MMD
#===== Rules =====#

.PHONY:all init clear %-depend clean

$(TARGET):$(OBJ)
	-@$(MOVE) *.o $(DIR_OBJ)
	-@$(MOVE) *.d $(DIR_OBJ)
	$(CC) $(addprefix $(DIR_OBJ),$(OBJ)) $(LIBS) -o $(TARGET)

