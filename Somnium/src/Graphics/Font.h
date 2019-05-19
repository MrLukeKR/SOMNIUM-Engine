#pragma once

#include "../Logic/Maths/Vector2.h"
#ifdef WEB_BUILD 
	#define GLFW_INCLUDE_ES3
#else 
	#include <glew.h> 
#endif

#include <glfw3.h>
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace Somnium
{
	namespace Graphics
	{
		struct UICharacter
		{
			GLuint textureID;
			Maths::Vector2 size;
			Maths::Vector2 bearing;
			FT_Pos advance;
		};

		class Font
		{
		public:
			Font(const char* fontFilepath, const FT_Library& freeTypeInstance);
			~Font() {};

			const std::map<GLchar, UICharacter>& getCharacterMap() const { return m_CharacterMap;  }
		private:
			const FT_Library& m_FreeType;
			FT_Face m_Face;
			std::map<GLchar, UICharacter> m_CharacterMap;
		};
	}
}
