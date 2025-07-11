#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#define MAX_CALLBACKS 10

// Callback 函式類型（使用 printf-style 參數）
typedef void (*CallbackFunc)(const char* fmt, va_list args);

// 儲存已註冊的 callback
static CallbackFunc g_callbacks[MAX_CALLBACKS];
static int g_callbackCount = 0;

// 註冊 callback
int register_callback(CallbackFunc cb) {
    if (g_callbackCount >= MAX_CALLBACKS) return -1;

    // 檢查是否已註冊過，避免重複
    for (int i = 0; i < g_callbackCount; ++i) {
        if (g_callbacks[i] == cb)
            return -2;  // 已註冊
    }

    g_callbacks[g_callbackCount++] = cb;
    return 0;
}

// 取消註冊 callback
int unregister_callback(CallbackFunc cb) {
    for (int i = 0; i < g_callbackCount; ++i) {
        if (g_callbacks[i] == cb) {
            // 把陣列往前搬移，compact callback list
            for (int j = i; j < g_callbackCount - 1; ++j) {
                g_callbacks[j] = g_callbacks[j + 1];
            }
            g_callbackCount--;
            return 0;  // 成功移除
        }
    }
    return -1;  // 沒找到
}

// 觸發所有 callback，支援 printf-style 可變參數
void trigger_callbacks(const char* fmt, ...) {
    for (int i = 0; i < g_callbackCount; ++i) {
        va_list args;
        va_start(args, fmt);
        g_callbacks[i](fmt, args);
        va_end(args);
    }
}

// Sample Callback 實作
void my_callback1(const char* fmt, va_list args) {
    printf("Callback1: ");
    vprintf(fmt, args);
}

void my_callback2(const char* fmt, va_list args) {
    printf("Callback2: ");
    vprintf(fmt, args);
}

int main() {
    register_callback(my_callback1);
    register_callback(my_callback2);

    printf("== First Trigger ==\n");
    trigger_callbacks("Value = %d, Text = %s\n", 100, "Hello");

    // 取消 callback1
    unregister_callback(my_callback1);

    printf("== After Unregister callback1 ==\n");
    trigger_callbacks("Only callback2 should be called: %d\n", 200);

    return 0;
}
