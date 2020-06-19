CXX=g++
CXXFLAGS=-Wall -std=c++17 -pedantic -Wextra
LD=g++
LDFLAGS=-Wall -pedantic -lpthread

all: game docs

docs: main.o CApplication.o CGame.o CMap.o CTile.o CTowerArcher.o CTowerBombarda.o \
	CTowerCaesar.o CTower.o CUnit.o ./Doxyfile
	@doxygen ./Doxyfile

clean:
	rm -f game *.o *~ core

game: main.o CApplication.o CGame.o CMap.o CTile.o CTowerArcher.o CTowerBombarda.o \
	CTowerCaesar.o CTower.o CUnit.o 
	$(LD) $(LDFLAGS) main.o CApplication.o CGame.o CMap.o CTile.o CTowerArcher.o \
	CTowerBombarda.o CTowerCaesar.o CTower.o CUnit.o -o game

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
CApplication.o: CApplication.cpp CApplication.hpp CGame.hpp

CGame.o: CGame.cpp CGame.hpp CMap.hpp

CTile.o: CTile.cpp CTile.hpp

CTower.o: CTower.cpp CTower.hpp CTile.hpp CUnit.hpp

CUnit.o: CUnit.cpp CUnit.hpp CTile.hpp

CTowerArcher.o: CTowerArcher.cpp CTowerArcher.hpp CTower.hpp CUnit.hpp

CTowerBombarda.o: CTowerBombarda.cpp CTowerBombarda.hpp CTower.hpp CUnit.hpp

CTowerCaesar.o: CTowerCaesar.cpp CTowerCaesar.hpp CTower.hpp CUnit.hpp

CMap.o: CMap.cpp CMap.hpp CTile.hpp CTower.hpp CUnit.hpp CTowerArcher.hpp \
	CTowerBombarda.hpp CTowerCaesar.hpp

main.o: main.cpp CApplication.hpp CMap.hpp CTile.hpp CTower.hpp CUnit.hpp \
	CGame.hpp

