import Task5header

N_hex = 'BDDD9F7CF8B69B24810B0A0F02CE69549F5E94BAD865100F60698C13A5E190F24D8900B8E9126461110D51FA7D5C7B1E0F2DA28568D36D96BE65D9062DD2EE89'
e_hex = '010001'
d_hex = '6D7690B4E44FA332709384C112C51E45037CEC12AD1FD71A866353B72033E3F44FE76BCC343CB4319CCD5049AE3B52CB65102249BAF44AB834311CC908E17461'

customtext = "This is a custom message for Task 5."
signedtext = 'bcca2cb71945e5e273ca84086f79116d73f3b72d0f5571092d2a74a153e541bede6888bd0f2b504ab7ceb12acb6bb605f58a01912661b9ed8eeaab7aa2d5e6fd'

N_int = Task5header.intfunc(N_hex)
e_int = Task5header.intfunc(e_hex)
d_int = Task5header.intfunc(d_hex)

#Part 1
print("\n Part 1\n")
int_sample = Task5header.strintfunc(customtext)
G = [int_sample, d_int, N_int, 1]
signed = Task5header.signing_algorithm(G)
print("\nThe resulting message after directly signing it: ", signed)
#Verification...
F = int_sample, e_int, d_int, N_int
verified = Task5header.verifying_algorithm(F)
print("\nThe resulting message after verifying it: ", verified)
print("\nIs the retrieved signed message same as the chosen signed message? ",verified == customtext)

#Part 2

print ("\n Part 2 \n")

f = open('my1kbfile.txt', 'r')
my1kbdata = f.readlines()
my1kbdata = ''.join(my1kbdata)
int_data = Task5header.strintfunc(my1kbdata)
H = [int_data, d_int, N_int, 1]
signed = Task5header.signing_algorithm(H)
f.close()

f = open('my100kbfile.txt', 'r')
my100kbdata = f.readlines()
my100kbdata = ''.join(my100kbdata)
int_data = Task5header.strintfunc(my100kbdata)
I = [int_data, d_int, N_int, 100]
signed = Task5header.signing_algorithm(I)
f.close()

f = open('my1mbfile.txt', 'r')
my1mbdata = f.readlines()
my1mbdata = ''.join(my1mbdata)
int_data = Task5header.strintfunc(my1mbdata)
J = [int_data, d_int, N_int, 1024]
signed = Task5header.signing_algorithm(J)
f.close()

f = open('my10mbfile.txt', 'r')
my10mbdata = f.readlines()
my10mbdata = ''.join(my10mbdata)
int_data = Task5header.strintfunc(my10mbdata)
K = [int_data, d_int, N_int, 10240]
signed = Task5header.signing_algorithm(K)
f.close()


# Changing the size of the key
Range = range(4)
print("\n                  Changing the size of the key\n")
for elem in Range:

	new_val = Task5header.sizefunc(elem)
	P = Task5header.randprime(new_val)
	Q = Task5header.randprime(new_val)
	N = P*Q

	plntxt = Task5header.strintfunc(customtext)
	L = [plntxt, d_int, N_int, 5]
	sgn = Task5header.signing_algorithm(L)
	print("\nThe resulting message after directly signing it: ", sgn)

	M = [plntxt, e_int, d_int, N_int]
	vrf = Task5header.verifying_algorithm(M)
	print("\nThe resulting message after verifying it: ", vrf)
	print("\nIs the retrieved signed message same as the chosen signed message? ",vrf == customtext)






