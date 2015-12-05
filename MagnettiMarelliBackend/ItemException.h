#pragma once

#include <stdexcept>

class ItemNotFoundException : public std::runtime_error
{
public:
	ItemNotFoundException() : runtime_error("Item not found") {  };
	~ItemNotFoundException() = default;
};
