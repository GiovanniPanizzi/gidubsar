# gidubsar

A c++ library for building TUIs

## Expected workflow
``` cpp
#include <gidusbar/gidusbar.hpp>

int main() {
    gidusbar::Stage stage;
    stage.init();

    // Main layout container
    auto root = std::make_shared<gidusbar::Table>("root_view");
    root->set_direction(gidusbar::Direction::Vertical);
    root->set_gap(1);
    root->set_sizing_policy(gidusbar::Sizing::Fill, gidusbar::Sizing::Fill);

    // Header section
    auto header = std::make_shared<gidusbar::Table>("header");
    header->set_direction(gidusbar::Direction::Horizontal);
    header->set_gap(2);
    header->set_sizing_policy(gidusbar::Sizing::Fill, gidusbar::Sizing::Fit);
    header->set_positioning(gidusbar::Positioning::Relative);
    header->set_color(255, 0, 0);
    
    auto title = std::make_shared<gidusbar::Text>("title", "Main Dashboard");
    header->add_child(title);

    // Content area
    auto content = std::make_shared<gidusbar::Table>("content_area");
    content->set_sizing_policy(gidusbar::Sizing::Fill, gidusbar::Sizing::Fill);
    
    auto info = std::make_shared<gidusbar::Text>("info_text", "System Status: Nominal");
    content->add_child(info);

    // Footer with interactive button
    auto exit_btn = std::make_shared<gidusbar::Button>("exit_btn", " QUIT ");
    exit_btn->set_alignment(gidusbar::Alignment::Center);

    root->add_child(header);
    root->add_child(content);
    root->add_child(exit_btn);
    stage.set_root(root);

    // Signal handling
    bool running = true;
    exit_btn->on_signal([&running](gidusbar::Signal s) {
        if (s.type == gidusbar::SignalType::Click) running = false;
    });

    // Execution loop
    while (running) {
        stage.process_inputs();
        
        // Example of dynamic update via ID
        auto status = stage.find_by_id("info_text");
        if (status) status->set_text("System Status: Active");

        stage.refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    stage.shutdown();
    return 0;
}

```

## How to build

