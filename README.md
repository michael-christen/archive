mojo_interface
==============

Modification of mojo fpga and atmega32u4 processor code base

Lock is:
	uint_reg_t CurrentGlobalInt = GetGlobalInterruptMask();
	GlobalInterruptDisable();
	<stuff>
	SetGlobalInterruptMask(CurrentGlobalInt);