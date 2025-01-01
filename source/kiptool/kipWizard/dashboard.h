#pragma once

#include "../params/customize.h"
#include "../params/param.h"
#include "../params/table.h"

void showDashboard(const CustomizeTable* cust, const Params* cpuParams[], const Tables* cpuTables[], const Params* gpuParams[], const Tables* gpuTables[],
                   const Params* ramParams[], const Tables* ramTables[], const Tables* mehTables[]);
