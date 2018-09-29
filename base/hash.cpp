#include <base/hash.h>

#include <iostream>
#include <string.h>
#include <logs/logs.hpp>
#include <event2/http.h>

namespace base {

std::string md5(const std::string& data) {
    char tmp[3] = {0};
    char result[33] = {0};
    unsigned char md[16] = {0};

    MD5((const unsigned char *)data.c_str(), data.size(), md);

    for (size_t i = 0; i < 16; i++){
        sprintf(tmp, "%2.2x", md[i]);
        strcat(result, tmp);
    }

    return result;
}
std::string sha1(const std::string& data) {
    char tmp[3] = {0};
    char result[41] = {0};
    unsigned char md[20] = {0};

	SHA1((const unsigned char *)data.c_str(), data.size(), md);

    for(size_t i = 0; i < 20; i++) {
        sprintf(tmp, "%02x", md[i]);
        strcat(result, tmp);
    }

    return result;
}
std::string sha224(const std::string& data) {
    char tmp[3] = {0};
    char result[57] = {0};
    unsigned char md[28] = {0};

	SHA224((const unsigned char *)data.c_str(), data.size(), md);

    for(size_t i = 0; i < 28; i++) {
        sprintf(tmp, "%02x", md[i]);
        strcat(result, tmp);
    }

    return result;
}
std::string sha256(const std::string& data) {
    char tmp[3] = {0};
    char result[65] = {0};
    unsigned char md[32] = {0};

	SHA256((const unsigned char *)data.c_str(), data.size(), md);

    for(size_t i = 0; i < 32; i++) {
        sprintf(tmp, "%02x", md[i]);
        strcat(result, tmp);
    }

    return result;
}
std::string sha384(const std::string& data) {
    char tmp[3] = {0};
    char result[97] = {0};
    unsigned char md[48] = {0};

	SHA384((const unsigned char *)data.c_str(), data.size(), md);

    for(size_t i = 0; i < 48; i++) {
        sprintf(tmp, "%02x", md[i]);
        strcat(result, tmp);
    }

    return result; 
}
std::string sha512(const std::string& data) {
    char tmp[3] = {0};
    char result[129] = {0};
    unsigned char md[64] = {0};

	SHA512((const unsigned char *)data.c_str(), data.size(), md);

    for(size_t i = 0; i < 64; i++) {
        sprintf(tmp, "%02x", md[i]);
        strcat(result, tmp);
    }

    return result;
}

std::string encode_aes(const std::string& data, 
                       const char password[AES_BLOCK_SIZE]) {
    size_t size = 0;
    if ((data.size() + 1) % AES_BLOCK_SIZE == 0) {
        size = data.size() + 1;
    } else {
        size = ((data.size()+1)/AES_BLOCK_SIZE+1)*AES_BLOCK_SIZE;
    }

    char key[AES_BLOCK_SIZE] = {0};
    strcpy(key, password);

    AES_KEY aes_key;
    if (AES_set_encrypt_key((const unsigned char*)key, 128, &aes_key) < 0) {
        LOG_ERROR("Unable to set encryption key in AES.");
        return "";
    }

    char iv[AES_BLOCK_SIZE] = {0};
    char* encrypt = new char[size];
    memset(encrypt, 0, size);
    AES_cbc_encrypt((const unsigned char*)data.c_str(), (unsigned char*)encrypt, 
        size, &aes_key, (unsigned char*)iv, AES_ENCRYPT);

    std::string result(encrypt, size);
    delete []encrypt;

    return result;
}
std::string decode_aes(const std::string& data, 
                       const char password[AES_BLOCK_SIZE]) {
    char key[AES_BLOCK_SIZE] = {0};
    strcpy(key, password);

    AES_KEY aes_key;
    if (AES_set_decrypt_key((const unsigned char *)key, 128, &aes_key) < 0) {
        LOG_ERROR("Unable to set encryption key in AES.");
        return "";
    }

    char iv[AES_BLOCK_SIZE] = {0};
    char* decrypt = new char[data.size()];
    memset(decrypt, 0, data.size());
    AES_cbc_encrypt((const unsigned char *)data.c_str(), (unsigned char *)decrypt, 
        data.size(), &aes_key, (unsigned char *)iv, AES_DECRYPT);

    std::string result(decrypt);
    delete []decrypt;

    return result;
}

bool new_rsa(int bits,
             std::string& public_key, 
             std::string& private_key) {
    RSA* rsa = RSA_new();
    BIGNUM* e = BN_new();
    BIO* private_pb = NULL;
    BIO* public_pb = NULL;
    char* privatekey = NULL;
    char* publickey = NULL;
    bool is_success = false;

    BN_set_word(e, RSA_F4);
    if (RSA_generate_key_ex(rsa, bits, e, NULL) != 1) {
        LOG_ERROR("new_rsa RSA_generate_key_ex fail");
        goto exit;
    }

    if ((private_pb = BIO_new(BIO_s_mem())) == NULL 
        || (public_pb = BIO_new(BIO_s_mem())) == NULL) {
        LOG_ERROR("new_rsa BIO_new fail");
        goto exit;
    }

    if (PEM_write_bio_RSAPrivateKey(private_pb, rsa, NULL, NULL, 0, NULL, NULL) != 1
        || PEM_write_bio_RSAPublicKey(public_pb, rsa) != 1) {
        LOG_ERROR("new_rsa PEM_write_bio fail");
        goto exit;
    }

    privatekey = new char[bits];
    publickey = new char[bits];
    if (BIO_read(private_pb, (void*)privatekey, bits) <=0
        || BIO_read(public_pb, (void*)publickey, bits) <=0) {
        LOG_ERROR("new_rsa BIO_read fail");
        goto exit;
    }

    private_key = std::string(privatekey, bits);
    public_key = std::string(publickey, bits);

    is_success = true;

exit:
    if (publickey != NULL) {
        delete []publickey;
    }
    if (privatekey != NULL) {
        delete []privatekey;
    }
    if (public_pb != NULL) {
        BIO_free_all(public_pb);
    }
    if (private_pb != NULL) {
        BIO_free_all(private_pb);
    }
    if (e != NULL) {
        BN_free(e);
    }
    if (rsa != NULL) {
        RSA_free(rsa);
    }

    return is_success;
}
bool encode_rsa(const std::string& data,
                const std::string& public_key,
                std::string& result) {
    RSA* rsa = NULL;
    BIO* pb = NULL;
    char* encrypt = NULL;
    bool is_success = false;

    if ((pb = BIO_new_mem_buf((void *)public_key.c_str(), -1)) == NULL) {
		LOG_ERROR("encode_rsa BIO_new_mem_buf fail");
		goto exit;
	}

    if ((rsa = PEM_read_bio_RSAPublicKey(pb, NULL, NULL, NULL)) == NULL) {
		LOG_ERROR("encode_rsa PEM_read_bio_RSAPublicKey fail");
		goto exit;
	}	
    
    {
        int size = RSA_size(rsa);
        encrypt = new char[size];
        memset(encrypt, 0, size);
        if (RSA_public_encrypt(size-11, (const unsigned char*)data.c_str(), 
            (unsigned char*)encrypt, rsa, RSA_PKCS1_PADDING) < 0) {
            LOG_ERROR("encode_rsa RSA_public_encrypt fail");
            goto exit;
        }

        result = std::string(encrypt, size);
        is_success = true;
    }

exit:
    if (encrypt != NULL) {
        delete []encrypt;
    }
    if (pb != NULL) {
        BIO_free_all(pb);
    }
    if (rsa != NULL) {
        RSA_free(rsa);
    }

    return is_success;
}
bool decode_rsa(const std::string& data, 
                const std::string& private_key,
                std::string& result) {
    RSA* rsa = NULL;
    BIO* pb = NULL;
    char* decrypt = NULL;
    bool is_success = false;

    if ((pb = BIO_new_mem_buf((void *)private_key.c_str(), -1)) == NULL) {
		LOG_ERROR("encode_rsa BIO_new_mem_buf fail");
		goto exit;
	}

    if ((rsa = PEM_read_bio_RSAPrivateKey(pb, NULL, NULL, NULL)) == NULL) {
		LOG_ERROR("encode_rsa PEM_read_bio_RSAPrivateKey fail");
		goto exit;
	}	
    
    {
        int size = RSA_size(rsa);
        decrypt = new char[size];
        memset(decrypt, 0, size);
        if (RSA_private_decrypt(size, (const unsigned char*)data.c_str(), 
            (unsigned char*)decrypt, rsa, RSA_PKCS1_PADDING) < 0) {
            LOG_ERROR("encode_rsa RSA_private_decrypt fail");
            goto exit;
        }

        result = decrypt;
        is_success = true;
    }

exit:
    if (decrypt != NULL) {
        delete []decrypt;
    }
    if (pb != NULL) {
        BIO_free_all(pb);
    }
    if (rsa != NULL) {
        RSA_free(rsa);
    }

    return is_success;
}

std::string url_encode(const std::string& data) {
    std::string result;
    if (!data.empty()) {
        char *encoded = evhttp_uriencode(data.c_str(), data.size(), false);
        if (encoded) {
            result = std::string(encoded);
            free(encoded);
        }
    }
    return result;
}
std::string url_decode(const std::string& data) {
    std::string result;
    if (!data.empty()) {
        char *decoded = evhttp_uridecode(data.c_str(), false, NULL);
        if (decoded) {
            result = std::string(decoded);
            free(decoded);
        }
    }
    return result;
}

}