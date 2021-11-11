#pragma once

#ifndef _PIPELINE_H_
#define _PIPELINE_H_

#include <array>
#include <vector>

#include "command.h"
#include "generator.h"

class StatisticsCollector;
class ExecutingCommand;

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
	size_t stage_to_index(const Stage stage) const;

private:
	StatisticsCollector _stats_collector;

	std::array<ExecutingCommand *, STAGES_COUNT> _executing_commands;
	std::vector<Command> _commands_vector;

public:
	explicit Pipeline(size_t commands_count);
	~Pipeline() = default;

	void run();
};

#endif
