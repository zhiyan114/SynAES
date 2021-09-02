const crypto = require("crypto")
class SynAES {
  constructor(key) {
    this.key = Buffer.from(key,'utf-8')
	switch(Buffer.byteLength(key)) {
		case 16:
			this.gcmalg = "aes-128-gcm"
			break;
		case 24:
			this.gcmalg = "aes-192-gcm"
			break;
		case 32:
			this.gcmalg = "aes-256-gcm"
			break;
		default:
			console.error("Invalid Key Length")
			return;
	}
  }
  encrypt = function(data,iv) {
    const cipher = crypto.createCipheriv(this.gcmalg, this.key, iv)
    const encryptedBuffer = Buffer.concat([cipher.update(data), cipher.final()])
    return Buffer.concat([encryptedBuffer,cipher.getAuthTag()]).toString("base64")
  }
  decrypt = function(data,iv) {
    data = Buffer.from(data,'base64');
    const datalen = Buffer.byteLength(data);
    const decipher = crypto.createDecipheriv(this.gcmalg, this.key, iv)
    decipher.setAuthTag(data.slice(datalen-16,datalen))
    return Buffer.concat([decipher.update(data.slice(0,datalen-16)),decipher.final()]).toString()
  }
}

// Example Usages
const crypt = new SynAES("0123456789ABCDEF0123456789ABCDEF")
console.log(crypt.decrypt("lyiAqsYTgCuWO0WcO7HKJ8IqZwwZWg==","0123456789AB"))
console.log(crypt.encrypt("YO SUP","0123456789AB"))