
from Crypto.Cipher import AES
from binascii import unhexlify


iv=unhexlify('09080706050403020100A2B2C2D2E2F2'.lower().strip())
plaintext=unhexlify('255044462d312e350a25d0d4c5d80a34'.lower().strip())
ciphertext=unhexlify('d06bf9d0dab8e8ef880660d2af65aa82'.lower().strip())

def fetchCipherText(key):
    return AES.new(unhexlify(key.lower()), AES.MODE_CBC, iv).encrypt(plaintext)


f = open("keys.txt", "r")
for key in f:
    res=fetchCipherText(key.strip().rstrip('\n'))
    if(ciphertext==res):
        print(key)

f.close()