#ifndef CONFIG_H
#define CONFIG_H

//#define SAVEPASSWORD

//#define DEBUG_EVENTREF

//#define  SHIPPING

#ifdef SHIPPING
#define ROOT_PATH wxT(".")
#else
#define ROOT_PATH wxT("../../..")
#endif

#define IMG_ROOT_PATH ROOT_PATH wxT("/img/")

#define STR(x) wxT(#x)
#define IMG_PATH(img, typ) (IMG_ROOT_PATH STR(typ) wxT("/") STR(img) wxT(".") STR(typ))

#define CONFIG_FILEPATH "./Config.ini"


//#define DISCONNECTED

#endif