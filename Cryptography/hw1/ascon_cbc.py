
print("------------Encryption in CBC Mode-----------")

data = b"APT38 is a cyber espionage group that has been active since at least 2014. It is believed to be sponsored by the North Korean government and has targeted various organizations and governments around the world, including financial institutions, defense contractors, and government agencies. APT38 is known for its sophisticated tactics, including the use of custom malware and targeted spearphishing campaigns to gain initial access to victim systems. It is also known for its use of living off the land tactics, in which it uses legitimate tools and software to carry out its operations in an attempt to avoid detection. APT38 has been linked to several high-profile attacks, including the 2014 attack on Sony Pictures and the 2017 WannaCry ransomware attack, which affected hundreds of thousands of computers in over 150 countries."
key = b"\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f"
iv = b"\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f"
def ascon(key, block, decrypt=False):
    xored = bytes([b1 ^ b2 for b1, b2 in zip(key, block)])
    if decrypt:
        
        return xored
    else:
        
        return xored

data_blocks = [data[i:i+16] for i in range(0, len(data), 16)]
ciphertext_blocks = []
prev_block = iv
for block in data_blocks:
    xored = bytes([b1 ^ b2 for b1, b2 in zip(prev_block, block)])

   
    ciphertext_block = ascon(key, xored)
    ciphertext_blocks.append(ciphertext_block)
    prev_block = ciphertext_block

ciphertext = b''.join(ciphertext_blocks)

plaintext_blocks = []
prev_block = iv
for block in ciphertext_blocks:
    plaintext_block = ascon(key, block, decrypt=True)
    xored = bytes([b1 ^ b2 for b1, b2 in zip(prev_block, plaintext_block)])
    plaintext_blocks.append(xored)
    prev_block = block


plaintext = b''.join(plaintext_blocks)


print("Veri:", data)
print("\n\n---------Encrypted Text----------\n", ciphertext)
print("\n\n---------Decrypted text----------\n", plaintext)
