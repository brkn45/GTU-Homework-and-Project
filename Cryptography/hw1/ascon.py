
key = "ahmet serif izgoren"
iv = "avcumuzdaki kelebek"

data = """Akıllı iki kız kardeş varmış, bilgiye açlarmış ve okullarındaki, etraflarından aldıkları bilgi yetersiz olmuş.
Yörelerindeki en büyük bilgeye gitmeye, ondan da bilgi almaya karar vermişler.
Bilge adam kızların sorduğu bütün soruları bilmiş. Kızlar daha fazla bilgi almak için bir süreliğine daha bilgenin yanında kalmışlar.
Ama sonra bilgenin her sordukları soruyu bilmelerinden sıkılmışlar. “Bilgenin dahi bilemeyeceği bir soru bulalım” demiş birisi.
Kızlardan biri, bilgenin bile bilemeyeceği bir soru buldum diye sevinmiş. Avucumun içine bir kelebek alacağım “Avucumun içinde bir kelebek var. Canlı mı, ölü mü?” diye bilgeye soracağım, ölü derse kelebeği serbest bırakacağım. Canlı derse, avucumu hafifçe bastıracağım.
Kızlardan biri avucu kapalı bilgeye uzatmış ve sormuş:
– Avucumun içinde bir kelebek var; bilin bakalım canlı mı, ölü mü?
Bilge, kızın gözlerine uzun uzun bakmış ve cevap vermiş:
– Senin elinde kızım senin elinde…"""


encrypted_data = ""
for i in range(len(data)):
    data_ord =ord(data[i])
    key_ord = ord(key[i % len(key)])
    iv_ord = ord(iv[i % len(iv)])
    encrypted_data = encrypted_data + chr(data_ord ^ key_ord ^ iv_ord)

print("\n\n---------Encrypted Text----------")
print(encrypted_data)

decrypted_data = ""
for i in range(len(encrypted_data)):
    data_ord = ord(encrypted_data[i])
    key_ord = ord(key[i % len(key)])
    iv_ord = ord(iv[i % len(iv)])
    decrypted_data += chr( data_ord^ key_ord ^iv_ord )

print("\n\n---------Decrypted text----------")
print(decrypted_data)







