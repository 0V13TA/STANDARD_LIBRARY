#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "headers/slice.h"

slice create_slice(size_t element_size)
{
    slice s;
    s.element_size = element_size;
    s.len = 0;
    s.cap = 1;
    s.data = s.pocket;
    memset(s.pocket, 0, POCKET_SIZE);
    return s;
}

int append_to_slice(slice *s, void *element)
{
    size_t required_size = (s->len + 1) * s->element_size;
    size_t current_size = s->len * s->element_size;
    if (s->len == 0 && required_size <= POCKET_SIZE)
    {
        memcpy(s->pocket + (current_size), element, s->element_size);
        s->len++;
        return 1;
    }

    if (s->data == s->pocket && required_size > POCKET_SIZE)
    {
        size_t new_cap = s->cap * 2;
        size_t new_size = new_cap * s->element_size;
        void *new_data = malloc(new_size);
        if (!new_data)
        {
            printf("Error Allocating memory for new data\n");
            return 0;
        }
        memcpy(new_data, s->pocket, current_size);
        s->data = new_data;
        s->cap = new_cap;
    }

    if (s->data != s->pocket && s->len == s->cap)
    {
        size_t new_cap = s->cap * 2;
        void *new_data = realloc(s->data, new_cap * s->element_size);
        if (!new_data)
        {
            printf("Error Allocating Memory for new data");
            return 0;
        }
        s->data = new_data;
        s->cap = new_cap;
    }

    memcpy((char *)s->data + (current_size), element, s->element_size);
    s->len++;
    return 1;
}

void *get(slice *s, size_t index)
{
    if (index >= s->len)
        return NULL; // Out of bounds
    return (char *)s->data + index * s->element_size;
}
