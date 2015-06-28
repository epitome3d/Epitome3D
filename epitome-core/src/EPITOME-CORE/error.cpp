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

	void Error::setErrorFunction(E3DErrorFunction callback)
	{
		_E3D_errorCallbackFn = callback;
	}

	void E3D_GLFWErrorCallback(int error, const char * description)
	{
		_E3D_errorCallbackFn(error, description, EP_ERROR);
	}

	void Error::resetErrorFunction()
	{
		_E3D_errorCallbackFn = defaultErrorFunction;
		glfwSetErrorCallback(E3D_GLFWErrorCallback);
	}
	
}
