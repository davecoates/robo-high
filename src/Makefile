SRCS = main.cpp robo.cpp
OBJS = $(SRCS:%.cpp=../obj/%.o)
LDFLAGS =-lsfml-graphics -lsfml-window -lsfml-system -lBox2d
CXXFLAGS = -c -Wall -std=c++11

TARGET = ../bin/robo-high

$(TARGET): dirs $(OBJS)
	g++ $(LDFLAGS) $(OBJS) -o $@

../obj/%.o: %.cpp
	g++ $(CXXFLAGS) $< -o $@

play: $(TARGET)
	$(TARGET)

.PHONY: dirs
dirs:
	@mkdir -p ../obj ../bin

.PHONY: clean
clean:
	-rm -r ../obj ../bin

dependencies:
	brew install sfml box2d
