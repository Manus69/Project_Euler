#include "why.h"

#include <stdlib.h>
#include <stdio.h>

#define _FILE ("file.txt")
#define LENGTH (4)

static void* _clean_up(Table* table, Byte* bytes, int code)
{
    TableDestroy(table);
    free(bytes);

    WhyEnd();
    exit(code);

    return NULL;
}

static Table* _get_table()
{
    Table*  table;
    Byte*   bytes;


    table = NULL;
    bytes = NULL;

    if (!(table = TableCreatePtr(NULL, NULL)))
        return _clean_up(table, bytes, EXIT_FAILURE);
    
    if (!(bytes = ReadFile(_FILE)))
        return _clean_up(table, bytes, EXIT_FAILURE);

    if (ParseTable(table, (char *)bytes, 0, 0, 0, '\n', ' ') <= 0)
        return _clean_up(table, bytes, EXIT_FAILURE);

    PrintTable(table, PrintCstrP);

    WhySavePtr(bytes);

    return table;
}

static Uint _compute_horizontal_product(const Matrix* matrix, Uint j, Uint k, Uint length)
{
    Uint product;
    Uint last;

    product = 1;
    last = k + length;
    while (k < last)
    {
        product *= *(Uint *)MatrixPointAt(matrix, j, k);
        ++ k;
    }

    return product;
}

static Uint _horizontal_max(const Matrix* matrix, Uint length)
{
    Uint max;
    Uint current;
    Uint j;
    Uint k;

    max = 0;
    j = 0;

    while (j < MatrixNRows(matrix))
    {
        k = 0;
        while (k + length < MatrixNCols(matrix))
        {
            current = _compute_horizontal_product(matrix, j, k, length);
            max = MAX(current, max);

            ++ k;
        }

        ++ j;
    }

    return max;
}

static Uint _compute_vertical_product(const Matrix* matrix, Uint j, Uint k, Uint length)
{
    Uint product;
    Uint last;

    product = 1;
    last = j + length;

    while (j < last)
    {
        product *= *(Uint *)MatrixPointAt(matrix, j, k);
        ++ j;
    }

    return product;
}

static Uint _vertical_max(const Matrix* matrix, Uint length)
{
    Uint max;
    Uint current;
    Uint j;
    Uint k;

    max = 0;
    j = 0;

    while (j + length < MatrixNRows(matrix))
    {
        k = 0;
        while (k < MatrixNCols(matrix))
        {
            current = _compute_vertical_product(matrix, j, k, length);
            max = MAX(current, max);

            ++ k;
        }
        ++ j;
    }

    return max;
}

static Uint _compute_lurd_product(const Matrix* matrix, Uint j, Uint k, Uint length)
{
    Uint product;
    Uint last;

    product = 1;
    last = j + length;

    while (j < last)
    {
        product *= *(Uint *)MatrixPointAt(matrix, j, k);

        ++ j;
        ++ k;
    }

    return product;
}

static Uint _lurd_max(const Matrix* matrix, Uint length)
{
    Uint max;
    Uint current;
    Uint j;
    Uint k;

    j = 0;
    max = 0;

    while (j + length < MatrixNRows(matrix))
    {
        k = 0;
        while (k + length < MatrixNCols(matrix))
        {
            current = _compute_lurd_product(matrix, j, k, length);
            max = MAX(current, max);
            ++ k;
        }
        ++ j;
    }

    return max;
}

static Uint _compute_ldru_product(const Matrix* matrix, Uint j, Uint k, Uint length)
{
    Uint product;
    Uint last;

    product = 1;
    last = j - length;

    while (j > last)
    {
        product *= *(Uint *)MatrixPointAt(matrix, j, k);

        -- j;
        ++ k;
    }

    return product;
}

static Uint _ldru_max(const Matrix* matrix, Uint length)
{
    Uint max;
    Uint current;
    Int  j;
    Uint k;

    max = 0;
    j = MatrixNRows(matrix) - 1;

    while (j >= (Int)length)
    {
        k = 0;
        while (k + length < MatrixNCols(matrix))
        {
            current = _compute_ldru_product(matrix, j, k, length);
            max = MAX(current, max);

            ++ k;
        }
        -- j;
    }

    return max;
}

static Uint _max(Uint* array, Uint length)
{
    Uint rhs;

    if (length == 0)
        return 0;
    
    if (length == 1)
        return *array;
    
    rhs = _max(++ array, -- length);

    return MAX(*array, rhs);
}

int main()
{
    Table*  table;
    Matrix* matrix;
    Uint    results[LENGTH];
    Uint max;

    WhyStart();
    
    table = _get_table();
    matrix = MatrixCreateUintFromTableWithParser(table, ParseDigitSequenceWRAP);

    PrintMatrix(matrix, PrintUintS);

    results[0] = _horizontal_max(matrix, LENGTH);
    results[1] = _vertical_max(matrix, LENGTH);
    results[2] = _lurd_max(matrix, LENGTH);
    results[3] = _ldru_max(matrix, LENGTH);

    max = _max(results, LENGTH);
    PrintUintN(&max);

    MatrixDestroy(matrix);
    TableDestroy(table);
    WhyEnd();

    return EXIT_SUCCESS;
}