#ifndef SLICE
#define SLICE
#define POCKET_SIZE 128
#include <stddef.h>

typedef struct slice
{
    void *data;
    size_t len;
    size_t cap;
    size_t element_size;
    char pocket[POCKET_SIZE];
} slice;

/*
 * @brief Creates a new slice with initial capacity 1.
 * @param element_size Size of each element in bytes.
 * @return Initialized slice struct.
 */
slice create_slice(size_t element_size);

/**
 * @brief Appends an element to the slice, resizing if needed.
 * @param s Pointer to the slice.
 * @param element Pointer to the element to append.
 * @return 1 on success, 0 on failure.
 */
int append_to_slice(slice *s, void *element);

/*
 * @brief Gets the value at a specific index
 * @param s The slice you want to get the value from
 * @param index the index you want to get
 * @return pointer to the value
 */
void *get(slice s, size_t index);
void free_slice(slice *s);
void concat_slices(slice *dest, slice *src);
void copy_slice(slice *dest, slice *src);
void slice_slice(slice *s, size_t start, size_t end);
void print_slice(slice *s, void (*print_element)(void *));
void map_slice(slice *s, void (*func)(void *));
void filter_slice(slice *s, int (*predicate)(void *));
void reduce_slice(slice *s, void *result, void (*func)(void *, void *));
void find_in_slice(slice *s, void *element, int (*predicate)(void *, void *));
void sort_slice(slice *s, int (*comparator)(const void *, const void *));
void reverse_slice(slice *s);
void for_each_in_slice(slice *s, void (*func)(void *));
#endif