#ifndef __SHA1_H__
#define __SHA1_H__

#include <stdint.h>
#include <string.h>

union _message {
  unsigned char data[64];
  uint32_t w[16];
};

struct shastate {
  uint32_t h0,h1,h2,h3,h4;
  uint16_t count;
};

union _digest {
  unsigned char data[20];
  struct shastate state;
};

union _digest shadigest;

extern void SHA1_init(void);
extern void SHA1_block(const unsigned char* data, uint8_t len);
extern void SHA1_done(void);
extern void SHA1_once(const unsigned char* data, int len);

#endif
