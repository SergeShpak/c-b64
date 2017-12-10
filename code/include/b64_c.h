#ifndef B64_C
#define B64_C

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>


int b64_get_encoding_len(const size_t data_len, size_t *encoding_buf_len);

int b64_encode(const unsigned char *data, const size_t data_len,
    char *encoding_buf);

int b64_is_valid(const char *encoded_str);

int b64_get_decode_len(const char *encoded_str, size_t *decode_len);

int b64_decode(const char *encoded_str,
    unsigned char *decoding_buf, size_t *decoded_len);

#ifdef __cplusplus
}
#endif

#endif
