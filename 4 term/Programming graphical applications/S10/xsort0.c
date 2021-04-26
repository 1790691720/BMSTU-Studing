#include <values.h> 
#include <X11/Xlib.h>
#include "xsort.h"

static int* nfrag; 
static XFragment* frag; 
static int* extra;
static XFragment* bak;

int pass0(void* p[]) {
  bak = (XFragment* ) p[0];
  extra = (int* ) p[1];
  frag = (XFragment* ) p[2];
  nfrag = (int*) p[3];
  return(0);
}

int miniextra() {
  extra[0] = extra[1] = 0;
  return(MINIFRAG);
}

int maxiextra() {
  extra[0] = extra[1] = (*nfrag - 1);
  return(MAXIFRAG);
}

int meanextra() {
  extra[0] = extra[1] = ((*nfrag)/2);
  return(MEANFRAG);
}

int diffextra() {
  extra[0] = 0; extra[1] = *nfrag - 1;
  return(DIFFFRAG);
}

int idenextra() {
  int i, j;
  int d;
  unsigned dmin=MAXINT;
  int e[2];
  extra[0] = extra[1] = 0;
  for(i = 0, j = 1; j < nfrag[0]; i++, j++) {
    if((d = difrag(frag + j, frag + i)) < 0) d -= d;
    if(d < dmin) {
      extra[0] = i; extra[1] = j;
      dmin = d;
    }
  }
  return(IDENFRAG);
}

int grp2extra() {
  extra[0] = extra[1] = (nfrag[0] / 2);
  reggc(AGC);
  return(GRP2FRAG);
}

int rextra(int n) {
  static int (*extrafunc[])()  = {
               miniextra, maxiextra, meanextra, 
               diffextra, idenextra, grp2extra
  };
  fragextra(extrafunc);
  purgextr(bak, frag+extra[0]);
  if(extra[0] != extra[1]) purgextr(bak+1, frag+extra[1]);
  return(0);
}

int isextra(int i) {
  return((i == extra[0]) || (i == extra[1]));
}
