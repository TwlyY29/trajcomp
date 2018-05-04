MODULE = trajcomp.so

BOOST_PATH = /usr/lib
BOOST_INCLUDE_PATH = /usr/include/boost/
TRAJCOMP_PREFIX = /usr/include/
PYTHON_HEADER_PATH = /usr/include/$(PYVERS)
PYTHON_MODULE_PATH = /usr/local/lib/$(PYVERS)/dist-packages/

INC_PATHS=-Isrc/ -I$(BOOST_INCLUDE_PATH) -I$(BOOST_PATH) -I$(PYTHON_HEADER_PATH) -I$(TRAJCOMP_PREFIX)

CPP = g++
CPP_FILES = $(wildcard src/*.cpp)
OBJ_FILES = $(addprefix build/,$(notdir $(CPP_FILES:.cpp=.o)))
DEP_FILES = $(addprefix build/,$(notdir $(CPP_FILES:.cpp=.d)))

#CFLAGS = -g -c -Wall -std=c++11 -pthread $(INC_PATHS)
#CFLAGS=-O3 -fno-inline -Wall -g -fPIC -std=c++11 $(INC_PATHS)
CFLAGS=-Ofast -Wall -fPIC -std=c++11 $(INC_PATHS)
#LDFLAGS = -DNDEBUG -g -fwrapv -O2 -Wall -g -fstack-protector-strong -Wformat -Werror=format-security -Wdate-time -D_FORTIFY_SOURCE=2 -fPIC 
LDFLAGS=
LIBS =-Wl,--start-group -L$(BOOST_PATH) -ldl -Wl,-rpath,$(BOOST_PATH) $(PYBOOSTLIB) -lboost_serialization -Wl,--end-group


.PHONY: all
all: installtrajcomp python3

installtrajcomp:
	mkdir -p $(TRAJCOMP_PREFIX)/trajcomp
	rsync -rtp --delete ../r-package/trajcomp/src/trajcomp/ $(TRAJCOMP_PREFIX)/trajcomp

python3: PYVERS=python3.6
python3: PYBOOSTLIB=-lboost_python3
python3: build

python2: PYVERS=python2.7
python2: PYBOOSTLIB=-lboost_python
python2: build

build: mkdirs $(MODULE)
	mv $(MODULE) $(PYTHON_MODULE_PATH)

$(MODULE): $(OBJ_FILES)
	$(CPP) -shared $(LDFLAGS) $(OBJ_FILES) $(LIBS) -o $(MODULE)

$(OBJ_FILES): $(CPP_FILES)
	$(CPP) $(CFLAGS) -c -MMD -MP -o $@ $<

-include $(DEP_FILES)

mkdirs:
	mkdir -p build

clean:
	rm -Rf build
	rm -f $(MODULE)
