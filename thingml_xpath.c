/*
 * thingml_xpath.c
 *
 *  Created on: Sep 2, 2015
 *      Author: vassik
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <libxml/xmlstring.h>

#include "thingml_xpath.h"


xmlXPathObjectPtr evaluate_expression(xmlChar** xpathExpr,
		xmlXPathContextPtr* xpathCtx, xmlXPathObjectPtr* xpathObj,
		const char* xml_content, const char* xpath, void* parser_context);


void parse_integer(const char* xml_content, const char* xpath, void* parser_context) {
	xmlChar* xpathExpr = BAD_CAST xpath;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;

    xpathObj = evaluate_expression(&xpathExpr, &xpathCtx, &xpathObj, xml_content, xpath, parser_context);

    if(xpathObj) {
    	ThingMLXPATHParserCnxt * context = (ThingMLXPATHParserCnxt*) parser_context;
    	int value = (int)floor(xpathObj->floatval);

    	context->fn_parse_integer_callback(context->thing_instance, value);

    	/* Cleanup */
    	xmlXPathFreeObject(xpathObj);
    	xmlXPathFreeContext(xpathCtx);
    }
}

void parse_double(const char* xml_content, const char* xpath, void* parser_context) {
	xmlChar* xpathExpr = BAD_CAST xpath;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;

    xpathObj = evaluate_expression(&xpathExpr, &xpathCtx, &xpathObj, xml_content, xpath, parser_context);

    if(xpathObj) {
    	ThingMLXPATHParserCnxt * context = (ThingMLXPATHParserCnxt*) parser_context;

    	context->fn_parse_double_callback(context->thing_instance, xpathObj->floatval);

    	/* Cleanup */
    	xmlXPathFreeObject(xpathObj);
    	xmlXPathFreeContext(xpathCtx);
    }
}

void parse_string(const char* xml_content, const char* xpath, void* parser_context) {
	xmlChar* xpathExpr = BAD_CAST xpath;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;

    xpathObj = evaluate_expression(&xpathExpr, &xpathCtx, &xpathObj, xml_content, xpath, parser_context);

    if(xpathObj) {
    	ThingMLXPATHParserCnxt * context = (ThingMLXPATHParserCnxt*) parser_context;

    	context->fn_parse_string_callback(context->thing_instance, (char *) xpathObj->stringval);

    	/* Cleanup */
    	xmlXPathFreeObject(xpathObj);
    	xmlXPathFreeContext(xpathCtx);
    }
}

void parse_boolean(const char* xml_content, const char* xpath, void* parser_context) {
	xmlChar* xpathExpr = BAD_CAST xpath;
    xmlXPathContextPtr xpathCtx = NULL;
    xmlXPathObjectPtr xpathObj = NULL;

    xpathObj = evaluate_expression(&xpathExpr, &xpathCtx, &xpathObj, xml_content, xpath, parser_context);

    if(xpathObj) {
    	ThingMLXPATHParserCnxt * context = (ThingMLXPATHParserCnxt*) parser_context;
    	if(strcmp((char *) xpathObj->stringval, "true") == 0 || strcmp((char *) xpathObj->stringval, "false") == 0) {
    		int value = (strcmp((char *) xpathObj->stringval, "true") == 0) ? 1 : 0;
    		context->fn_parse_boolean_callback(context->thing_instance, value);
    	} else {
    		fprintf(stderr,"Error: value is neither false nor true '%s'\n", (char *) xpathObj->stringval);
    		context->fn_onerror_callback(context->thing_instance);
    	}

    	/* Cleanup */
    	xmlXPathFreeObject(xpathObj);
    	xmlXPathFreeContext(xpathCtx);
    }
}

xmlXPathObjectPtr evaluate_expression(xmlChar** xpathExpr,
		xmlXPathContextPtr* xpathCtx, xmlXPathObjectPtr* xpathObj,
		const char* xml_content, const char* xpath, void* parser_context) {

	xmlDocPtr doc = xmlParseMemory(xml_content, strlen(xml_content));
	ThingMLXPATHParserCnxt * context = (ThingMLXPATHParserCnxt*) parser_context;

    if (doc == NULL) {
    	fprintf(stderr, "Error: unable to parse string \"%s\"\n", xml_content);
    	context->fn_onerror_callback(context->thing_instance);
    	return NULL;
    }

    /* Create xpath evaluation context */
    *xpathCtx = xmlXPathNewContext(doc);
    if(*xpathCtx == NULL) {
        fprintf(stderr,"Error: unable to create new XPath context\n");
        xmlFreeDoc(doc);
        context->fn_onerror_callback(context->thing_instance);
        return NULL;
    }

    /* Evaluate xpath expression */
    *xpathObj = xmlXPathEvalExpression(*xpathExpr, *xpathCtx);
    if(*xpathObj == NULL) {
        fprintf(stderr,"Error: unable to evaluate xpath expression \"%s\"\n", *xpathExpr);
        xmlXPathFreeContext(*xpathCtx);
        xmlFreeDoc(doc);
        context->fn_onerror_callback(context->thing_instance);
        return NULL;
    }

    xmlFreeDoc(doc);
	return *xpathObj;
}
