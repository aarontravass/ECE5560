#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

// a simple hex-print routine. could be modified to print 16 bytes-per-line
static void hex_print(const void* pv, size_t len)
{
const unsigned char * p = (const unsigned char*)pv;
if (NULL == pv)
    printf("NULL");
else
{
    size_t i = 0;
    for (; i<len;++i)
        printf("%02X ", *p++);
}
printf("\n");
}

// main entrypoint
int main(int argc, char **argv)
{
    int keylength = 32;
    int inputlength = 16;
    static unsigned char aes_key[32] = \
	{0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef, \
	0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef};
    unsigned char data_block[16] = "This is a Test 1"; // Notice that it is less than 16 bytes 


    // buffers for encryption and decryption
    const size_t encslength = inputlength;
    unsigned char enc_out[encslength];
    unsigned char dec_out[inputlength];
    memset(enc_out, 0, sizeof(enc_out));
    memset(dec_out, 0, sizeof(dec_out));
    // We do with this aes-cbc-128 aes-cbc-192 aes-cbc-256
    AES_KEY enc_key, dec_key;
    AES_set_encrypt_key(aes_key, keylength*8, &enc_key);
    
    AES_encrypt((unsigned char *)&data_block, enc_out, &enc_key);

    AES_set_decrypt_key(aes_key, keylength*8, &dec_key);
    AES_decrypt(enc_out, dec_out, &dec_key);

    printf("original:\t");
    hex_print((unsigned char *)&data_block, inputlength);

    printf("encrypt:\t");
    hex_print(enc_out, sizeof(enc_out));

    printf("decrypt:\t");
    hex_print(dec_out, sizeof(dec_out));

    printf("Decrypted Data - [%.16s]\n", &dec_out[0]);
    return 0;
}
