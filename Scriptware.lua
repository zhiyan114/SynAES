--[[
    Scriptware Version
    I do not own scriptware so the implementation here may be incorrect, please make poll request if it is incorrect to help me fix it
--]] 
local SynAES = function(key)
    local crypto = syn.crypt.custom
    local enc = function(data,iv)
        return crypt.custom_encrypt(data,key,iv,"GCM")
    end
    local dec = function(data,iv)
        return crypt.custom_decrypt(data,key,iv,"GCM")
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