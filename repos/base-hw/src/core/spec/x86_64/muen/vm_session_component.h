/*
 * \brief  Core-specific instance of the VM session interface
 * \author Stefan Kalkowski
 * \date   2015-06-03
 */

/*
 * Copyright (C) 2015-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _CORE__SPEC__X86_64__MUEN__VM_SESSION_COMPONENT_H_
#define _CORE__SPEC__X86_64__MUEN__VM_SESSION_COMPONENT_H_

/* Genode includes */
#include <base/allocator.h>
#include <base/rpc_server.h>
#include <vm_session/vm_session.h>
#include <dataspace/capability.h>

/* Core includes */
#include <dataspace_component.h>
#include <object.h>
#include <kernel/vm.h>

namespace Genode {
	class Vm_session_component;
}

class Genode::Vm_session_component
: public Genode::Rpc_object<Genode::Vm_session>,
  private Kernel_object<Kernel::Vm>
{
	private:

		Vm_state _state;

	public:

		Vm_session_component(Rpc_entrypoint*, size_t) : _state() { }
		~Vm_session_component() { }

		using Genode::Rpc_object<Genode::Vm_session>::cap;


		/**************************
		 ** Vm session interface **
		 **************************/

		Dataspace_capability cpu_state(void) { return Dataspace_capability(); }

		void exception_handler(Signal_context_capability handler)
		{
			if (!create(&_state, Capability_space::capid(handler), nullptr))
				warning("Cannot instantiate vm kernel object, "
				        "invalid signal context?");
		}

		void run(void)
		{
			if (Kernel_object<Kernel::Vm>::_cap.valid())
				Kernel::run_vm(kernel_object());
		}

		void pause(void)
		{
			if (Kernel_object<Kernel::Vm>::_cap.valid())
				Kernel::pause_vm(kernel_object());
		}

		void attach(Dataspace_capability, addr_t) {}
		void attach_pic(addr_t) {}
		void detach(addr_t, size_t) {}
};

#endif /* _CORE__SPEC__X86_64__MUEN__VM_SESSION_COMPONENT_H_ */
