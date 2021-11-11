#pragma once

#ifndef _COMMAND_H_
#define _COMMAND_H_

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
	Type _type;
	OperandType _left_operand_type;
	OperandType _right_operand_type;

public:
	Command();
	Command(const Command & other) = default;
	~Command() = default;

	Command & operator=(const Command & other) = default;

	Type type() const;
	OperandType left_operand_type() const;
	OperandType right_operand_type() const;

	static Command generate_command();

};

#endif