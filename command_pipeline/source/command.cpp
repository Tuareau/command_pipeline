#include "command.h"
#include "generator.h"

size_t Command::commands_count = 0;

Command::Command() {
	this->_type = Type::FIRST;
	this->_left_operand_type = OperandType::REGISTER;
	this->_right_operand_type = OperandType::REGISTER;
	this->_name = (std::stringstream() << "cmd#" << this->commands_count).str();
	this->commands_count += 1;
}

Command Command::generate_command() {
	Command cmd;
	cmd._type = Generator::generate_command_type();
	cmd._left_operand_type = Generator::generate_operand_type();
	cmd._right_operand_type = Generator::generate_operand_type();
	return cmd;

}

const std::string & Command::name() const {
	return this->_name;
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