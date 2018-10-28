#include <termios.h>
#include <unistd.h>  
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>
#include "keyPress.h"
using namespace std;

// if no key has been pressed return false
// otherwise copy the character to c and return true
bool keyQuick(char &c)
{
    // remember the previous terminal settings
    struct termios original;
    tcgetattr(0,&original);

    // setup new temporary values
    struct termios temporary = original;
    temporary.c_lflag &= ~ICANON; // toggle off eof/eoln/kill/etc
    temporary.c_lflag &= ~ECHO;   // toggle off keyboard echo
    temporary.c_lflag &= ~ISIG;   // toggle off interrupt/suspend/quit
    temporary.c_cc[VMIN] = 1;     // min characters for successful read
    temporary.c_cc[VTIME] = 0;    // timeout duration in deciseconds

    // apply the temporary settings
    tcsetattr(0, TCSANOW, &temporary);

    // check for a key hit waiting to be processed
    unsigned char newCh;
    int numRead;
    temporary.c_cc[VMIN]=0;
    tcsetattr(0, TCSANOW, &temporary);
    numRead = read(0,&newCh,1);
    temporary.c_cc[VMIN]=1;
    tcsetattr(0, TCSANOW, &temporary);

    // if the read actually captured characters, 
    //    copy the value read in, reset the terminal, 
    //    and return true
    // otherwise reset the terminal and return false
    if(numRead > 0) {
        c = (char)(newCh);
        tcsetattr(0, TCSANOW, &original);
        return true;
    } else {
        tcsetattr(0, TCSANOW, &original);
        return false;
    }
}

// if no key has been pressed return false,
// otherwise set the classification type and character
//    and return true
bool keyPress(char &c, string &keyType)
{
    if (keyQuick(c))  {
        if (isalpha(c)) keyType = "KeyAlpha";
        else if (isdigit(c)) keyType = "KeyDigit";
        else if (isspace(c)) keyType = "KeySpace";
        else if (ispunct(c)) keyType = "KeyPunct";
        else if (c == '\127') keyType = "KeyBackSpace";
        else if ((int)(c) == 27) {
           keyType = "KeyEscape";
           if (keyQuick(c)) {
              // treat it as one of the key combo cases
              // (arrows, page up/down, etc)
              if (c == '0') {
                 if (keyQuick(c)) {
                    // H is Home key, F is End key
                    if (c == 'H') keyType = "KeyHome";
                    else if (c == 'F') keyType = "KeyEnd";
                 }
              } else if (c == '[') {
                 if (keyQuick(c)) {
                    if (c == 'A') keyType = "KeyUArrow";
                    else if (c == 'B') keyType = "KeyDArrow";
                    else if (c == 'C') keyType = "KeyRArrow";
                    else if (c == 'D') keyType = "KeyLArrow";
                    else if (c == '1') {
                       if (keyQuick(c)) {
                          if (c == '~') {
                             keyType = "KeyHome";
                          } else {
                             char closer;
                             if (keyQuick(closer) && (closer == '~')) {
                                if (c == '1') keyType = "KeyF1";
                                else if (c == '2') keyType = "KeyF2";
                                else if (c == '3') keyType = "KeyF3";
                                else if (c == '4') keyType = "KeyF4";
                                else if (c == '5') keyType = "KeyF5";
                                else if (c == '7') keyType = "KeyF6";
                                else if (c == '8') keyType = "KeyF7";
                                else if (c == '9') keyType = "KeyF8";
                             }
                          }
                       }
                    } else if (c == '2') {
                       if (keyQuick(c)) {
                          if (c == '~') {
                             keyType = "KeyInsert";
                          } else {
                             char closer;
                             if (keyQuick(closer) && (closer == '~')) {
                                if (c == '0') keyType = "KeyF9";
                                else if (c == '1') keyType = "KeyF10";
                                else if (c == '3') keyType = "KeyF11";
                                else if (c == '4') keyType = "KeyF12";
                             }
                          }
                       }
                    } else if (c == '3') {
                       if (keyQuick(c) && (c == '~')) 
                          keyType = "KeyDelete";
                    } else if (c == '4') {
                       if (keyQuick(c) && (c == '~')) 
                          keyType = "KeyEnd";
                    } else if (c == '5') {
                       if (keyQuick(c) && (c == '~')) 
                          keyType = "KeyPageUp";
                    } else if (c == '6') {
                       if (keyQuick(c) && (c == '~')) 
                          keyType = "KeyPageDown";
                    }
                 }
              }
           }
        } else keyType = "KeyOther";
        return true;
    } else {
        return false;
    }
}

/*****************************************************
   The names that keyType might be assigned include
       KeyAlpha, KeyDigit, KeySpace, KeyPunct, KeyBackSpace,
       KeyEscape, KeyHome, KeyEnd, KeyUArrow, KeyDArrow,
       KeyLArrow, KeyRArrow, KeyDelete, KeyEnd, KeyPageUp,
       KeyPageDown, KeyInsert, KeyF1, ... , KeyF12, KeyOther
   
   Keys it still can't handle include: 
        num lock, caps lock, scroll lock,
        pause, printscreen, windows key, control, shift, and alt.

 *****************************************************/

