/**
 * @file dynamic_array.c
 * @author I2day
 * @brief 动态数组
 * @date 2025-01-31
 */

#include "dynamic_array.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

/**
 * @brief 创建动态数组
 *
 * @param dyn_arr: 待创建的动态数组结构体地址
 * @param length: 新动态数组的长度
 * @return DynamicArrayStatus
 */
DynamicArrayStatus dynamicArrayCreate(DynamicArray* dyn_arr, size_t length)
{
    dyn_arr->pdata = (int*)malloc(length * sizeof(int));
    if (dyn_arr->pdata == NULL) {
        dyn_arr->length = 0U;
        return DYNAMIC_ARRAY_MEMORY_ALLOCATE_ERROR;
    }
    dyn_arr->length = length;

    return DYNAMIC_ARRAY_NOERROR;
}

/**
 * @brief 删除动态数组
 *
 * @param dyn_arr: 待删除的动态数组结构体地址
 */
void dynamicArrayDelete(DynamicArray* dyn_arr)
{
    free(dyn_arr->pdata);
    dyn_arr->pdata = NULL;  // 避免悬挂指针
    dyn_arr->length = 0U;
}

/**
 * @brief 设置动态数组给定 id 的元素的值
 *
 * @param dyn_arr: 待设置的动态数组结构体地址
 * @param id: 给定的 id
 * @param set_value: 待设置的值
 * @return DynamicArrayStatus
 */
DynamicArrayStatus dynamicArraySetAt(DynamicArray* dyn_arr, size_t id, int set_value)
{
    if (id >= dyn_arr->length) {
        return DYNAMIC_ARRAY_OVERFLOW;
    }

    dyn_arr->pdata[id] = set_value;
    return DYNAMIC_ARRAY_NOERROR;
}

/**
 * @brief 获得动态数组给定 id 的元素的值
 *
 * @param[in] dyn_arr: 待获得的动态数组结构体地址
 * @param[in] id: 给定的 id
 * @param[out] get_value: 返回获得的值
 * @return DynamicArrayStatus
 */
DynamicArrayStatus dynamicArrayGetAt(const DynamicArray* dyn_arr, size_t id, int* get_value)
{
    if (id >= dyn_arr->length) {
        return DYNAMIC_ARRAY_OVERFLOW;
    }
    if (get_value == NULL) {
        return DYNAMIC_ARRAY_DEREFERENCE_NULLPTR;
    }

    *get_value = dyn_arr->pdata[id];
    return DYNAMIC_ARRAY_NOERROR;
}

/**
 * @brief 在动态数组的尾部（id 最大的元素）后面插入一个值
 *
 * @param dyn_arr: 待插入的动态数组结构体地址
 * @param add_value: 待插入的值
 * @return DynamicArrayStatus
 */
DynamicArrayStatus dynamicArrayAddTail(DynamicArray* dyn_arr, int add_value)
{
    int* tmp = (int*)realloc(dyn_arr->pdata, (dyn_arr->length + 1U) * sizeof(int));
    if (tmp == NULL) {
        return DYNAMIC_ARRAY_MEMORY_ALLOCATE_ERROR;
    }
    dyn_arr->pdata = tmp;
    tmp = NULL;

    dyn_arr->pdata[dyn_arr->length] = add_value;
    dyn_arr->length++;

    return DYNAMIC_ARRAY_NOERROR;
}

/**
 * @brief 在动态数组的头部（id 最小的元素）前面插入一个值
 *
 * @param dyn_arr: 待插入的动态数组结构体地址
 * @param add_value: 待插入的值
 * @return DynamicArrayStatus
 */
DynamicArrayStatus dynamicArrayAddHead(DynamicArray* dyn_arr, int add_value)
{
    // 这里需要先把临时数组创建好。如果先重分配内存再创建这个数组的话，
    // 若这个数组创建失败，无法还原重分配之前的数组
    DynamicArray arr_tmp;
    if (dynamicArrayCreate(&arr_tmp, dyn_arr->length) != DYNAMIC_ARRAY_NOERROR) {
        return DYNAMIC_ARRAY_MEMORY_ALLOCATE_ERROR;
    }

    int* tmp = (int*)realloc(dyn_arr->pdata, (dyn_arr->length + 1U) * sizeof(int));
    if (tmp == NULL) {
        dynamicArrayDelete(&arr_tmp);
        return DYNAMIC_ARRAY_MEMORY_ALLOCATE_ERROR;
    }
    dyn_arr->pdata = tmp;
    tmp = NULL;

    assert(dyn_arr->length == arr_tmp.length);
    // memcpy 比使用循环更快，所以这里创建了一个临时数组
    memcpy(arr_tmp.pdata, dyn_arr->pdata, dyn_arr->length * sizeof(int));
    dyn_arr->length++;
    memcpy(&dyn_arr->pdata[1], arr_tmp.pdata, arr_tmp.length * sizeof(int));

    dyn_arr->pdata[0] = add_value;

    dynamicArrayDelete(&arr_tmp);

    return DYNAMIC_ARRAY_NOERROR;
}

/**
 * @brief 修改动态数组的长度（会根据 @c over_flow_arr 参数决定是否保留被截断的数据）
 *
 * @param[in, out] dyn_arr: 待修改的动态数组结构体的地址
 * @param[in] new_length: 修改后的数组的长度
 * @param[in, out] over_flow_arr: 若传入 NULL, 那么当修改后的数组长度小于修改前的长度时，
 *                       会直接丢弃被截断的数据；若需要保留被截断的数据，则传入一个
 *                       未被创建的动态数组结构体的地址，将会从这个参数返回被截断的数据
 *                       （以一个新的动态数组的形式返回）。如果没有被截断的数据，
 *                       则将传入的动态数组的成员都置零（如果传入的不是 NULL 的话）
 * @return DynamicArrayStatus
 */
DynamicArrayStatus dynamicArrayChangeLength(DynamicArray* dyn_arr, size_t new_length, DynamicArray* over_flow_arr)
{
    if (new_length == dyn_arr->length) {
        if (over_flow_arr != NULL) {
            over_flow_arr->length = 0U;
            over_flow_arr->pdata = NULL;
        }

        return DYNAMIC_ARRAY_NOERROR;
    }

    if (new_length > dyn_arr->length || over_flow_arr == NULL) {
        if (over_flow_arr != NULL) {
            over_flow_arr->length = 0U;
            over_flow_arr->pdata = NULL;
        }

        int* tmp = realloc(dyn_arr->pdata, new_length * sizeof(int));
        if (tmp == NULL) {
            return DYNAMIC_ARRAY_MEMORY_ALLOCATE_ERROR;
        }
        dyn_arr->pdata = tmp;
        tmp = NULL;
        dyn_arr->length = new_length;

        return DYNAMIC_ARRAY_NOERROR;
    }

    assert(new_length < dyn_arr->length && over_flow_arr != NULL);
    /// 用于存储被截断的数据的临时数组
    DynamicArray arr_tmp;
    if (dynamicArrayCreate(&arr_tmp, dyn_arr->length - new_length) != DYNAMIC_ARRAY_NOERROR) {
        over_flow_arr->length = 0U;
        over_flow_arr->pdata = NULL;

        return DYNAMIC_ARRAY_MEMORY_ALLOCATE_ERROR;
    }

    memcpy(arr_tmp.pdata, &dyn_arr->pdata[new_length], arr_tmp.length * sizeof(int));

    int* tmp = realloc(dyn_arr->pdata, new_length * sizeof(int));
    if (tmp == NULL) {
        dynamicArrayDelete(&arr_tmp);

        over_flow_arr->length = 0U;
        over_flow_arr->pdata = NULL;

        return DYNAMIC_ARRAY_MEMORY_ALLOCATE_ERROR;
    }
    dyn_arr->pdata = tmp;
    tmp = NULL;
    dyn_arr->length = new_length;

    over_flow_arr->length = arr_tmp.length;
    over_flow_arr->pdata = arr_tmp.pdata;
    arr_tmp.length = 0U;
    arr_tmp.pdata = NULL;

    return DYNAMIC_ARRAY_NOERROR;
}

/**
 * @brief 打印动态数组（会自动在末尾换一行）
 *
 * @param dyn_arr: 待打印的动态数组
 * @param name: 待打印的动态数组的名称
 */
void dynamicArrayPrintln(const DynamicArray* dyn_arr, const char* name)
{
    printf("%s.length = %zu\n", name, dyn_arr->length);
    printf("%s.pdata = ", name);
    if (dyn_arr->pdata != NULL) {
        for (int i = 0; i < dyn_arr->length; i++) {
            int tmp;
            dynamicArrayGetAt(dyn_arr, i, &tmp);
            printf("%d ", tmp);
        }
    }
    else {
        printf("NULL");
    }
    
    printf("\n");
}
