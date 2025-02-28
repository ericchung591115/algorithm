#include <stdio.h>

#define MAX_BCD_DIGITS 20  // 最大BCD長度

// HEX 轉 BCD 陣列 (結構更直觀，效能更佳)
int hex2bcd(unsigned long long hex, unsigned char *bcd, int max_size) {
    if (!bcd || max_size <= 0) return 0;  // NULL 檢查 + 陣列大小檢查

    int size = 0;
    
    // 處理特例：當 hex 為 0 時，直接返回
    if (hex == 0) {
        bcd[0] = 0;
        return 1;
    }

    // 計算 BCD 長度
    unsigned long long temp = hex;
    while (temp) {
        size++;
        temp /= 10;
    }

    // 若超過陣列最大長度，返回錯誤
    if (size > max_size) return 0;

    // 直接從高位開始存入 BCD 陣列
    for (int i = size - 1; i >= 0; i--) {
        bcd[i] = hex % 10;
        hex /= 10;
    }

    return size; // 回傳 BCD 長度
}

int main() {
    unsigned long long hex_value = 123456789;
    unsigned char bcd[MAX_BCD_DIGITS];

    int bcd_size = hex2bcd(hex_value, bcd, MAX_BCD_DIGITS);

    if (bcd_size > 0) {
        printf("HEX: %llu -> BCD: ", hex_value);
        for (int i = 0; i < bcd_size; i++) {
            printf("%X", bcd[i]);
        }
        printf("\n");
    } else {
        printf("HEX 轉換失敗，數值過大或輸入錯誤！\n");
    }

    return 0;
}

