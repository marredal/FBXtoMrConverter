#ifndef __MRANIMHANDLER_H__
#define __MRANIMHANDLER_H__


#include <fstream>
#include <cstdint>
#include <glm.hpp>


class MrAnimHandler
{
public:
	MrAnimHandler();
	virtual ~MrAnimHandler();

	bool Import();
	bool Export();

	void Free();



private:

};


#endif // ! __MRANIMHANDLER_H__