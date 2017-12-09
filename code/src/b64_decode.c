#include <stddef.h>
#include <string.h>


int b64_get_decode_len(const char *encoded_str, size_t *decode_len) {
  if (!encoded_str) return -1; 
  if (!decode_len) return -2;
   
  size_t decoded_str_len = strlen(encoded_str);

  if (0 == decoded_str_len) {
    *decode_len = 0; 
    return 0;
  }
  // Decoded string length must be a multiple of 4
  if (0 != decoded_str_len % 4) return -3;  
  // Calculate decoded bytes array length, without considering the padding
  *decode_len = ((decoded_str_len >> 2) - 1) * 3;

  // Calculate decoded padding length
  const char *padding_ptr = encoded_str + decoded_str_len;
  size_t padding_len = 0;
  while ('=' == *(--padding_ptr)) padding_len++;
  if (padding_len > 2) return -4;
  *decode_len += 0 == padding_len ? 3 : 3 - padding_len;
  
  return 0;
}

int b64_decode(const char *encoded_str, unsigned char *decoding_buf,
    size_t *decoded_len) {
  return 0;
}
