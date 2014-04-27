SRCS = main.cpp robo.cpp app.cpp entitymanager.cpp component.cpp entity.cpp\
	   box2d_debug.cpp \
	   systems/render.cpp systems/physics.cpp systems/keyboardinput.cpp \
	   systems/movement.cpp
OBJS = $(SRCS:%.cpp=../obj/%.o)
LDFLAGS =-lsfml-graphics -lsfml-window -lsfml-system -lBox2d
CXXFLAGS = -c -Wall -std=c++11

TARGET = ../bin/robo-high

$(TARGET): components.hpp dirs $(OBJS)
	g++ $(LDFLAGS) $(OBJS) -o $@

../obj/%.o: %.cpp
	g++ $(CXXFLAGS) $< -o $@

components.hpp:
	for i in `ls components/*.hpp`; do echo "#include \"$$i\""; done >> components.hpp

play: $(TARGET)
	$(TARGET)

.PHONY: dirs
dirs:
	@mkdir -p ../obj ../bin ../obj/systems

.PHONY: clean
clean:
	-rm -r ../obj ../bin components.hpp

dependencies:
	brew install sfml box2d
