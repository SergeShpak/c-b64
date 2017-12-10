#include <stddef.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include "b64_c.h"

int main(int argc, char **argv) {
  const char *string_to_encode = "Ceci n'est pas une pipe";
  size_t string_to_encode_len = strlen(string_to_encode);
  size_t encoding_len;
  int status = b64_get_encoding_len(string_to_encode_len, &encoding_len);
  if (status) {
    return -1; 
  }
  printf("Encoding length: %lu\n", encoding_len);
  char *encoding_buf = (char*) malloc(encoding_len);
  if (!encoding_len) {
    return -2; 
  }
  status = b64_encode((const unsigned char*)string_to_encode,
      string_to_encode_len, encoding_buf);
  if (status) {
    free(encoding_buf);
    return -3; 
  }
  printf("Encoded string: %s\n", encoding_buf);
  int is_valid_b64 = b64_is_valid(encoding_buf);
  if (!is_valid_b64) {
    free(encoding_buf);
    return -4; 
  }
  printf("%s\n", "Encoding is valid");
  size_t decoding_len;
  status = b64_get_decoding_len(encoding_buf, &decoding_len);
  if (status) {
    free(encoding_buf);
    return -5; 
  }
  printf("Decoding length: %lu\n", decoding_len);
  unsigned char *decoding = (unsigned char*) malloc(decoding_len + 1);
  if (!decoding) {
    free(encoding_buf);
    return -6; 
  }
  decoding[decoding_len] = '\0';
  size_t actual_decoding_len;
  status = b64_decode(encoding_buf, decoding, &actual_decoding_len);
  free(encoding_buf);
  if (status) {
    free(decoding);
    return -7;
  }
  if (actual_decoding_len != decoding_len) {
    free(decoding);
    return -8;
  }
  printf("Decoded string: %s\n", (char*) decoding);
  free(decoding);
  return 0;
}
