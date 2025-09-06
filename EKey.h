#ifndef __EKEY_H__
#define __EKEY_H__
typedef enum
{
    eKey_None = 0,
    K1,
    K2,
    K3,
    K4
}ekey;

ekey scan_ekey();

#endif