#include "bloom.h"

/* Create a new empty bloom filter */
BF BF_empty() {
  BF b;
  memset(b.filter, 0, _FILTER_SIZE);
  return b;
}

/* Add more data to the filter */;
void BF_add(char *data, BF *b) {
  uint32_t hash[_HASH_NUM+(4-(_HASH_NUM%4))];
  for(int i = 0; i < _HASH_NUM; i+=4)
    MurmurHash3_x64_128(data, sizeof(data), i, &hash[i]);
  for(int i = 0; i < _HASH_NUM; i++) {
    int bit = hash[i]%(_FILTER_SIZE*8);
    b->filter[bit/64] |= 1L<<(bit%64);
  }      
}

/* Filter requested data */
int BF_query(char *data, BF b) {
  uint32_t hash[_HASH_NUM+(4-(_HASH_NUM%4))];
  for(int i = 0; i < _HASH_NUM; i+=4)
    MurmurHash3_x64_128(data, sizeof(data), i, &hash[i]);
  for(int i = 0; i < _HASH_NUM; i++) {
    int bit = hash[i]%(_FILTER_SIZE*8);
    if((b.filter[bit/64]&(1L<<(bit%64))) != (1L<<(bit%64))) return 0;
  }
  return 1;
}

void BF_debug_filter(BF b) {
  printf("BEGIN FILTER\n");
  for(int i = 0; i < _FILTER_SIZE/8; i++) {
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
  printf("%d\n", BF_query(data, b));
  BF_add(data, &b);
  BF_debug_filter(b);
  printf("%d\n", BF_query(data, b));
  printf("%d\n", BF_query(data2, b));
  BF_add(data2, &b);
  BF_debug_filter(b);
  return 0;
}
