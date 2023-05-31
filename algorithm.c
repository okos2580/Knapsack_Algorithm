//202210423 김태정
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int number;
    int weight;
    int value;
} Item;

int maximum (int a, int b) { return (a > b) ? a : b; }

int knapsack(int C, Item* items, int n) {
    int** dp = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int*)malloc((C + 1) * sizeof(int));
    }

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= C; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            }
            else if (items[i - 1].weight <= w) {
                dp[i][w] = max(items[i - 1].value + dp[i - 1][w - items[i - 1].weight], dp[i - 1][w]);
            }
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int max_value = dp[n][C];

    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return max_value;
}

int main() {
    int C;
    printf("배낭 용량을 입력하세요: ");
    scanf("%d", &C);

    FILE* file = fopen("items.txt", "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    int n = 6;  // 물건의 개수
    Item* items = (Item*)malloc(n * sizeof(Item));

    for (int i = 0; i < n; i++) {
        fscanf(file, "%d %d %d", &items[i].number, &items[i].weight, &items[i].value);
    }

    fclose(file);

    int max_value = knapsack(C, items, n);

    printf("최대 가치: %d\n", max_value);

    free(items);

    return 0;
}
