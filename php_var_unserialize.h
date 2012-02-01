#include <string.h>
#include <v8.h>
#include <node.h>

#ifndef PHP_VAR_UNSERIALIZE_H
#define PHP_VAR_UNSERIALIZE_H

using namespace v8;

#define UNSERIALIZE_PARAMETER Handle<Value> *rval, const unsigned char **p, const unsigned char *max
#define UNSERIALIZE_PASSTHRU rval, p, max
static inline int process_nested_data(UNSERIALIZE_PARAMETER, long elements, int objprops);
int php_var_unserialize(Handle<Value> *rval/*zval **rval*/, const unsigned char **p, const unsigned char *max);

#endif