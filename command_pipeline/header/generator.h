#pragma once

#ifndef _GENERATOR_H_
#define _GENERATOR_H_

#include "command.h"

#include <random>
#include <ctime>
#include <stdexcept>

using ClockCycles = std::time_t;

class Generator
{
private:
	double generate_register_adressing_probability() const;
	double generate_first_command_type_probability() const;

public:
	Generator();

	Command::Type generate_command_type() const;
	OperandType generate_operand_type() const;

	ClockCycles generate_second_type_command_clc() const;
	ClockCycles generate_memory_access_clc() const;

};

#endif