#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>

int main() {
    // 1. getpid() – получение PID процесса
    pid_t pid = getpid();
    printf("Process PID: %d\n", pid);

    // 2. gettimeofday() – получение текущего времени
    struct timeval tv;
    gettimeofday(&tv, NULL);
    printf("Current time: %ld.%06ld seconds\n", tv.tv_sec, tv.tv_usec);

    // 3. open() – открытие файла для записи
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // 4. write() – запись в файл
    const char *msg = "Hello, tracing!\n";
    write(fd, msg, strlen(msg));

    // 5. close() – закрытие файла
    close(fd);

    // 6. stat() – получение информации о файле
    struct stat st;
    if (stat("output.txt", &st) == 0) {
        printf("File size: %ld bytes\n", st.st_size);
    }

    // 7. read() – чтение файла (дополнительный системный вызов)
    fd = open("output.txt", O_RDONLY);
    if (fd >= 0) {
        char buf[100];
        ssize_t n = read(fd, buf, sizeof(buf) - 1);
        if (n > 0) {
            buf[n] = '\0';
            printf("Read from file: %s", buf);
        }
        close(fd);
    }

    return 0;
}