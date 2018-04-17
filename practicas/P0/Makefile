# Makefile de P0

CXX = g++
CXXFLAGS = -g -Wall -std=c++11 -pedantic
CPPFLAGS = -DP0 -I ../Tests-auto -I.
OBJETOS = test-caso0-fecha-auto.o test-caso0-cadena-auto.o \
	test-auto.o cadena.o fecha.o
VPATH = ../Tests-auto:.

test-P0-auto: $(OBJETOS)
	$(CXX) $(LDFLAGS) $(OBJETOS) -o $@

all: test-P0-auto

test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o: \
	test-caso0-fecha-auto.cpp test-caso0-cadena-auto.cpp \
	test-auto.cpp test-auto.hpp fecha.hpp cadena.hpp
fecha.o: fecha.hpp fecha.cpp
cadena.o: cadena.hpp cadena.cpp

clean:
	$(RM) test-P0-auto $(OBJETOS) core *~

