#include "Flock.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include "Using.hpp"

void Init(World &world) {
    world.GetRegistry().RegisterComponent<Tile>();
    world.GetRegistry().RegisterComponent<Player>();

   world.Load("../../../assets/world.json");

    for (i32 i = -5; i <= 5; i++) {
        for (i32 j = -5; j <= 5; j++) {
            world.GetRegistry().Create(Tile{.position = {i, j}});
        }
    }

    world.GetRegistry().Create(Player{});
    const auto &assets = world.GetResource<Asset::Assets>();

    if (!assets.SetDefaultPipeline(Asset::PipelineType::Pbr, "assets/shader.glsl")) {
        FLK_ASSERT(false);
    }

    if (!assets.SetDefaultPipeline(Asset::PipelineType::Unlit, "assets/unlit.glsl")) {
        FLK_ASSERT(false);
    }
}

i32 main() {
    App app = App::Create({
        .windowConfig = {
            .title = "FrenJam2",
            .size  = {1280, 720}
        },
    }).value();

    app.AddSystem(Stage::Startup, Init);
    app.AddSystem(Stage::Update, UpdatePlayer);
    app.AddSystem(Stage::Update, UpdateTiles);
    app.AddSystem(Stage::Update, [](World &world) {
        Debug::LogDbg("POS: {}, {}", Player::GetPosition(world).x, Player::GetPosition(world).y);
    });

    app.Run();
}
