#include <stdio.h>
#define SIZE (size_t)sizeof(array)/sizeof(*array)

int array_average(const int *array, size_t count) {
    int sum=0;
    for(int i=0; i<(count); i++){
        sum += array[i];
    }
    int avg = sum/(count);
    return avg;
}

int array_max(const int *array, size_t count) {
    int val = 0;
    for(int i=0; i<(count);i++) {
        if(val<array[i]) val=array[i];
    }
    return val;
}

int main() {
    int array[] = {1,2,3,4,5};
    printf("Avg: %d Max: %d\n",array_average(array,SIZE),array_max(array,SIZE));
    return 0;
}
