#ifndef _M20__HEADER_INCLUDED_
#define _M20__HEADER_INCLUDED_

#include <string>
#include "Library.h"
#include "LibraryBuilder.h"
#include "Logging.h"

class M20 : public Library {
	public:
		M20();
		bool getEnabled();
		std::string getRawRoutine() override;
		int getLength();
		std::string getName();
		void setEnabled();
		std::shared_ptr<int> getCallingValue();
		bool applyOffset(int offset);
		LIBRARY_TYPE getType();
	private:
		int instruction_length;
		std::string subroutine_text;
		bool is_enabled;
		std::string name;
		std::shared_ptr<int> calling_value;
		LIBRARY_TYPE type; 

};
#endif