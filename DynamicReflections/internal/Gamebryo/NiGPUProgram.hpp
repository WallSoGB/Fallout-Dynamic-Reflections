#pragma once

#include "NiRefObject.hpp"
class NiGPUProgram : public NiRefObject {
public:
	enum ProgramType {
		PROGRAM_VERTEX = 0,
		PROGRAM_PIXEL,
		PROGRAM_GEOMETRY,
		PROGRAM_MAX
	};

	ProgramType m_eProgramType;
};