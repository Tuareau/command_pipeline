#pragma once

#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <ctime>
#include <random>

using ClockCycles = time_t;

enum class OperandType {
	REGISTER,
	MEMORY,
};

class Command
{
public:
	enum class Type {
		FIRST,
		SECOND,
	};

private:
	Type type;
	OperandType left_operand_type;
	OperandType right_operand_type;
	ClockCycles clock_cycles;

public:
	Command();
	Command(const Command & other) = default;
	~Command() = default;

	Type type() const;
	OperandType left_operand_type() const;
	OperandType right_operand_type() const;

};

#endif