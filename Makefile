CXX=g++
CXXFLAGS=-Wall
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
EXEC=open-world
SRCDIR=src
BUILDDIR=build
SRC=$(shell find $(SRCDIR) -type f -name *.cpp)
OBJ=$(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SRC:.cpp=.o))

all: gen-build-dir $(EXEC)

debug: CXXDEBUG=-g

debug: all


open-world: $(OBJ)
	$(CXX) $^ -o $@ $(LDFLAGS) $(CXXFLAGS) $(CXXDEBUG)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(CXXDEBUG)

clean:
	rm -rf build

mrproper: clean
	rm -rf open-world

# Create build/ directory and its equivalent src/ subdirectories
gen-build-dir:
	mkdir -p $(shell for i in $(shell find src); do if [ -d $$i ]; then echo $${i/$(SRCDIR)/$(BUILDDIR)}; fi; done)

.PHONY: clean gen-build-dir
