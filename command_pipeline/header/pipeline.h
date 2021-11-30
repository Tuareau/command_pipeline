#pragma once

#ifndef _PIPELINE_H_
#define _PIPELINE_H_

#include <map>
#include <vector>
#include <stdexcept>

#include "command.h"
#include "executing_command.h"

class ExecutingCommand;
class StatisticsCollector;

class Pipeline
{
public:
	enum class Stage {
		DECODE,
		FETCH_LEFT_OPERAND,
		FETCH_RIGHT_OPERAND,
		EXECUTE,
		WRITE_BACK,
	};
	const static size_t STAGES_COUNT = 5;


private:
	StatisticsCollector * stats_collector;

	std::map<size_t, ExecutingCommand> executing_commands;
	std::vector<Command> commands_vector;

	void run_cycle_clock();
	void try_insert_command();
	void try_shift_command(size_t key);

	bool try_execute_reg_and_decode();
	bool try_execute_reg_and_count();

public:
	explicit Pipeline(size_t commands_count);
	~Pipeline() = default;

	static size_t stage_to_key(const Stage stage);
	static Stage key_to_stage(size_t key);

	void run();
};

#endif
