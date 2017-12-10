#include <stddef.h>
#include <string.h>


static unsigned char decode_lookup(const char b64_char);
static char is_in_b64_range(const char c);


int b64_is_valid(const char *encoded_str) {
  if (!encoded_str) return 0;
  size_t encoded_str_len = strlen(encoded_str);
  if (0 == encoded_str_len) return 1;
  if (0 != encoded_str_len % 4) return 0;

  // Pointer to the null terminator of encoded_str
  const char *encoded_str_out_ptr = encoded_str + encoded_str_len;
  const char *encoded_str_offset = encoded_str_out_ptr;
  // Checking padding
  do {
    encoded_str_offset--;
    if (!is_in_b64_range(*encoded_str_offset)
        && (*encoded_str_offset != '=')) return 0; 
  } while (encoded_str_offset != encoded_str_out_ptr - 2);
  // Checking body
  do {
    encoded_str_offset--;
    if (!is_in_b64_range(*encoded_str_offset)) return 0;
  } while (encoded_str_offset != encoded_str);
  return 1;
}


int b64_get_decoding_len(const char *encoded_str, size_t *decoding_len) {
  if (!encoded_str) return -1; 
  if (!decoding_len) return -2;
   
  size_t decoded_str_len = strlen(encoded_str);

  if (0 == decoded_str_len) {
    *decoding_len = 0; 
    return 0;
  }
  // Decoded string length must be a multiple of 4
  if (0 != decoded_str_len % 4) return -3;  
  // Calculate decoded bytes array length, without considering the padding
  *decoding_len = ((decoded_str_len >> 2) - 1) * 3;

  // Calculate decoded padding length
  const char *encoded_str_tail = encoded_str + decoded_str_len;
  size_t padding_len = 0;
  while ('=' == *(--encoded_str_tail)) padding_len++;
  if (padding_len > 2) return -4;
  *decoding_len += 0 == padding_len ? 3 : 3 - padding_len;
  
  return 0;
}


int b64_decode(const char *encoded_str,
    unsigned char *decoding_buf, size_t *decoded_len) {
  if (!encoded_str) return -1; 
  if (!decoding_buf) return -2;
  if (decoded_len) *decoded_len = 0;
  
  size_t encoded_len = strlen(encoded_str);
  if (encoded_len == 0) return 0;

  unsigned char group[3];
  size_t decoded_len_inner = 0;
  const char *encoded_offset = encoded_str;
  while (encoded_offset != encoded_str + encoded_len - 4) {
    group[0] =
      (decode_lookup(encoded_offset[0]) << 2)
      | (decode_lookup(encoded_offset[1]) >> 4);
    group[1] =
      (decode_lookup(encoded_offset[1]) << 4)
      | (decode_lookup(encoded_offset[2]) >> 2);
    group[2] =
      (decode_lookup(encoded_offset[2]) << 6)
      | decode_lookup((encoded_offset[3]));
    
    memcpy(decoding_buf + decoded_len_inner, group, 3);
    decoded_len_inner += 3;
    encoded_offset += 4;
  }
  unsigned char *decoding_tail = decoding_buf + decoded_len_inner;

  // this cycle is here just for breaking execution, without using goto
  do {
  decoding_tail[0] =
      (decode_lookup(encoded_offset[0]) << 2)
      | (decode_lookup(encoded_offset[1]) >> 4);
  if ('=' == encoded_offset[2]) {
    decoded_len_inner += 1;
    break;
  }
  decoding_tail[1] =
      (decode_lookup(encoded_offset[1]) << 4)
      | (decode_lookup(encoded_offset[2]) >> 2);
  if ('=' == encoded_offset[3]) {
    decoded_len_inner += 2;
    break;
  }
  decoding_tail[2] =
    (decode_lookup(encoded_offset[2]) << 6)
    | decode_lookup((encoded_offset[3]));
  decoded_len_inner += 3;
  } while(0);
  if (decoded_len) {
    *decoded_len = decoded_len_inner; 
  } 
  return 0;
}


/******************************************************************************
 * Static functions
 * ***************************************************************************/

unsigned char decode_lookup(const char b64_char) {
  switch (b64_char) {
    case '+':
      return 62;
    case '/':
      return 63;
    default:
      break;
  }
  // if b64_char is a digit
  if (b64_char <= 57) return b64_char + 4;
  // if b64_char is a capital letter
  if (b64_char <= 90) return b64_char - 65;
  // if b64_char is a letter
  return b64_char - 71;
}

char is_in_b64_range(const char c) {
  if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
      || (c >= '1' && c <= '9') || c == '+' || c == '/') return 1;
  return 0;
}

/******************************************************************************
 * End of static functions section
 * ***************************************************************************/


