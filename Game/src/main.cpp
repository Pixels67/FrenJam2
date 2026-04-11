#include "DialogueUi.hpp"
#include "Flock.hpp"
#include "Fren.hpp"
#include "Item.hpp"
#include "ItemUi.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include "Using.hpp"

void RegisterComps(World &world) {
    world.Registry().Register<Tile>();
    world.Registry().Register<Player>();
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
    world.InsertResource(Dialogue{});
    world.InsertResource(Inventory{
        .items = {
            Item{.name = "Circle", .imagePath = "assets/Circle.png"},
            Item{.name = "Checkerboard", .imagePath = "assets/Checkerboard.png"},
            Item{.name = "Box", .imagePath = ""}
        }
    });

    world.InsertResource(ItemUi{});
    world.InsertResource(PlayerInfo{.overworldPos = {5, -5}, .overworldPrevPos = {4, -5}});

    world.Resource<AmbientLight>().color = {20, 20, 20};

    LoadMap(world, "assets/map.txt", true);

    world.Registry().Create(
        RectTransform{
            {{0, 520}, {1280, 200}}
        },
        Box{
            .color = Color4u8::Black()
        },
        DialogueBox{}
    );

    world.Registry().Create(
        RectTransform{
            {{0, 0}, {1280, 100}}
        },
        Box{
            .color = Color4u8::Black()
        }
    );

    world.Registry().Create(
        RectTransform{
            {{10, 530}, {1270, 190}}
        },
        Text{
            .content  = "Title",
            .fontPath = "assets/font.ttf",
            .color    = {40, 120, 140, 255}
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

    world.Save("../../../assets/world.json");
}

i32 main() {
    App app = App::Create({
        .windowConfig = {
            .title = "FrenJam2",
            .size  = {1280, 720}
        },
    }).value();

    app.AddSystems(Stage::Startup, RegisterComps, SetPipelines, Init)
       .AddSystems(Stage::Update, UpdateTiles, UpdatePlayer, UpdateFren, UpdateDialogueUi, UpdateItemUi)
       .Run();
}
