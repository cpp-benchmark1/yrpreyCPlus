#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <cstring>

#define BUFSIZE 16
#define OVERSIZE 8 /* overflow buf2 by OVERSIZE bytes */

int main()
{
    int diff;
    char *buf1 = (char *)malloc(BUFSIZE);
    char *buf2 = (char *)malloc(BUFSIZE);

    diff = (intptr_t)buf2 - (intptr_t)buf1;
    std::cout << "buf1 = " << (void *)buf1 << ", buf2 = " << (void *)buf2
              << ", diff = 0x" << std::hex << diff << " bytes" << std::endl;

    memset(buf2, 'A', BUFSIZE - 1);
    buf2[BUFSIZE - 1] = '\0';

    std::cout << "before overflow: buf2 = " << buf2 << std::endl;
    memset(buf1, 'B', (size_t)(diff + OVERSIZE));
    std::cout << "after overflow: buf2 = " << buf2 << std::endl;

    free(buf1);
    free(buf2);

    return 0;
}
