MODULE = trajcomp.so

BOOST_PATH = /usr/local/lib
BOOST_INCLUDE_PATH = /usr/local/include/boost/
TRAJCOMP_PATH = /usr/include/
PYTHON_HEADER_PATH = /usr/include/python3.5
PYTHON_MODULE_PATH = /usr/local/lib/python3.5/dist-packages/

INC_PATHS=-Isrc/ -I$(BOOST_INCLUDE_PATH) -I$(BOOST_PATH) -I$(PYTHON_HEADER_PATH) -I$(TRAJCOMP_PATH)

CPP = g++
CPP_FILES = $(wildcard src/*.cpp)
OBJ_FILES = $(addprefix build/,$(notdir $(CPP_FILES:.cpp=.o)))
DEP_FILES = $(addprefix build/,$(notdir $(CPP_FILES:.cpp=.d)))

#CFLAGS = -g -c -Wall -std=c++11 -pthread $(INC_PATHS)
CFLAGS=-O3 -fno-inline -Wall -g -fPIC -std=c++11 $(INC_PATHS)
#LDFLAGS = -DNDEBUG -g -fwrapv -O2 -Wall -g -fstack-protector-strong -Wformat -Werror=format-security -Wdate-time -D_FORTIFY_SOURCE=2 -fPIC 
LDFLAGS=
LIBS =-Wl,--start-group -L$(BOOST_PATH) -ldl -Wl,-rpath,$(BOOST_PATH) -lboost_python3 -lboost_serialization -Wl,--end-group


.PHONY: all
all: python3

python3: mkdirs $(MODULE)
	cp $(MODULE) $(PYTHON_MODULE_PATH)

$(MODULE): $(OBJ_FILES)
	$(CPP) -shared $(LDFLAGS) $(OBJ_FILES) $(LIBS) -o $(MODULE)

$(OBJ_FILES): $(CPP_FILES)
	$(CPP) $(CFLAGS) -c -MMD -MP -o $@ $<

-include $(DEP_FILES)

mkdirs:
	mkdir -p build

clean:
	rm build -Rf
	rm -f $(MODULE)
