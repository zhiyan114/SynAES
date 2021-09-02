<?php
class SynAES {
    protected $key;

    public function __construct($key) {
        $this->key = $key;
        switch(strlen($key)) {
            case 16:
                $this->cryptalg = "aes-128-gcm";
                break;
            case 24:
                $this->cryptalg = "aes-192-gcm";
                break;
            case 32:
                $this->cryptalg = "aes-256-gcm";
                break;
            default:
                throw new Exception('SynAES: Invalid key size (16, 24, and 32 are the only valid size)');
        }
    }
    public function encrypt($data,$iv) {
        $CipherData = openssl_encrypt($data,$this->cryptalg,$this->key,OPENSSL_RAW_DATA,$iv,$Tag);
        return base64_encode($CipherData.$Tag);
    }
    public function decrypt($data,$iv) {
        $data = base64_decode($data);
        return openssl_decrypt(substr($data,0,strlen($data)-16), $this->cryptalg, $this->key, OPENSSL_RAW_DATA, $iv, substr($data,-16));
    }
}

# Example Usages
$crypt = new SynAES("0123456789ABCDEF0123456789ABCDEF");
echo $crypt->encrypt("YO SUP","0123456789ABCDEF");
echo "\n";
echo $crypt->decrypt("hraYXZ+qvP5dYceEIoP+ZVbhZqbaUw==","0123456789ABCDEF")
?>
