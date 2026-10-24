/**
 * @file main.c
 * @author I2dayy
 * @brief 动态数组 - 主函数
 * @date 2025-01-31
 */

#include "dynamic_array.h"
#include <stdio.h>

int main(void)
{
    DynamicArray da;

    dynamicArrayCreate(&da, 5);

    for (int i = 0; i < da.length; i++) {
        dynamicArraySetAt(&da, i, i + 1);
    }

    dynamicArrayPrintln(&da, "da");

    printf("\n");

    dynamicArrayAddTail(&da, 1437);

    dynamicArrayPrintln(&da, "da");
    printf("\n");

    dynamicArrayAddHead(&da, 4231);
    dynamicArrayPrintln(&da, "da");
    printf("\n");

    DynamicArray da2;
    // 定义了一个 da2 用于存储被截断的数组（当然，这里不会截断数据，所以得到的 da2 是空数组）
    dynamicArrayChangeLength(&da, da.length + 1, &da2);
    dynamicArraySetAt(&da, da.length - 1, 114514);
    printf("After change length and set data,\n");
    dynamicArrayPrintln(&da, "da");
    dynamicArrayPrintln(&da2, "da2");
    printf("\n");

    dynamicArrayChangeLength(&da, da.length - 3, &da2);
    printf("After change length,\n");
    dynamicArrayPrintln(&da, "da");
    dynamicArrayPrintln(&da2, "da2");
    printf("\n");

    // 参数三传入NULL，表示丢弃被截断的数据
    dynamicArrayChangeLength(&da, da.length - 1, NULL);
    printf("After change length (delete overflow datas),\n");
    dynamicArrayPrintln(&da, "da");
    dynamicArrayPrintln(&da2, "da2");
    printf("\n");

    dynamicArrayDelete(&da);
    if (da2.pdata != NULL) {
        dynamicArrayDelete(&da2);
    }

    return 0;
}
