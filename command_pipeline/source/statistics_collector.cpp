#include "statistics_collector.h"

void StatisticsCollector::print_command_type(const Command & cmd) const {
	if (cmd.type() == Command::Type::FIRST) {
		std::cout << "FIRST";
	}
	else {
		std::cout << "SECOND";
	}
}

void StatisticsCollector::print_operand_type(const OperandType type) const {
	if (type == OperandType::REGISTER) {
		std::cout << "REGISTER";
	}
	else {
		std::cout << "MEMORY";
	}
}

void StatisticsCollector::print_commands(std::vector<Command> & commands) const {
	const auto indent_form = std::setw(20);
	const auto indent_data = std::setw(10);
	std::cout << "\n" << indent_form << "COMMANDS:\n";
	auto cnt = 0;
	for (const auto & cmd : commands) {
		std::cout << "\n" << indent_form << "C#" << ++cnt;
		std::cout << "\n" << indent_form << "Type: ";
		std::cout << indent_data; print_command_type(cmd);
		std::cout << "\n" << indent_form << "Left operand: ";
		std::cout << indent_data; print_operand_type(cmd.left_operand_type());
		std::cout << "\n" << indent_form << "Right operand: ";
		std::cout << indent_data; print_operand_type(cmd.right_operand_type());
		std::cout << std::endl;
	}
}