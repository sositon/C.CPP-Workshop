
#ifndef CIPHER
#define CIPHER
#define DEF_LETTERS_SIZE 26
#define LAST_LOWER_LETTER 122
#define LAST_CAPITAL_LETTER 90

void encode (char *p, int k)
{
  k = k % DEF_LETTERS_SIZE;
  if (islower (*p)){
    if (*p <= LAST_LOWER_LETTER - k){
      *p += k;
    }
    else {
      *p += k - DEF_LETTERS_SIZE;
    }
  }
  else if (isupper(*p)){
    if (*p <= LAST_CAPITAL_LETTER - k){
      *p += k;
    }
    else {
      *p += k - DEF_LETTERS_SIZE;
    }
  }

}

void decode (char *p, int k)
{
  encode (p, DEF_LETTERS_SIZE- (k % DEF_LETTERS_SIZE));
}

#endif