#ifndef __HMAC_H__
#define __HMAC_H__

#include <stdint.h>
#include <string.h>
#include "sha1.h"

#define hmacdigest shadigest

void HMAC_init(const unsigned char *key, const uint8_t len);
void HMAC_block(const unsigned char *data, const uint8_t len);
void HMAC_done(void);
void HMAC_once(const unsigned char *key, const uint8_t klen, const unsigned char *data, int8_t len);

#endif
