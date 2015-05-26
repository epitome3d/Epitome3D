#include "error.h"

void EPITOME::Errors::CreateError(int error, const char * description, ErrorPriority priority)
{
	//TODO send to logger here

	if (E3D_SUCCESS) return;
	if (priority < E3D_ErrorMinPriority) return;
	if (callback)
	{
		callback(error, description, priority);
	}
}

void EPITOME::Errors::SetErrorFunction(void(*cb)(int, const char*, ErrorPriority))
{
	callback = cb;
}

void EPITOME::Errors::ResetErrorFunction()
{
	callback = DefaultErrorFunction;
}

void EPITOME::Errors::DefaultErrorFunction(int error, const char* description, ErrorPriority priority)
{
	return;
}
