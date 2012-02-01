#include <string.h>
#include <v8.h>
#include <node.h>

#ifndef PHP_VAR_SERIALIZE_H
#define PHP_VAR_SERIALIZE_H

using namespace v8;

Handle<String> php_var_serialize(const v8::Handle<Value> &in);

#endif