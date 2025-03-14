import hashlib

from isap import permute
BLOCK_SIZE = 16
def permute_cbc(key, nonce, message, iv):

  ciphertext = bytearray()
  blocks = [message[i:i+BLOCK_SIZE] for i in range(0, len(message), BLOCK_SIZE)]
  prev_block = iv
  
  
  for block in blocks:
    
    block = block.ljust(BLOCK_SIZE, b'\x00')
    xored_block = bytes([b1 ^ b2 for b1, b2 in zip(prev_block, block)])
    encrypted_block = permute(key, nonce, xored_block)
    ciphertext += encrypted_block
    prev_block = encrypted_block

  mac = hashlib.sha256(ciphertext).digest()
  return ciphertext + mac



def verify_and_decrypt_cbc(key, nonce, encrypted_message, iv):
  
  ciphertext = encrypted_message[:-32]
  received_mac = encrypted_message[-32:]
  expected_mac = hashlib.sha256(ciphertext).digest()

  if received_mac != expected_mac:
    return None
  
  decrypted_message = bytearray()
  blocks = [ciphertext[i:i+BLOCK_SIZE] for i in range(0, len(ciphertext), BLOCK_SIZE)]
  prev_block = iv
  
  for block in blocks:
    decrypted_block = permute(key, nonce, block)
    xored_block = bytes([b1 ^ b2 for b1, b2 in zip(prev_block, decrypted_block)])
    decrypted_message += xored_block
    prev_block = block
  
 
  return decrypted_message

key = b'\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10'
nonce = b'\x11\x12\x13\x14\x15\x16\x17\x18'
data = b"APT38 is a cyber espionage group that has been active since at least 2014. It is believed to be sponsored by the North Korean government and has targeted various organizations and governments around the world, including financial institutions, defense contractors, and government agencies. APT38 is known for its sophisticated tactics, including the use of custom malware and targeted spearphishing campaigns to gain initial access to victim systems. It is also known for its use of living off the land tactics, in which it uses legitimate tools and software to carry out its operations in an attempt to avoid detection. APT38 has been linked to several high-profile attacks, including the 2014 attack on Sony Pictures and the 2017 WannaCry ransomware attack, which affected hundreds of thousands of computers in over 150 countries."

  

iv = b'\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'
ciphertext = permute_cbc(key, nonce, data, iv)

print("\n\n---------Encrypted Text----------\n", )
print(ciphertext)
plaintext = verify_and_decrypt_cbc(key, nonce, ciphertext,iv)
print("\n\n---------Decrypted text----------\n", )
print(plaintext)