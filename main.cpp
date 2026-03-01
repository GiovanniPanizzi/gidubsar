#include <ncurses.h>
#include <Types.hpp>
#include <vector>

void write_table_border_to_buffer(gidubsar::DrawBuffer &buf, gidubsar::Size size, gidubsar::Position pos) {
    int x0 = pos.x;
    int y0 = pos.y;
    int x1 = x0 + size.width - 1;
    int y1 = y0 + size.height - 1;

    buf.put(x0, y0, ACS_ULCORNER);
    buf.put(x1, y0, ACS_URCORNER);
    buf.put(x0, y1, ACS_LLCORNER);
    buf.put(x1, y1, ACS_LRCORNER);

    for (int x = x0 + 1; x < x1; ++x) {
        buf.put(x, y0, ACS_HLINE);
        buf.put(x, y1, ACS_HLINE);
    }

    for (int y = y0 + 1; y < y1; ++y) {
        buf.put(x0, y, ACS_VLINE);
        buf.put(x1, y, ACS_VLINE);
    }
}

void write_table_width_border_to_buffer(gidubsar::DrawBuffer &buf, gidubsar::Size size, gidubsar::Position pos) {
	write_table_border_to_buffer(buf, size, pos);
	for (int y = 1; y < size.height - 1; ++y) {
		for (int x = 1; x < size.width - 1; ++x) {
			buf.put(pos.x + x, pos.y + y, ' ');
		}
	}
}

int main() {

    initscr();

	gidubsar::DrawBuffer buf(80, 80);
	
	gidubsar::Size table_size{20, 10};
	gidubsar::Position table_pos{5, 5};

	write_table_width_border_to_buffer(buf, table_size, table_pos);
	write_table_width_border_to_buffer(buf, {10, 5}, {10, 12});
	buf.render();

	getch();

	endwin();

	return 0;
}
