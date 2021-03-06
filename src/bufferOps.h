/*
* DBMS Implementation
* Copyright (C) 2013 George Piskas, George Economides
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*
* Contact: geopiskas@gmail.com
*/

#ifndef BUFFEROPS_H
#define	BUFFEROPS_H

#include <fcntl.h> 
#include <unistd.h>
#include <sys/types.h>

#include "dbtproj.h"

// empties a block

inline void emptyBlock(block_t *buffer) {
    for (int i = 0; i < MAX_RECORDS_PER_BLOCK; i++) {
        (*buffer).entries[i].valid = false;
    }
    (*buffer).nreserved = 0;
}

// empties the whole buffer

inline void emptyBuffer(block_t *buffer, uint size) {
    for (uint i = 0; i < size; i++) {
        emptyBlock(buffer + i);
        buffer[i].valid = true;
    }
}

// opens filename for writing (append mode), and writes size blocks
// starting from pointer buffer

inline uint writeBlocks(char* filename, block_t *buffer, uint size) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
    write(fd, buffer, size * sizeof (block_t));
    close(fd);
    return size;
}

// writes size blocks starting from pointer buffer to the file described
// by fd file descriptor

inline uint writeBlocks(int fd, block_t *buffer, uint size) {
    write(fd, buffer, size * sizeof (block_t));
    return size;
}

// reads size blocks to buffer

inline uint readBlocks(char* filename, block_t *buffer, uint size) {
    int fd = open(filename, O_RDONLY, S_IRWXU);
    read(fd, buffer, size * sizeof (block_t));
    close(fd);
    return size;
}

// reads size blocks to buffer

inline uint readBlocks(int fd, block_t *buffer, uint size) {
    read(fd, buffer, size * sizeof (block_t));
    return size;
}

// reads size blocks to buffer from a specific point (offset) of the file

inline uint preadBlocks(int fd, block_t *buffer, uint offset, uint size) {
    pread(fd, buffer, size * sizeof (block_t), offset * sizeof (block_t));
    return size;
}

#endif
