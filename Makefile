# Derleyici
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Hedef kaynak
TARGET = build/main
SRC = Main.cpp src/DeadlockManager.cpp

# dERLEME KURALLARI
all: ${TARGET}

${TARGET}: ${SRC}
	${CXX} ${CXXFLAGS} -o $@ $^

clean:
	rm -f ${TARGET}