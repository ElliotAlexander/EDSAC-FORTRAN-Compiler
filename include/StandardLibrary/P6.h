#ifndef _P6__HEADER_INCLUDED_
#define _P6__HEADER_INCLUDED_

#include <string>
#include "Library.h"
#include "LibraryBuilder.h"
#include "Logging.h"

class P6 : public Library {
	public:
		P6();
		bool getEnabled();
		std::string getRoutine();
		int getLength();
		std::string getName();
		void setEnabled();
	private:
		int instruction_length;
		std::string subroutine_text;
		bool is_enabled;
		std::string name;

};
#endif