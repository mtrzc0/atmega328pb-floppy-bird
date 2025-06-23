#ifndef MACRO_H
#define MACRO_H

#define LOWBYTE(x)   ((unsigned char) (x))
#define HIGHBYTE(x)  ((unsigned char) (((unsigned int) (x)) >> 8))

#define LOW(x) ((unsigned char) (((unsigned int) (x)) & 0x0f))
#define HIGH(x) ((unsigned char) ((((unsigned int) (x)) & 0xf0)>>4))

#endif