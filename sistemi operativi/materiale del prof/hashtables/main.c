#include "ht.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <assert.h>

#ifdef COUNT_KEY_PROBES
extern uint64_t key_probes_counter_read;
extern uint64_t key_probes_counter_write;
#endif

#define BUFSIZE 8192
#define DELIMITERS " ,.:;!?\"'-~\n"

extern uint64_t hash_key(const char *key);

int main() {
  ht *table = ht_create();
  assert(table != NULL);

  char buf[BUFSIZE];
  while (fgets(buf, BUFSIZ, stdin) != NULL) {

    // Get the first token
    char* token = strtok(buf, DELIMITERS);

    // Keep printing tokens while one of the delimiters present in str[].
    while (token != NULL) {
      for (char *p = token; *p; ++p) {
        *p = tolower(*p);
      }

#if 0
      printf("%s ", token);
#endif

      uint64_t value;
      if (ht_get(table, token, &value)) {
        ++value;
      }
      else {
        value = 1;
      }
      if (!ht_set(table, token, value)) {
        return 1;
      }

#if 0
      printf("%lu\n", value);
#endif

      token = strtok(NULL, DELIMITERS);
    }
  }

  hti iterator;
  if (ht_iterator_begin(table, &iterator)) {
    printf("%s %lu\n", iterator.key, iterator.value);
    while (ht_iterator_next(&iterator)) {
      printf("%s %lu\n", iterator.key, iterator.value);
    }
  }
  else {
    fprintf(stderr, "Table is empty!\n");
  }

#ifdef COUNT_KEY_PROBES
  fprintf(stderr, "Key probes for reading: %lu\n", key_probes_counter_read);
  fprintf(stderr, "Key probes for writing: %lu\n", key_probes_counter_write);
#endif

  return 0;
}
