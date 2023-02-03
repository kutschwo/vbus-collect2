
//****************************************************************************
// kbhit.h
//
// (c) Hewell Technology Ltd. 2014
// 
// functions to handle Ctrl-C an other keys
//
//****************************************************************************


#ifndef KBHIT_H
#define KBHIT_H

extern int caughtSigQuit(void (*userSignalCallback)());
extern int catchSig(int sig);

#endif
