#include "why.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _FILE ("file.txt")
#define MAX_LENGTH (1000)

static Uint PATH_LENGTH[MAX_LENGTH][MAX_LENGTH];

const char* test_string = "3\n7 4\n2 4 6\n8 5 9 3";

static Uint _find_max_path(const Table* pyramid, Uint row, Uint col)
{
    Uint    value;
    Uint    left;
    Uint    right;
    char*   current;

    current = *(char **)TablePointAt(pyramid, row, col);

    if (!PATH_LENGTH[row][col])
    {
        ParseUint(&value, current);

        if (row + 1 == TableNRows(pyramid))
        {
            PATH_LENGTH[row][col] = value;
            return value;
        }

        left = _find_max_path(pyramid, row + 1, col);
        right = _find_max_path(pyramid, row + 1, col + 1);
        value += MAX(left, right);

        PATH_LENGTH[row][col] = value;
    }

    return PATH_LENGTH[row][col];
}


int main()
{
    char*  bytes;
    Table* pyramid;
    Uint   length;

    WhyStart();
    bytes = (char *)ReadFile(_FILE);
    pyramid = TableCreatePtr(NULL, NULL);
    ParseTable(pyramid, bytes, 0, 0, 0, 0, ' ');
    // PrintTable(pyramid, PrintCstrP);

    length = _find_max_path(pyramid, 0, 0);
    PrintUintN(&length);

    free(bytes);
    TableDestroy(pyramid);

    WhyEnd();

    return EXIT_SUCCESS;
}