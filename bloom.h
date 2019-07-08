#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "murmur3.h"

#define _FILTER_SIZE 128   //Size of bloom filter in BYTES
#define _HASH_NUM 19       //Number of hash functions

typedef struct {
  uint64_t filter[_FILTER_SIZE/8];
} BF;

BF BF_empty();

void BF_add(char *data, int size, BF *b, int print, int debug);

int BF_query(char *data, int size, BF b, int print);

void BF_debug_hash(uint32_t *hash);

void BF_debug_filter(BF b);

void print_binary(uint64_t num);
