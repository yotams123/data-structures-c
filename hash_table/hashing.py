import hashlib

msg = "Yotam Soudry".encode()

print("TEXT:\t", msg.decode())
print("MD5:\t", hashlib.md5(msg).hexdigest())
print("SHA256:\t", hashlib.sha256(msg).hexdigest())
print("SHA512:\t", hashlib.sha512(msg).hexdigest())
print("SHA3256:", hashlib.sha3_256(msg).hexdigest())
print("SHA3512:", hashlib.sha3_512(msg).hexdigest())
print("BLAKE2c:", hashlib.blake2s(msg).hexdigest())
print("BLAKE2b:", hashlib.blake2b(msg).hexdigest())