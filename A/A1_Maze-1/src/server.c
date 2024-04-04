#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void serve_file(int client_fd, const char *filename) {
  int fd = open(filename, O_RDONLY);
  if (fd < 0) {
    perror("Error opening file");
    return;
  }

  char buffer[BUFFER_SIZE];
  ssize_t bytes_read;

  while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
    if (write(client_fd, buffer, bytes_read) != bytes_read) {
      perror("Error writing to client");
      break;
    }
  }

  if (bytes_read < 0) {
    perror("Error reading file");
  }

  close(fd);
}

int start_server(const char *port) {
  printf("Starting server on port %s\n", port);
  return 0;
}

// int main(int argc, char *argv[]) {
//     if (argc != 3) {
//         fprintf(stderr, "Usage: %s <port> <file_to_serve>\n", argv[0]);
//         return 1;
//     }

//     const char *port = argv[1];
//     const char *file_to_serve = argv[2];

//     int server_fd = start_server(port);
//     if (server_fd < 0) {
//         fprintf(stderr, "Failed to start server on port %s\n", port);
//         return 1;
//     }

//     printf("Serving %s on port %s\n", file_to_serve, port);
//     serve_file(server_fd, file_to_serve);

//     close(server_fd);
//     return 0;
// }
