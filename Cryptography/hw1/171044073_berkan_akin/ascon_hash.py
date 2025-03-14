def ascon_encrypt(data):
   
    blocks = [data[i:i+16] for i in range(0, len(data), 16)]
    encrypted = blocks[0]
    for block in blocks[1:]:
        encrypted_prev = ascon_encrypt(encrypted)
        xored = bytes([b1 ^ b2 for b1, b2 in zip(encrypted_prev, block)])
        encrypted = ascon_encrypt(xored)

    return encrypted
def ascon(data):

    blocks = [data[i:i+16] for i in range(0, len(data), 16)]
    hash = blocks[0]
    for block in blocks[1:]:
        encrypted_prev_hash = ascon_encrypt(hash)
        xored = bytes([b1 ^ b2 for b1, b2 in zip(encrypted_prev_hash, block)])
        hash = ascon_encrypt(xored)

    return hash

with open('try.txt', 'a') as f:
    data = f.read()

hash_value = ascon(data)

print("-----Hash Value--------")
print(hash_value)   