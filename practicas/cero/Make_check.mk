#	$Id: Make_check.mk 375 2017-03-10 21:22:58Z gerardo $
#
DIR=../dsl-comprobaciones/

# Obligatorio Clang, versión 3.9 al menos
CXX         := clang++
CPPFLAGS    := -I${DIR} $(shell llvm-config --cppflags)
CXXFLAGS    := -std=c++11
# Descomentar la siguiente línea para obtener un ejecutable enlazado 
# estáticamente muy grande y pesado pero que se puede distribuir al 
# alumnado para que no tengan que instalarse todos los paquetes de 
# desarrollo de LLVM/CLang.
LDFLAGS     := # -static
LLVMLDFLAGS := $(shell llvm-config --libs) $(LDFLAGS)
COMMONSRCS  := 	$(DIR)checkCode.cpp $(DIR)execute.cpp $(DIR)matchers.cpp
SOURCES     := fecha_check.cpp cadena_check.cpp ${COMMONSRCS}
COMMONHDRS  := $(COMMONSRCS:.cpp=.h) $(DIR)info.h
COMMONOBJS  := $(COMMONSRCS:.cpp=.o)
OBJECTS     := $(SOURCES:.cpp=.o)
EXES        := fecha_check cadena_check
CLANGLIBS   := -lclangFrontend -lclangSerialization -lclangDriver \
		-lclangTooling -lclangParse -lclangSema -lclangAnalysis \
		-lclangEdit -lclangAST -lclangASTMatchers -lclangLex \
		-lclangBasic -lclangRewrite

.PHONY: clean all
all: $(EXES)

fecha_check: fecha_check.o $(COMMONOBJS)
	@echo "(LINK) fecha_check.o"
	@$(CXX) -o $@ $^ $(CLANGLIBS) $(LLVMLDFLAGS)

fecha_check.o: $(COMMONHDRS) $(COMMONOBJS) fecha.hpp fecha.cpp

cadena_check: cadena_check.o $(COMMONOBJS)
	@echo "(LINK) cadena_check.o"
	@$(CXX) -o $@ $^ $(CLANGLIBS) $(LLVMLDFLAGS)

cadena_check.o: $(COMMONHDRS) $(COMMONOBJS) cadena.hpp cadena.cpp

check_Fecha: fecha_check
	@echo Verificando fecha.cpp ...
	@./fecha_check -extra-arg="-std=c++11" fecha.cpp --

check_Cadena: cadena_check
	@echo Verificando cadena.cpp ...
	@./cadena_check -extra-arg="-std=c++11" cadena.cpp --

checks: check_Fecha check_Cadena

clean:
	@echo "Limpiando."
	@${RM} $(EXES) $(OBJECTS)

