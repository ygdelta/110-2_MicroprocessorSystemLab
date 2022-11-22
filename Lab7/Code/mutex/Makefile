CROSS_COMPILE = aarch64-linux-gnu-
CXX = $(CROSS_COMPILE)g++
LD = $(CROSS_COMPILE)ld
CXXFLAGS = -std=c++11
SRC = lab7_mutex.cpp
EXE = lab7_mutex
all:$(EXE)
$(EXE):$(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lpthread
#$(OBJ):$(SRC)
#	$(CXX) -c $?
clean:
	rm -f $(EXE)
	#rm -f $(OBJ)
