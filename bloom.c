#include "bloom.h"

/* Create a new empty bloom filter */
BF BF_empty() {
  BF b;
  memset(b.filter, 0, _FILTER_SIZE);
  return b;
}

/* Add more data to the filter */;
void BF_add(char *data, int size, BF *b, int debug, int print) {
  uint32_t hash[_HASH_NUM+(4-(_HASH_NUM%4))];
  for(int i = 0; i < _HASH_NUM; i+=4)
    MurmurHash3_x64_128(data, size, i, &hash[i]);
  for(int i = 0; i < _HASH_NUM; i++) {
    int bit = hash[i]%(_FILTER_SIZE*8);
    b->filter[bit/64] |= 1L<<(bit%64);
  }

  if(print) printf("ADD : %s has been added to the filter\n", data);
  if(debug) {
    printf("\nDEBUG INFO :\n");
    BF_debug_hash(hash);
    BF_debug_filter(*b);
    printf("\n");
  }
}

/* Filter requested data */
int BF_query(char *data, int size, BF b, int print) {
  uint32_t hash[_HASH_NUM+(4-(_HASH_NUM%4))];
  for(int i = 0; i < _HASH_NUM; i+=4)
    MurmurHash3_x64_128(data, size, i, &hash[i]);
  for(int i = 0; i < _HASH_NUM; i++) {
    int bit = hash[i]%(_FILTER_SIZE*8);
    if((b.filter[bit/64]&(1L<<(bit%64))) != (1L<<(bit%64))) {
      if(print) printf("QUERY : %s is not in filter\n", data);
      return 0;
    }
  }
  if(print) printf("QUERY : %s is in filter\n", data);
  return 1;
}

void BF_debug_hash(uint32_t *hash) {
  for(int i = 0; i < _HASH_NUM; i++) {
    int bit = hash[i]%(_FILTER_SIZE*8);
    int line = bit/64;
    int num = bit%64;
    printf("Bit number %d on line %d of filter\n", num, line);
  }
}

void BF_debug_filter(BF b) {
  printf("BEGIN FILTER\n");
  for(int i = 0; i < _FILTER_SIZE/8; i++) {
    printf("%d  ", i);
    print_binary(b.filter[i]);
  }
  printf("END FILTER\n");
}

void print_binary(uint64_t num) {
  for(int i = 63; i >= 0; i--) {
    if(num >= pow(2.0,(double)i)) {
      printf("1");
      num -= pow(2.0,(double)i);
    } else {
      printf("0");
    }
  }
  printf("\n");
}

int main() {
  BF b = BF_empty();
  char* data = "a";
  char* data2 = "aabab";
  BF_query(data, 1, b, 1);
  BF_add(data, 1, &b, 1, 1);
  BF_query(data, 1, b, 1);
  BF_query(data2, 5, b, 1);
  BF_add(data2, 5, &b, 1, 1);
  return 0;
}
