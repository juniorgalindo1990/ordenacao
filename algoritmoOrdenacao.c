#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funções de ordenação
void merge(int *arr, int l, int m, int r);
void mergeSort(int *arr, int l, int r);
void quickSort(int *arr, int low, int high);
int partition(int *arr, int low, int high);

// Função para imprimir o vetor
void printArray(int *arr, int size);

int main() {
    FILE *file = fopen("dados.txt", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return EXIT_FAILURE;
    }

    // Determinar o número de elementos
    int size = 0;
    int capacity = 1000;  // Capacidade inicial maior para evitar muitas realocações
    int *data1 = malloc(capacity * sizeof(int));
    int *data2 = malloc(capacity * sizeof(int));
    
    if (data1 == NULL || data2 == NULL) {
        perror("Erro ao alocar memoria");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Ler dados do arquivo e copiar para o segundo array
    while (fscanf(file, "%d", &data1[size]) != EOF) {
        if (size >= capacity) {
            capacity *= 2;
            int *temp1 = realloc(data1, capacity * sizeof(int));
            int *temp2 = realloc(data2, capacity * sizeof(int));

            // Verificar se a realocação foi bem-sucedida
            if (temp1 == NULL || temp2 == NULL) {
                free(data1);
                free(data2);
                perror("Erro ao realocar memoria");
                fclose(file);
                return EXIT_FAILURE;
            }

            data1 = temp1;
            data2 = temp2;
        }
        data2[size] = data1[size]; // Copiar para o segundo vetor
        size++;
    }

    fclose(file);

    // Exibir dados originais
  //  printArray(data1, size);
   // printf("\n");

    // Ordenar usando Merge Sort
    mergeSort(data1, 0, size - 1);
    printf("Merge Sort:\n");
    printArray(data1, size);
    printf("\n\n");

    // Ordenar usando Quick Sort
    quickSort(data2, 0, size - 1);
    printf("Quick Sort:\n");
    printArray(data2, size);
    printf("\n\n");

    // Liberar memória
    free(data1);
    free(data2);

    return EXIT_SUCCESS;
}

void merge(int *arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    if (L == NULL || R == NULL) {
        perror("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }

    memcpy(L, &arr[l], n1 * sizeof(int));
    memcpy(R, &arr[m + 1], n2 * sizeof(int));

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }

    free(L);
    free(R);
}

void mergeSort(int *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1);
}

void quickSort(int *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", arr[i]);
    }
}
