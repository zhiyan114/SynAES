-- Main Usage
--Decryption:
print(syn.crypt.custom.decrypt("aes-gcm","jbb6QoWiK6tB4ZEWU+nei5mQgmyiMQ==","0123456789ABCDEF0123456789ABCDEF","0123456789ABCDEF"))
--Encryption:
print(syn.crypt.custom.encrypt("aes-gcm","ROBLOX","0123456789ABCDEF0123456789ABCDEF","0123456789ABCDEF"))

-- Constructor format
local SynAES = function(key)
    local crypto = syn.crypt.custom
    local enc = function(data,iv)
        return syn.crypt.custom.encrypt("aes-gcm",data,key,iv)
    end
    local dec = function(data,iv)
        return syn.crypt.custom.decrypt("aes-gcm",data,key,iv)
    end
    return {
        encrypt=enc,
        decrypt=dec
    }
end

-- Example Usages
local crypt = SynAES("0123456789ABCDEF0123456789ABCDEF")
print(crypt.encrypt("ROBLOX","0123456789ABCDEF"))
print(crypt.decrypt("jbb6QoWiK6tB4ZEWU+nei5mQgmyiMQ==","0123456789ABCDEF"))