#include <ege/gui.h>
#include <ege/gui/LayoutElement.h>
#include <ege/scene.h>
#include <ege/util.h>

class MySceneObject : public EGE::SceneObject
{
public:
    EGE_SCENEOBJECT("MySceneObject")

    MySceneObject(EGE::Scene& scene)
    : EGE::SceneObject(scene) {}

    virtual void onInit() override
    {
        setPosition({EGE::randomDouble(-50, 50), EGE::randomDouble(-50, 50), 0});
    }
    
    virtual void render(EGE::Renderer& renderer) const override
    {
        // Exceptionally not using part system here.
        EGE::SceneObject::render(renderer);
        renderer.renderRectangle(-5 + getPosition().x, -5 + getPosition().y, 10, 10, EGE::Colors::blue, EGE::Colors::red);
    }
};

class ViewWidget : public EGE::Widget
{
public:
    ViewWidget(EGE::Widget& parent, EGE::String const& str, EGE::SharedPtr<EGE::Scene> const& scene)
    : EGE::Widget(parent) {
        layoutDirection = EGE::LayoutElement::Direction::Vertical;
        auto label = addNewWidget<EGE::Label>();
        label->setString(EGE::String(str));
        label->setSize({"1N", "20px"});
        label->setColor(EGE::Colors::white);
        label->setTextAlign(EGE::Renderer::TextAlign::Center);

        m_sceneWidget = addNewWidget<EGE::SceneWidget>(scene);
    }

    void setCamera(EGE::SharedPtr<EGE::Camera> const& camera)
    {
        m_sceneWidget->setCamera(camera);
    }

    virtual void render(EGE::Renderer& renderer) const override
    {
        renderer.renderRectangle(1, 1, getSize().x - 2, getSize().y - 2, EGE::Colors::transparent, EGE::Colors::white);
    }

private:
    EGE::SharedPtr<EGE::SceneWidget> m_sceneWidget;
};

int main()
{
    EGE::GUIGameLoop loop;
    auto window = loop.openWindow(sf::VideoMode(600, 600), "Scene and Objects");
    auto guiScreen = window->setNewGUIScreen<EGE::GUIScreen>();

    auto resMan = make<EGE::GUIResourceManager>();
    resMan->registerDefaultFont("font.ttf");
    loop.setResourceManager(resMan);

    auto scene = make<EGE::Scene>(loop);
    auto& registry = scene->getRegistry();
    
    registry.addType<MySceneObject>();

    for(size_t s = 0; s < 10; s++)
        scene->addNewObject<MySceneObject>();

    guiScreen->layoutDirection = EGE::LayoutElement::Direction::Vertical;
    auto row1 = guiScreen->addNewWidget<EGE::Widget>();
    {
        row1->layoutDirection = EGE::LayoutElement::Direction::Horizontal;
        auto camNone = scene->addNewObject<EGE::Plain2DCamera>(); 
        camNone->setScalingMode(EGE::ScalingMode::None);
        row1->addNewWidget<ViewWidget>("None", scene)->setCamera(camNone);

        auto camCentered = scene->addNewObject<EGE::Plain2DCamera>();
        camCentered->setScalingMode(EGE::ScalingMode::Centered);
        row1->addNewWidget<ViewWidget>("Centered", scene)->setCamera(camCentered);

        auto camFit = scene->addNewObject<EGE::Plain2DCamera>();
        camFit->setScalingMode(EGE::ScalingMode::Fit);
        camFit->setDisplaySize({100, 100});
        row1->addNewWidget<ViewWidget>("Fit", scene)->setCamera(camFit);
    }
    auto row2 = guiScreen->addNewWidget<EGE::Widget>();
    {
        row2->layoutDirection = EGE::LayoutElement::Direction::Horizontal;
        auto camXLocked = scene->addNewObject<EGE::Plain2DCamera>();
        camXLocked->setScalingMode(EGE::ScalingMode::XLocked);
        camXLocked->setFOV(100);
        row2->addNewWidget<ViewWidget>("XLocked", scene)->setCamera(camXLocked);

        auto camYLocked = scene->addNewObject<EGE::Plain2DCamera>();
        camYLocked->setScalingMode(EGE::ScalingMode::YLocked);
        camYLocked->setFOV(100);
        row2->addNewWidget<ViewWidget>("YLocked", scene)->setCamera(camYLocked);

        auto camScaled = scene->addNewObject<EGE::Plain2DCamera>();
        camScaled->setScalingMode(EGE::ScalingMode::Scaled);
        camScaled->setDisplaySize({100, 100});
        row2->addNewWidget<ViewWidget>("Scaled", scene)->setCamera(camScaled);
    }

    return loop.run();
}
