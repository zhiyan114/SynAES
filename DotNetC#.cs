using System;
using System.Security.Cryptography;
using System.Text;

class SynAES {
	private AesGcm AesEngine = null;
	public SynAES(string key)
	{
		this.AesEngine = new AesGcm(Encoding.UTF8.GetBytes(key));
	}
	public string encrypt(string data, string iv) {
		byte[] Plaintxt = Encoding.UTF8.GetBytes(data);
		byte[] Ciphertxt = new Byte[Plaintxt.Length];
		byte[] Tag = new Byte[16];
		AesEngine.Encrypt(Encoding.UTF8.GetBytes(iv),Plaintxt,Ciphertxt,Tag);
		byte[] FinalData = new byte[Ciphertxt.Length+Tag.Length];
		Buffer.BlockCopy(Ciphertxt,0,FinalData,0,Ciphertxt.Length);
		Buffer.BlockCopy(Tag,0,FinalData,Ciphertxt.Length,Tag.Length);
		return Convert.ToBase64String(FinalData);
	}
	public string decrypt(string data, string iv) {
		byte[] arrdata = Convert.FromBase64String(data);
		byte[] Ciphertxt = new byte[arrdata.Length-16];
		Buffer.BlockCopy(arrdata,0,Ciphertxt,0,arrdata.Length-16);
		byte[] Tag = new byte[16];
		Buffer.BlockCopy(arrdata, arrdata.Length-16,Tag,0,16);
		byte[] Plaintxt = new byte[arrdata.Length-16];
		AesEngine.Decrypt(Encoding.UTF8.GetBytes(iv),Ciphertxt,Tag,Plaintxt);
		return Encoding.UTF8.GetString(Plaintxt);
	}
}

public class Program
{
	public static void Main()
	{
		// Example Usages
		SynAES crypt = new SynAES("0123456789ABCDEF0123456789ABCDEF");
		Console.WriteLine(crypt.encrypt("YO SUP","0123456789AB"));
		Console.WriteLine(crypt.decrypt("lyiAqsYTgCuWO0WcO7HKJ8IqZwwZWg==","0123456789AB"));
	}
}