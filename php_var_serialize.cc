#include <v8.h>
#include <node.h>
#include <string.h>
#include "util.h"
#include "php_var_serialize.h"

using namespace v8;

Handle<String> nested_object(const v8::Handle<Value> &in) {
    Local<v8::Array> names = in->ToObject()->GetPropertyNames();
    int length = names->Length();
    Handle<String> buf = String::Concat(Number::New(length)->ToString(), String::New(":{"));
    for (int i = 0; i < length; i++) {
        /*buf = String::Concat(buf, php_var_serialize(names->Get(i)->ToString()));
        buf = String::Concat(buf, String::New(";"));
        buf = String::Concat(buf, php_var_serialize(in->ToObject()->Get(names->Get(i)->ToString())));
        buf = String::Concat(buf, String::New(";"));*/
        buf = String::Concat(
                String::Concat(
                  String::Concat(
                    String::Concat(
                      buf, php_var_serialize(names->Get(i)->ToString())
                    ), String::New(";")
                  ), php_var_serialize(in->ToObject()->Get(names->Get(i)->ToString()))
                ), String::New(";")
              );
    }
    buf = String::Concat(buf, String::New("}"));
    return buf;
}

Handle<String> php_var_serialize(const v8::Handle<Value> &in) {
    if (in->IsString()) {
        return String::Concat(
                 String::Concat(
                   String::Concat(
                     String::Concat(
                       String::New("s:"), Number::New(in->ToString()->Length())->ToString()
                     ), String::New(":\"")
				   ), in->ToString()
				 ), String::New("\"")
			   );
    } else if (in->IsNumber()) {
        uint64_t d64 = DoubleToBits(in->NumberValue());
//#include<stdlib.h>
//		uint64_t a = V8_INFINITY;
//system("pause");
        if (in->IsUint32()) {
            return String::Concat(String::New("i:"), in->ToString());
        } else if (d64 == V8_INFINITY) { //check with V8 double.h
            return String::New("d:INF");
        } else if (d64 == V8_NEG_INFINITY) {
            return String::New("d:-INF");
        } else if (((d64 & kExponentMask) == kExponentMask) && ((d64 & kSignificandMask) != 0)) {
            return String::New("d:NAN");
        } else if (DoubleToBits(in->NumberValue()) == V8_NEG_INFINITY) {//is Double
            return String::Concat(String::New("d:"), in->ToString());
        }
    } else if (in->IsBoolean()) {
        return String::Concat(String::New("b:"), in->ToBoolean()->Value() ? String::New("1") : String::New("0"));
    } else if (in->IsObject()) {
        return String::Concat(String::New("a:"), nested_object(in));
    } else if (in->IsNull() || in->IsUndefined()) {
        return String::New("N");
    }
    return String::New("");
}
