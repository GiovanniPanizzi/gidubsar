# General Workflow

```
gidusbar::Stage stage;

// Create elements
auto root = std::make_shared<Table>("id", {"class1", "class2", "class3"});

root->set_direction(gidusbar::Direction::Vertical);
root->set_gap(1);
root->set_sizing_policy_x(gidusbar::Sizing::Fill);
root->set_sizing_policy_y(gidusbar::Sizing::Fill);

auto header = std::make_shared<Table>("header");

header->set_direction(gidusbar::Direction::Orizontal);
header->set_gap(2);
header->set_sizing_policy_x(gidusbar::Sizing::Fill);
header->set_sizing_policy_y(gidusbar::Sizing::Fit);
header->set_positioning(gidusbar::Positioning::Fixed_Relative);
header->set_color(255, 0, 0);

auto title = std::make_shared<Text>("title");

