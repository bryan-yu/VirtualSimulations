#ifndef STRING_TOKENIZER_H
#define STRING_TOKENIZER_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

namespace AABSEngine
{
	namespace Utility
	{
		/**
		 * @class StringTokenizer
		 * @brief A static class to tokenize string
		 *
		 * @author AABS
		 * @version X
		 * @date October 2013
		 *
		 */
		class StringTokenizer
		{
		public:
			/**
			* @brief Tokenise string
			* @param line (std::string)
			* @param container (std::vector<std::string>&)
			* @param delimiter (char)
			* @retun void
			*/
			static void TokenizeString(std::string line, std::vector<std::string> &container, char delimiter);
		};

	}
}

#endif