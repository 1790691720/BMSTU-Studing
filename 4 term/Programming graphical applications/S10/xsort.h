typedef union {
  XSegment seg[1];
  XRectangle rec[1];
  XArc arc[1];
} XFragment; 

#define NGC 5
#define FGC 0
#define RGC 1
#define EGC 2
#define AGC 3
#define BGC 4

#define MINIFRAG 0
#define MAXIFRAG 1
#define MEANFRAG 2
#define DIFFFRAG 3
#define IDENFRAG 4
#define GRP2FRAG 5

#define MINSIZEX 4
#define MINSIZEY 4

int pass1(Display*, Window, GC*);
int photo();
int rebak();            
int rubin(XEvent*);
int rubout(XEvent*);
int rerub(XEvent*);
int fix(XEvent*);
int widewin();
int miniwin();
int fragcmp(const void*, const void*);
int refrag();
int near(int, int);
int cancet();
int purgextr(XFragment*, XFragment*);
int reggc(int);

int pass0(void**);
int miniextra();
int maxiextra();
int meanextra();
int diffextra();
int idenextra();
int grp2extra();
int rextra(int);
int isextra(int);

int fragon(XFragment*, int, int, int);
int difrag(XFragment*, XFragment*);
int tinyfrag(XFragment*);
int fragsize(XFragment*);
int frag0(XFragment*, int, int);
int fragvar(XFragment*, int, int);
int fragmaxix(XFragment*);
int fragmaxiy(XFragment*);
int fragover(XFragment*, XFragment*);
int fragextra(int (*[])());

int XFixes(Display*, Window, GC, XFragment*, int);
int XContour(Display*, Window, GC, XFragment*);
int XExtra(Display*, Window, GC, XFragment*);
int XFix(Display*, Window, GC, XFragment*);

int resmng(int, char*[]);
int canvas();
int gcing();
int dispatch();
int expo(XEvent*);
int rekey(XEvent*);
