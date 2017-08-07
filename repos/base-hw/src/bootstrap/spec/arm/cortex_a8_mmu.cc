/*
 * \brief   MMU initialization for Cortex A8
 * \author  Stefan Kalkowski
 * \date    2015-12-09
 */

/*
 * Copyright (C) 2015-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <platform.h>

void Bootstrap::Platform::enable_mmu()
{
	Cpu::Sctlr::init();
	Cpu::enable_mmu_and_caches((addr_t)core_pd->table_base);
}
