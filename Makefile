CXX=g++
CXXFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
EXEC=open-world
SRCDIR=src
BUILDDIR=build
SRC=$(shell find $(SRCDIR) -type f -name *.cpp)
OBJ=$(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SRC:.cpp=.o))

all: gen-build-dir $(EXEC)

open-world: $(OBJ)
	$(CXX) $^ -o $@ $(CXXFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $< -o $@

clean:
	rm -rf build

mrproper: clean
	rm -rf open-world

# Create build/ directory and its equivalent src/ subdirectories
gen-build-dir:
	mkdir $(shell for i in $(shell find src); do if [ -d $$i ]; then echo $${i/$(SRCDIR)/$(BUILDDIR)}; fi; done)

.PHONY: clean gen-build-dir
