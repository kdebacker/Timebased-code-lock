#include "hmac.h"

#define SHA1_DIGESTSIZE  20
#define SHA1_BLOCKSIZE   64

unsigned char hmackey[SHA1_BLOCKSIZE];

void HMAC_init(const unsigned char *key, const uint8_t len)
{
    uint8_t i;

    for (i = 0; i < len; i++) {
        hmackey[i] = key[i] ^ 0x36;
    }
    for (i = len; i < SHA1_BLOCKSIZE; i++) {
        hmackey[i] = 0x36;
    }

    SHA1_init();
    SHA1_block(hmackey, SHA1_BLOCKSIZE);
}

void HMAC_block(const unsigned char *data, const uint8_t len)
{
    SHA1_block(data, len);
}

void HMAC_done(void)
{
    uint8_t i;
    unsigned char temp[SHA1_DIGESTSIZE];

    SHA1_done();
    memcpy(temp, &shadigest, SHA1_DIGESTSIZE);

    for (i = 0; i < SHA1_BLOCKSIZE; i++) {
        hmackey[i] ^= 0x6a;
    }

    SHA1_init();
    SHA1_block(hmackey, SHA1_BLOCKSIZE);
    SHA1_block(temp, SHA1_DIGESTSIZE);
    SHA1_done();
}

void HMAC_once(const unsigned char *key, const uint8_t klen, const unsigned char *data, int8_t len)
{
    HMAC_init(key, klen);
    while (len>=0) {
        HMAC_block(data, len > SHA1_BLOCKSIZE ? SHA1_BLOCKSIZE : len);
        len -= SHA1_BLOCKSIZE;
        data += SHA1_BLOCKSIZE;
    }
    HMAC_done();
}
