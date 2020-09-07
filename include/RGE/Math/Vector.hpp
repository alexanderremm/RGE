#pragma once

#include "RGE/rge_exports.h"

#include <cmath>
#include <iostream>

namespace RGE
{
	namespace Math
	{
		/**
		* \brief 2D Vector data structure
		*/
		template <typename T>
		struct Vector2
		{
			T x;
			T y;

			Vector2(T xVal, T yVal)
			{
				x = xVal;
				y = yVal;
			}

			/**
			* \brief Calculates the magnitude of the vector
			*
			* \returns Magnitude
			*/
			double Magnitude() const
			{
				return sqrt(pow(x, 2) + pow(y, 2));
			}

			/**
			* \brief Normalizes the vector
			*
			* \returns The normalized vector
			*/
			Vector2<double> Normalize() const
			{
				double magnitude = this->Magnitude();
				double nX = x / magnitude;
				double nY = y / magnitude;

				return Vector2<double>(nX, nY);
			}

			// Operator overloading
			friend std::ostream& operator<<(std::ostream& os, const Vector2& v2)
			{
				os << "<" << v2.x << ", " << v2.y << ">";
				return os;
			}
		};

		/**
		* \brief 3D Vector data structure
		*/
		template <typename T>
		struct Vector3
		{
			T x;
			T y;
			T z;

			Vector3(T xVal, T yVal, T zVal)
			{
				x = xVal;
				y = yVal;
				z = zVal;
			}

			/**
			* \brief Calculates the magnitude of the vector
			* 
			* \returns Magnitude
			*/
			double Magnitude() const
			{
				return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
			}

			/**
			* \brief Normalizes the vector
			* 
			* \returns The normalized vector
			*/
			Vector3<double> Normalize() const
			{
				double magnitude = this->Magnitude();
				double nX = x / magnitude;
				double nY = y / magnitude;
				double nZ = z / magnitude;

				return Vector3<double>(nX, nY, nZ);
			}

			// Operator overloading
			friend std::ostream& operator<<(std::ostream& os, const Vector3& v3)
			{
				os << "<" << v3.x << ", " << v3.y << ", " << v3.z << ">";
				return os;
			}
		};

		/**
		* \brief 4D Vector data structure
		*/
		template <typename T>
		struct Vector4
		{
			T x;
			T y;
			T z;
			T w;

			Vector4(T xVal, T yVal, T zVal, T wVal)
			{
				x = xVal;
				y = yVal;
				z = zVal;
				w = wVal;
			}

			/**
			* \brief Calculates the magnitude of the vector
			*
			* \returns Magnitude
			*/
			double Magnitude() const
			{
				return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));
			}

			/**
			* \brief Normalizes the vector
			*
			* \returns The normalized vector
			*/
			Vector4<double> Normalize() const
			{
				double magnitude = this->Magnitude();
				double nX = x / magnitude;
				double nY = y / magnitude;
				double nZ = z / magnitude;
				double nW = w / magnitude;

				return Vector4<double>(nX, nY, nZ, nW);
			}

			// Operator overloading
			friend std::ostream& operator<<(std::ostream& os, const Vector4& v4)
			{
				os << "<" << v4.x << ", " << v4.y << ", " << v4.z << ", " << v4.z << ">";
				return os;
			}
		};

	} // Math

} // RGE
