#ifndef FCOPY_H
#define FCOPY_H

namespace bellshire{
// File copy function prototype by M. Ratcliff

#define COPY_ERROR      -1
#define COPY_OK          0

int FileCopy
  ( const char *src,
    const char *dst );

}//namespace bellshire

#endif
