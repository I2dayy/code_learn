/**
 * @file dynamic_array.h
 * @author I2day
 * @brief 动态数组
 * @date 2025-01-31
 */

#ifndef __DYNAMIC_ARRAY_H__
#define __DYNAMIC_ARRAY_H__

#include <stddef.h>

/**
 * 动态数组状态
 */
typedef enum DynamicArrayStatus {
    DYNAMIC_ARRAY_NOERROR = 0,            ///< 动态数组无错误
    DYNAMIC_ARRAY_MEMORY_ALLOCATE_ERROR,  ///< 动态数组内存分配错误
    DYNAMIC_ARRAY_OVERFLOW,               ///< 动态数组数组上溢出
    DYNAMIC_ARRAY_DEREFERENCE_NULLPTR     ///< 动态数组解引用空指针
} DynamicArrayStatus;

/**
 * 动态数组
 */
typedef struct DynamicArray {
    int* pdata;     ///< 指向存储数据的内存
    size_t length;  ///< 数组中，元素的个数
} DynamicArray;

DynamicArrayStatus dynamicArrayCreate(DynamicArray* dyn_arr, size_t length);
void dynamicArrayDelete(DynamicArray* dyn_arr);
DynamicArrayStatus dynamicArraySetAt(DynamicArray* dyn_arr, size_t id, int set_value);
DynamicArrayStatus dynamicArrayGetAt(const DynamicArray* dyn_arr, size_t id, int* get_value);
DynamicArrayStatus dynamicArrayAddTail(DynamicArray* dyn_arr, int add_value);
DynamicArrayStatus dynamicArrayAddHead(DynamicArray* dyn_arr, int add_value);
DynamicArrayStatus dynamicArrayChangeLength(DynamicArray* dyn_arr, size_t new_length, DynamicArray* over_flow_arr);
void dynamicArrayPrintln(const DynamicArray* dyn_arr, const char* name);

#endif  //!__DYNAMIC_ARRAY_H__
