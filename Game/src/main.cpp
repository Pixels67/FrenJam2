#include "DialogueUi.hpp"
#include "Flock.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include "Using.hpp"

void RegisterComps(World &world) {
    world.Registry().Register<Tile>();
    world.Registry().Register<Player>();
    world.Registry().Register<Message>();
    world.Registry().Register<Dialogue>();
    world.Registry().Register<DialogueText>();
    world.Registry().Register<DialogueTitle>();
    world.Registry().Register<DialogueImage>();
    world.Registry().Register<DialogueBox>();
    world.Registry().Register<Interactable>();
}

void SetPipelines(World &world) {
    const auto &assets = world.Resource<Asset::Assets>();

    if (!assets.SetDefaultPipeline(Asset::PipelineType::Pbr, "assets/shader.glsl")) {
        FLK_ASSERT(false);
    }

    if (!assets.SetDefaultPipeline(Asset::PipelineType::Unlit, "assets/unlit.glsl")) {
        FLK_ASSERT(false);
    }
}

void Init(World &world) {
    world.InsertResource(Dialogue{.messages = {{.title = "1"}, {.title = "2"}}});
    world.Resource<AmbientLight>().color = {20, 20, 20};

    const Entity character = world.Registry().Create(
        Transform{.position = {2.0F, 2.0F, -1.0F}},
        SpriteRenderer{.spritePath = "assets/Circle.png"},
        Interactable{
            .dialogue = {
                .messages = {
                    Message{
                        .title = "Greeting",
                        .text  = "Hello!",
                    },
                    Message{
                        .title = "Farewell",
                        .text  = "Bye!",
                    }
                }
            },
        }
    );

    for (i32 i = -5; i <= 5; i++) {
        for (i32 j = -5; j <= 5; j++) {
            TileType type = Ground;
            if (i == -5 || i == 5 || j == 5 || j == -5) {
                type = Wall;
            }

            if (i == 2 && j == 2) {
                world.Registry().Create(Transform{}, SpriteRenderer{}, Tile{.position = {i, j}, .type = type, .occupant = character});
                continue;
            }

            world.Registry().Create(Transform{}, SpriteRenderer{}, Tile{.position = {i, j}, .type = type});
        }
    }

    world.Registry().Create(Transform{}, SpriteRenderer{.spritePath = "assets/Circle.png"}, Player{});

    world.Registry().Create(
        RectTransform{
            {{0, 520}, {1280, 200}}
        },
        Box{
            .color = {0, 0, 0, 100}
        },
        DialogueBox{}
    );

    world.Registry().Create(
        RectTransform{
            {{10, 530}, {1270, 190}}
        },
        Text{
            .content  = "Title",
            .fontPath = "assets/font.ttf"
        },
        DialogueTitle{}
    );

    world.Registry().Create(
        RectTransform{
            {{10, 560}, {1270, 190}}
        },
        Text{
            .content  = "Content\nMore content\nEven more content",
            .fontPath = "assets/font.ttf"
        },
        DialogueText{}
    );
}

i32 main() {
    App app = App::Create({
        .windowConfig = {
            .title = "FrenJam2",
            .size  = {1280, 720}
        },
    }).value();

    app.AddSystems(Stage::Startup, RegisterComps, SetPipelines, Init)
       .AddSystems(Stage::Update, UpdateTiles, UpdatePlayer, UpdateDialogueUi)
       .Run();
}
