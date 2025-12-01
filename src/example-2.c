#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMALL_ALLOC_SIZE ((size_t)1024)
#define LARGE_ALLOC_SIZE ((size_t)(200 * 1024))

int main(void)
{
    int saved_errno;

    // Small allocation (likely brk)
    void *p1 = malloc(SMALL_ALLOC_SIZE);
    if (!p1)
    {
        saved_errno = errno;
        fprintf(stderr, "malloc p1 failed: %s (errno=%d)\n", strerror(saved_errno), saved_errno);
        goto error_exit;
    }
    printf("p1 allocated at: %p (%zu bytes)\n", p1, SMALL_ALLOC_SIZE);

    // Large allocation (likely mmap)
    void *p2 = malloc(LARGE_ALLOC_SIZE);
    if (!p2)
    {
        saved_errno = errno;
        fprintf(stderr, "malloc p2 failed: %s (errno=%d)\n", strerror(saved_errno), saved_errno);
        goto cleanup_p1;
    }
    printf("p2 allocated at: %p (%zu bytes)\n", p2, LARGE_ALLOC_SIZE);

    free(p2);
    p2 = NULL;

    free(p1);
    p1 = NULL;

    return EXIT_SUCCESS;

cleanup_p1:
    free(p1);
    p1 = NULL;

error_exit:
    return EXIT_FAILURE;
}
