#include "Core/Logging.hpp"

#include <cstdlib>

namespace Eng
{
	namespace logger
	{
		void LogCritticalError(ErrorType Type, int ID)
		{
			int log = 0;
			switch (Type)
			{
			case Eng::logger::window:
				log = 1 + (10 * ID);
				std::exit(log);
				break;
			case Eng::logger::engine:
				log = 2 + (10 * ID);
				std::exit(log);
				break;
			case Eng::logger::renderer:
				log = 3 + (10 * ID);
				std::exit(log);
				break;
			default: // an error is passed that has no registration in the logger
				log = -1;
				std::exit(log);
				break;
			}
		}
	}
}