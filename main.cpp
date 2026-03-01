#include <ncurses.h>
#include <Types.hpp>

int main() {

	// Initialize ncurses
    initscr();

	// Set up ncurses options
    refresh();

	// Enable cbreak mode and disable echoing of input
    cbreak();

	// Disable echoing of input characters
    noecho();

    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);
    WINDOW* table = newwin(10, 50, 5, 5);
    
	box(table, 0, 0);

    wrefresh(table);

    getch();

    delwin(table);
    endwin();
    
	return 0;
}
