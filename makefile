# Les dossiers sources
SRC_DIR         = ./Src/
OBJ_DIR         = ./Obj/
INC_DIR         = ./Inc/
DEP_DIR         = ./Dep/
RES_DIR         = ./Res/
BIN_DIR         = ./

# Nom *.exe
BIN             = compilateur

# 
CC      = g++
CPP     = g++
LD      = g++
FLEX    = flex
BISON   = bison -d

# flags and libs
CPPFLAGS        = -I$(INC_DIR) -g -Wall -pipe
CFLAGS          = -I$(INC_DIR) -g -Wall -pipe
LDFLAGS = -I$(INC_DIR) -lfl

# Les fichiers
SRCS_CPP        = $(wildcard $(SRC_DIR)*.cpp)
SRCS_C          = $(wildcard $(SRC_DIR)*.c)
SRCS_L          = $(wildcard $(RES_DIR)*.l)
SRCS_Y          = $(wildcard $(RES_DIR)*.y)

# Liste des dépendances *.cpp, *.c -> *.d
DEPS    = $(SRCS_CPP:$(SRC_DIR)%.cpp=$(DEP_DIR)%.d) $(SRCS_C:$(SRC_DIR)%.c=$(DEP_DIR)%.d)

# Liste des objets *.cpp, *.c, *.y, *.l -> *.o
OBJS    = $(SRCS_CPP:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o) $(SRCS_C:$(SRC_DIR)%.c=$(OBJ_DIR)%.o) \
          $(SRCS_Y:$(RES_DIR)%.y=$(OBJ_DIR)%.o) $(SRCS_L:$(RES_DIR)%.l=$(OBJ_DIR)%.o)

# main
all: $(BIN_DIR)/$(BIN)


$(BIN_DIR)/$(BIN): $(OBJS)
	@$(LD) $+ -o $@ $(LDFLAGS)
        
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -o $@ -c $<

$(SRC_DIR)%.c : $(RES_DIR)%.l 
	@$(FLEX) -o $@ $<
	@rm -f $(INC_DIR)parser.h #On efface l'ancien fichier parser.h du dossier "include"
	@mv -v $(SRC_DIR)parser.h $(INC_DIR) #Déplacement du nouveau parser.h dans le dossier "include"

$(SRC_DIR)%.c : $(RES_DIR)%.y
	@$(BISON) -o $@ $<

#Gestion des dépendances
$(DEP_DIR)%.d: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -MM -MD -o $@ $<

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@$(CPP) $(CPPFLAGS) -o $@ -c $<

$(DEP_DIR)%.d: $(SRC_DIR)%.cpp
	@$(CPP) $(CPPFLAGS) -MM -MD -o $@ $<

-include $(DEPS)

.PHONY: clean distclean


run: $(BIN_DIR)/$(BIN)
	$(BIN_DIR)/$(BIN)

clean:
	@rm -f $(OBJ_DIR)*.o $(SRC_DIR)*~ $(DEP_DIR)*.d *~ $(BIN_DIR)/$(BIN)

distclean: clean
	@rm -f $(BIN_DIR)/$(BIN)
