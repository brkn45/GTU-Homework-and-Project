import hashlib


BLOCK_SIZE = 16
def permute(key, nonce, feedback):


  state = key + nonce
  
 
  for b in feedback:
   
    state = bytes([b1 ^ b2 for b1, b2 in zip(state, feedback)])
    
    
    state = hashlib.sha256(state).digest()
  
  
  return state

def permute_ofb(key, nonce, message, iv):
  
  
 
  ciphertext = bytearray()
  
  
  feedback = iv
  
 
  for i in range(0, len(message), BLOCK_SIZE):
   
    keystream_block = permute(key, nonce, feedback)
    
   
    xored_block = bytes([b1 ^ b2 for b1, b2 in zip(keystream_block, message[i:i+BLOCK_SIZE])])
    
    
    ciphertext += xored_block
    
    
    feedback = keystream_block
  
  
  mac = hashlib.sha256(ciphertext).digest()
  
 
  return ciphertext + mac

def verify_and_decrypt_ofb(key, nonce, encrypted_message, iv):
 
  ciphertext = encrypted_message[:-32]
  received_mac = encrypted_message[-32:]
  
  
  expected_mac = hashlib.sha256(ciphertext).digest()
  
 
  if received_mac != expected_mac:
    return None
  
  
  decrypted_message = bytearray()
  
  
  feedback = iv
  
  
  for i in range(0, len(ciphertext), BLOCK_SIZE):
    
    keystream_block = permute(key, nonce, feedback)
    xored_block = bytes([b1 ^ b2 for b1, b2 in zip(keystream_block, ciphertext[i:i+BLOCK_SIZE])])
    decrypted_message += xored_block
    feedback = keystream_block
  
  return decrypted_message

data = b"APT38 is a cyber espionage group that has been active since at least 2014. It is believed to be sponsored by the North Korean government and has targeted various organizations and governments around the world, including financial institutions, defense contractors, and government agencies. APT38 is known for its sophisticated tactics, including the use of custom malware and targeted spearphishing campaigns to gain initial access to victim systems. It is also known for its use of living off the land tactics, in which it uses legitimate tools and software to carry out its operations in an attempt to avoid detection. APT38 has been linked to several high-profile attacks, including the 2014 attack on Sony Pictures and the 2017 WannaCry ransomware attack, which affected hundreds of thousands of computers in over 150 countries."
key = b'\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10'
iv = b'\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20'
nonce = b'\x11\x12\x13\x14\x15\x16\x17\x18'
ciphertext = permute_ofb(key, nonce, data, iv)

print("\n\n---------Encrypted Text----------\n", )
print(ciphertext)
plaintext = verify_and_decrypt_ofb(key, nonce, ciphertext,iv)
print("\n\n---------Decrypted text----------\n", )
print(plaintext)