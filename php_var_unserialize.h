#include <string.h>
#include <v8.h>
#include <node.h>

#ifndef PHP_VAR_UNSERIALIZE
#define PHP_VAR_UNSERIALIZE

using namespace v8;

static inline v8::Local<v8::String> v8_str(const char* x) {
  return v8::String::New(x);
}

static inline v8::Local<v8::Script> v8_compile(const char* x) {
  return v8::Script::Compile(v8_str(x));
}

static inline double DoubleFromBits(uint64_t value) {
  double target;
  memcpy(&target, &value, sizeof(target));
  return target;
}

static inline uint64_t DoubleToBits(double value) {
  uint64_t target;
  memcpy(&target, &value, sizeof(target));
  return target;
}

static inline double DoubleFromBits(uint32_t high_bits, uint32_t low_bits) {
  return DoubleFromBits((static_cast<uint64_t>(high_bits) << 32) | low_bits);
}



#define UNSERIALIZE_PARAMETER Handle<Value> *rval, const unsigned char **p, const unsigned char *max
#define UNSERIALIZE_PASSTHRU rval, p, max
static inline int process_nested_data(UNSERIALIZE_PARAMETER, long elements, int objprops);
int php_var_unserialize(Handle<Value> *rval/*zval **rval*/, const unsigned char **p, const unsigned char *max);

#endif