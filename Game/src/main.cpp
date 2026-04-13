#include "DialogueUi.hpp"
#include "Flock.hpp"
#include "Fren.hpp"
#include "Item.hpp"
#include "ItemUi.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include "Events.hpp"
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
    world.InsertResource(Inventory{});
    world.InsertResource(ItemUi{});
    world.InsertResource(PlayerInfo{.overworldPos = {5, -5}, .overworldPrevPos = {4, -5}});
    world.InsertResource(GameState{
        .characterImagePaths = {
            {"mike", "assets/mike.png"},
            {"samson", "assets/samson.png"},
            {"maggie", "assets/maggie.png"},
            {"jack", "assets/jack.png"},
            {"chris", "assets/chris.png"},
            {"dilto", "assets/dilto.png"},
            {"vinny", "assets/vinny.png"},
        },
        .itemsLocked = {
            {"pillow", true},
            {"statuette", true},
            {"coin", true},
            {"grill", true},
            {"cd", true},
            {"maxwell", true},
            {"toothbrush", true},
            {"card", true},
        },
        .items = {
            {"pillow", true},
            {"statuette", true},
            {"coin", true},
            {"grill", true},
            {"cd", true},
            {"maxwell", true},
            {"toothbrush", true},
            {"card", true},
        }
    });

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
            {{0, 0}, {1280, 90}}
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

    app.AddSystems(Stage::Startup, RegisterComps, SetPipelines, SetEvents, Init)
       .AddSystems(Stage::Update, UpdateTiles, UpdatePlayer, UpdateFren, UpdateDialogueUi, UpdateItemUi)
       .Run();
}
