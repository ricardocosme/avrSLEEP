#pragma once

#include <stdint.h>

namespace avr { namespace sleep {

constexpr uint32_t operator "" _ms(unsigned long long ms)
{ return ms; }

constexpr uint32_t operator "" _s(unsigned long long s)
{ return s * 1000; }

constexpr uint32_t operator "" _min(unsigned long long min)
{ return min * 1000 * 60; }

constexpr uint32_t operator "" _h(unsigned long long h)
{ return h * 1000 * 60 * 60; }

}}
