#include "Types.hpp"
#include <vector>
#include <ncurses.h>
#include <map>

namespace gidubsar {


    class UiElement : public std::enable_shared_from_this<UiElement> {
        private:
        Sizing width_sizing = Sizing::Fit;
        Sizing height_sizing = Sizing::Fit;
        Positioning positioning_policy = Positioning::Relative;
        std::weak_ptr<UiElement> parent;
        WINDOW* win = nullptr;

        Size size;
        Position position;

        std::string id;
        std::vector<std::string> classes;

        std::map<Signal, std::vector<std::function<void()>>> signal_handlers;

        bool focused = false;

        public:
            UiElement(std::string id, std::vector<std::string> classes = {}) : id(id), classes(classes) {}
            ~UiElement() {
                if(win) delwin(win);
            }
            virtual void move(Position new_pos);
            virtual void hide();

            virtual void write_to_buffer() = 0;
            virtual void handle_input(int ch) = 0;

            void set_parent(std::shared_ptr<UiElement> parent) {
                this->parent = parent;
            }
            void set_sizing_policy(Sizing w_sizing, Sizing h_sizing) {
                width_sizing = w_sizing;
                height_sizing = h_sizing;
            }
            void set_positioning(Positioning policy) {
                positioning_policy = policy;
            }
            void set_focus(bool focused) {
                this->focused = focused;
            }

            template<typename F>
            void on_signal(const Signal signal, const F& payload) {
                signal_handlers[signal].push_back(payload);
            }
    };

    class ParentElement : public UiElement {
        private:
            std::vector<std::shared_ptr<UiElement>> children;

            Padding padding;

        public:
            void add_child(std::shared_ptr<UiElement> child) {
                child->set_parent(shared_from_this());
                children.push_back(child);
            }

            void set_padding(Padding p) {
                padding = p;
            }
    };
}
