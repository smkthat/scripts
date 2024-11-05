#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    int length;
    int element_size;
    uint8_t *data;
} array_t;

/* Recieves: element byte size.
 * Returns: NULL on failure
 *        , pointer to an empty array on success.
 */
array_t *array_new(int element_size);

array_t *arrat_new_filled(int element_size, int length, void* element);

/* Returns: 0 on failure
 *        , 1 on success
 */
bool array_clear(array_t *);

void array_destroy(array_t *);

/*  Returns: NULL on failure
 *         , pointer to an element on success.
 */
void *array_at(const array_t *, int element_number);

/* Returns: 1 on failure
 *        , 1 if empty
 *        , 0 if not empty.
 */
bool array_empty(const array_t *);

/* Returns: -1 on failure
 *        , length on success.
 */
int array_size(const array_t *);

/* Returns: -1 on failure
 *        , length * element_size on success.
 */
int array_memsize(const array_t *);

/* Note: in case if it's an array of pointers does not copy contents of what
 *       pointers point to.
 * Recieves: a pointer to not allocated array_t* to which copy will be taken to
 *         , array_t* from which copy will be taken from.
 * Returns: 0 on failure
 *        , 1 on success.
 */
bool array_copy(array_t **copy, const array_t *original);

// Note: unimplemented.
bool array_compare(array_t *, array_t *);

// Note: unimplemented.
bool array_concatenate(array_t *destination, array_t *source);

/* Returns: 0 on failure
 *        , 1 on success.
 */
bool array_push_back(array_t *, const void *element);
#define array_push array_push_back

// Note: unimplemented.
void *array_front(array_t *);

// Note: unimplemented.
void *array_back(array_t *);

// Note: unimplemented.
void *array_pop_back(array_t *);

#endif  // ARRAY_H
