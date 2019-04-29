#ifndef _LIBRARY_H_INCLUDED_
#define _LIBRARY_H_INCLUDED_

#include <string>
#include <memory>

enum LIBRARY_TYPE{
	OPEN_LIBRARY,
	CLOSED_LIBRARY,
	SPECIAL_LIBRARY
};

class Library {
	public:
		virtual std::string getName() = 0;
		virtual std::string getRoutine() = 0;
		virtual bool getEnabled() = 0;
		virtual void setEnabled() = 0;
		virtual int getLength() = 0;
		virtual std::shared_ptr<int> getCallingValue() = 0;
		virtual bool applyOffset(int offset) = 0;
		virtual LIBRARY_TYPE getType() = 0;
};

#endif