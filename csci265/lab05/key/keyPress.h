
#ifndef keyPress_exists
#define keyPress_exists

#include <string>
using namespace std;

// if no key has been pressed return false
// otherwise copy the character to c and return true
bool keyQuick(char &c);

// if no key has been pressed return false,
// otherwise set the both classification type (keyType)
//    and the key character (c) and return true
// the classification keyTypes are:
bool keyPress(char &c, string &keyType);

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

#endif

