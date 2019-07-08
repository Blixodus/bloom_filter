#include "bloom.h"

int test() {
  printf("Beginning test sequence\n");
  printf("Testing to be implemented\n");
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

void help() {
  printf("Commands : add, query, debug, exit, help\nUsage : add word, query word\n");
}

int main(int argc, char *argv[]) {
  if(argc > 1) {
    if(!strcmp(argv[1], "test") || !strcmp(argv[1], "-t")) test();
    if(!strcmp(argv[1], "interactive") || !strcmp(argv[1], "-i")) interactive();
  } else {
    printf("Please give argument 'interactive'/'-i' or 'test'/'-t'...\n");
  }
  return 0;
}
