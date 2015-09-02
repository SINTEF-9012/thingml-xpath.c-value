/*
 * parse_xml.c
 *
 *  Created on: Sep 2, 2015
 *      Author: vassik
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>


#include "../thingml_xpath.c"


void xpath_error_callback(void* _instance, ...) {
	printf("xpath_error_callback is called\n");
}

void xpath_integer_value_callback(void* _instance, ...) {
	int value;

	va_list valist;
	va_start(valist, _instance);

	value = va_arg(valist, int);

	va_end(valist);

	printf("xpath_integer_value_callback - %d \n", value);
}


int main(int argc, char * argv[]) {
	const char * xml_string = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><senml xmlns=\"urn:ietf:params:xml:ns:senml\" bn=\"urn:dev:mac:0024befffe804ff1\" bt=\"0\" ver=\"1\"><e n=\"temp\" u=\"Cel\" v=\"25.000000\"/></senml>";
	const char * int_xpath = "number(//*[local-name()='e'][1]/@v)";

	ThingMLXPATHParserCnxt* context = malloc(sizeof(ThingMLXPATHParserCnxt));

	context->thing_instance = NULL;
	context->fn_onerror_callback = xpath_error_callback;
	context->fn_parse_integer_callback = xpath_integer_value_callback;

	parse_integer(xml_string, int_xpath, (void*) context);

	free(context);

	return 0;
}

