import hashlib

BLOCK_SIZE = 16

def permute(key, nonce, message):
 
  keystream = permutation_function(key, nonce)
  ciphertext = bytes([m ^ k for m, k in zip(message, keystream)])
  mac = hashlib.sha256(ciphertext).digest()

  return ciphertext + mac

def permutation_function(key, nonce):

  key_nonce = key + nonce
  keystream = bytearray(BLOCK_SIZE)
  
  for i in range(0, len(keystream), BLOCK_SIZE):
    block = key_nonce[i:i+BLOCK_SIZE]
    keystream[i:i+BLOCK_SIZE] = permute_block(block)
    return bytes(keystream)

def permute_block(block):

  block = bytearray(block)
  block[0] ^= block[-1]
  block[1] ^= block[-2]
  block[2] ^= block[-3]
  block[3] ^= block[-4]
  
  return bytes(block)


def verify_and_decrypt(key, nonce, encrypted_message):
 
  ciphertext = encrypted_message[:-32]
  received_mac = encrypted_message[-32:]
  expected_mac = hashlib.sha256(ciphertext).digest()
  
  if received_mac != expected_mac:
    return None
  
  return permute(key, nonce, encrypted_message)

# Example usage:

key = b'\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10'
nonce = b'\x11\x12\x13\x14\x15\x16\x17\x18'
data = b"APT38 is a cyber espionage group that has been active since at least 2014. It is believed to be sponsored by the North Korean government and has targeted various organizations and governments around the world, including financial institutions, defense contractors, and government agencies. APT38 is known for its sophisticated tactics, including the use of custom malware and targeted spearphishing campaigns to gain initial access to victim systems. It is also known for its use of living off the land tactics, in which it uses legitimate tools and software to carry out its operations in an attempt to avoid detection. APT38 has been linked to several high-profile attacks, including the 2014 attack on Sony Pictures and the 2017 WannaCry ransomware attack, which affected hundreds of thousands of computers in over 150 countries."

ciphertext = permute(key, nonce, data)
print("\n\n---------Encrypted Text----------\n", )
print(ciphertext)
plaintext = verify_and_decrypt(key, nonce, ciphertext)
print("\n\n---------Decrypted text----------\n", )
print(plaintext)