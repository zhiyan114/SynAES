from Crypto.Cipher import AES
import base64
class SynAES:
    def __init__(self,key):
        self.key = key.encode('utf-8')
    def encrypt(self,data,iv):
        # Encryption Method
        cipher = AES.new(self.key,AES.MODE_GCM,nonce=iv.encode("utf-8"))
        ciphertxt,tag = cipher.encrypt_and_digest(data.encode("utf-8"))
        return base64.b64encode(ciphertxt+tag).decode("utf-8")
    def decrypt(self,data,iv):
        data = base64.b64decode(data)
        cipher = AES.new(self.key,AES.MODE_GCM,nonce=iv.encode("utf-8"))
        plaintxt = cipher.decrypt(data[:len(data)-16])
        cipher.verify(data[-16:])
        return plaintxt.decode("utf-8")
    def handled_decrypt(self,data,iv):
        # Encryption Method
        data = base64.b64decode(data)
        cipher = AES.new(self.key,AES.MODE_GCM,nonce=iv.encode("utf-8"))
        plaintxt = cipher.decrypt(data[:len(data)-16])
        TagValidation = False
        try:
            cipher.verify(data[-16:])
            TagValidation = True
        except ValueError:
            TagValidation = False
        finally:
            return {
                "ValidTag": TagValidation,
                "Data": plaintxt.decode("utf-8")
            }

# Example Usages
crypt = SynAES("0123456789ABCDEF0123456789ABCDEF")
print(crypt.encrypt("YO SUP","0123456789AB"))
print(crypt.decrypt("lyiAqsYTgCuWO0WcO7HKJ8IqZwwZWg==","0123456789AB"))
print(crypt.handled_decrypt("lyiAqsYTgCuWO0WcO7HKJ8IqZwwZWg==","0123456789AB"))
# Difference between the decrypt methods is that regular decrypt will only return data and throws an error when tag is mismatched
# handled_decrypt on the other hand will handle it for you and returns a table containing both the tag's validation status and the data
# handled_decrypt allows you to use the data even if the tag validation fails but it recommended that the data should not be trusted as it likely tampered