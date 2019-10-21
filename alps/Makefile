CC = /usr/bin/g++
SRC_DIR = src/
OUT_DIR = _build/

Z3_H = z3_env/z3/include
Z3_LIB = z3_env/z3/bin

CFLAGS = -g -std=c++11 -I$(Z3_H) -L$(Z3_LIB) 

SRC_Names = global main input utility template matching datalog context query fixedpoint refinement config

SRC = $(addprefix $(SRC_DIR), $(addsuffix .cpp, $(SRC_Names)))
OBJ = $(addprefix $(OUT_DIR), $(notdir $(SRC:.cpp=.o)))

alps: $(OBJ) Makefile
	@echo $(OBJ)
	$(CC) $(CFLAGS)  $(OBJ) -lz3 -o $@ 

ifeq ($(MAKECMDGOALS),clean)
# doing clean, so dont make deps.
DEPS=
else
# doing build, so make deps.
DEPS = $(addprefix $(OUT_DIR), $(notdir $(SRC:.cpp=.d)))

$(OUT_DIR)%.d: $(SRC_DIR)%.cpp
	$(CC) $(CFLAGS) -MM -MT '$(patsubst $(SRC_DIR)%.cpp,$(OUT_DIR)%.o,$<)' $< > $@

-include $(DEPS)
endif


$(OUT_DIR)%.o: $(SRC_DIR)%.cpp
	mkdir -p $(OUT_DIR)
	@echo "compiling  $<  "
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean all alps


all: alps

clean:
	rm $(OBJ) alps 

$(OUT_DIR):
	mkdir -p $(OUT_DIR)
