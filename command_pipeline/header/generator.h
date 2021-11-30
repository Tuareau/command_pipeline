#pragma once

#ifndef _GENERATOR_H_
#define _GENERATOR_H_

#include "command.h"
#include "pipeline.h"

#include <random>
#include <ctime>
#include <stdexcept>

using ClockCycles = std::time_t;

class Generator
{
private:
	static double generate_register_adressing_probability();
	static double generate_first_command_type_probability();

	static ClockCycles generate_memory_access_clc(const OperandType op_type);
	static ClockCycles generate_execution_clc(const Command::Type cmd_type);

public:
	static Command::Type generate_command_type();
	static OperandType generate_operand_type();

	static ClockCycles generate_clc(const Command & cmd, Pipeline::Stage stage);

};

#endif