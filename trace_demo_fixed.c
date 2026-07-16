#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>

int main() {
    // 1. getpid() – получение PID процесса
    pid_t pid = getpid();
    printf("Process PID: %d\n", pid);

    // 2. gettimeofday() – получение текущего времени
    struct timeval tv;
    gettimeofday(&tv, NULL);
    printf("Current time: %ld.%06ld seconds\n", tv.tv_sec, tv.tv_usec);

    // 3. open() – открытие файла для записи (O_WRONLY | O_CREAT | O_TRUNC)
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // 4. write() – запись в файл
    const char *msg = "Hello, tracing!\n";
    ssize_t written = write(fd, msg, strlen(msg));
    if (written < 0) {
        perror("write");
        close(fd);
        return 1;
    }

    // 5. close() – закрытие файла
    close(fd);

    // 6. stat() – получение информации о файле
    struct stat st;
    if (stat("output.txt", &st) == 0) {
        printf("File size: %ld bytes\n", st.st_size);
    } else {
        perror("stat");
    }

    // 7. read() – чтение файла
    fd = open("output.txt", O_RDONLY);
    if (fd >= 0) {
        char buf[100];
        ssize_t n = read(fd, buf, sizeof(buf) - 1);
        if (n > 0) {
            buf[n] = '\0';
            printf("Read from file: %s", buf);
        } else if (n < 0) {
            perror("read");
        }
        close(fd);
    } else {
        perror("open (read)");
    }

    // 8. Дополнительный системный вызов: getuid() – получение UID пользователя
    uid_t uid = getuid();
    printf("User UID: %d\n", uid);

    // 9. Дополнительный системный вызов: getgid() – получение GID пользователя
    gid_t gid = getgid();
    printf("User GID: %d\n", gid);

    // 10. Дополнительный системный вызов: access() – проверка доступа к файлу
    if (access("output.txt", R_OK) == 0) {
        printf("File output.txt is readable\n");
    } else {
        printf("File output.txt is NOT readable\n");
    }

    return 0;
}