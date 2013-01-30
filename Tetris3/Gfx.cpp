#include "Gfx.h"

void Gfx::BeginPaint(HDC hdc)
{
	this->hdc = hdc;
}

void Gfx::EndPaint()
{
	//this->hdc = NULL;
}