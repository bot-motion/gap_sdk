#ifndef __RESIZEKERNEL_H__
#define __RESIZEKERNEL_H__

#include "AutoTilerLibTypes.h"
#include "ResizeBasicKernels.h"
#define _Resize_L1_Memory_SIZE 39288
#define _Resize_L2_Memory_SIZE 0
extern char *Resize_L1_Memory; /* Size given for generation: 40000 bytes, used: 39288 bytes */
extern char *Resize_L2_Memory; /* Size used for generation: 0 bytes */
extern void ResizeImage(
		unsigned char * In,
		unsigned char * Out);
#endif
