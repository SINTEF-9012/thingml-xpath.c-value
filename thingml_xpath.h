/*
 * ThingMLXPATH.h
 *
 *  Created on: Jul 13, 2015
 *      Author: vassik
 */

#ifndef THINGML_XPATH_UTILITY_H_
#define THINGML_XPATH_UTILITY_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*pthingMLXPATHCallback)(void* _instance, ...);

typedef struct {
	pthingMLXPATHCallback fn_onerror_callback;
	pthingMLXPATHCallback fn_parse_integer_callback;
	pthingMLXPATHCallback fn_parse_double_callback;
	pthingMLXPATHCallback fn_parse_string_callback;
	pthingMLXPATHCallback fn_parse_boolean_callback;
	void* thing_instance;

} ThingMLXPATHParserCnxt;


void parse_integer(const char* xml_content, const char* xpath, void* parser_context);
void parse_double(const char* xml_content, const char* xpath, void* parser_context);
void parse_string(const char* xml_content, const char* xpath, void* parser_context);
void parse_boolean(const char* xml_content, const char* xpath, void* parser_context);


#ifdef __cplusplus
}
#endif

#endif /* THINGML_XPATH_UTILITY_H_ */
