# Project Lane Detection. Compilation file (g++ lane_detection.cpp -o lane_detection `pkg-config --cflags --libs opencv4`)

CC = g++
CFLAGS = -Wall -g
SRC = lane_detection.cpp
OUT = lane_detection
LIBS = `pkg-config --cflags --libs opencv4`

all:
	$(CC) $(SRC) -o $(OUT) $(LIBS)

build:
	docker build -t lane_detection .

docker_run:
	docker run -it --rm -v $(PWD):/app lane_detection

clean:
	rm -f $(OUT)

run:
	./$(OUT)

re: clean all
