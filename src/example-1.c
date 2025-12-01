#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>

#define MAPPING_LENGTH (640 * 1024)

int main(void)
{
    // Standard data protections (no execute for security)
    int protections = PROT_READ | PROT_WRITE;

    // Flags:
    // - MAP_ANONYMOUS: Not backed by file (RAM only)
    // - MAP_PRIVATE: Copy-on-write (changes not shared to other processes)
    int flags = MAP_ANONYMOUS | MAP_PRIVATE;

    // Allocation
    void *chunk = mmap(NULL, MAPPING_LENGTH, protections, flags, -1, 0);
    if (chunk == MAP_FAILED)
    {
        perror("mmap failed");
        fprintf(stderr, "Error code: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    printf("Memory allocated at: %p\n", chunk);

    // Deallocation
    if (munmap(chunk, MAPPING_LENGTH) == -1)
    {
        perror("munmap failed");
        fprintf(stderr, "Error code: %d\n", errno);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
