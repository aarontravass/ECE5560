from Crypto.Util import number
from random import randrange
import math
from binascii import unhexlify


def egcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)
        return (g, x - (b // a) * y, y)


def modinv(a, m):
    g, x, y = egcd(a, m)
    if g != 1:
        raise Exception('modular inverse does not exist')
    else:
        return x % m


message = "Hello world"
int_msg = int(bytes(message.encode('utf8')).hex(), 16)
p = number.getPrime(256)
q = number.getPrime(256)
N = p * q
phi = (p - 1) * (q - 1)
e = randrange(1, phi)
g = math.gcd(e, phi)
while g != 1:
    e = randrange(1, phi)
    g = math.gcd(e, phi)
d = modinv(e, phi)
int_ciphertext = pow(int_msg, e, N)
ciphertext = hex(int_ciphertext)
print("Ciphertext is: ", ciphertext[2:])
plain_after = pow(int_ciphertext, d, N)
print("Plain text after decryption ", unhexlify(hex(plain_after)[2:]).decode('utf8'))
print(unhexlify(hex(plain_after)[2:]).decode('utf8') == message)
