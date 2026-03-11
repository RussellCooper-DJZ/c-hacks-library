#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bit_hacks.h"
#include "../include/macro_hacks.h"
#include "../include/memory_hacks.h"
#include "../include/perf_hacks.h"

// 演示 container_of
typedef struct {
    int id;
    char name[20];
    int age;
} user_t;

void test_container_of() {
    user_t u = {1, "Manus", 1};
    int *age_ptr = &u.age;
    user_t *u_ptr = container_of(age_ptr, user_t, age);
    printf("[container_of] User ID: %d, Name: %s\n", u_ptr->id, u_ptr->name);
}

// 演示 C11 _Generic
void test_generic() {
    int i = 10;
    float f = 3.14f;
    double d = 2.718;
    printf("[_Generic] i is %s, f is %s, d is %s\n", 
           print_type(i), print_type(f), print_type(d));
}

// 演示位运算
void test_bit_hacks() {
    int x = 150;
    printf("[bit_hacks] 150 in [0, 255]? %s\n", in_range(x, 0, 255) ? "Yes" : "No");
    printf("[bit_hacks] next power of 2 of 150: %u\n", next_power_of_2(150));
    printf("[bit_hacks] is 128 power of 2? %s\n", is_power_of_2(128) ? "Yes" : "No");
}

// 演示指针标记
void test_pointer_tagging() {
    int val = 42;
    void *ptr = &val;
    void *tagged = SET_TAG(ptr, 3);
    printf("[pointer_tagging] Tag: %lu, Original Ptr: %p, Tagged Ptr: %p\n", 
           GET_TAG(tagged), GET_PTR(tagged), tagged);
}

// 演示 __attribute__((cleanup))
void cleanup_file(FILE **f) {
    if (*f) {
        printf("[cleanup] Closing file automatically...\n");
        fclose(*f);
    }
}

void test_cleanup() {
    FILE *f __cleanup(cleanup_file) = fopen("test.txt", "w");
    if (f) {
        fprintf(f, "Hello Manus!");
        // 函数结束时 f 会自动关闭
    }
}

int main() {
    printf("--- C Hacks Library Examples ---\n");
    test_container_of();
    test_generic();
    test_bit_hacks();
    test_pointer_tagging();
    test_cleanup();
    printf("--- End of Examples ---\n");
    return 0;
}
