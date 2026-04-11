#ifndef MAP_HPP
#define MAP_HPP

#include "Flock.hpp"
#include "Tile.hpp"
#include "Using.hpp"

inline void CreateCharacter(World &world, Tile &tile, const std::string &spritePath, const Dialogue &dialogue) {
    const Entity character = world.Registry().Create(
        Transform{},
        SpriteRenderer{.spritePath = spritePath},
        Interactable{
            .dialogue          = dialogue,
            .destroyOnInteract = false,
        }
    );

    tile.occupant = character;
}

inline void CreateItem(World &world, Tile &tile, const std::string &spritePath, const Dialogue &dialogue) {
    const Entity character = world.Registry().Create(
        Transform{},
        SpriteRenderer{.spritePath = spritePath},
        Interactable{
            .dialogue          = dialogue,
            .destroyOnInteract = true,
        }
    );

    tile.occupant = character;
}

inline void CreateFren(World &world, Tile &tile) {
    CreateCharacter(world, tile, "assets/fren.png", {});
}

inline void CreateMike(World &world, Tile &tile) {
    CreateCharacter(world, tile, "", {
                        .messages = {
                            Message{
                                .title = "Joel",
                                .text  = "Hey, waddup Michaél!",
                            },
                            Message{
                                .title = "Mike",
                                .text  =
                                "I’m fockin’ PISSED, dude! I somehow lost my emotional support figurine and can’t find it anywhere, man...",
                            },
                            Message{
                                .title = "Fren",
                                .text  = "do nat worri, it vill be arund hiere sumwere :)",
                            },
                            Message{
                                .title = "Mike",
                                .text  =
                                "Uhhh, ok? Can you find it for me instead? You’ll know once you find it, I need to sort my toothpick collection now.",
                            }
                        }
                    });
}

inline void CreateChris(World &world, Tile &tile) {
    tile.type = Sand;
    CreateCharacter(world, tile, "", {
                        .messages = {
                            Message{
                                .title = "Chris",
                                .text  = "WHAT’S UP BRO? DO YOU WANT TO BECOME A GAJILLIONAIRE LIKE ME?!!",
                            },
                            Message{
                                .title = "Joel",
                                .text  = "Wha...",
                            },
                            Message{
                                .title = "Chris",
                                .text  = "YOU NEED TO INVEST IN VARGCOIN, BRO! IT’S LIKE, THE FUTURE IS HERE, BRO!",
                            },
                            Message{
                                .title = "Joel",
                                .text  = "Sorry, but I don’t-",
                            },
                            Message{
                                .title = "Chris",
                                .text  = "YOU AND YOUR STUPID NERD DOLLARS, THEY WILL NEVER MATCH THE AURA THE VARGCOIN HAS, BRO.",
                            },
                            Message{
                                .title = "Joel",
                                .text  = "Whatever you say, man.",
                            },
                        }
                    });
}

inline void CreateSamson(World &world, Tile &tile) {
    CreateCharacter(world, tile, "", {
                        .messages = {
                            Message{
                                .title = "Samson",
                                .text  =
                                "Good day to you, did you perhaps stumble upon a big, leather bound book by any chance in this area?",
                            },
                            Message{
                                .title = "Joel",
                                .text  = "Unfortunately not",
                            },
                            Message{
                                .title = "Samson",
                                .text  =
                                "That is a shame. If you find it, please let me know, it is very important that I get ahold of the book fast.",
                            },
                            Message{
                                .title = "Fren",
                                .text  = "vat hapen if yu do not find it?",
                            },
                            Message{
                                .title = "Samson",
                                .text  = "I do not wish to know, my child",
                            },
                        }
                    });
}

inline void CreateDilto(World &world, Tile &tile) {
    CreateCharacter(world, tile, "", {
                        .messages = {
                            Message{
                                .title = "D*lto",
                                .text  = "HeLlo tHeRE...",
                            },
                            Message{
                                .title = "Joel",
                                .text  = "HOLY JESUS WHAT ARE YOU?",
                            },
                            Message{
                                .title = "D*lto",
                                .text  = "Can yOu HElp mE..?",
                            },
                            Message{
                                .title = "Joel",
                                .text  = "You're already beyond that, man",
                            },
                            Message{
                                .title = "D*lto",
                                .text  = "Am KiNd of hOmELeSs... NeEd a bED...",
                            },
                            Message{
                                .title = "D*lto",
                                .text  = "PLeAse...",
                            },
                        }
                    });
}

inline void CreateGrill(World &world, Tile &tile) {
    CreateItem(world, tile, "", {
                   .messages = {
                       Message{
                           .title = "Grill",
                           .text  = "You obtained 'Grill'.",
                       },
                   }
               });
}

inline void CreateBeautiful(World &world, Tile &tile) {
    CreateItem(world, tile, "", {
                   .messages = {
                       Message{
                           .title = "Is Beautiful",
                           .text  = "You obtained 'Is Beautiful'.",
                       },
                   }
               });
}

inline void CreateVerse(World &world, Tile &tile) {
    tile.type = Sand;
    CreateItem(world, tile, "", {
                   .messages = {
                       Message{
                           .title = "Bible Verse",
                           .text  = "You obtained 'Bible Verse', it reads \"Go up, you bald head\".",
                       },
                   }
               });
}

inline void LoadMap(World &world) {
    const auto txt = FileIo::ReadText("assets/map.txt").value();

    i32 x = 0, y = 0;
    for (const char c: txt) {
        if (c == '\n') {
            y--;
            x = 0;
            continue;
        }

        const Entity e    = world.Registry().Create(Transform{}, SpriteRenderer{}, Tile{.position = {x, y}});
        Tile &       tile = world.Registry().Get<Tile>(e).value();

        tile.type = Ground;

        if (c == ',') {
            tile.type = Trail;
        }

        if (c == 's') {
            tile.type = Sand;
        }

        if (c == '#') {
            tile.type = Wall;
        }

        if (c == 't') {
            tile.type = Trash;
        }

        if (c == 'o') {
            tile.type = Water;
        }

        if (c == 'P') {
            const Entity player = world.Registry().Create(
                Transform{.scale = {0.62F, 1.0F, 1.0F}},
                SpriteRenderer{.spritePath = "assets/joel.png"},
                Player{}
            );

            tile.occupant = player;
        }

        //if (c == 'f') {
        //    CreateFren(world, tile);
        //}

        if (c == 'M') {
            CreateMike(world, tile);
        }

        if (c == 'C') {
            CreateChris(world, tile);
        }

        if (c == 'S') {
            CreateSamson(world, tile);
        }

        if (c == 'd') {
            CreateDilto(world, tile);
        }

        if (c == 'g') {
            CreateGrill(world, tile);
        }

        if (c == 'B') {
            CreateBeautiful(world, tile);
        }

        if (c == 'b') {
            CreateVerse(world, tile);
        }

        x++;
    }
}

#endif //MAP_HPP
