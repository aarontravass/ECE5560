
from Crypto.Cipher import AES
from binascii import unhexlify
from base64 import b64encode, b64decode
#key = b'\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef'
block_size = 16
key = bytes.fromhex('ffeeddccbbaa99887766554433221100')
key=bytes.fromhex('ffeeddccbbaa99887766554433221100ffeeddccbbaa99887766554433221100')
def pad(block):
    length = block_size - (len(block) % block_size)
    return block + bytes([length]) * length


def unpad(data):
    len = data[-1]
    return data[0:-int(len)]


def xor(s1, s2):
    return bytes([_a ^ _b for _a, _b in zip(s1, s2)])


iv = bytes.fromhex('0f0e0d0c0b0a09080f0e0d0c0b0a0908')
f=open('AES_CBC_Plaintext1.txt')
text1 = bytes(''.join(f.readlines()),'utf-8')
aescipher = AES.new(key, AES.MODE_CBC,iv)
aes_round_res = aescipher.encrypt(pad(text1))
print(aes_round_res.hex())

"""
26083dc8d3c3f700fade6a41612953b2
987f2c6d5af894ee6d1864edd19446bd
8e114454b188294dd53eaa48dc8ea941
cba01fe64a7ff2e510834a3b24ee9bcb
82628db176fdfc459c2cf89d7d619cd4

"""
"""
d22865eb44d64f44e4cdf330b0761500
bce7ae6489d3f0cf85acee675b38b44b
116b3c0d7e0bb8ebbc5d0cd518173d69
8fc49f940919aa868c13916ae8861f2a
cf29d03fe9876966c02ea4273f7e81fe


"""