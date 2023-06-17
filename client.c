#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define SORT_DEV "/dev/sort_test"

int main()
{
    int fd = open(SORT_DEV, O_RDWR);
    int t;
    char buf[1000];
    if (fd < 0) {
        perror("Failed to open character device");
        exit(1);
    }
    FILE *data = fopen("data.txt", "w");
    t = read(fd, buf, 1);
    fprintf(data, "sorting time is %d", t);
    close(fd);
    fclose(data);
    return 0;
}