#include <stddef.h>
#include <string.h>


static const char encode_lookup_table[] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
  'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
  'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
  't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
  '8', '9', '+', '/'
};


int b64_get_encoding_len(const size_t data_len, size_t *encoding_buf_len) {
  if (!encoding_buf_len) return -1;

  *encoding_buf_len = data_len / 3;
  *encoding_buf_len += data_len % 3 == 0 ? 0 : 1;
  (*encoding_buf_len) *= 4;
  // a byte for \0 ending
  (*encoding_buf_len)++;
  return 0;
}


int b64_encode(const unsigned char *data, const size_t data_len,
    char *encoding_buf) {
  if (!data) return -1;
  if (!encoding_buf) return -2;

  encoding_buf[data_len] = '\0';
  if (0 == data_len) {
    *encoding_buf = '\0'; 
    return 0;
  }

  char group[4];
  const unsigned char *data_offset = data;
  char *encoding_buf_offset = encoding_buf;
  while (data_offset < (data + data_len - 3)) {
    group[0] = (data_offset[0] >> 2)
      [encode_lookup_table];
    group[1] = (((data_offset[0] << 4) & 0x30) | (data_offset[1] >> 4))
      [encode_lookup_table];
    group[2] = (((data_offset[1] << 2) & 0x3c) | (data_offset[2] >> 6))
      [encode_lookup_table];
    group[3] = (data_offset[2] & 0x3f)
      [encode_lookup_table];
    memcpy(encoding_buf_offset, group, 4);
    encoding_buf_offset += 4;
    data_offset += 3;
  }
  encoding_buf_offset[4] = '\0';
  encoding_buf_offset[0] = (data_offset[0] >> 2)[encode_lookup_table];
  const unsigned char *data_out_ptr = data + data_len;
  if (data_out_ptr == data_offset + 1) {
    encoding_buf_offset[1] =
      ((data_offset[0] << 4) & 0x30)[encode_lookup_table];
    encoding_buf_offset[2] = encoding_buf_offset[3] = '=';
    return 0;
  }
  encoding_buf_offset[1] =
    (((data_offset[0] << 4) & 0x30) | (data_offset[1] >> 4))
    [encode_lookup_table];
  if (data_out_ptr == data_offset + 2) {
    encoding_buf_offset[2] =
      ((data_offset[1] << 2) & 0x3c)[encode_lookup_table];
    encoding_buf_offset[3] = '=';
    return 0;
  }
  encoding_buf_offset[2] =
    (((data_offset[1] << 2) & 0x3c) | (data_offset[2] >> 6))
    [encode_lookup_table];
  encoding_buf_offset[3] = (data_offset[2] & 0x3f)[encode_lookup_table]; 
  return 0; 
}
