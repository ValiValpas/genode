/*
 * \brief  NOVA-specific 'Native_cpu' setup
 * \author Christian Prochaska
 * \date   2016-05-13
 */

/*
 * Copyright (C) 2016-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */


/* Genode includes */
#include <nova_native_cpu/client.h>

/* Cpu_sampler includes */
#include "cpu_session_component.h"
#include "cpu_thread_component.h"


namespace Cpu_sampler {
	class Native_cpu_component;
}


using namespace Genode;


class Cpu_sampler::Native_cpu_component : public Rpc_object<Cpu_session::Native_cpu,
                                                            Native_cpu_component>
{
	private:

		Cpu_session_component &_cpu_session_component;
		Nova_native_cpu_client _nova_native_cpu;

	public:

		Native_cpu_component(Cpu_session_component &cpu_session_component)
		: _cpu_session_component(cpu_session_component),
		  _nova_native_cpu(_cpu_session_component.parent_cpu_session().native_cpu())
		{
			_cpu_session_component.thread_ep().manage(this);
		}

		~Native_cpu_component()
		{
			_cpu_session_component.thread_ep().dissolve(this);
		}

		void thread_type(Thread_capability thread_cap,
		                 Cpu_session::Native_cpu::Thread_type thread_type,
		                 Cpu_session::Native_cpu::Exception_base exception_base) override
		{
			auto lambda = [&] (Cpu_sampler::Cpu_thread_component *cpu_thread) {
				_nova_native_cpu.thread_type(cpu_thread->parent_thread(),
				                             thread_type, exception_base);
			};

			_cpu_session_component.thread_ep().apply(thread_cap, lambda);
		}
};


Capability<Cpu_session::Native_cpu>
Cpu_sampler::Cpu_session_component::_setup_native_cpu()
{
	Native_cpu_component *native_cpu_component =
		new (_md_alloc) Native_cpu_component(*this);

	return native_cpu_component->cap();
}


void Cpu_sampler::Cpu_session_component::_cleanup_native_cpu()
{
	Native_cpu_component *native_cpu_component = nullptr;
	_thread_ep.apply(_native_cpu_cap,
	                 [&] (Native_cpu_component *c) { native_cpu_component = c; });

	if (!native_cpu_component) return;

	destroy(_md_alloc, native_cpu_component);
}
