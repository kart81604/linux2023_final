#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define LEN 8000
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
    for(int i = 0; i < LEN; i++) {
        lseek(fd, i, SEEK_SET);
        t = read(fd, buf, 1);
        fprintf(data, "%d %d\n", i + 1, t);
    }
    close(fd);
    fclose(data);
    return 0;
}