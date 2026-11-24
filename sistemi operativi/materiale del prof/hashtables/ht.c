#include "ht.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifdef COUNT_KEY_PROBES
uint64_t key_probes_counter_read = 0ULL;
uint64_t key_probes_counter_write = 0ULL;
#endif

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

// Return 64-bit FNV-1a hash for key (NUL-terminated). See description:
// https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
static uint64_t hash_key(const char *key) {
  uint64_t hash = FNV_OFFSET;
  for (const char *p = key; *p; p++) {
    hash ^= (uint64_t)(unsigned char)(*p);
    hash *= FNV_PRIME;
  }
  return hash;
}

#define KEYSIZE 80

// Hash table entry (slot may be filled or empty).
typedef struct {
  char key[KEYSIZE];  // Empty string if this slot is empty
  value_type value;
} ht_entry;

typedef struct ht_impl {
    size_t capacity;     // Size of _entries array
    size_t length;       // Number of items in hash table
    ht_entry entries[];  // Hash slots
} ht_impl;

// Hash table structure: create with ht_create, free with ht_destroy.
struct ht {
  ht_impl *impl;    // Pointer to the actual implementation
};

#define INITIAL_CAPACITY 16  // Must not be zero
//#define INITIAL_CAPACITY 32768  // Must not be zero

ht *ht_create(void) {
  ht *table = malloc(sizeof(ht));
  if (table == NULL) {
    return NULL;
  }

  struct ht_impl *impl = malloc(sizeof(ht_impl)
                                + INITIAL_CAPACITY*sizeof(ht_entry));

  if (impl == NULL) {
    return NULL;
  }

  impl->capacity = INITIAL_CAPACITY;
  impl->length = 0;
  memset(impl->entries, 0, impl->capacity*sizeof(ht_entry));

  table->impl = impl;

  return table;
}


void ht_destroy(ht *table) {
  assert(table != NULL);
  assert(table->impl != NULL);

  // Destroy the implementation.
  free(table->impl);
  // Destroy the table itself.
  free(table);
}

bool ht_get(ht *table, const char *key, value_type *pvalue) {
  assert(table != NULL);
  assert(table->impl != NULL);

  uint64_t hash = hash_key(key);
  size_t index = hash % table->impl->capacity;

  while (true) {

    if (table->impl->entries[index].key[0] == '\0') {
      return false;
    }

    bool found = (strcmp(key, table->impl->entries[index].key) == 0);

#ifdef COUNT_KEY_PROBES
    ++key_probes_counter_read;
#endif

    if (found) {
      *pvalue = table->impl->entries[index].value;
      return true;
    }

    ++index;
    if (index >= table->impl->capacity) {
      index = 0;
    }

  }
}

// Internal function to set an entry (without expanding table).
// If plength is not NULL, *plength must be incremented.
static bool ht_set_entry(ht_entry* entries, size_t capacity,
                         const char* key, value_type value, size_t* plength) {
  if (strlen(key) > KEYSIZE) {
    return false;
  }

  uint64_t hash = hash_key(key);
  size_t index = hash % capacity;

  while (true) {
    if (entries[index].key[0] == '\0') {

      strcpy(entries[index].key, key);
      entries[index].value = value;

      if (plength != NULL) {
        ++(*plength);
      }

      return true;
    }

    bool found = (strcmp(key, entries[index].key) == 0);

#ifdef COUNT_KEY_PROBES
    ++key_probes_counter_write;
#endif

    if (found) {
      entries[index].value = value;
      return true;
    }

    ++index;
    if (index >= capacity) {
      index = 0;
    }
  }

  // This is unreachable.
  assert(false);
  return false;
}

// Expand hash table to twice its current size. Return true on success,
// false if out of memory.
static bool ht_expand(ht* table) {
  assert(table != NULL);
  assert(table->impl != NULL);

  size_t old_capacity = table->impl->capacity;
  size_t new_capacity = old_capacity * 2;

  ht_impl *new_impl = malloc(sizeof(ht_impl) + new_capacity*sizeof(ht_entry));
  if (new_impl == NULL) {
    return false;
  }

  memset(new_impl->entries, 0, new_capacity*sizeof(ht_entry));

  for (size_t index = 0U; index < old_capacity; ++index) {
    const char *key = table->impl->entries[index].key;
    if (key[0] == '\0') {
      continue;
    }

    value_type value = table->impl->entries[index].value;

    bool r = ht_set_entry(new_impl->entries, new_capacity,
                          key, value, NULL);
    assert(r);
#ifdef NDEBUG
    (void) r;
#endif
  }

  new_impl->capacity = new_capacity;
  new_impl->length = table->impl->length;
  table->impl = new_impl;

  return true;
}

bool ht_set(ht *table, const char *key, value_type value) {
  assert(table != NULL);
  assert(table->impl != NULL);

  if (table->impl->length >= (table->impl->capacity / 2)) {
    // Table half full: expand.
    if (!ht_expand(table)) {
      return false;
    }
  }

  return ht_set_entry(table->impl->entries, table->impl->capacity,
                      key, value, &table->impl->length);
}

size_t ht_length(ht *table) {
  assert(table != NULL);
  assert(table->impl != NULL);

  return table->impl->length;
}

bool ht_iterator_begin(ht *table, hti *it) {
  for (size_t index = 0U; index < table->impl->capacity; ++index) {
    if (table->impl->entries[index].key[0] != '\0') {
      it->key = table->impl->entries[index].key;
      it->value = table->impl->entries[index].value;

      it->priv_table = table;
      it->priv_index = index;
      return true;
    }
  }

  assert(table->impl->length == 0U);
  return false;
}

bool ht_iterator_next(hti *it) {
  for (size_t index = it->priv_index + 1;
       index < it->priv_table->impl->capacity;
       ++index) {
    if (it->priv_table->impl->entries[index].key[0] != '\0') {
      it->key = it->priv_table->impl->entries[index].key;
      it->value = it->priv_table->impl->entries[index].value;
      it->priv_index = index;
      return true;
    }
  }

  return false;
}

