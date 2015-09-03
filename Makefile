SRC = thingml_xpath.c
OBJ = thingml_xpath.o

EXAMPLE_SRC = ./examples/parse_xml.c
EXAMPLE_OBJ = ./examples/parse_xml.o
EXAMPLE_BIN = ./examples/parse_xml

LIB = -lxml2 -lm

DYNAMIC_LIB = libtmlxpathvalue.so
STATIC_LIB = libtmlxpathvalue.a

INSTALL_INCLUDE_DIR = /usr/local/include/
INSTALL_LIB_DIR = /usr/local/lib/

THINGML_XPATH_DIR = thingmlxpath

XML2_INCLUDE_DIR = -I/usr/include/libxml2/

CROSS_COMPILE :=

GFLAGS = -fPIC -g

GCC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar

%.o : %.c
	$(GCC) $(XML2_INCLUDE_DIR) $(GFLAGS) -c -o $@ $<

all: static dynamic bin

static : $(OBJ)
	$(AR) -rcs $(STATIC_LIB) $(OBJ)

dynamic : $(OBJ)
	$(GCC) -shared -rdynamic -o $(DYNAMIC_LIB) $(OBJ)
	
install:
	install -d $(INSTALL_INCLUDE_DIR)$(THINGML_XPATH_DIR)
	install $(DYNAMIC_LIB) $(INSTALL_LIB_DIR)
	install $(STATIC_LIB) $(INSTALL_LIB_DIR)
	cp -r ./*.h $(INSTALL_INCLUDE_DIR)$(THINGML_XPATH_DIR)
	ldconfig

uninstall:
	rm -rf $(INSTALL_INCLUDE_DIR)$(THINGML_XPATH_DIR)
	rm -rf $(INSTALL_LIB_DIR)$(DYNAMIC_LIB)
	rm -rf $(INSTALL_LIB_DIR)$(STATIC_LIB)

bin : example

example : $(EXAMPLE_OBJ)
	$(GCC) -o $(EXAMPLE_BIN) $(GFLAGS) $(EXAMPLE_OBJ) $(STATIC_LIB) $(LIB)
	
clean :
	rm $(OBJ) $(DYNAMIC_LIB) $(STATIC_LIB) $(EXAMPLE_BIN) $(EXAMPLE_OBJ)
