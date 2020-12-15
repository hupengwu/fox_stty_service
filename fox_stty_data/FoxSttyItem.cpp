#include "FoxSttyItem.h"

FoxSttyItem::FoxSttyItem()
{
	this->stty = nullptr;
}

FoxSttyItem::~FoxSttyItem()
{
}

FoxSttyItemSettings& FoxSttyItem::getSettings()
{
	return this->settings;
}

void FoxSttyItem::setSettings(FoxSttyItemSettings& settings)
{
	this->settings = settings;
}

FoxStty* FoxSttyItem::getStty() 
{
	return this->stty;
}
void FoxSttyItem::setStty(FoxStty* stty) 
{
	this->stty = stty;
}