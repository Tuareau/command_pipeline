#pragma once

#ifndef _EXECUTING_COMMAND_H_
#define _EXECUTING_COMMAND_H_

#include "command.h"

#include <ctime>

using ClockCycles = std::time_t;

class ExecutingCommand
{
private:
	Command _command;
	ClockCycles _clc;

public:
	explicit ExecutingCommand(const Command & cmd, ClockCycles clc = 1);
	~ExecutingCommand() = default;

	Command::Type type() const;
	OperandType left_operand_type() const;
	OperandType right_operand_type() const;

	ClockCycles clock_cycles() const;
	void decrease_clock_cycles();

	bool executed() const;
	const Command & command() const;

};

#endif
