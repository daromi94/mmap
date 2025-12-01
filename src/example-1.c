#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#define CHUNK_SIZE ((size_t)(200 * 1024))

int main(void)
{
    // Standard data protections (no execute for security)
    const int protections = PROT_READ | PROT_WRITE;

    // Flags:
    // - MAP_ANONYMOUS: Not backed by file (RAM only)
    // - MAP_PRIVATE: Copy-on-write (changes not shared to other processes)
    const int flags = MAP_ANONYMOUS | MAP_PRIVATE;

    const int fd = -1;
    const off_t offset = 0;

    // Allocate chunk
    void *chunk = mmap(NULL, CHUNK_SIZE, protections, flags, fd, offset);
    if (chunk == MAP_FAILED)
    {
        int saved_errno = errno;
        fprintf(stderr, "mmap chunk failed: %s (errno=%d)\n", strerror(saved_errno), saved_errno);
        return EXIT_FAILURE;
    }

    printf("Chunk allocated at: %p (%zu bytes)\n", chunk, CHUNK_SIZE);

    // Free chunk
    if (munmap(chunk, CHUNK_SIZE) == -1)
    {
        int saved_errno = errno;
        fprintf(stderr, "munmap chunk failed: %s (errno=%d)\n", strerror(saved_errno), saved_errno);
        return EXIT_FAILURE;
    }

    chunk = NULL;

    return EXIT_SUCCESS;
}
