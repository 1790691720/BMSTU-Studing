#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <string.h>
#include <stdlib.h>
#include "xsort.h"

#define FRAGSIZ sizeof(XFragment)

static Display* dpy;
static Window win;
static GC* gc;

static XFragment ftmp[1];
static XFragment bak[2];
static XFragment* frag;
static int nfrag=0;
static int extra[2]={0, 0};
static int GGC=FGC;

int pass1(Display* d, Window w, GC* g) {
  dpy = d; win = w; gc = g;
  return(0);
}

int photo() {
  static void* p[4];
  p[0] = bak; p[1] = extra, p[2] = frag; p[3] = &nfrag;
  pass0(p);
  return(nfrag);
}

int XFixes(Display* dpy, Window win , GC gc, XFragment* f, int n) {
  int i;
  for(i = 0; i < n; i++, f++) XFix(dpy, win, gc, f);
  return(0);
}

int rebak() {
  if(nfrag > 0) memcpy(bak, frag+extra[0], FRAGSIZ);
  if(extra[1] > extra[0]) memcpy(bak+1, frag+extra[1], FRAGSIZ);
  return(0);
}

int rubin(XEvent* ev) {
  XGrabPointer(dpy, win, False, (ButtonReleaseMask | Button1MotionMask), 
               GrabModeAsync, GrabModeAsync, win, None, CurrentTime);
  rebak();
  if(ev->xbutton.button != Button1) return(~Button1);
  frag0(ftmp, ev->xbutton.x, ev->xbutton.y);
  return(Button1);
}

int near(int x, int y) {
  int i;
  for(i = 0; i < nfrag; i++)
    if(fragon(frag+i, x, y, isextra(i)) > 0) break;
  return(i);
}

int rubout(XEvent* ev) {
  int i;
  if(nfrag < 1) return(0);
  if((i = near(ev->xbutton.x, ev->xbutton.y)) == nfrag) return(nfrag);
  if((i == extra[0]) || (i == extra[1])) XExtra(dpy, win, gc[BGC], frag+i);
  XFix(dpy, win, gc[BGC], frag+i);
  XFlush(dpy);
  if(--nfrag > i) memmove((frag + i), (frag + i + 1), (nfrag - i)*FRAGSIZ);
  frag = realloc(frag, nfrag*FRAGSIZ);
  if(nfrag == 0) frag = NULL;
  return(nfrag);
}

int rerub(XEvent* ev) {
  static int x, y;
  XContour(dpy, win, gc[RGC], ftmp);
  if(fragvar(ftmp, ev->xmotion.x, ev->xmotion.y) < 0) {
    XContour(dpy, win, gc[RGC], ftmp);
    return(XWarpPointer(dpy, None, win, 0, 0, 0, 0, x, y));
  }
  XContour(dpy, win, gc[RGC], ftmp);
  x = ev->xmotion.x; y =  ev->xmotion.y;
  return(0);
}

int reggc(int g) {
  return(GGC = g);
}

int refrag() {
  int n;
  if((n = extra[0]) > 0) XFixes(dpy, win, gc[FGC], frag, n);
  if((n = (extra[1] - extra[0])) > 1) XFixes(dpy, win, gc[FGC], (frag + extra[0] + 1), n - 1);
  if((n = (nfrag - extra[1])) > 1) XFixes(dpy, win, gc[GGC], (frag + extra[1] + 1), n - 1);
  if(nfrag > 0) XExtra(dpy, win, gc[EGC], frag + extra[0]);
  if(extra[1] > extra[0]) XExtra(dpy, win, gc[EGC], frag + extra[1]);
  return(nfrag);
}

int widewin() {
  int w, h;
  XWindowAttributes attr;
  XGetWindowAttributes(dpy, win, &attr);
  w = fragmaxix(ftmp); 
  h = fragmaxiy(ftmp);
  if((w < attr.width) && (h < attr.height)) return(0);
  if(w < attr.width) w = attr.width;
  if(h < attr.height) h = attr.height;
  XResizeWindow(dpy, win, w, h); 
  return(0);
}

int cancet() {
  int i;
  if(tinyfrag(ftmp) > 0) return(1);
  for(i=0; i < nfrag; i++)
    if(fragover(ftmp, frag + i) > 0) return(1);
  return(0);
}

int fix(XEvent* ev) {
  int w, h;
  XUngrabPointer(dpy, CurrentTime);
  if(ev->xbutton.button != Button1) return(nfrag);
  fragvar(ftmp, ev->xbutton.x, ev->xbutton.y);
  XContour(dpy, win, gc[RGC], ftmp);
  XFlush(dpy);
  if(cancet() > 0) return(0);
  widewin(w, h);
  frag = realloc(frag, (nfrag + 1)*FRAGSIZ);
  memcpy((frag+nfrag), ftmp, FRAGSIZ);
  if(++nfrag > 1) qsort(frag, nfrag, FRAGSIZ, fragcmp);
  return(nfrag);
}

int purgextr(XFragment* b, XFragment* e) {
  if(memcmp(b, e, FRAGSIZ) != 0) {
    XExtra(dpy, win, gc[BGC], b);
    XFix(dpy, win, gc[BGC], e);
  }
  return(0);
}

int fragcmp(const void* s1, const void* s2) {
  return(difrag((XFragment*) s1, (XFragment*) s2));
}

int miniwin() {
  XSizeHints hint;
  int i=0;
  unsigned w=128;
  unsigned h=128;
  int xm, ym;
  for(i=0; i < nfrag; i++) {
    if((xm = fragmaxix(frag+i)) > w) w = xm;
    if((ym = fragmaxiy(frag+i)) > h) h = ym;
  }
  hint.min_width = w; hint.min_height = h;
  hint.flags = PMinSize;
  XSetNormalHints(dpy, win, &hint);
  return(0);
} 
