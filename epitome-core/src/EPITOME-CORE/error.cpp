#include "error.h"

namespace EPITOME
{
	Error::Error(int error, const char * description, ErrorPriority priority)
	{
		this->error = error;
		this->description = description;
		this->priority = priority;

		//TODO send to logger here

		if (E3D_SUCCESS) return;
		if (priority < E3D_ErrorMinPriority) return;
		if (callback)
		{
			callback(error, description, priority);
		}
	}

	void Error::SetErrorFunction(void(*cb)(int, const char*, ErrorPriority))
	{
		callback = cb;
	}

	void Error::GLFWErrorFunction(int error, const char * description)
	{
		callback(error, description, EP_ERROR);
	}

	void Error::ResetErrorFunction()
	{
		callback = DefaultErrorFunction;
		glfwSetErrorCallback(GLFWErrorFunction);
	}
	
}
