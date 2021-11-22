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
    return data[0:-int(len)]


def xor(s1, s2):
    return bytes([_a ^ _b for _a, _b in zip(s1, s2)])


def decrypt(enc_string):
    final_dec = b''
    enc = bytes.fromhex(enc_string)
    is_first = True
    prevBlock = None
    for rnd in range(int(len(enc) / block_size)):
        block = enc[rnd * block_size: (rnd + 1) * block_size]
        xor_bytes = block
        aescipher = AES.new(key, AES.MODE_ECB)
        aes_round_res = aescipher.decrypt(xor_bytes)
        xor_res = None
        if is_first:
            xor_res = xor(iv, aes_round_res)
        else:
            xor_res = xor(prevBlock, aes_round_res)
        # print('Decrypted:	', xor_res)
        final_dec += xor_res
        prevBlock = block
        is_first = False
    print("Decrypted text is", unpad(final_dec))


def encrypt(text1):
    text1 = pad(text1)
    # print('Original:	', text1)
    is_first = True
    aes_round_res = ""
    final_enc = ""
    for rnd in range(int(len(text1) / block_size)):
        block = text1[rnd * block_size: (rnd + 1) * block_size]
        xor_res: bytes = None
        if is_first:
            xor_res = xor(iv, block)
        else:
            xor_res = xor(aes_round_res, block)
        aescipher = AES.new(key, AES.MODE_ECB)
        aes_round_res = aescipher.encrypt(xor_res)
        # print('Encrypted:	', aes_round_res.hex())
        final_enc += aes_round_res.hex()
        is_first = False
    print("Encrypted text is", final_enc)
    return final_enc


iv = bytes.fromhex('0f0e0d0c0b0a09080f0e0d0c0b0a0908')
f = open('AES_CBC_Plaintext1.txt')
text1 = bytes(''.join(f.readlines()), 'utf-8')

final_enc = encrypt(text1)
decrypt(final_enc)
