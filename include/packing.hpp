#ifndef PACKING_H
#define PACKING_H

#include <libdragon.h>

#define U8(x) (uint8_t)((x) & 0xFF) // unsigned 8 bit
#define U16(x) U8(x), U8((x) >> 8) // unsigned 16 bit
#define U32(x) U8(x), U8((x) >> 8), U8((x) >> 16), U8((x) >> 24) // unsigned 32 bit
#define F16(x) U32(((int32_t)((x) * 65536.0f))) // fixed point 16 (i couldnt come up with a better name)

inline uint8_t read_u8(const uint8_t* buf) {
    return buf[0];
}

inline uint16_t read_u16(const uint8_t* buf) {
    return (uint16_t)(buf[0] | (buf[1] << 8));
}

inline uint32_t read_u32(const uint8_t* buf) {
    return (uint32_t)(buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24));
}

inline float read_f16(const uint8_t* buf) {
    return (int32_t)read_u32(buf) / 65536.0f;
}

#endif