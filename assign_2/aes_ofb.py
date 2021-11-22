import math
from Crypto.Random import get_random_bytes
from Crypto.Cipher import AES
from binascii import unhexlify
from base64 import b64encode, b64decode

# key = b'\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef'
block_size = 16
# key = bytes.fromhex('ffeeddccbbaa99887766554433221100')
key = bytes.fromhex('ffeeddccbbaa99887766554433221100ffeeddccbbaa99887766554433221100')


def pad(block):
    length = block_size - (len(block) % block_size)
    return block + bytes([length]) * length


def unpad(data):
    len = data[-1]
    return data[0:int(len)]


def xor(s1, s2):
    return bytes([_a ^ _b for _a, _b in zip(s1, s2)])


def decrypt(enc_string):
    final_dec = b''
    enc = bytes.fromhex(enc_string)
    is_first = True
    aes_round_res = None
    for rnd in range(math.ceil(len(text1) / block_size)):
        block = enc[rnd * block_size: min((rnd + 1) * block_size, len(text1))]
        aescipher = AES.new(key, AES.MODE_ECB)
        if is_first:
            aes_round_res = aescipher.encrypt(iv)
        else:
            aes_round_res = aescipher.encrypt(aes_round_res)
        xor_res = xor(block, aes_round_res)
        # print('Decrypted:	', xor_res)
        final_dec += xor_res
        is_first = False
    print("Decrypted text is", (final_dec))


def encrypt(text1):
    # print('Original:	', text1)
    is_first = True
    aes_round_res = None
    final_enc = ""
    for rnd in range(math.ceil(len(text1) / block_size)):
        block = text1[rnd * block_size: min((rnd + 1) * block_size, len(text1))]
        aescipher = AES.new(key, AES.MODE_ECB)
        if is_first:
            aes_round_res = aescipher.encrypt(iv)
        else:
            aes_round_res = aescipher.encrypt(aes_round_res)
        xor_res = xor(aes_round_res, block)
        # print('Encrypted:	', xor_res.hex())
        final_enc += xor_res.hex()
        is_first = False
    print("Encrypted text is", final_enc)
    return final_enc


iv = get_random_bytes(16)
f = open('AES_OFB_plaintext1.txt')
text1 = bytes(''.join(f.readlines()), 'utf-8')

final_enc = encrypt(text1)
decrypt(final_enc)
