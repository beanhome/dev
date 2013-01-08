#ifndef SQUAREBASE_H_
#define SQUAREBASE_H_

#include "Utils.h"
#include "GridBase.h"

class SquareBase
{
	public:
		SquareBase() {}

		virtual bool IsBlock() const = 0;

	private:
};

#endif //SQUAREBASE_H_
