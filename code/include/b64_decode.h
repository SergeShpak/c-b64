#ifndef B64_C_DECODE
#define B64_C_DECODE

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

int b64_get_decode_len(const char *encoded_str, size_t *decode_len);

int b64_decode(const char *encoded_str,
    unsigned char *decoding_buf, size_t *decoded_len);

#ifdef __cplusplus
}
#endif

#endif
