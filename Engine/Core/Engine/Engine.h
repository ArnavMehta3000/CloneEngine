#pragma once
#include "Tools/Logger.h"
#include "Common/Defines.h"
#include "Common/Property.h"
#include "Common/Property.h"
#include "Math/SimpleMath.h"

namespace Clone::Engine
{
	class Engine final
	{
	public:
		Engine();
		~Engine();

		
	};


	// Engine to prevent warning C4251
	// Solution reference: https://web.archive.org/web/20170811142318/http://www.microsoft-questions.com/microsoft/VC-Language/30952961/a-solution-to-warning-c4251--class-needs-to-have-dllinterface.aspx
	struct EnginePtr
	{
		std::unique_ptr<Engine> m_enginePtr;
	};
	
}