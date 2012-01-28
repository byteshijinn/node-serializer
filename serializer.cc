#include <stdio.h>
#include <node.h>
#include <v8.h>
#include "php_var_unserialize.h"
using namespace v8;

extern "C" {
  NODE_MODULE_EXPORT void init(Handle<Object> target);
}

#define PS_DELIMITER '|'
#define PS_UNDEF_MARKER '!'

Handle<Value> php_sess_unserialize(const Arguments& args)
{
	HandleScope scope;
	if(args.Length() != 1 || !(args[0]->IsString() || args[0]->IsStringObject())){
		return ThrowException(Exception::Error(String::New("Invalid number of arguments.")));
	}
	String::AsciiValue asciiValue(args[0]);
	const char *val = *asciiValue;
	int vallen = args[0]->ToString()->Length();
	const char *p, *q;
    Local<String> name;
	const char *endptr = val + vallen;
	Local<Value> current;
	int namelen;
	int has_value;

	Local<Object> obj = Object::New();
	p = val;
	while (p < endptr) {
		q = p;
		while (*q != PS_DELIMITER) {
			if (++q >= endptr) goto break_outer_loop;
		}
		if (p[0] == PS_UNDEF_MARKER) {
			p++;
			has_value = 0;
		} else {
			has_value = 1;
		}

		namelen = q - p;
		
		name = String::New((const char *)p,namelen);
		q++;

		if (has_value) {
			if(php_var_unserialize(&current, (const unsigned char **) &q, (const unsigned char *) endptr)) {
				obj->Set(name, current);
			}
		}
skip:

		p = q;
	}
break_outer_loop:

	return scope.Close(obj);
}

void init(Handle<Object> target) {
  NODE_SET_METHOD(target, "php_sess_unserialize", php_sess_unserialize);
}
