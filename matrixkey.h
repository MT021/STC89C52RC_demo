#ifndef __MATRIXKEY_H__
#define __MATRIXKEY_H__

typedef enum {
    mKey_None = 0,
    mKey1,
    mKey2,
    mKey3,
    mKey4,
    mKey5,
    mKey6,
    mKey7,
    mKey8,
    mKey9,
    mKey10,
    mKey11,
    mKey12,
    mKey13,
    mKey14,
    mKey15,
    mKey16
} mkey;

mkey matrix_key_scan();

#endif