class SynAES {
    constructor(key) {
        this.gcmalg = {
            name: 'AES-GCM',
        }
        this.encoder = new TextEncoder();
        this.key = this.encoder.encode(key)
    }
    encrypt = async function(data,iv) {
        const enckey = await crypto.subtle.importKey('raw',this.key,this.gcmalg,false,['encrypt'])
        this.gcmalg.iv = this.encoder.encode(iv);
        const ciphertxt = await crypto.subtle.encrypt(this.gcmalg,enckey,this.encoder.encode(data));
        const strciphertxt = Array.from(new Uint8Array(ciphertxt)).map(byte => String.fromCharCode(byte)).join('');
        return btoa(strciphertxt);
    }
    decrypt = async function(data,iv) {
        const deckey = await crypto.subtle.importKey('raw',this.key,this.gcmalg,false,['decrypt'])
        this.gcmalg.iv = this.encoder.encode(iv);
        let arrciphertxt = new Uint8Array(atob(data).match(/[\s\S]/g).map(ch => ch.charCodeAt(0)))
        let plaintxt = await crypto.subtle.decrypt(this.gcmalg, deckey, arrciphertxt);
        return new TextDecoder().decode(plaintxt);
    }
}

// Example Usages
const crypt = new SynAES("0123456789ABCDEF0123456789ABCDEF")
crypt.encrypt("YO SUP","0123456789ABCDEF").then(res=>console.log(res));
crypt.decrypt("hraYXZ+qvP5dYceEIoP+ZVbhZqbaUw==","0123456789ABCDEF").then(res=>console.log(res));