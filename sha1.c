#include "sha1.h"

#define init_h0  0x67452301
#define init_h1  0xEFCDAB89
#define init_h2  0x98BADCFE
#define init_h3  0x10325476
#define init_h4  0xC3D2E1F0

#define rol(value, bits) (((value) << (bits)) | ((value) >> (32 - (bits))))

union _message message;

void SHA1(void)
{
    uint8_t i;
    uint32_t a,b,c,d,e,f,k,t;

    a = shadigest.state.h0;
    b = shadigest.state.h1;
    c = shadigest.state.h2;
    d = shadigest.state.h3;
    e = shadigest.state.h4;

    for (i=0; i<=79; i++) {
        if (i<=19) {
            f = d ^ (b & (c ^ d));
            k = 0x5A827999;
        } else if (i<=39) {
            f = b ^ c ^ d;
            k = 0x6ED9EBA1;
        } else if (i<=59) {
            f = (b & c) | (d & (b | c));
            k = 0x8F1BBCDC;
        } else {
            f = b ^ c ^ d;
            k = 0xCA62C1D6;
        }

        if (i>=16) {
            t = rol(message.w[(i+13)&15] ^ message.w[(i+8)&15] ^ message.w[(i+2)&15] ^ 
                  message.w[i&15], 1);
            message.w[i&15] = t;
        }

        t = rol(a, 5) + f + e + k + message.w[i&15];
        e = d;
        d = c;
        c = rol(b, 30);
        b = a;
        a = t;
    }

    shadigest.state.h0 += a;
    shadigest.state.h1 += b;
    shadigest.state.h2 += c;
    shadigest.state.h3 += d;
    shadigest.state.h4 += e;
}

void SHA1_init(void)
{
    shadigest.state.h0 = init_h0;
    shadigest.state.h1 = init_h1;
    shadigest.state.h2 = init_h2;
    shadigest.state.h3 = init_h3;
    shadigest.state.h4 = init_h4;
    shadigest.state.count = 0;
}

void SHA1_block(const unsigned char* data, uint8_t len)
{
    uint8_t i;

    for (i=len>>2;i<=15;i++) {
        message.w[i] = 0;
    }

    for (i=0;i<len;i+=4) {
        message.data[i] = data[i+3];
        message.data[i+1] = data[i+2];
        message.data[i+2] = data[i+1];
        message.data[i+3] = data[i];
    }

    shadigest.state.count += len;

    if (len<64) {
        message.w[len >> 2] &= 0xffffffffL << (((~len & 3)*8)+8);
        message.w[len >> 2] |= 0x80L << ((~len & 3)*8);
        if (len<=55) {
            message.w[15] = (uint32_t)(shadigest.state.count) * 8;
        }
    }

    SHA1();

    if ((len>=56) && (len<64)) {
        for (i=0; i<=14; i++) {
            message.w[i] = 0;
        }
        message.w[15] = (uint32_t)(shadigest.state.count) * 8;
        SHA1();
    }
}

void SHA1_done(void)
{
    uint8_t i;
    unsigned char j;
    for (i=0;i<=4;i++) {
        j = shadigest.data[4*i];
        shadigest.data[4*i] = shadigest.data[4*i+3];
        shadigest.data[4*i+3] = j;
        j = shadigest.data[4*i+1];
        shadigest.data[4*i+1] = shadigest.data[4*i+2];
        shadigest.data[4*i+2] = j;
    }
}

void SHA1_once(const unsigned char* data, int len)
{
  SHA1_init();
  while (len>=0) {
    SHA1_block(data, (len>64) ? 64 : len);
    len -= 64;
    data += 64;
  }
  SHA1_done();
}
