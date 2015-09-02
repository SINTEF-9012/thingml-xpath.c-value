SRC = thingml_xpath.c
OBJ = thingml_xpath.o

EXAMPLE_SRC = ./examples/parse_xml.c
EXAMPLE_OBJ = ./examples/parse_xml.o
EXAMPLE_BIN = ./examples/parse_xml

LIB = -lxml2 -lm

DYNAMIC_LIB = libtmlxpathvalue.so
STATIC_LIB = libtmlxpathvalue.a

INCLUDE_DIR = -I/usr/include/libxml2/

CROSS_COMPILE :=

GFLAGS = -fPIC -g

GCC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar

%.o : %.c
	$(GCC) $(INCLUDE_DIR) $(GFLAGS) -c -o $@ $<

all: static dynamic bin

static : $(OBJ)
	$(AR) -rcs $(STATIC_LIB) $(OBJ)

dynamic : $(OBJ)
	$(GCC) -shared -rdynamic -o $(DYNAMIC_LIB) $(OBJ)
	
bin : example

example : $(EXAMPLE_OBJ)
	$(GCC) -o $(EXAMPLE_BIN) $(GFLAGS) $(EXAMPLE_OBJ) $(STATIC_LIB) $(LIB)
	
clean :
	rm $(OBJ) $(DYNAMIC_LIB) $(STATIC_LIB) $(EXAMPLE_BIN) $(EXAMPLE_OBJ)
