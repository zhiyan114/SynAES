import javax.crypto.Cipher;
import javax.crypto.SecretKey;
import javax.crypto.spec.GCMParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.security.SecureRandom;
import java.security.spec.AlgorithmParameterSpec;
import java.util.Base64;

public class SynAES {
    SecretKeySpec Key = null;
    public SynAES(String key) {
        this.Key = new SecretKeySpec(key.getBytes(StandardCharsets.UTF_8),"AES");
    }
    public String encrypt(String data, String iv) throws Exception {
        Cipher cipher = Cipher.getInstance("AES/GCM/NoPadding");
        cipher.init(Cipher.ENCRYPT_MODE,this.Key,new GCMParameterSpec(128,iv.getBytes(StandardCharsets.UTF_8)));
        return new String(Base64.getEncoder().encode(cipher.doFinal(data.getBytes(StandardCharsets.UTF_8))));
    }
    public String decrypt(String data, String iv) throws Exception {
       Cipher cipher = Cipher.getInstance("AES/GCM/NoPadding");
       cipher.init(Cipher.DECRYPT_MODE,this.Key,new GCMParameterSpec(128,iv.getBytes(StandardCharsets.UTF_8)));
        return new String(cipher.doFinal(Base64.getDecoder().decode(data)));
    }
}

// Example Usages
public class Main {
    public static void main(String args[]) throws Exception {
      SynAES crypt = new SynAES("0123456789ABCDEF0123456789ABCDEF");
      System.out.println(crypt.encrypt("YO SUP","0123456789AB"));
      System.out.println(crypt.decrypt("lyiAqsYTgCuWO0WcO7HKJ8IqZwwZWg==","0123456789AB"));
    }
}