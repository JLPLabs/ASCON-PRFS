#include <stdio.h>

#include "api.h"
#include "ascon.h"
#include "constants.h"
#include "permutations.h"
#include "printstate.h"
#include "round.h"
#include "word.h"

int crypto_prf(unsigned char* out, unsigned long long outlen,
               const unsigned char* in, unsigned long long inlen,
               const unsigned char* k);

void print_str(const char* label, const unsigned char* data, unsigned long long length);
void print_bstr(const char* label, const unsigned char* data, unsigned long long length);


int main(void) {
  unsigned char tag[8]  = {0, 0, 0, 0, 0, 0, 0, 0};
  unsigned char key[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  unsigned char msg[16] = {'C', 'y', 'c', 'l', 'o', 'n', 'e', 's', '2', '0', '2', '4', ' ', 00, 00, 00};
  int nonces[4] = {1000, 20000, 100000, 1000000};

  printf("Demonstration of ASCON-PRFS\n");
  print_str ("base msg (ascii) ", msg, 16);
  print_bstr("base msg (hex)   ", msg, 16);
  printf("\nnote: the last three bytes of the base message are updated with a nonce value\n");
  printf("and then a tag generated.\n");

  int i;
  for (i=0; i<4; i++) {
    msg[15] = nonces[i]         & 0xff;
    msg[14] = (nonces[i] >> 8)  & 0xff;
    msg[13] = (nonces[i] >> 16) & 0xff;

    printf("nonces[%d] = %7d  ", i, nonces[i]); 
    int ret = crypto_prf(tag, 8, msg, 16, key);
    if (ret == 0) {
      print_bstr("tag = ", tag, 8);
    } else {
      printf("error; ret = %d\n", ret);
    }
  }
  return 0;
}

// print as bytes
void print_bstr(const char* label, const unsigned char* data, unsigned long long length) {
  unsigned long long i;
  printf("%s: ", label);

  for (i = 0; i < length; i++) printf("%02x", data[i]);

  printf("\n");
}

// print as chars
void print_str(const char* label, const unsigned char* data, unsigned long long length) {
  unsigned long long i;
  printf("%s: [", label);

  for (i = 0; i < length; i++) printf("%c", data[i]);

  printf("]\n");
}
