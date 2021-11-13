#pragma once

#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <string>
#include <sstream>

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
	static size_t commands_count;

private:
	std::string _name;
	Type _type;
	OperandType _left_operand_type;
	OperandType _right_operand_type;

public:
	Command();
	Command(const Command & other) = default;
	~Command() = default;

	Command & operator=(const Command & other) = default;

	const std::string & name() const;
	Type type() const;
	OperandType left_operand_type() const;
	OperandType right_operand_type() const;

	static Command generate_command();

};

#endif