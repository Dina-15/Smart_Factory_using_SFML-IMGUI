#pragma once
#ifndef SMARTFACTORY_H
#define SMARTFACTORY_H
#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

#include "queueSubLList.h"
#include "Stack.h"
#include "Product.h"
#include "Operation.h"
#include "Order.h"
using namespace sf;

class smartFactory
{
private:
    Texture backGroundTexture;
    Sprite backGroundSprite;
    Texture productTexture;
    vector<Sprite> productSprites;
    Texture TruckTexture;
    RectangleShape truck;
    SoundBuffer soundBuffer;
    Sound sound1;
    SoundBuffer soundBuffer3;
    Sound sound3;

    queueSubLList<Product*> list;

    int id;
    int ordernum;
    int quantity;
    string productName ;
    int delPos{};
    vector<string> items;
    vector<const char*> itemsCString;
    bool selectedItems[11] = { false };
    int distance = 0;
    ImVec4 buttonColor;
    float borderRadius;
    bool pressed;
    bool ship;
    float truckX;
    float truckY;
public:
    smartFactory() { initialization(); }
    ~smartFactory() { sound1.pause(); sound3.pause(); list.clear(); clear(); }
    void Load(RenderWindow& window);
    void initialization();
    void addNewProduct();
    void Execution();
    void Shipping();
    void delProduct();
    void clear();
    void Draw(RenderWindow& window);
};
#endif

void smartFactory::Load(RenderWindow& window)
{
    if (!backGroundTexture.loadFromFile("background.png")) { std::cout << "Can't load BACKGROUND\n"; }
    backGroundSprite.setTexture(backGroundTexture, true);
    backGroundSprite.setScale(static_cast<float>(window.getSize().x) / backGroundSprite.getLocalBounds().width,
        static_cast<float>(window.getSize().y) / backGroundSprite.getLocalBounds().height);

    if (!productTexture.loadFromFile("product.png")) { std::cout << "Can't load product\n"; }
    
    if (!TruckTexture.loadFromFile("truckImage.png")) { std::cout << "Can't load truckImage\n"; }
    truck.setSize(sf::Vector2f(140, 80));
    truck.setTexture(&TruckTexture, true);


    if (!soundBuffer.loadFromFile("mainSound.mp3"))
    {
        cout << "can't find mainSound";
    }

    sound1.setBuffer(soundBuffer);

    if (!soundBuffer3.loadFromFile("truncHorn.mp3"))
    {
        cout << "can't find truncHorn";
    }

    sound3.setBuffer(soundBuffer3);

    sound1.play();
}

void smartFactory::initialization()
{
    truck.setPosition(10, 300);
    id = 0;
    ordernum = 0;
    quantity = 0;
    memset(&productName, 0, sizeof(productName));
    items = { "Cut", "Assemble", "Design","procure", "package", 
        "fill", "wrap","manufacture", "test", "repair", "customize"};
    for (const auto& item : items) {
        itemsCString.push_back(item.c_str());
    }
    buttonColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    borderRadius = 10.0f;
    pressed = false;
    ship = false;
    truckX = 5.0f;
    truckY = 400.0f;
}

void smartFactory::addNewProduct()
{
    ImGui::InputText("Prouduct Name ", &productName[0], sizeof(productName));
    ImGui::InputInt("Prouduct ID ", &id);
    ImGui::InputInt("Order Number", &ordernum);
    ImGui::InputInt("Quantity", &quantity);
    ImGui::Begin("Operations List");
    for (int i = 0; i < 11; ++i)
    {
        ImGui::Checkbox(("##Check" + std::to_string(i)).c_str(), &selectedItems[i]);
        ImGui::SameLine();
        ImGui::Text(itemsCString[i]);
    }
    ImGui::End();

    if (ImGui::Button("SAVE"))
    {
        Product* product = new Product();
        product->setID(id);
        product->setName(productName);
        Operation* op{};
        for (int i = 0; i < 11;++i)
        {
            if (selectedItems[i] == true) {
                op = new Operation();
                op->setName(items[i]);
                product->pushBack(op);
            }
        }
        Order* order = new Order();
        order->setNum(ordernum);
        order->setQuantity(quantity);
        product->pushBack(order);

        list.pushBack(product);

        Sprite productSprite;
        productSprite.setTexture(productTexture, true);
        productSprite.setScale(0.2f, 0.2f);
        productSprite.setPosition(225 + distance, 255);
        productSprites.push_back(productSprite);

        distance += 100;

        initialization();
        for (int i = 0; i < 11; i++)
        {
            selectedItems[i] = false;
        }
    }
}

void smartFactory::Execution()
{

    ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, borderRadius);
    if (ImGui::Button("Execute"))
    {
        pressed = true;
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();

    if (pressed)
    {
        ImGui::Begin("Execute");
        
        ImGui::BeginChild("Execution");
        Product* currProduct;
        for(int i=0; i<list.getCount(); i++)
        {
            currProduct = list.get(i);
            string Pid = to_string(currProduct->getID());
            ImGui::Text("=> Product %s ..", Pid.c_str());
            if (!productSprites.empty())
                productSprites.pop_back();
        }
        ImGui::EndChild();
        ship = true;
        ImGui::End();
    }
    truck.setPosition(truckX, truckY);
}

void smartFactory::Shipping()
{
    if (ship) {

        float deltaTime = 1.0f / 60.0f;
        float carMovement = 0.5f * deltaTime;
        if (ImGui::Button("Ship"))
        {
            while (truckX < 660) {
                truckX += carMovement;
            }
            sound3.play();
            clear();
        }
        ship = false;
        distance = 0;
    }
}
void smartFactory::delProduct()
{
    ImGui::Begin("Delete Product");
    
    ImGui::InputInt("Position:", &delPos);

    if (ImGui::Button("Delete"))
    {
        if (list.getCount() > delPos) 
        {
            Product* currProduct = list.get(delPos);
            if (currProduct->getSize() != 0) {
                while (currProduct->getSize() > 1)
                {
                    Operation* op = currProduct->Front();
                    currProduct->popFront();
                    delete op;
                }
                Operation* order = currProduct->Front();
                currProduct->popFront();
                delete order;
            }
            list.popAt(delPos);
            delete currProduct;
            productSprites.pop_back();
        }
    }
    ImGui::End();
    if (list.getCount() == 0)
        distance = 0;
}
void smartFactory::Draw(RenderWindow& window)
{
    window.draw(backGroundSprite);

    for (const auto& sprite : productSprites)
    {
        window.draw(sprite);
    }
    truck.setPosition(truckX, truckY);
    window.draw(truck);
}
void smartFactory::clear()
{
    Product* currProduct;
    while (list.getCount() != 0)
    {
        currProduct = list.topFront();
        if (currProduct->getSize() != 0) {
            while (currProduct->getSize() > 1)
            {
                Operation* op = currProduct->Front();
                currProduct->popFront();
                delete op;
            }
            Operation* order = currProduct->Front();
            currProduct->popFront();
            delete order;
        }
        list.popFront();
        delete currProduct;
    }
}