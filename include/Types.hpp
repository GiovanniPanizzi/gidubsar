#pragma once

#include <algorithm>

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
}
