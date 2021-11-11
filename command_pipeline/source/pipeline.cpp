#include "pipeline.h"
#include "executing_command.h"
#include "generator.h"

Pipeline::Pipeline(size_t commands_count) {
	for (size_t i = 0; i < commands_count; ++i) {
		auto cmd = Command::generate_command();
		this->commands_vector.push_back(cmd);
	}
}

size_t Pipeline::stage_to_key(const Stage stage) const {
	size_t idx = 0;
	switch (stage) {
	case Stage::DECODE:
		idx = 0;
		break;
	case Stage::FETCH_LEFT_OPERAND:
		idx = 1;
		break;
	case Stage::FETCH_RIGHT_OPERAND:
		idx = 2;
		break;
	case Stage::EXECUTE:
		idx = 3;
		break;
	case Stage::WRITE_BACK:
		idx = 4;
		break;
	default:
		throw std::logic_error("Pipeline::stage_to_index(): stage type mismatch");
		break;
	}
	return idx;
}

Pipeline::Stage Pipeline::key_to_stage(size_t key) const {
	Stage stage = Stage::DECODE;
	switch (key) {
	case 0:
		stage = Stage::DECODE;
		break;
	case 1:
		stage = Stage::FETCH_LEFT_OPERAND;
		break;
	case 2:
		stage = Stage::FETCH_RIGHT_OPERAND;
		break;
	case 3:
		stage = Stage::EXECUTE;
		break;
	case 4:
		stage = Stage::WRITE_BACK;
		break;
	default:
		throw std::logic_error("Pipeline::stage_to_index(): stage type mismatch");
		break;
	}
	return stage;
}

void Pipeline::run() {
	while (this->commands_vector.empty() != true) {
		this->run_cycle_clock();
	}
	//this->_stats_collector->show();
}

void Pipeline::run_cycle_clock() {
	this->try_insert_command();
	// executing instructions and shifting if executed
	for (size_t stage_key = STAGES_COUNT - 1; stage_key >= 0; --stage_key) {
		this->executing_commands[stage_key].decrease_clock_cycles();
		if (this->executing_commands[stage_key].executed()) {
			this->try_shift_command(stage_key);
		}
	}
}

void Pipeline::try_insert_command() {
	// check if there is no decoding instruction still executing
	auto decode_stage_key = this->stage_to_key(Stage::DECODE);
	auto decode_stage_command = this->executing_commands.find(decode_stage_key);

	// inserting next command to pipeline 1st stage
	if (decode_stage_command == this->executing_commands.end()) {
		const auto & next_command = this->commands_vector.back();
		this->executing_commands[decode_stage_key] = ExecutingCommand(next_command);
		this->commands_vector.pop_back();
	}
}

void Pipeline::try_shift_command(size_t key) {
	// nowhere to shift if there is the last stage
	if (key == this->stage_to_key(Stage::WRITE_BACK)) {
		return;
	}

	auto stage_command = this->executing_commands.find(key);
	if (stage_command == this->executing_commands.end()) {
		throw std::logic_error("Pipeline::try_shift_command(): trying to shift unexisting command");
	}

	auto next_stage_key = key + 1;
	auto next_stage_command = this->executing_commands.find(next_stage_key);

	// generate new clc for next stage
	auto clc {
		Generator::generate_clc(next_stage_command->second.command(), this->key_to_stage(next_stage_key))
	};

	// shift to next stage
	if (next_stage_command == this->executing_commands.end()) {
		this->executing_commands[next_stage_key] = ExecutingCommand(stage_command->second.command(), clc);
	}
	else if (next_stage_command->second.executed()) {		
		next_stage_command->second = ExecutingCommand(stage_command->second.command(), clc);
	}
}