import sys
from Crypto.Util import number
from random import randrange
import time
import math
sys.setrecursionlimit(1500000)

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



start_bits=256

for i in range(6):
    start = time.process_time()
    key_lenth=start_bits*pow(2,i)
    p=number.getPrime(int(key_lenth/2))
    q=number.getPrime(int(key_lenth/2))
    phi=(p-1)*(q-1)
    e = randrange(1, phi)
    g = math.gcd(e, phi)
    while g != 1:
        e = randrange(1, phi)
        g = math.gcd(e, phi)
    private_key=modinv(e,phi)
    end = time.process_time()
    print("Time taken for",key_lenth,"is: ",end-start,"ns")

