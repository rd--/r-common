#ifndef _COMMON_SF_AU_H
#define _COMMON_SF_AU_H

#include "float.h"
#include "int.h"

void write_au_f32(const char *nm, i32 nc, i32 nf, i32 sr, const f32 *d);
f32 *read_au_f32(const char *nm, i32 *nc, i32 *nf, i32 *sr);

#endif
