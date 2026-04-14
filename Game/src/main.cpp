#include "AudioHandler.hpp"
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
    world.Registry().Register<DialogueNoButton>();
    world.Registry().Register<DialogueYesButton>();
    world.Registry().Register<Interactable>();
    world.Registry().Register<Door>();
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
    world.InsertResource(AudioHandler{});
    world.InsertResource(GameState{
        .characterImagePaths = {
            {"mike", "assets/mike.png"},
            {"samson", "assets/samson.png"},
            {"maggie", "assets/maggie.png"},
            {"jack", "assets/jack.png"},
            {"chris", "assets/chris.png"},
            {"dilto", "assets/dilto.png"},
            {"vinny", "assets/vinny.png"},
            {"girlfren", "assets/girlfren.png"},
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
            {"jack", true},
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

    world.Resource<AudioHandler>().AddSfx(world.Registry(), "walk", "assets/sfx/walk.wav", 0.25F);
    world.Resource<AudioHandler>().AddSfx(world.Registry(), "steve", "assets/music/scsa-reveal.oga");

    world.Resource<AudioHandler>().AddSfx(world.Registry(), "Joel", "assets/sfx/d_joel.wav");
    world.Resource<AudioHandler>().AddSfx(world.Registry(), "Mike", "assets/sfx/d_mike.wav");
    world.Resource<AudioHandler>().AddSfx(world.Registry(), "Fren", "assets/sfx/d_fren.wav");
    world.Resource<AudioHandler>().AddSfx(world.Registry(), "Girlfren", "assets/sfx/d_girlfren.wav");
    world.Resource<AudioHandler>().AddSfx(world.Registry(), "STEVE AUSTIN", "assets/sfx/d_scsa.wav");
    world.Resource<AudioHandler>().AddSfx(world.Registry(), "D*lto", "assets/sfx/d_dilto.wav");
    world.Resource<AudioHandler>().AddSfx(world.Registry(), "Chris", "assets/sfx/d_dilto.wav");
    world.Resource<AudioHandler>().AddSfx(world.Registry(), "Samson", "assets/sfx/d_samson.wav");
    world.Resource<AudioHandler>().AddSfx(world.Registry(), "Maggie Pie", "assets/sfx/d_maggie.wav");
    world.Resource<AudioHandler>().AddSfx(world.Registry(), "Vinny", "assets/sfx/d_vinny.wav");
    world.Resource<AudioHandler>().AddSfx(world.Registry(), "Jack Black™", "assets/sfx/d_jack.wav");

    world.Resource<AudioHandler>().AddSfx(world.Registry(), "Radio", "assets/sfx/d_default.wav");
    world.Resource<AudioHandler>().AddSfx(world.Registry(), "???", "assets/sfx/d_default.wav");
    world.Resource<AudioHandler>().AddSfx(world.Registry(), "Electric Toothbrush", "assets/sfx/d_default.wav");
    world.Resource<AudioHandler>().AddSfx(world.Registry(), "Grill", "assets/sfx/d_default.wav");
    world.Resource<AudioHandler>().AddSfx(world.Registry(), "Statuette", "assets/sfx/d_default.wav");
    world.Resource<AudioHandler>().AddSfx(world.Registry(), "Saitama Body Pillow", "assets/sfx/d_default.wav");
    world.Resource<AudioHandler>().AddSfx(world.Registry(), "Maxwell", "assets/sfx/d_default.wav");
    world.Resource<AudioHandler>().AddSfx(world.Registry(), "CD", "assets/sfx/d_default.wav");
    world.Resource<AudioHandler>().AddSfx(world.Registry(), "Vinerizon Card", "assets/sfx/d_default.wav");

    world.Resource<AudioHandler>().PlayMusic("assets/music/title.oga");
    world.Registry().Create(RectTransform{{{0, 0}, {1280, 720}}}, Gui::Image{.imagePath = "assets/bg.png"});
    world.Registry().Create(
        RectTransform{{{540, 450}, {200, 50}}},
        Button{.hoverTint = {255, 255, 255, 40}, .onReleaseEvent = "start"},
        Text{.content = "Start", .fontSize = 30, .fontPath = "assets/font.ttf", .horizontalAlignment = Center, .verticalAlignment = Middle}
    );

    world.Registry().Create(
        RectTransform{{{540, 550}, {200, 50}}},
        Button{.hoverTint = {255, 255, 255, 40}, .onReleaseEvent = "quit"},
        Text{.content = "Quit", .fontSize = 30, .fontPath = "assets/font.ttf", .horizontalAlignment = Center, .verticalAlignment = Middle}
    );
}

i32 main() {
    App app = App::Create({
        .windowConfig = {
            .title = "FrenJam2",
            .size  = {1280, 720}
        },
    }).value();

    app.AddSystems(Stage::Startup, RegisterComps, SetPipelines, SetEvents, Init)
       .AddSystems(Stage::Update, UpdateTiles, UpdatePlayer, UpdateFren, UpdateDialogueUi, UpdateItemUi, UpdateAudio)
       .Run();
}
