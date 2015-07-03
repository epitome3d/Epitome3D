#pragma once
#include <stdio.h>
#include <exception>
#include <GLFW/glfw3.h>

namespace EPITOME
{
	//List of errors supported by EPITOME-Core
	enum Errors
	{
		E3D_UNKNOWN = -1,
		E3D_SUCCESS = 0,
		E3D_FAILURE = 1,
		E3D_FAIL_CORE_INIT = 2,
		E3D_INVALID_PARAMETER = 3,
		E3D_LIBRARY_NOT_INITIALIZED = 4,
		E3D_COMPONENT_NOT_INITIALIZED = 5
	};

	//Priority of an error.  Higher priority means more actions are taken due to the error.
	enum ErrorPriority
	{
		EP_FATAL = 4,	//fatal error - destroys Epitome
		EP_ERROR = 3,	//high priority error - always throws prompt
		EP_WARNING = 2,	//warning - may throw prompt
		EP_INFO = 1,	//info - may throw prompt when debugging
		EP_RESULT = 0	//result - never throws or logs
	};

	typedef void(*E3DErrorFunction)(int, const char*, ErrorPriority);

	static const ErrorPriority E3D_ErrorMinPriority = EP_ERROR;

	//The internal error function dealing with OpenGL
	static void E3D_GLFWErrorCallback(int error, const char* description);

	//Internal callback for the error function.  When an error is created, this class forwards to the callback.
	static void(*_E3D_errorCallbackFn)(int, const char*, ErrorPriority); 

	//An error returned by a call to Epitome's functions
	class Error
	{
	public:

		//Instantiate an error returned by a call to Epitome's functions.  Priority defaults to level 3 (error).
		Error(int error, const char* description, ErrorPriority priority = EP_ERROR);

		//Set an error function for Epitome.  When errors are created AND are of higher or equal priority than 
		//E3D_ErrorMinPriority, they will pipe into the function.
		//The callback should be a function defined as function(int error, const char* description, ErrorPriority priority).
		static void setErrorFunction(E3DErrorFunction callback);

		//Set the error function to the default state.
		static void resetErrorFunction();

		//The default error function.  Custom error functions may fall back to this function by calling it.
		inline static void defaultErrorFunction(int error, const char* description, ErrorPriority priority)
		{
			fprintf(stderr, "[EPITOME] %s\r\n", description);
			
			#ifdef _DEBUG
			throw std::exception(description);
			#endif
		}

		inline int getCode()
		{
			return error;
		}
		inline const char* getDescription()
		{
			return description;
		}
		inline ErrorPriority getPriority()
		{
			return priority;
		}

	private:
		int error;
		const char* description;
		ErrorPriority priority;
	};
}