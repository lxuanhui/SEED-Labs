#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>

int main(){
	char plaintext[] = "This is a top secret.";
	char ciphertext[] = "442187958311d908b7a8d3824af8cd651bc47a03bdca345b96fbe7f67e9b84ee";
	char IV[] = "010203040506070809000a0b0c0d0e0f";
	int i;
	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init(&ctx);
	FILE *keys;
	unsigned char outbuffer[1024 + EVP_MAX_BLOCK_LENGTH];
	int outlen, tmplen;
	
	keys = fopen("words.txt", "r");
	while( fgets(words,16,keys))
	{
		i = strlen(words);
		words[i-1] = '\0';
		if (i<16){
			pad(words);
		}
		EVP_EncryptInit_ex(&ctx, EVP_aes_128_cbc(), NULL, words, IV);
		if(!EVP_EncryptUpdate(&ctx, outbuffer, &outlen, plaintext, strlen(plaintext))){
			EVP_CIPHER_CTX_cleanup(&ctx);
			return 0;
		}
		if(!EVP_EncryptFinal_ex(&ctx, outbuffer + outlen, plaintext, &tmplen)){
			EVP_CIPHER_CTX_cleanup(&ctx);
			return 0;
		}
		outlen += tmplen;
		int i;
		char* buffer_str = (char*) malloc(2*outlen + 1);
		char* buffer_ptr = buffer_str;
		for (i=0;i<outlen;i++){
			buffer_ptr += sprintf(buffer_ptr, "%02X", outbuffer[i]);
		}
		*(buffer_ptr + 1) = "\0";
		if(strcicmp(ciphertext, buffer_str) == 0){
			printf(buffer_str);
		}
		fclose(keys);
		return 1;
		
		
}
}

// have to add padding to the key as it is AES-128

void pad(char *s)
{
	int length;
	length = strlen(s);
	
	while(length<16){
		s[length] = ' ';
		length++;
	}
	s[length] = '\0'; //null terminator
}


int strcicmp(char const *a, char const *b)
{
    for (;; a++, b++) {
        int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
        if (d != 0 || !*a)
            return d;
    }
}


