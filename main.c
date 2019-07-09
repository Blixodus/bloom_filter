#include "bloom.h"

int test(int test_size) {
  printf("Beginning test sequence\n");
  printf("Using %d hash functions\n", _HASH_NUM);
  printf("Using %d bytes for Bloom filter\n", _FILTER_SIZE);
  printf("Filling filter with %d elements\n", test_size);

  return 0;

  char buffer[100];
  for(int i = 0; i < test_size; i++) {
    itoa(i, buffer, 2);
  }
}

void help() {
  printf("Commands : add, query, debug, exit, help\n");
  printf("Usage : add word, query word\n");
}

void interactive() {
  printf("Beginning interactive session (write help for help)\n");
  BF b = BF_empty();
  char instr[10];
  char code[100];
  int len;
  int debug = 0;
  while(1) {
    printf("> ");
    scanf("%s", instr);
    if(!strcmp(instr, "add")) {
      scanf("%s", code);
      BF_add(code, strlen(code), &b, 1, debug);
    } else if(!strcmp(instr, "query")) {
      scanf("%s", code);
      BF_query(code, strlen(code), b, 1);
    } else if(!strcmp(instr, "debug")) {
      debug = 1-debug;
      printf("Debug is now on state %d\n", debug);
    } else if(!strcmp(instr, "exit")) {
      printf("Quitting...\n");
      break;
    } else if(!strcmp(instr, "help")) {
      help();
    }
  }
}

int main(int argc, char *argv[]) {
  int test_size = (argc > 2)?atoi(argv[2]):100;
  if(argc > 1) {
    if(!strcmp(argv[1], "test") || !strcmp(argv[1], "-t")) test(test_size);
    if(!strcmp(argv[1], "interactive") || !strcmp(argv[1], "-i")) interactive();
  } else {
    printf("Please give argument 'interactive'/'-i' or 'test'/'-t'...\n");
  }
  return 0;
}
