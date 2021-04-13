#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <zlib.h>
#include <time.h>
#define N 1000000
#define s_to_us 1000000
//chunksize = {512, 1024, 2048, 4096, 8192, 16384}; //0.5kB, 1kB, 2kB, 4kB, 8kB, 16kB (Unit: Byte)
//gcc test.c -o test -L/usr/local/opt/openssl@1.1/lib -I/usr/local/opt/openssl@1.1/include -lcrypto -lz
//./test 0.5 <linux-5.3.5.tar.xz
unsigned char digest[SHA_DIGEST_LENGTH];//SHA_DIGEST_LENGTH = 20 (Unit: Byte)

int main(int argc, char *argv[])
{
    int chunksize = 1024 * atof(argv[1]);
    unsigned char buffer[chunksize];
    int read_bytes = fread(buffer, 1, chunksize, stdin);//input file from command line, read only csize bytes
    printf("read %d bytes data\n", read_bytes);
    clock_t s = clock();
    //printf("start clock = %lu\n", s);
    for(int i = 0; i < N; i++)
        SHA1(buffer, chunksize, digest);//SHA computation of N times
    clock_t e = clock();
    //printf("end clock = %lu\n", e);
    //printf("time(end - start) = %lu\n", (e-s));
    double time = ((double)(e-s)/(double)CLOCKS_PER_SEC)*s_to_us;
    printf("SHA average execution time = %.10f us\n", time/N);

    //print SHA value  
    char mdString[SHA_DIGEST_LENGTH*2+1];
    for(int i = 0; i < SHA_DIGEST_LENGTH; i++)
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);    
    //printf("SHA1 digest: %s\n", mdString);

    uint32_t crc = crc32(0L, Z_NULL, 0);
    s = clock();
    //printf("start clock = %lu\n", s);
    for(int i = 0; i < N; i++)
        crc32(crc, buffer, chunksize);//CRC computation of N times
    e = clock();
    //printf("end clock = %lu\n", e);
    time = ((double)(e-s)/(double)CLOCKS_PER_SEC)*s_to_us;
    printf("CRC average execution time = %.10f us\n", time/N);
    
    return 0;
}