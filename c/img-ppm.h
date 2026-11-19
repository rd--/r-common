#ifndef _COMMON_IMG_PPM_H
#define _COMMON_IMG_PPM_H

#include <stdio.h>

#include "int.h"

i32 img_write_ppm(const u8 *data, i32 w, i32 h, FILE *fp);
i32 img_write_ppm_file(const u8 *data, i32 w, i32 h, const char *name);
u8 *img_read_ppm(i32 *w, i32 *h, FILE *fp);
u8 *img_read_ppm_file(i32 *w, i32 *h, const char *name);

#endif
