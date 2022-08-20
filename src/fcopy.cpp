#include <stdio.h>
#include <string.h>

//#define TEST_IT 1 // 1 to test as DOS application. 0 to compile CopyFile
                  // function only...uses ANSI C functions only.
                  // compatible with DOS, Windows 3.1, 95, NT,
                  // UNIX, anything that supports ANSI C++ standards.

#include "fcopy.h"

namespace bellshire{

// Function Name: FileCopy
//
// Copy the file specified by "src" to the file specified by "dst".
// Both source and destination file names must be full path/file names,
// such as c:\myfile.txt a:\myfile.txt.
//
// A more sophisticated version would make certain src and dst file names
// were complete and valid.  It would handle "wild card" characters to
// copy multiple files, and all sorts of goodies like that...but all those
// things destroy the "portability" of this code.
//
// This FileCopy function will work with virtually any ANSI C++ compiler.

int FileCopy ( const char *src, const char *dst )
{
    #define BUFSZ 16000
    char            *buf;
    FILE            *fi;
    FILE            *fo;
    unsigned        amount;
    unsigned        written;
    int             result;

    buf = new char[BUFSZ];

    fi = fopen( src, "rb" );
    fo = fopen( dst, "wb" );

    result = COPY_OK;
    if  ((fi == NULL) || (fo == NULL) )
    {
        result = COPY_ERROR;
        if (fi != NULL) fclose(fi);
        if (fo != NULL) fclose(fo);
    }

if (result == COPY_OK)
{
    do
    {
        amount = fread( buf, sizeof(char), BUFSZ, fi );
        if (amount)
        {
            written = fwrite( buf, sizeof(char), amount, fo );
            if (written != amount)
            {
                result = COPY_ERROR; // out of disk space or some other disk err?
            }
        }
    } // when amount read is < BUFSZ, copy is done
    while ((result == COPY_OK) && (amount == BUFSZ));

    fclose(fi);
    fclose(fo);

}
delete [] buf;
return(result);
}

//#if TEST_IT
//void main( int argc, char **argv )
//{
//if (argc != 3)
//  {
//  printf("Call format: fcopy SRC DST\n");
//  }
//else
//  {
//  if (FileCopy( argv[1], argv[2] ) != COPY_OK)
//    {
//    printf("Failed to copy file %s to %s\n",
//            argv[1], argv[2] );
//    }
//  else
//    {
//    printf("Copied file %s to file %s\n",
//            argv[1], argv[2] );
//    }
//  }
//}
//
//#define BUFSZ 16000
//
//char            *buf;
//FILE            *fi;
//FILE            *fo;
//unsigned        amount;
//unsigned        written;
//int             result;
//
//buf = new char[BUFSZ];
//
//fi = fopen( src, "rb" );
//fo = fopen( dst, "wb" );
//
//result = COPY_OK;
//if  ((fi == NULL) || (fo == NULL) )
//{
//  result = COPY_ERROR;
//  if (fi != NULL) fclose(fi);
//  if (fo != NULL) fclose(fo);
//}
//
//if (result == COPY_OK)
//{
//    do
//    {
//        amount = fread( buf, sizeof(char), BUFSZ, fi );
//        if (amount)
//        {
//            written = fwrite( buf, sizeof(char), amount, fo );
//            if (written != amount)
//            {
//                result = COPY_ERROR; // out of disk space or some other disk err?
//            }
//        }
//    } // when amount read is < BUFSZ, copy is done
//    while ((result == COPY_OK) && (amount == BUFSZ));
//
//    fclose(fi);
//    fclose(fo);
//
//}
//delete [] buf;
//return(result);
//}
//
//#if TEST_IT
//void main( int argc, char **argv )
//{
//if (argc != 3)
//  {
//  printf("Call format: fcopy SRC DST\n");
//  }
//else
//  {
//  if (FileCopy( argv[1], argv[2] ) != COPY_OK)
//    {
//    printf("Failed to copy file %s to %s\n",
//            argv[1], argv[2] );
//    }
//  else
//    {
//    printf("Copied file %s to file %s\n",
//            argv[1], argv[2] );
//    }
//  }
//}
//#endif

}//namespace bellshire
