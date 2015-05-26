#pragma once

namespace EPITOME
{	
	//List of errors supported by EPITOME-Core
	enum Error
	{
		E3D_SUCCESS = (int)true,
		E3D_FAILURE = (int)false,
		E3D_UNKNOWN = -1
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

	static const ErrorPriority E3D_ErrorMinPriority = EP_ERROR;

	//An error returned by a call to Epitome's functions
	class Errors
	{
	public:
		//Instantiate an error returned by a call to Epitome's functions.  Priority defaults to level 3 (error).
		static void CreateError(int error, const char* description, ErrorPriority priority = EP_ERROR);

		//Set an error function for Epitome.  When errors are created AND are of higher or equal priority than 
		//E3D_ErrorMinPriority, they will pipe into the function.
		//The callback should be a function defined as function(int error, const char* description, ErrorPriority priority).
		static void SetErrorFunction(void(*callback)(int, const char*, ErrorPriority));

		//Set the error function to the default state.
		static void ResetErrorFunction();

		//The default error function.  Custom error functions may fall back to this function by calling it.
		static void DefaultErrorFunction(int, const char*, ErrorPriority);
	private:
		static void(*callback)(int, const char*, ErrorPriority); //Callback for the error function.  When an error is created, this class forwards to the callback.
	};
}