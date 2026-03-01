#include <ncurses.h>
#include <Types.hpp>
#include <vector>

void write_table_border_to_buffer(gidubsar::DrawBuffer &buf, gidubsar::Size size, gidubsar::Position pos, short fg, short bg) {
    int x0 = pos.x;
    int y0 = pos.y;
    int x1 = x0 + size.width - 1;
    int y1 = y0 + size.height - 1;

    buf.put(x0, y0, ACS_ULCORNER, fg, bg);
    buf.put(x1, y0, ACS_URCORNER, fg, bg);
    buf.put(x0, y1, ACS_LLCORNER, fg, bg);
    buf.put(x1, y1, ACS_LRCORNER, fg, bg);

    for (int x = x0 + 1; x < x1; x++) {
        buf.put(x, y0, ACS_HLINE, fg, bg);
        buf.put(x, y1, ACS_HLINE, fg, bg);
    }

    for (int y = y0 + 1; y < y1; y++) {
        buf.put(x0, y, ACS_VLINE, fg, bg);
        buf.put(x1, y, ACS_VLINE, fg, bg);
    }
}

void write_table_width_border_to_buffer(gidubsar::DrawBuffer &buf, gidubsar::Size size, gidubsar::Position pos, short border_fg, short border_bg, short inner_fg, short inner_bg) {
    write_table_border_to_buffer(buf, size, pos, border_fg, border_bg);
    for (int y = 1; y < size.height - 1; y++) {
        for (int x = 1; x < size.width - 1; x++) {
            buf.put(pos.x + x, pos.y + y, ' ', inner_fg, inner_bg);
        }
    }
}

void write_text_to_buffer(gidubsar::DrawBuffer &buf, const std::string &text, gidubsar::Position pos,
                          short fg, short bg) {
    for (size_t i = 0; i < text.size(); i++) {
        buf.put(pos.x + i, pos.y, text[i], fg, bg);
    }
}

void write_text_input_box_to_buffer(gidubsar::DrawBuffer &buf, gidubsar::Size size, gidubsar::Position pos, short border_fg, short border_bg, short inner_fg, short inner_bg) {
    int x0 = pos.x;
    int y0 = pos.y;
    int x1 = x0 + size.width - 1;
    int y1 = y0 + size.height - 1;

    buf.put(x0, y0, ACS_ULCORNER, border_fg, border_bg);
    buf.put(x1, y0, ACS_URCORNER, border_fg, border_bg);
    buf.put(x0, y1, ACS_LLCORNER, border_fg, border_bg);
    buf.put(x1, y1, ACS_LRCORNER, border_fg, border_bg);

    for (int x = x0 + 1; x < x1; x++) {
        buf.put(x, y0, ACS_HLINE, border_fg, border_bg);
        buf.put(x, y1, ACS_HLINE, border_fg, border_bg);
    }

    for (int y = y0 + 1; y < y1; y++) {
        buf.put(x0, y, ACS_VLINE, border_fg, border_bg);
        buf.put(x1, y, ACS_VLINE, border_fg, border_bg);
    }

    for (int y = y0 + 1; y < y1; y++) {
        for (int x = x0 + 1; x < x1; x++) {
            buf.put(x, y, ' ', inner_fg, inner_bg);
		}
	}
}

int main() {
    initscr();
    start_color();
    use_default_colors();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    gidubsar::DrawBuffer buf(80, 80);

    write_text_input_box_to_buffer(buf, {30, 3}, {40, 5}, COLOR_WHITE, COLOR_BLUE, COLOR_BLACK, COLOR_WHITE);

    write_text_to_buffer(buf, "Hello world!", {42, 6}, COLOR_RED, COLOR_WHITE);

    buf.render();
    getch();
    endwin();

    return 0;
}
