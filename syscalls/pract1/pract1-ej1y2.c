#include <stdio.h>
#define START 0
#define TRUE 1
#define FALSE 0

int partition1(int*, int , int, int (*f)(int,int));
int partition2(int*, int , int);
void quicksort(int*, int, int, int (*f)(int,int));
int compare(int, int);
void qsort(int*, size_t, int (*f)(int,int));
int binary_search(unsigned int, unsigned int*, size_t);

int main(int argc, char *argv[]){
    int n;

    do{
        printf("Inserte el tamanio de la lista de numeros a ingresar\n");
        scanf("%d",&n);
    }while(n <= 0);
    
    unsigned int arr[n];

    for (int i = 0; i < n; i++) {
        printf("Inserte un numero entero [%d restantes] : ", n - i);
        scanf("%ui", arr + i);
    }

    //qsort(arr, (size_t)n, compare);

    for (int i = 0; i < n; i++) {
        printf("%d | ", arr[i]);
    }
    printf("\n");

    int draco_malfoy = 12;
    if(binary_search(draco_malfoy, arr,n)){
        printf("%d esta en el arreglo\n", draco_malfoy);
    }else{
        printf("%d no esta en el arreglo\n", draco_malfoy);
    }

    return 0;
}

void qsort(int *arr, size_t arr_size, int (*comparison_function)(int,int)){
    quicksort(arr, START,arr_size - 1,comparison_function);
}

void quicksort(int *arr, int lo, int hi, int (*comparison_function)(int,int)){
    if(lo < hi){
        int m = partition1(arr,lo,hi,comparison_function);
        quicksort(arr, lo, m-1, comparison_function);
        quicksort(arr, m+1, hi, comparison_function);
    }
}

int partition1(int *arr, int lo, int hi,int (*comparison_function)(int,int)){
    int i = lo - 1;
    int j = lo;
    int pivot = arr[hi];
    int aux;

    while(j < hi){
        if((*comparison_function)(arr[j],pivot) < 0){
            i++;
            aux = arr[j];
            arr[j] = arr[i];
            arr[i] = aux;
        }
        j++;
    }
    i++;
    arr[hi] = arr[i];
    arr[i] = pivot;
    return i;
}

int partition2(int *arr, int lo, int hi){
    int pivot = arr[hi];
    int i = lo-1;
    int j = hi;
    int aux;
    while(i < j){
        do{
            i++;
        }while(arr[i] < pivot);

        do{
            j--;
        }while(arr[j] >= pivot);

        if(i < j){
            aux = arr[i];
            arr[i] = arr[j];
            arr[j] = aux;
        }
    }

    aux = arr[i];
    arr[i] = arr[hi];
    arr[hi] = aux;

    return i;
}

int compare(int a, int b){
    return a - b;
}

int binary_search(unsigned int number_to_search, unsigned int *arr, size_t arr_size){
    int lo = 0;
    int hi = arr_size - 1;
    int m;

    while(lo <= hi){
        m = (hi - lo) / 2 + lo;
        if(number_to_search < arr[m]){
            hi = m - 1;
        }else if(number_to_search > arr[m]){
            lo = m + 1;
        }else{
            return TRUE;
        }
    }
    return FALSE;
}
