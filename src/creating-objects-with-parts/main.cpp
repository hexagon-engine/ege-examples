#include <ege/gui/GUIScreen.h>
#include <ege/scene.h>
#include <ege/util.h>
#include <ege/util/GlobalConfig.h>

class Player : public EGE::SceneObject
{
public:
    EGE_SCENEOBJECT("Player") // This is required to assign a type to SceneObject to allow saving/loading them from files

    Player(EGE::Scene& scene)
    : EGE::SceneObject(scene) {}

    virtual void onInit() override
    {
        // You actually don't need to give this third argument
        setPosition({EGE::randomDouble(10, 500), EGE::randomDouble(10, 500)});
    }
};

int main()
{
    EGE::GlobalConfig::set(EGE::GlobalConfig::Option::SceneObject_Overlay);
    EGE::GUIGameLoop loop;
    auto window = loop.openWindow(sf::VideoMode(600, 600), "Scene and Objects");
    auto guiScreen = window->setNewGUIScreen<EGE::GUIScreen>();

    auto scene = make<EGE::Scene>(loop);
    auto& registry = scene->getRegistry();

    // NOTE: The order of loading/registering types doesn't matter, the engine
    // will figure it out.
    if(!registry.loadFromFile("objects.json"))
        return 1;
    registry.addType<Player>();

    // Add a Player
    scene->addNewObject<Player>();

    // Add some Enemies
    for(size_t s = 0; s < 10; s++)
    {
        auto object = scene->addNewObject("Enemy");
        object->setPosition({EGE::randomDouble(10, 500), EGE::randomDouble(10, 500)});
    }

    guiScreen->addNewWidget<EGE::SceneWidget>(scene);
    return loop.run();
}
