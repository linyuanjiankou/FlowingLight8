#ifndef _FONT_H_
#define _FONT_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

#define Font_Width 8
#define Font_Height 16

typedef struct{
    uint8_t index[4]; //存放UTF-8编码值
    const uint8_t data[16]; //纵向取模后的16字节数据
}tFontUTF8;

extern const tFontUTF8 FontUTF8[];
extern const uint32_t Font_Size;

#ifdef __cplusplus
}
#endif

#endif
