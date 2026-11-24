#ifndef ht_h
#define ht_h 1

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint64_t value_type;

// Hash table structure: create with ht_create, free with ht_destroy.
typedef struct ht ht;

// Create hash table and return pointer to it, or NULL if out of memory.
ht *ht_create(void);

// Free memory allocated for hash table, including allocated keys.
void ht_destroy(ht *table);

// Get item with given key (NUL-terminated) from hash table. Return
// true, if key is found and set *pvalue to the value set with ht_set,
// or false, if key not found.
bool ht_get(ht *table, const char *key, value_type *pvalue);

// Set item with given key (NUL-terminated) to value.
// Return true on success, or false if out of memory.
bool ht_set(ht *table, const char *key, value_type value);

// Return number of items in hash table.
size_t ht_length(ht *table);

// Hash table iterator: create with ht_iterator_begin, iterate with
// ht_iterator_next.
typedef struct {
  const char *key;       // Current key
  value_type value;      // Current value

  // Don't use these fields directly.
  ht *priv_table;        // Reference to hash table being iterated
  size_t priv_index;     // Current index into ht.entries
} hti;

// Set new hash table iterator pointing to the first non-empty entry,
// if any, and return true.  Return false if table is empty.
bool ht_iterator_begin(ht *table, hti *it);

// Move iterator to next item in hash table, update iterator's key
// and value to current item, and return true. If there are no more
// items, return false. Don't call ht_set during iteration.
bool ht_iterator_next(hti *it);

#endif // ifndef ht_h
