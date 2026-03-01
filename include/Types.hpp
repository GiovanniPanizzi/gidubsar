#pragma once

#include <algorithm>
#include <vector>
#include <ncurses.h>
#include <map>

namespace gidubsar {
	enum class Direction {Horizontal, Vertical};
	enum class Sizing {Fit, Fill};
	enum class Positioning {Absolute, Relative, Fixed_Absolute, Fixed_Relative};
	enum class Alignment {Start, Center, End};
	enum class Wrap {None, Word, Character, Ellipsis};
	
	struct Size {
		int width = 0;
		int height = 0;	
	};

	struct Padding {
		int left = 0;
		int right = 0;
		int top = 0;
		int bottom = 0;
	};

	struct Position {
		int x = 0;
		int y = 0;	
	};

	struct BoxConstraints {
		int min_width = 0;
		int max_width = 10;
		int min_height = 0;
		int max_height = 10;
		
		Size clamp(Size preferred) const {
			return {
				std::max(min_width, std::min(preferred.width, max_width)),
				std::max(min_height, std::min(preferred.height, max_height))
			};
		}
	};

	// Rendering
	struct Cell {
		chtype ch = ' ';
		short fg = -1;
		short bg = -1;
	};

	struct DrawBuffer {
		std::vector<Cell> cells;
		Size size;
		mutable std::map<std::pair<short, short>, short> color_pairs;
		mutable short next_pair_id = 1;

		DrawBuffer(int w, int h) {
			size.width = w;
			size.height = h;
			cells.resize(w * h);
			for (auto &cell : cells) cell.ch = ' ';
		}

		short get_or_create_pair(short fg, short bg) const {
			auto key = std::make_pair(fg, bg);
			if (color_pairs.count(key)) return color_pairs.at(key);

			short pair_id = next_pair_id++;
			if(pair_id >= COLOR_PAIRS) pair_id = 0;
			init_pair(pair_id, fg, bg);
			color_pairs[key] = pair_id;
			return pair_id;
		}
		void put(int x, int y, chtype ch) {
			if (x < 0 || x >= size.width || y < 0 || y >= size.height) return;
			cells[y * size.width + x].ch = ch;
			cells[y * size.width + x].fg = -1;
			cells[y * size.width + x].bg = -1;
		}

		void put(int x, int y, chtype ch, short fg, short bg) {
			if (x < 0 || x >= size.width || y < 0 || y >= size.height) return;
			cells[y * size.width + x].ch = ch;
			cells[y * size.width + x].fg = fg;
			cells[y * size.width + x].bg = bg;
		}

		void render() const {
			for (int y = 0; y < size.height; y++) {
				for (int x = 0; x < size.width; x++) {
					const Cell &cell = cells[y * size.width + x];
					chtype ch = cell.ch;

					short pair_id = 0;
					if (cell.fg != -1 && cell.bg != -1)
						pair_id = get_or_create_pair(cell.fg, cell.bg);

					if (pair_id)
						mvaddch(y, x, ch | COLOR_PAIR(pair_id));
					else
						mvaddch(y, x, ch);
				}
			}
			refresh();
		}
	};
}
