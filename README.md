# SHA1 vs. CRC32

SHA-1 and CRC32 are widely implemented in __data deduplication__ on storage system.  
This program simply evaluates SHA-1 and CRC32 performance with different chunk size.

Environment: macOS on intel mac  
Library: `openSSL`(SHA-1), `zlib`(CRC32)

dowload zlib
```
sudo apt-get install libz-dev
```

download openSSL
```
sudo apt-get install libssl-dev
```

## Compile command:  
```
gcc test.c -o test LDFLAGS CPPFLAGS -lcrypto -lz  
```
* Check LDFLAGS and CPPFLAGS by command "brew info openssl"  
* -lz to link zlib.h  

* linux
  * LDFLAGS default might be -L/usr/local/opt/openssl@1.1/lib 
  * CPPFLAGS default might be -I/usr/local/opt/openssl@1.1/include

* M1 macbook
  * LDFLAGS="-L/opt/homebrew/opt/openssl@1.1/lib"
  * CPPFLAGS="-I/opt/homebrew/opt/openssl@1.1/include"

## Run the program:  
```
./test <InputFile chunksize(KB)  
``` 
* The unit of chunksize is KB and its the multiples of 512B, such as 0.5KB or 8KB

## Here's the example:  
```
gcc test.c -o test -L/usr/local/opt/openssl@1.1/lib -I/usr/local/opt/openssl@1.1/include -lcrypto -lz
```
```
./test <linux-5.3.5.tar.xz 0.5
```
