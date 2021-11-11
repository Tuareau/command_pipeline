#include "command.h"
#include "generator.h"

Command::Command() {
	this->_type = Type::FIRST;
	this->_left_operand_type = OperandType::REGISTER;
	this->_right_operand_type = OperandType::REGISTER;
}

Command Command::generate_command() {
	Command cmd;	
	cmd._type = Generator::generate_command_type();
	cmd._left_operand_type = Generator::generate_operand_type();
	cmd._right_operand_type = Generator::generate_operand_type();
	return cmd;
}

Command::Type Command::type() const {
	return this->_type;
}

OperandType Command::left_operand_type() const {
	return this->_left_operand_type;
}

OperandType Command::right_operand_type() const {
	return this->_right_operand_type;
}