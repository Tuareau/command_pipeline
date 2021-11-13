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
	const auto cmd_form = std::setw(7);
	const auto cmd_type_form = std::setw(13);
	const auto cmd_operand_form = std::setw(20);

	const auto indent_title = std::setw(20);
	std::cout << "\n" << indent_title << "COMMANDS:\n";

	std::cout << "\n" << cmd_form << "CMD#";
	std::cout << cmd_type_form << "CMD TYPE";
	std::cout << cmd_operand_form << "CMD LEFT OPRD";
	std::cout << cmd_operand_form << "CMD RIGHT OPRD" << std::endl;

	for (const auto & cmd : commands) {
		std::cout << cmd_form << cmd.name();
		std::cout << cmd_type_form; print_command_type(cmd);
		std::cout << cmd_operand_form; print_operand_type(cmd.left_operand_type());
		std::cout << cmd_operand_form; print_operand_type(cmd.right_operand_type());
		std::cout << std::endl;
	}
}

void StatisticsCollector::print_statistics() const {

	const auto table_form = std::setw(15);

	const auto title_form = std::setw(20);
	std::cout << "\n" << title_form << "RESULT:\n";

	std::cout << "\n" << table_form << "CMD COUNT";
	std::cout << table_form << "CLC COUNT";
	std::cout << table_form << "AVERAGE CLC";
	std::cout << table_form << "TOTAL CLC";
	std::cout << table_form << "SAVED TIME" << std::endl;

	std::cout << table_form << this->commands_count;
	std::cout << table_form << this->clc;
	auto clc_per_command = static_cast<int>(std::round(this->clc / this->commands_count));
	std::cout << table_form << clc_per_command;
	std::cout << table_form << this->total_clc;
	auto saved_time_percentage = 100 - static_cast<int>(std::round(((this->clc * 1.0) / this->total_clc * 100)));
	std::cout << table_form << (std::stringstream() << saved_time_percentage << "%").str();
	std::cout << std::endl;
}

void StatisticsCollector::print_clc_state(const std::map<size_t, ExecutingCommand> & executing_commands) const {
	const auto cmd_form = std::setw(7);
	const auto stage_form = std::setw(20);
	const auto clc_form = std::setw(5);

	const auto indent_title = std::setw(20);
	std::cout << "\n" << indent_title << "\nPIPELINE CYCLE #" << this->clc;

	std::cout << "\n\n" << stage_form << "STAGE";
	std::cout << cmd_form << "CMD#";
	std::cout << clc_form << "CLC" << std::endl;

	for (size_t stage_key = 0; stage_key < Pipeline::STAGES_COUNT; ++stage_key) {
		std::cout << stage_form; print_stage(Pipeline::key_to_stage(stage_key));
		if (executing_commands.contains(stage_key)) {		
			std::cout << cmd_form << executing_commands.find(stage_key)->second.command().name();
			std::cout << clc_form << executing_commands.find(stage_key)->second.clock_cycles();
		}
		else {
			std::cout << cmd_form << "-";
			std::cout << clc_form << "-";
		}
		std::cout << std::endl;	
	}

}