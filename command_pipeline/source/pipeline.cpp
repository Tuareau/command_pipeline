#include "pipeline.h"
#include "generator.h"
#include "statistics_collector.h"

Pipeline::Pipeline(size_t commands_count) {
	this->stats_collector = new StatisticsCollector(commands_count);
	for (size_t i = 0; i < commands_count; ++i) {
		auto cmd = Command::generate_command();
		this->commands_vector.push_back(cmd);
	}
}

size_t Pipeline::stage_to_key(const Stage stage) {
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

Pipeline::Stage Pipeline::key_to_stage(size_t key) {
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

	Generator::seed();
	this->stats_collector->print_commands(this->commands_vector);
	std::reverse(this->commands_vector.begin(), this->commands_vector.end());

	while (this->commands_vector.empty() != true ||
		this->executing_commands.empty() != true) 
	{
		this->run_cycle_clock();
		//this->stats_collector->increase_clock_cycles();
		//this->stats_collector->print_clc_state(this->executing_commands);
	}

	this->stats_collector->print_statistics();
}

void Pipeline::run_cycle_clock() {
	this->try_insert_command();
	this->stats_collector->increase_clock_cycles();
	this->stats_collector->print_clc_state(this->executing_commands);
	// executing instructions and shifting if executed
	for (int stage_key = STAGES_COUNT - 1; stage_key >= 0; --stage_key) {
		if (this->executing_commands.contains(stage_key)) {
			this->executing_commands[stage_key].decrease_clock_cycles();
			if (this->executing_commands[stage_key].executed()) {
				this->try_shift_command(stage_key);
			}
		}
	}
}

void Pipeline::try_insert_command() {
	auto decode_stage_key = this->stage_to_key(Stage::DECODE);
	auto contains_decoding_command = this->executing_commands.contains(decode_stage_key);
	// decode stage is busy
	if (contains_decoding_command) {
		return;
	}
	// nothing to insert
	else if (this->commands_vector.empty()) {
		return;
	} 
	// inserting to decode stage, clc = 1 by default
	else {
		const auto & next_command = this->commands_vector.back();
		this->executing_commands[decode_stage_key] = ExecutingCommand(next_command);
		this->commands_vector.pop_back();
		this->stats_collector->add_total_clock_cycles(1);
	}
}

void Pipeline::try_shift_command(size_t key) {
	auto contains_command = this->executing_commands.contains(key);
	if (!contains_command) {
		throw std::logic_error("Pipeline::try_shift_command(): trying to shift unexisting command");
	}

	// last stage, nowhere to shift
	if (key == stage_to_key(Stage::WRITE_BACK)) {
		this->executing_commands.erase(key);
		return;
	}
	
	auto next_stage_key = key + 1;
	// generate new clc for next stage
	auto clc {
		Generator::generate_clc(this->executing_commands[key].command(), this->key_to_stage(next_stage_key))
	};
		
	auto contains_next_command = this->executing_commands.contains(next_stage_key);

	// shift to next stage
	if (!contains_next_command ||
		this->executing_commands[next_stage_key].executed()) 
	{
		this->executing_commands[next_stage_key] = ExecutingCommand(this->executing_commands[key].command(), clc);
		this->executing_commands.erase(key);
		this->stats_collector->add_total_clock_cycles(clc);
	}	
}