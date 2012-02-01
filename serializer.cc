#include <stdio.h>
#include <node.h>
#include <v8.h>
#include "php_var_unserialize.h"
#include "php_var_serialize.h"
using namespace v8;

extern "C" {
    NODE_MODULE_EXPORT void init(Handle<Object> target);
}

#define PS_DELIMITER '|'
#define PS_UNDEF_MARKER '!'

Handle<Value> php_sess_unserialize(const Arguments& args) {
    HandleScope scope;
    if (args.Length() != 1 || !(args[0]->IsString() || args[0]->IsStringObject())) {
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

        name = String::New((const char *) p, namelen);
        q++;

        if (has_value) {
            if (php_var_unserialize(&current, (const unsigned char **) &q, (const unsigned char *) endptr)) {
                obj->Set(name, current);
            }
        }
skip:

        p = q;
    }
break_outer_loop:

    return scope.Close(obj);
}

Handle<Value> php_sess_serialize(const Arguments& args) {
    HandleScope scope;
    if (args.Length() != 1 || !args[0]->IsObject()) {
        return ThrowException(Exception::Error(String::New("Invalid number of arguments.")));
    }
    Local<Object> obj = args[0]->ToObject();
    Local<String> buf = String::New("");
    Local<v8::Array> names = obj->GetPropertyNames();
    for (unsigned int i = 0; i < names->Length(); i++) {
        Local<v8::String> name = names->Get(i)->ToString();
        buf = String::Concat(buf, String::Concat(String::Concat(
                String::Concat(name, String::New("|"))
                , php_var_serialize(obj->Get(name)))
                , obj->Get(name)->IsObject() ? String::New("") : String::New(";")
                )
                );
    }
    return scope.Close(buf);
}

void init(Handle<Object> target) {
    NODE_SET_METHOD(target, "php_sess_unserialize", php_sess_unserialize);
    NODE_SET_METHOD(target, "php_sess_serialize", php_sess_serialize);
}
