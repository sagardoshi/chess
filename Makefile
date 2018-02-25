# Compiler, Linker, and Target Executable
CXX 		:= g++
TARGET 		:= chess

# Directories
SRCDIR		:= src
INCDIR		:= inc
OBJDIR		:= obj
TARGETDIR	:= bin

# Extensions
SRCEXT		:= cpp
DEPEXT		:= d
OBJEXT		:= o

# Flags
CXXFLAGS 	:= -Wall -g

# Objects
_OBJ 		:= ChessMain.o \
	  		   ChessBoard.o \
			   ChessPiece.o \
			   Pawn.o \
			   Rook.o \
			   Knight.o \
			   Bishop.o \
			   Queen.o \
			   King.o \

OBJ			:= $(patsubst %,$(OBJDIR)/%,$(_OBJ))

$(TARGETDIR)/$(TARGET): $(OBJ)
	@$(CXX) $(OBJ) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

run:
	@$(TARGETDIR)/$(TARGET)

.PHONY: clean
clean:
	@rm -f $(OBJDIR)/*.o *.gch $(TARGETDIR)/$(TARGET)
