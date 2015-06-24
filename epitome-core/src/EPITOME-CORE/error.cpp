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
		if (_E3D_errorCallbackFn)
		{
			_E3D_errorCallbackFn(error, description, priority);
		}
	}

	void Error::SetErrorFunction(E3DErrorFunction callback)
	{
		_E3D_errorCallbackFn = callback;
	}

	void GLFWErrorFunction(int error, const char * description)
	{
		_E3D_errorCallbackFn(error, description, EP_ERROR);
	}

	void Error::ResetErrorFunction()
	{
		_E3D_errorCallbackFn = DefaultErrorFunction;
		glfwSetErrorCallback(GLFWErrorFunction);
	}
	
}
