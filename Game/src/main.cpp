#include "Flock.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include "Using.hpp"

void Init(World &world) {
    world.GetRegistry().RegisterComponent<Tile>();
    world.GetRegistry().RegisterComponent<Player>();

    world.GetResource<AmbientLight>().color = {20, 20, 20};

    for (i32 i = -5; i <= 5; i++) {
        for (i32 j = -5; j <= 5; j++) {
            TileType type = Ground;
            if (i == -5 || i == 5 || j == 5 || j == -5) {
                type = Wall;
            }

            world.GetRegistry().Create(Transform{}, SpriteRenderer{}, Tile{.position = {i, j}, .type = type});
        }
    }

    world.GetRegistry().Create(Transform{}, SpriteRenderer{.spritePath = "assets/Circle.png"}, Player{});

    world.GetRegistry().Create(
        RectTransform{
            {{0, 520}, {1280, 200}}
        },
        Box{
            .color = {0, 0, 0, 100}
        }
    );

    world.GetRegistry().Create(
        RectTransform{
            {{10, 530}, {1270, 190}}
        },
        Text{
            .content  = "Title",
            .fontPath = "assets/font.ttf"
        }
    );

    world.GetRegistry().Create(
        RectTransform{
            {{10, 560}, {1270, 190}}
        },
        Text{
            .content  = "Content\nMore content\nEven more content",
            .fontPath = "assets/font.ttf"
        }
    );

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

    app.AddSystems(Stage::Startup, Init);
    app.AddSystems(Stage::Update, UpdateTiles, UpdatePlayer);

    app.Run();
}
