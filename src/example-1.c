#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>

#define CHUNK_SIZE (200 * 1024)

int main(void)
{
    // Standard data protections (no execute for security)
    int protections = PROT_READ | PROT_WRITE;

    // Flags:
    // - MAP_ANONYMOUS: Not backed by file (RAM only)
    // - MAP_PRIVATE: Copy-on-write (changes not shared to other processes)
    int flags = MAP_ANONYMOUS | MAP_PRIVATE;

    // Allocate chunk
    void *chunk = mmap(NULL, CHUNK_SIZE, protections, flags, -1, 0);
    if (chunk == MAP_FAILED)
    {
        perror("mmap failed");
        fprintf(stderr, "Error code: %d\n", errno);
        return EXIT_FAILURE;
    }

    printf("Chunk allocated at: %p\n", chunk);

    // Deallocate chunk
    if (munmap(chunk, CHUNK_SIZE) == -1)
    {
        perror("munmap failed");
        fprintf(stderr, "Error code: %d\n", errno);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
