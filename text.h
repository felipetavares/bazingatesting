#ifndef BAZINGA_TEXT_H
#define BAZINGA_TEXT_H

#include "filesystem.h"
#include "video.h"
#include <ft2build.h>
#include FT_FREETYPE_H

namespace bazinga {
	namespace text {
		extern FT_Library freetype;

		typedef struct Area {
			int x,y;
			int w,h;
		}Area;

		class AreaBuffer {
			vector <Area> freeAreas;
		public:
			AreaBuffer(int, int);

			// Insert a new area
			Area insert (int, int);
		private:
			vector <Area> createChildren(Area, int, int);
		};

		class Font {
			FT_Face face;

			vector <GLuint> textures;
			vector <AreaBuffer*> areaManagers;
			const unsigned int bufferLen = 256;

			uint32_t fontSize = 0;

			class Char {
			public:
				// Texture number
				int tn;

				// Position on the buffer
				int x;
				int y;

				// Size
				int w;
				int h;

				// Distance to baseline
				int dw;
				int dh;

				// Advance
				int adw;
				int adh;

				// Font size
				int fontSize;
			};

			map <uint64_t, Char*> charCache;

			video::Color color;
		public:
			Font (Path);
			~Font();
			void setSize (int);
			int render (const char*, int);
			int measure (const char*, int, float&, float&, float&);
			void setColor (video::Color);
		private:
			uint32_t utf82unicode(uint32_t);
			int utf8asint(const char*, int, uint32_t&);
			void newAtlas();
		};

		typedef struct TextMetrics {
			float w,h;

			// Distance from top to baseline
			float dh;
		}TextMetrics;

		enum Align {
			Center,
			Left,
			Right
		};
		enum Baseline {
			Top,
			Middle,
			Bottom,
			Alphabetic
		};

		extern Font* font;
		extern Align alignment;
		extern Baseline baseline;

		void init ();
		void deinit ();

		// Text rendering API
		// Based upon HTML5 Canvas' one
		// For meanings of constants, refer to
		// https://developer.mozilla.org/en-US/docs/Web/API/Canvas_API/Tutorial/Drawing_text
		void setFont (Font*); 	// ctx.font = font
		void setAlign (Align); 	// ctx.textAlign = ('center'|'left'|'right')
		// Not fully implemented
		void setBaseline (Baseline); // ctx.textBaseline = ('top'|'middle'|'bottom'|'alphabetic')
		// Fill an UTF-8 encoded string
		void fillText (string, int, int); // ctx.fillText(str, x, y)
		// Measures an UTF-8 encoded strnig
		TextMetrics measureText (string);
		// Not based upon HTML5
		void fillArgText (string, int, int, vector<int>,
											vector<function <void(Font*)>>);

		/*
			Auxiliar fuzzy search functions
		*/

		/*
			Distance between two strings

			Edit distance consider transforming one string
			into another using some basic primitives:

			* insert char
			* delete char
			* change char

			returns how many of these operations are needed
		*/
		float ed (string, string);
		/*
			Used for visualization of how the strings
			are "mixed" with ed.
			0's are for characters from x
			1's for y's ones
		*/
		vector<int> visualed(string, string);
	}
}

#endif /* BAZINGA_TEXT_H */
