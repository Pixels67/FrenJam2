#include "DialogueUi.hpp"
#include "Flock.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include "Using.hpp"

void RegisterComps(World &world) {
    world.GetRegistry().RegisterComponent<Tile>();
    world.GetRegistry().RegisterComponent<Player>();
    world.GetRegistry().RegisterComponent<Message>();
    world.GetRegistry().RegisterComponent<Dialogue>();
    world.GetRegistry().RegisterComponent<DialogueText>();
    world.GetRegistry().RegisterComponent<DialogueTitle>();
    world.GetRegistry().RegisterComponent<DialogueImage>();
    world.GetRegistry().RegisterComponent<DialogueBox>();
    world.GetRegistry().RegisterComponent<Interactable>();
}

void SetPipelines(World &world) {
    const auto &assets = world.GetResource<Asset::Assets>();

    if (!assets.SetDefaultPipeline(Asset::PipelineType::Pbr, "assets/shader.glsl")) {
        FLK_ASSERT(false);
    }

    if (!assets.SetDefaultPipeline(Asset::PipelineType::Unlit, "assets/unlit.glsl")) {
        FLK_ASSERT(false);
    }
}

void Init(World &world) {
    world.InsertResource(Dialogue{.messages = {{.title = "1"}, {.title = "2"}}});
    world.GetResource<AmbientLight>().color = {20, 20, 20};

    const Entity character = world.GetRegistry().Create(
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
                world.GetRegistry().Create(Transform{}, SpriteRenderer{}, Tile{.position = {i, j}, .type = type, .occupant = character});
                continue;
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
        },
        DialogueBox{}
    );

    world.GetRegistry().Create(
        RectTransform{
            {{10, 530}, {1270, 190}}
        },
        Text{
            .content  = "Title",
            .fontPath = "assets/font.ttf"
        },
        DialogueTitle{}
    );

    world.GetRegistry().Create(
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

    app.AddSystems(Stage::Startup, RegisterComps, SetPipelines, Init);
    app.AddSystems(Stage::Update, UpdateTiles, UpdatePlayer, UpdateDialogueUi);

    app.Run();
}
