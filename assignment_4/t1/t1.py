from Crypto.Util import number
from random import getrandbits

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

p=87712020782810358806012366960530480363676290880575039025592945358193408249897
q=102835471351264451708400576484301274347085188629221996951152314010256656047547
e=65537
private_key=2777113439026967813870345260359839597823226328146295814538363064080293099090869828193345932139225213849393071682039628960771675474665521453093256445593377

phi=(p-1)*(q-1)
d=modinv(e,phi)
print("Calculated private key is: ",d)
print(private_key==d)
