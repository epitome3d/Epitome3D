#pragma once

namespace EPITOME
{
	namespace Math
	{
		template<class T>
		inline T gcd(T a, T b)
		{
			for (;;)
			{
				if (a == 0) return b;
				b %= a;
				if (b == 0) return a;
				a %= b;
			}
		}

		template<class T>
		inline T lcm(T a, T b)
		{
			int temp = gcd(a, b);

			return temp ? (a / temp * b) : 1;
		}
	}
}