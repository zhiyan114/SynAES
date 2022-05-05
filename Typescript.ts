import { assert } from 'console';
import { CipherGCMTypes, createCipheriv, createDecipheriv } from 'crypto';
export default class SynAES {
    private key: Buffer;
    private gcmalg: CipherGCMTypes;
    constructor(key: string) {
        this.key = Buffer.from(key, 'utf-8')
        switch (Buffer.byteLength(key)) {
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
                throw new Error("Invalid Key Length: 16, 24, 32")
        }
    }
    encrypt(data : string, iv : string) : string  {
        assert(iv.length == 12, "IV must be 12 bytes")
        const cipher = createCipheriv(this.gcmalg, this.key, iv);
        const encryptedBuffer = Buffer.concat([cipher.update(data), cipher.final()])
        return Buffer.concat([encryptedBuffer, cipher.getAuthTag()]).toString("base64")
    }
    decrypt(data : string, iv : string) : string {
        let byteData = Buffer.from(data, 'base64');
        const datalen = Buffer.byteLength(byteData);
        const decipher = createDecipheriv(this.gcmalg, this.key, iv)
        decipher.setAuthTag(byteData.slice(datalen - 16, datalen))
        return Buffer.concat([decipher.update(byteData.slice(0, datalen - 16)), decipher.final()]).toString()
    }
}

/*
// Example Usages
import {SynAES} from "./Typescript"
const crypt = new SynAES("0123456789ABCDEF0123456789ABCDEF")
console.log(crypt.decrypt("lyiAqsYTgCuWO0WcO7HKJ8IqZwwZWg==","0123456789AB"))
console.log(crypt.encrypt("YO SUP","0123456789AB"))
*/
