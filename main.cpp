
#include <iostream>

#include "smartFactory.h"

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(800, 500), "SMART FACTORY");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    smartFactory factory;

    /////// Load //////////////
    factory.Load(window);

    ///// initialization //////
    factory.initialization();

    Clock deltaClock;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == Event::Closed) {
                window.close();
            }
        }
        //////// Update ////////////////////
        ImGui::SFML::Update(window, sf::seconds(1.0f / 60.0f));

        //////// add New Product ////////////
        ImGui::Begin("Add New Product");
        factory.addNewProduct();
        ImGui::End();

        //////// Execution //////////////////
        factory.Execution();

        //////// shipping ///////////////////
        factory.Shipping();

        /////// delete a proudct /////////////
        factory.delProduct();
        window.clear();

        ////// Draw ////////
        factory.Draw(window);

        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}
