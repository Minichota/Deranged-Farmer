PROGRAM_NAME=Deranged-farmer
SRC_DIR=src
O_DIR=obj
CXX=g++
cpp_dirs=math game-state ui animation io entity entity/player entity/map debug entity/animals ai audio entity/inventory
external_files=
SRC=src
FILE=NULL

SRC_FILES= $(wildcard $(SRC)/*.cpp $(addsuffix /*.cpp,$(addprefix $(SRC)/,$(cpp_dirs))))
H_FILES=$(SRC_DIR) $(addprefix $(SRC_DIR)/,$(cpp_dirs))
OBJ_FILES=$(patsubst $(SRC)/%.o,$(O_DIR)/%.o, $(SRC_FILES:.cpp=.o))

VPATH=$(SRC_DIR) $(addprefix $(SRC)/,$(cppdirs))

CXX_FLAGS=$(addprefix -I, $(H_FILES)) `sdl2-config --libs --cflags` -O3 -Wall -lSDL2_image -lm -std=c++17 -lSDL2_ttf -lutil -lSDL2_image -pthread -lSDL2_mixer

all: $(O_DIR)/$(PROGRAM_NAME) | run

compile: $(O_DIR)/$(PROGRAM_NAME)

single: $(O_DIR)/$(FILE).o

$(O_DIR)/$(PROGRAM_NAME): $(OBJ_FILES)
	@echo "combining: $^"
	@$(CXX) -o $@ $^ $(CXX_FLAGS) $(external_files)
	@echo "done :)"

$(O_DIR)/%.o: %.cpp | $(addprefix $(O_DIR)/,$(cpp_dirs))
	@echo "compiling: $@"
	@$(CXX) -c -o $@ $< $(CXX_FLAGS)


$(addprefix $(O_DIR)/,$(cpp_dirs)):
	@mkdir -p $@

.PHONY: clean run
clean:
	@rm -rf $(O_DIR)
	@echo "cleaned :)"

run: $(O_DIR)/$(PROGRAM_NAME)
	@echo "running $(PROGRAM_NAME) :)"
	@$^
