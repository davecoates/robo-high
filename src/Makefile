SRCS = main.cpp robo.cpp app.cpp entitymanager.cpp component.cpp entity.cpp\
	   box2d_debug.cpp system.cpp\
	   systems/render.cpp systems/physics.cpp systems/keyboardinput.cpp \
	   systems/movement.cpp \
	   contactlistener.cpp node.cpp \
	   nodes/rendernode.cpp nodes/physicsnode.cpp nodes/movementnode.cpp
OBJS = $(SRCS:%.cpp=../obj/%.o)
LDFLAGS =-framework sfml-graphics -framework sfml-window -framework sfml-system -lBox2d
CXXFLAGS = -c -Wall -Wextra -std=c++11

TARGET = ../bin/robo-high

$(TARGET): all_nodes.hpp components.hpp dirs $(OBJS)
	g++ $(LDFLAGS) $(OBJS) -o $@

../obj/%.o: %.cpp
	g++ $(CXXFLAGS) $< -o $@

components.hpp:
	for i in `ls components/*.hpp`; do echo "#include \"$$i\""; done >> components.hpp

all_nodes.hpp:
	for i in `ls nodes/*.hpp`; do echo "#include \"$$i\""; done >> all_nodes.hpp

ALLFILES = $(shell gfind -type f -name "*.*pp")

todolist:
	-@for file in $(ALLFILES:Makefile=); do fgrep -H -e TODO -e FIXME $$file; done; true

play: $(TARGET)
	$(TARGET)

.PHONY: dirs
dirs:
	@mkdir -p ../obj ../bin ../obj/systems ../obj/nodes

.PHONY: clean
clean:
	-rm -r ../obj ../bin components.hpp all_nodes.hpp

dependencies:
	brew install sfml box2d
