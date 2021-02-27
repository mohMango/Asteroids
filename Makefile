# Compiler setting
CC = g++
CXXFLAGS = -std=c++14# -Wall
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network


# Makefile settings
APPNAME = game
SRCDIR = src
OBJDIR = obj
PCH_H = 

# Basie settings
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
PCH_OUT = $(PCH_H).gch
# UNIX-based OS settings
RM = rm -f
# Windows OS settings
DEL = del
EXE = .exe
WDELOBJ = $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)\\%.o)

# Targests
all: $(APPNAME)

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Builds the pch file
$(PCH_OUT): $(PCH_H)
	$(CC) $(CXXFLAGS) -o $@ $^

# Building rule for .o
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CXXFLAGS) -o $@ -c $<

# Building rule for .o with pch
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(PCH_OUT)
	$(CC) $(CXXFLAGS) -o $@ -c $< -include $(PCH_H)


# UNIX-based os clean
.PHONY: clean
clean:
	$(RM) $(OBJ) $(APPNAME)

# Windows OS clean
.PHONY: cleanw
cleanw:
	$(DEL) $(WDELOBJ) $(APPNAME)$(EXE)
