# SHA1vsCRC32
SHA-1 and CRC32 are widely implemented in data deduplication on storage system.  
This program simply evaluates SHA-1 and CRC32 performance with different buffer size.  
Markdown will be added in the future.  

>OS --> macOS  
>SHA-1 --> from openSSL  
>CRC32 --> from zlib  

1. Compile command:  
***
gcc test.c -o test LDFLAGS CPPFLAGS -lcrypto -lz  
***
    - You can check LDFLAGS and CPPFLAGS throught command "brew info openssl"  
    - Using -lz to link zlib.h  

2. Run the program:  
***
./test <InputFile chunksize(KB)  
***
    - Mention that the unit of chunksize is KB  
    - Usually the multiples of 512B, such as 0.5KB (512Byte sector on disk), 4kB (4kB page on flash)  


3. Here's the example:  
***
gcc test.c -o test -L/usr/local/opt/openssl@1.1/lib -I/usr/local/opt/openssl@1.1/include -lcrypto -lz  
./test <linux-5.3.5.tar.xz 0.5
***
