#include "Types.hpp"
#include <vector>

namespace gidubsar {


    class UiElement : public std::enable_shared_from_this<UiElement> {
        private:
        Sizing width_sizing = Sizing::Fit;
        Sizing height_sizing = Sizing::Fit;
        Positioning positioning_policy = Positioning::Relative;
        std::weak_ptr<UiElement> parent;

        Size size;
        Position position;

        std::string id;
        std::vector<std::string> classes;

        bool focused = false;

        public:
            UiElement(std::string id, std::vector<std::string> classes = {}) : id(id), classes(classes) {}
            virtual void draw() = 0;
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