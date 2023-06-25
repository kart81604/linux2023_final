#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>

#define LEN 20000
#define SORT_DEV "/dev/sort_test"

int main()
{
    int fd = open(SORT_DEV, O_RDWR);
    int t;
    char buf[1];
    if (fd < 0) {
        perror("Failed to open character device");
        exit(1);
    }
    FILE *data = fopen("data.txt", "w");
    for(uint64_t i = 0; i < LEN; i++) {
        lseek(fd, i, SEEK_SET);
        t = read(fd, buf, 1);
        fprintf(data, "%ld %d\n", i + 1, t);
    }
    close(fd);
    fclose(data);
    return 0;
}