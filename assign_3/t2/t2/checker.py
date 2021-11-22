from Crypto.Cipher import AES
from binascii import unhexlify

iv = unhexlify('09080706050403020100A2B2C2D2E2F2'.lower())
plaintext = unhexlify('255044462d312e350a25d0d4c5d80a34'.lower())
ciphertext = 'd06bf9d0dab8e8ef880660d2af65aa82'.lower()


def fetchCipherText(key):
    return AES.new(unhexlify(key.lower()), AES.MODE_CBC, iv).encrypt(plaintext).hex()


f = open("keys.txt", "r")
for key in f:
    res = fetchCipherText(key.strip())
    if (ciphertext == res):
        print(key)

f.close()
