#include <ege/gui.h>
#include <ege/util.h>

int main()
{
    EGE::GUIGameLoop loop;

    auto resourceManager = make<EGE::GUIResourceManager>();
    resourceManager->registerDefaultFont("font.ttf");
    loop.setResourceManager(resourceManager);

    auto window = loop.openWindow(sf::VideoMode(500, 500), "Hello World!");
    auto guiScreen = window->setNewGUIScreen<EGE::GUIScreen>();

    auto label = guiScreen->addNewWidget<EGE::Label>();
    label->setString("Hello World!");
    label->setColor(EGE::Colors::white);

    return loop.run();
}
