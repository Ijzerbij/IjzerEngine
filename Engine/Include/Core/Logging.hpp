#pragma once

namespace Eng
{
	namespace logger
	{
		enum ErrorType
		{
			window,
			engine,
			renderer
		};

		void LogCritticalError(ErrorType Type, int ID);
	}
}