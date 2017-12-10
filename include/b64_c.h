/**
 *  \file b64_c.h
 *  \brief B64 encoding/decoding.
 *  \author Sergey Shpak
 *  \date 2017
 *  
 *  File contains declarations of functions related to b64 encoding/decoding.
 *
 */


#ifndef B64_C
#define B64_C

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>


/**
 * \brief Calculate encoding length.
 *
 * Calculates length of the buffer, that is needed to contain the result of
 * b64-encoding of \p n bytes.
 *
 * \param[in] n Length of the bytes array, that is to be b64-encoded.
 * \param[out] encoding_buf Output variable for the length of b64-encoding
 * of \p n bytes. If an error occurs, the value is invalid.
 *
 * \return Zero, if the length has been succesfully calculated.
 * A non-zero value otherwise.
 */
int b64_get_encoding_len(const size_t n, size_t *encoding_buf_len);


/**
 * \brief B64-encodes a bytes array.
 *
 * Calculates a b64-encoding of \p data. \p encoding_buf must be initialized
 * and be of a length, that is sufficient to contain the result of \p data
 * encoding (the length can be calculated with the use of
 * \link b64_get_encoding_len() \endlink).
 *
 * \param[in] data Bytes array to be b64-encoded.
 * \param[in] data_len Length of \p data.
 * \param[out] encoding_buf Buffer for the resulting b64-encoding of \p data.
 *
 * \return Zero, if no error during b64-encoding calculation has occurred.
 * A non-zero value otherwise.
 */
int b64_encode(const unsigned char *data, const size_t data_len,
    char *encoding_buf);


/**
 * \brief Check if the passed string is b64-encoded.
 *
 * Checks if the passed string is in a valid b64-encoding format.
 * In particular checks string length, validity of contained characters and
 * padding format.
 *
 * \param[in] encoded_str String to validate.
 *
 * \return A non-zero integer, if \p encoded_str is a valid b64-encoded string.
 * Zero, otherwise.
 */
int b64_is_valid(const char *encoded_str);


/**
 * \brief Calculate decoding length.
 *
 * Calculates length of the buffer, that is needed to contain the result of
 * b64-decoding of \p encoded_str.
 *
 * \param[in] encoded_str B64-encoded string to be decoded.
 * \param[out] decoding_len Output variable for the length of b64-decoding
 * of \p encoded_str. If an error occurs, the value is invalid.
 *
 * \return Zero, if the length has been succesfully calculated.
 * A non-zero value otherwise.
 */
int b64_get_decoding_len(const char *encoded_str, size_t *decoding_len);


/**
 * \brief Decodes a b64-encoded string.
 *
 * Decodes b64-encoded \p encoded_str. \p decoding_buf must be initialized
 * and be of a length, that is sufficient to contain the result of
 * \p encode_str decoding (the length can be calculated with the use of
 * \link b64_get_decoding_len() \endlink). \p encoded_str must be a valid
 * b64-encoded string, otherwise the function behavior is undefined (to
 * verify the validity of \p encoded_str use \link b64_is_valid() \endlink).
 *
 * \param[in] encoded_str B64-encoded string to be decoded.
 * \param[out] decoding_buf Buffer for the resulting decoding of
 * \p encoded_str.
 * \param[out] decoded_len Length of the decoding, stored in \p decoding_buf.
 * If NULL is passed, length of the decoding is not be returned.
 *
 * \return Zero, if no error during decoding has occurred.
 * A non-zero value otherwise.
 */
int b64_decode(const char *encoded_str,
    unsigned char *decoding_buf, size_t *decoded_len);

#ifdef __cplusplus
}
#endif

#endif
