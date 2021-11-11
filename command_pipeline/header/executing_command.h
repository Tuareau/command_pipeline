#pragma once

#ifndef _EXECUTING_COMMAND_H_
#define _EXECUTING_COMMAND_H_

#include "command.h"

class ExecutingCommand
{
private:
	Command * _command;
	ClockCycles _clc;

public:
	explicit ExecutingCommand(Command * cmd, ClockCycles clc = 1);
	~ExecutingCommand() = default;

	Command::Type type() const;
	OperandType left_operand_type() const;
	OperandType right_operand_type() const;

	ClockCycles clock_cycles() const;
	void decrease_clock_cycles();

	bool is_executed() const;

};

#endif
