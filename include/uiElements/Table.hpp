#pragma once

#include "UiElement.hpp"

namespace gidubsar {

    class Table : public ParentElement {
        private:
            std::vector<std::vector<std::shared_ptr<UiElement>>> cells;
            std::vector<int> column_widths;
            std::vector<int> row_heights;

        public:
            void add_row(const std::vector<std::shared_ptr<UiElement>>& row);

            void write_to_buffer(DrawBuffer &buf) override {
                int x0 = position.x;
                int y0 = position.y;
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
            void handle_input(int ch) override;
    };

}