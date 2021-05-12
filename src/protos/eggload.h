#pragma once

#include "egg.h"

typedef __attribute__((sysv_abi)) void(*egg_kernel_entry)(egg_t*);

void load_egg_kernel();