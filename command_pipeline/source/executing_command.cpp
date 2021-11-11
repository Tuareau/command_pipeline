#include "executing_command.h"

ExecutingCommand::ExecutingCommand() {
	this->_command = Command();
	this->_clc = 0;
}

ExecutingCommand::ExecutingCommand(const Command & cmd, ClockCycles clc) {
	this->_command = cmd;
	this->_clc = clc;
}

Command::Type ExecutingCommand::type() const {
	return _command.type();
}


OperandType ExecutingCommand::left_operand_type() const {
	return _command.left_operand_type();
}


OperandType ExecutingCommand::right_operand_type() const {
	return _command.right_operand_type();
}

ClockCycles ExecutingCommand::clock_cycles() const {
	return this->_clc;
}

void ExecutingCommand::decrease_clock_cycles() {
	if (this->_clc <= 0) {
		this->_clc = 0;
	}
	else {
		this->_clc -= 1;
	}
}

bool ExecutingCommand::executed() const {
	return this->_clc == 0;
}

const Command & ExecutingCommand::command() const {
	return this->_command;
}