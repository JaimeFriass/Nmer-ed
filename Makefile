SRC = src
INC = include
OBJ = obj
LIB = lib
BIN = bin
CXX = g++ -std=c++11
AR = ar rvs		
AR_MACOSX = libtool -static -o  # Para MACs
CPPFLAGS = -g  -I$(INC) -c



all: $(BIN)/principal

# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/doxPractica.txt

	
# ************ Compilación de módulos ************
$(BIN)/principal: $(OBJ)/principal.o $(LIB)/libNmer.a $(INC)/ktree.h
	$(CXX) -o $(BIN)/principal $(OBJ)/principal.o -I$(INC) -L$(LIB) -lNmer

$(OBJ)/principal.o: $(SRC)/principal.cpp
	$(CXX) $(CPPFLAGS)  -o $(OBJ)/principal.o $(SRC)/principal.cpp 

$(LIB)/libNmer.a: $(OBJ)/Nmer.o
	$(AR) $(LIB)/libNmer.a $(OBJ)/Nmer.o

$(OBJ)/Nmer.o: $(SRC)/Nmer.cpp $(INC)/Nmer.h
	$(CXX) $(CPPFLAGS)  -o $(OBJ)/Nmer.o $(SRC)/Nmer.cpp 

# ************ Limpieza ************
clean :
	-rm $(OBJ)/*

clean_bin : clean
	-rm $(BIN)/*

clean_doc : clean
	-rm doc/html/* doc/latex/*
