/*
 * System call implementations for MSP432.
 *
 * Copyright (c) 2016, Sultan Qasim Khan
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <errno.h>

typedef char * caddr_t;

static caddr_t heap_end = NULL;
extern unsigned long __heap_bottom;
extern unsigned long __heap_top;

// sbrk is used to set aside space for use by malloc
caddr_t _sbrk(int incr)
{
    caddr_t prev_heap_end;

    // If this is the first run, initialize the heap_end pointer to the
    // bottom of the heap
    if (heap_end == NULL)
        heap_end = (caddr_t)&__heap_bottom;

    // The current heap end is what we'll return
    // It is the start of the region allocated for the caller
    prev_heap_end = heap_end;

    // Don't allow allocating more memory than we have room for in our heap
    if (heap_end + incr > (caddr_t)&__heap_top)
    {
        errno = ENOMEM;
        return (void *)-1;
    }

    // Shift up the heap end so that it won't get reallocated
    heap_end += incr;

    // Return the allocated memory on the heap
    return prev_heap_end;
}

int _close(int file)
{
    // Do nothing for now
    return -1;
}

int _fstat(int file)
{
    return -1;
}

int _isatty(int file)
{
    return -1;
}

int _lseek(int file, int ptr, int dir)
{
    return -1;
}

int _open(const char *name, int flags, int mode)
{
    return -1;
}

int _read(int file, char *ptr, int len)
{
    return -1;
}

int _write(int file, char *ptr, unsigned int len)
{
    return -1;
}
