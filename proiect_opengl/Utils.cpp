#include "Utils.h"
#include <GL/glut.h>
#include <fstream>
#include <array>
#include <iostream>
#include <cassert>
#include <random>

namespace pg
{
	Image::Image(char* pixels, int width, int height): pixels(pixels), width(width), height(height)
	{
	}

	namespace
	{
		//Convertește un sir de patru caractere la un număr întreg
		int toInt(const char* bytes)
		{
			return (int)(((unsigned char)bytes[3] << 24) |
				((unsigned char)bytes[2] << 16) |
				((unsigned char)bytes[1] << 8) |
				(unsigned char)bytes[0]);
		}

		//Convertește un sir de patru caractere la un număr întreg
		short toShort(const char* bytes)
		{
			return (short)(((unsigned char)bytes[1] << 8) |
				(unsigned char)bytes[0]);
		}

		//Citește următorii octeți ca un întreg
		int readInt(std::ifstream& input)
		{
			char buffer[4];
			input.read(buffer, 4);
			return toInt(buffer);
		}

		//Citește următorii octeți
		short readShort(std::ifstream& input)
		{
			char buffer[2];
			input.read(buffer, 2);
			return toShort(buffer);
		}

		//Just like auto_ptr, but for arrays
		template <class T>
		class auto_array
		{
		private:
			T* array;
			mutable bool isReleased;
		public:
			explicit auto_array(T* array_ = NULL) :
				array(array_), isReleased(false)
			{
			}

			auto_array(const auto_array<T>& aarray)
			{
				array = aarray.array;
				isReleased = aarray.isReleased;
				aarray.isReleased = true;
			}

			~auto_array()
			{
				if (!isReleased && array != NULL)
				{
					delete[] array;
				}
			}

			T* get() const
			{
				return array;
			}

			T& operator*() const
			{
				return *array;
			}

			void operator=(const auto_array<T>& aarray)
			{
				if (!isReleased && array != NULL)
				{
					delete[] array;
				}
				array = aarray.array;
				isReleased = aarray.isReleased;
				aarray.isReleased = true;
			}

			T* operator->() const
			{
				return array;
			}

			T* release()
			{
				isReleased = true;
				return array;
			}

			void reset(T* array_ = NULL)
			{
				if (!isReleased && array != NULL)
				{
					delete[] array;
				}
				array = array_;
			}

			T* operator+(int i)
			{
				return array + i;
			}

			T& operator[](int i)
			{
				return array[i];
			}
		};
	}

	

	Image* loadImage(const char* filename)
	{
		std::ifstream input;
		input.open(filename, std::ifstream::binary);
		assert(!input.fail() || !"Nu a gasit fisierul");
		char buffer[2];
		input.read(buffer, 2);
		assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Nu a gasit fisierul bitmap");
		input.ignore(8);
		int dataOffset = readInt(input);
		//Read the header
		int headerSize = readInt(input);
		int width;
		int height;
		switch (headerSize)
		{
		case 40:
			//V3
			width = readInt(input);
			height = readInt(input);
			input.ignore(2);
			assert(readShort(input) == 24 || !"Imaginea nu este de 24 bits per pixel");
			assert(readShort(input) == 0 || !"Imagine comprimata");
			break;
		case 12:
			//OS/2 V1
			width = readShort(input);
			height = readShort(input);
			input.ignore(2);
			assert(readShort(input) == 24 || !"Imaginea nu este de 24 bits per pixel");
			break;
		case 64:
			//OS/2 V2
			assert(!"Nu se poate incarca ");
			break;
		case 108:
			//Windows V4
			assert(!"Nu se poate incarca ");
			break;
		case 124:
			//Windows V5
			assert(!"Can't load Windows V5 bitmaps");
			break;
		default:
			assert(!"Unknown bitmap format");
		}
		//Citeste datele
		int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
		int size = bytesPerRow * height;
		auto_array<char> pixels(new char[size]);
		input.seekg(dataOffset, std::ios_base::beg);
		input.read(pixels.get(), size);
		//Obtine datele in formatul corect
		auto_array<char> pixels2(new char[width * height * 3]);
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				for (int c = 0; c < 3; c++)
				{
					pixels2[3 * (width * y + x) + c] =
						pixels[bytesPerRow * y + 3 * x + (2 - c)];
				}
			}
		}
		input.close();
		return new Image(pixels2.release(), width, height);
	}

	int pg::randomGeneratorInt(int min, int max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(min, max);

		return distr(gen);
	}

	double pg::randomGeneratorDouble(double min, double max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> distr(min, max);

		return distr(gen);
	}

	game_entity::GameEntity pg::randomGenerateEntity()
	{
		auto number = randomGeneratorInt(0, 101);
		return number <= 29 ? game_entity::GameEntity::ROCK : game_entity::GameEntity::FRUIT; 
	}

}
