#include <string.h>
#include <v8.h>
#include <node.h>

#ifndef UTIL_H
#define UTIL_H

using namespace v8;

static inline v8::Local<v8::String> v8_str(const char* x) {
    return v8::String::New(x);
}

static inline v8::Local<v8::Script> v8_compile(const char* x) {
    return v8::Script::Compile(v8_str(x));
}

static inline double DoubleFromBits(uint64_t value) {
    double target;
    memcpy(&target, &value, sizeof (target));
    return target;
}

static inline uint64_t DoubleToBits(double value) {
    uint64_t target;
    memcpy(&target, &value, sizeof (target));
    return target;
}

static inline double DoubleFromBits(uint32_t high_bits, uint32_t low_bits) {
    return DoubleFromBits((static_cast<uint64_t> (high_bits) << 32) | low_bits);
}

#define V8_2PART_UINT64_C(a, b) (((static_cast<uint64_t>(a) << 32) + 0x##b##u))

//#define V8_SNAN DoubleFromBits(0x7ff00000, 00000001)
#define V8_SNAN DoubleFromBits(V8_2PART_UINT64_C(0x7ff00000, 00000001))
#define V8_INFINITY V8_2PART_UINT64_C(0x7ff00000, 00000000)
#define V8_NEG_INFINITY V8_2PART_UINT64_C(0xfff00000, 00000000)

static const uint64_t kExponentMask = V8_2PART_UINT64_C(0x7FF00000, 00000000);
static const uint64_t kSignificandMask = V8_2PART_UINT64_C(0x000FFFFF, FFFFFFFF);
#endif
