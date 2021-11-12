#include "statistics_collector.h"
#include "pipeline.h"
#include "executing_command.h"

StatisticsCollector::StatisticsCollector(size_t commands_count) {
	this->commands_count = commands_count;
	this->clc = 0;
	this->total_clc = 0;
}

void StatisticsCollector::increase_clock_cycles() {
	this->clc += 1;
}

void StatisticsCollector::add_total_clock_cycles(ClockCycles clc) {
	this->total_clc += clc;
}

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

void StatisticsCollector::print_stage(Pipeline::Stage stage) const {
	switch (stage) {
	case Pipeline::Stage::DECODE:
		std::cout << "DECODE";
		break;
	case Pipeline::Stage::FETCH_LEFT_OPERAND:
		std::cout << "FETCH_LEFT_OPERAND";
		break;
	case Pipeline::Stage::FETCH_RIGHT_OPERAND:
		std::cout << "FETCH_RIGHT_OPERAND";
		break;
	case Pipeline::Stage::EXECUTE:
		std::cout << "EXECUTE";
		break;
	case Pipeline::Stage::WRITE_BACK:
		std::cout << "WRITE_BACK";
		break;
	default:
		break;
	}
}

void StatisticsCollector::print_commands(const std::vector<Command> & commands) const {
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

void StatisticsCollector::print_statistics() const {
	const auto indent_form = std::setw(40);
	const auto indent_data = std::setw(10);
	std::cout << "\n" << indent_form << "RESULT:\n";

	std::cout << "\n" << indent_form << "Command count: ";
	std::cout << indent_data << this->commands_count;

	std::cout << "\n" << indent_form << "CLC count: ";
	std::cout << indent_data << this->clc;

	std::cout << "\n" << indent_form << "Average CLC for command executing: ";
	auto clc_per_command = static_cast<int>(std::round(this->clc / this->commands_count));
	std::cout << indent_data << clc_per_command;

	std::cout << "\n" << indent_form << "Total CLC without using pipeline: ";
	std::cout << indent_data << this->total_clc;

	std::cout << "\n" << indent_form << "Saved time percentage: ";
	auto saved_time_percentage = 100 - static_cast<int>(std::round(((this->clc * 1.0) / this->total_clc * 100)));
	std::cout << indent_data << saved_time_percentage << "%";

	std::cout << std::endl;
}

void StatisticsCollector::print_clc_state(const std::map<size_t, ExecutingCommand> & executing_commands) const {
	const auto indent_form = std::setw(10);
	const auto indent_data = std::setw(20);
	const auto indent_clc = std::setw(4);
	std::cout << "\n" << indent_form << "\nPIPELINE CYCLE #" << this->clc;
	for (size_t stage_key = 0; stage_key < Pipeline::STAGES_COUNT; ++stage_key) {
		std::cout << "\n" << indent_form << "Stage: ";
		std::cout << indent_data; print_stage(Pipeline::key_to_stage(stage_key));
		std::cout << indent_form << "CLC: ";
		if (executing_commands.contains(stage_key)) {			
			std::cout << indent_clc << executing_commands.find(stage_key)->second.clock_cycles();
		}
		else {
			std::cout << indent_clc << "#";
		}		
	}
	std::cout << std::endl;
}