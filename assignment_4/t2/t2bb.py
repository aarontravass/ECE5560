e = int('010001', 16)
N = int(
    'EF38064573FC9B1DF7BD8415B6BFB64402E5DB284FE8CAD9A85F0785BC3E3D07A3CFCFCEE6C8B64C37966982472C36604EF8B5A4AA5178CD2758D0E443126C19',
    16)
d = int(
    'DB94C484EA239C4B14C5FC41663F71D1DA0B1D715270700AFCF745D3676885E0FFEB7067C95BDADE54A62BE6066801093A5E2D3C2B98A95B9D763AF437B09795',
    16)

msg_plain = b'This is a much longer second RSA message. I am having so much fun!'.hex()
msg_int = int(msg_plain, 16)
given_ciphertext = '722732586FFB8B6639AED189A822D92D16630FAC0D54C9F7A7DF9810E2F2200476FAD29DB5DE2AAA2C82F1F706CBD674E09CBAF5E7215CB179933B359FCA8997'
int_ciphertext = pow(msg_int, e, N)
ciphertext = hex(int_ciphertext)
print("Ciphertext is: ", ciphertext[2:])
plain_after = pow(int_ciphertext, d, N)
print("Plain text after decryption ", hex(plain_after))
print(msg_plain)
