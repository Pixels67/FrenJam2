#include "Flock.hpp"

using namespace Flock;
using namespace Flock::Ecs;
using namespace Flock::Graphics;
using namespace Flock::Input;
using namespace Flock::Audio;
using namespace Flock::Gui;

i32 main() {
    App app = App::Create({
        .windowConfig = {
            .title = "FrenJam2",
            .size = {1280, 720}
        },
    }).value();

    app.AddSystem(Stage::Startup, [](World &world) {
        world.Load("assets/world.json");

        const auto &assets = world.GetResource<Asset::Assets>();

        if (!assets.SetDefaultPipeline(Asset::PipelineType::Pbr, "assets/shader.glsl")) {
            FLK_ASSERT(false);
        }

        if (!assets.SetDefaultPipeline(Asset::PipelineType::Unlit, "assets/unlit.glsl")) {
            FLK_ASSERT(false);
        }
    });

    app.Run();
}
