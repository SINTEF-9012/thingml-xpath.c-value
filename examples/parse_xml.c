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

void xpath_double_value_callback(void* _instance, ...) {
	double value;

	va_list valist;
	va_start(valist, _instance);

	value = va_arg(valist, double);

	va_end(valist);

	printf("xpath_double_value_callback - %f \n", value);
}

void xpath_string_value_callback(void* _instance, ...) {
	char* value;

	va_list valist;
	va_start(valist, _instance);

	value = va_arg(valist, char*);

	va_end(valist);

	printf("xpath_string_value_callback - '%s' \n", value);
}

void xpath_boolen_value_callback(void* _instance, ...) {
	int value;

	va_list valist;
	va_start(valist, _instance);

	value = va_arg(valist, int);

	va_end(valist);

	printf("xpath_boolen_value_callback - %d \n", value);
}


int main(int argc, char * argv[]) {
	const char * xml_string = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><senml xmlns=\"urn:ietf:params:xml:ns:senml\" bn=\"urn:dev:mac:0024befffe804ff1\" bt=\"0\" ver=\"1\"><e n=\"temp\" u=\"Cel\" v=\"25.000000\" bfalse=\"false\" btrue=\"true\"/></senml>";
	const char * int_xpath = "number(//*[local-name()='e'][1]/@v)";
	const char * double_xpath = "number(//*[local-name()='e'][1]/@v)";
	const char * string_xpath = "string(//*[local-name()='e'][1]/@u)";
	const char * bool_xpath_false = "string(//*[local-name()='e'][1]/@bfalse)";
	const char * bool_xpath_true = "string(//*[local-name()='e'][1]/@btrue)";

	ThingMLXPATHParserCnxt* context = malloc(sizeof(ThingMLXPATHParserCnxt));

	context->thing_instance = NULL;
	context->fn_onerror_callback = xpath_error_callback;
	context->fn_parse_integer_callback = xpath_integer_value_callback;
	context->fn_parse_double_callback = xpath_double_value_callback;
	context->fn_parse_string_callback = xpath_string_value_callback;
	context->fn_parse_boolean_callback = xpath_boolen_value_callback;

	parse_integer(xml_string, int_xpath, (void*) context);
	parse_double(xml_string, double_xpath, (void*) context);
	parse_string(xml_string, string_xpath, (void*) context);
	parse_boolean(xml_string, bool_xpath_false, (void*) context);
	parse_boolean(xml_string, bool_xpath_true, (void*) context);

	free(context);

	return 0;
}

