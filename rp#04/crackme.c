#include <stdio.h>
#include <string.h>

int main() {
    char input[100];
    printf("Nhap mat khau: ");
    scanf("%99s", input);
    
    // Logic kiem tra mat khau
    if (strlen(input) != 8) {
        printf("Sai roi!\n");
        return 1;
    }
    
    // Mat khau that la: "Reverse1"
    char secret[] = "Reverse1"; // Mang ky tu
    
    for (int i = 0; i < 8; i++) {
        if (input[i] != secret[i]) {
            printf("Sai roi!\n");
            return 1;
        }
    }
    
    printf("Chuc mung! Ban da tim ra mat khau!\n");
    return 0;
}
