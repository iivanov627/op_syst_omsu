#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Использование: %s <источник> <назначение>\n", argv[0]);
        return 1;
    }

    int from_fd = open(argv[1], O_RDONLY);
    if (from_fd == -1) {
        perror("open source");
        return 1;
    }

    int to_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (to_fd == -1) {
        perror("open destination");
        close(from_fd);
        return 1;
    }

    char buffer[BUF_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(from_fd, buffer, sizeof(buffer))) > 0) {
        ssize_t total_written = 0;

        while (total_written < bytes_read) {
            ssize_t bytes_written = write(to_fd, buffer + total_written,
                                          bytes_read - total_written);
            if (bytes_written == -1) {
                perror("write");
                close(from_fd);
                close(to_fd);
                return 1;
            }
            total_written += bytes_written;
        }
    }

    if (bytes_read == -1) {
        perror("read");
        close(from_fd);
        close(to_fd);
        return 1;
    }

    if (close(from_fd) == -1) {
        perror("close source");
        close(to_fd);
        return 1;
    }

    if (close(to_fd) == -1) {
        perror("close destination");
        return 1;
    }

    return 0;
}
