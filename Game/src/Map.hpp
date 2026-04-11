#ifndef MAP_HPP
#define MAP_HPP

#include "Door.hpp"
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

inline void CreateMaggie(World &world, Tile &tile) {
    CreateCharacter(world, tile, "", {
                        .messages = {
                            Message{
                                .title = "Joel",
                                .text  = "Uh... hey, magpie lady, are you looking for Zanzibar Island, by any chance?",
                            },
                            Message{
                                .title = "Maggie Pie",
                                .text  = "Oh, hello, young man! No, I actually live here in this house-tree!" "After all, why would I have things monogrammed with my initials everywhere?",
                            },
                            Message{
                                .title = "Joel",
                                .text  = "Uh... you just kinda looked like you were in the wrong ga-",
                            },
                            Message{
                                .title = "Maggie Pie",
                                .text  = "Good grief, I forgot to introduce myself! My name is Maggie, Maggie Pie! Nice to meet you, misterrrrr...?",
                            },
                            Message{
                                .title = "Joel",
                                .text  = "...uh, Joel.",
                            },
                            Message{
                                .title = "Joel",
                                .text  = "Nice to meet you, Ms. Pie. By the way, everyone I talk to has lost something or needs an item. Do you need anything?",
                            },
                            Message{
                                .title = "Maggie Pie",
                                .text  = "Please, just call me Maggie! And no, sweetie, I just finished a grocery trip today.",
                            },
                            Message{
                                .title = "Maggie Pie",
                                .text  = "Of course, I won't say no if you found something you'd think I'd like. You're a very sweet young man!",
                            },
                            Message{
                                .title = "Maggie Pie",
                                .text  = "By the way, I just baked some Piebald Pie! I was inspired by my late kitty Jess. She was piebald.",
                            },
                            Message{
                                .title = "Joel",
                                .text  = "Ooooh! Looks tasty!",
                            },
                            Message{
                                .title = "Maggie Pie",
                                .text  = "It's Å-rej-å flavored cookies and cream pie! The creme filling is made from crushed Å-rej-ås.",
                            },
                            Message{
                                .title = "Joel",
                                .text  = "Ehhhh, okay. I'll see if I can pay you back for the pie. Thanks, Ms. Maggie Pie.",
                            },
                            Message{
                                .title = "Maggie Pie",
                                .text  = "It's just 'Maggie!' And don't be a stranger, honey bunny!",
                            },
                            Message{
                                .title = "Fren",
                                .text  = "Híhi. 'Hönni bönni.",
                            },
                            Message{
                                .title = "Joel",
                                .text  = "SHADDAP!!!",
                            },
                        }
                    });
}

inline void CreateJack(World &world, Tile &tile) {
    CreateCharacter(world, tile, "", {
                        .messages = {
                            Message{
                                .title = "Jack Black™",
                                .text  = "Yo, yo, yo! How’s it goin’, duderinos? Do ya like the view from up here? Pretty sweet, right?",
                            },
                            Message{
                                .title = "Joel",
                                .text  = "I've seen better, to be honest. Like that one time in-",
                            },
                            Message{
                                .title = "Jack Black™",
                                .text  = "Don't care, but check this out. I got this super duper awesomesauce CD stashed here somewhere. could you get it for me? Pretty, pretty please?",
                            },
                            Message{
                                .title = "Jack Black™",
                                .text  = "Could you get it for me? Pretty, pretty, pretty, pretty please?",
                            },
                            Message{
                                .title = "Joel",
                                .text  = "Maybe. Depends on what we gain from this...",
                            },
                            Message{
                                .title = "Jack Black™",
                                .text  = "You get to hear the most jawdropping symphony of tunes that your puny mind is even capable of hearing!",
                            },
                            Message{
                                .title = "Jack Black™",
                                .text  = "Plus it is mandatory to progress in this game.",
                            },
                            Message{
                                .title = "Fren",
                                .text  = "vat?",
                            },
                            Message{
                                .title = "Jack Black™",
                                .text  = "Oh nothing... So, are you brave enough to do such a task?",
                            },
                            Message{
                                .title = "Joel",
                                .text  = "Fine, but only because you were in my dreams lately, for some odd reason.",
                            },
                            Message{
                                .title = "Jack Black™",
                                .text  = "Yeeaaahh, that's what I like to hear! Report to me back once you get it.",
                            },
                        }
                    });
}

inline void CreateGrill(World &world, Tile &tile) {
    CreateItem(world, tile, "", {
                   .messages = {
                       Message{
                           .title = "Grill",
                           .text  = "You obtained 'Grill'. George Foreman branded.",
                       },
                   }
               });
}

inline void CreateStatuette(World &world, Tile &tile) {
    CreateItem(world, tile, "", {
                   .messages = {
                       Message{
                           .title = "Statuette",
                           .text  = "You obtained 'Statuette'. The name of this piece is 'Bald Is Beautiful'.",
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
                           .text  = "You obtained 'Bible Verse'. It's a highlighted verse, Leviticus 13:40.",
                       },
                   }
               });
}

inline void CreateRadio(World &world, Tile &tile) {
    CreateItem(world, tile, "", {
                   .messages = {
                       Message{
                           .title = "Radio",
                           .text  = "You obtained 'Radio'.",
                       },
                   }
               });
}

inline void CreateMaxwell(World &world, Tile &tile) {
    CreateItem(world, tile, "", {
                   .messages = {
                       Message{
                           .title = "Maxwell",
                           .text  = "You obtained 'Maxwell'. The piebald cat. :3",
                       },
                   }
               });
}

inline void CreateCd(World &world, Tile &tile) {
    CreateItem(world, tile, "", {
                   .messages = {
                       Message{
                           .title = "CD",
                           .text  = "You obtained 'CD'. Contains 'Night on Bald Mountain' compositions.",
                       },
                   }
               });
}

inline void CreateDoor(World &world, Tile &tile, const std::string &mapPath) {
    const Entity door = world.Registry().Create(Transform{}, SpriteRenderer{.spritePath = ""}, Door{.mapPath = mapPath});
    tile.occupant     = door;
}

inline void LoadMap(World &world, const std::string &mapPath, const bool overworld = false) {
    const auto txt = FileIo::ReadText(mapPath).value();

    Debug::LogInf("Loading '{}', Overworld: {}", mapPath, overworld);

    world.Registry().ForEach<Entity, Tile>([&](const Entity e, const Tile &tile) {
        if (tile.HasOccupant()) {
            world.Registry().Destroy(tile.occupant);
        }

        world.Registry().Destroy(e);
    });

    world.Registry().All<Fren>().ForEach<Entity>([&](const Entity e) {
        world.Registry().Destroy(e);
    });

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

        Vector2i pos = {world.Resource<PlayerInfo>().overworldPos.x, world.Resource<PlayerInfo>().overworldPos.y};
        Vector2i prevPos = {world.Resource<PlayerInfo>().overworldPrevPos.x, world.Resource<PlayerInfo>().overworldPrevPos.y};

        if (c == 'P' && !overworld) {
            const Entity player = world.Registry().Create(
                Transform{.position = Vector3f{tile.position}, .scale = {0.62F, 1.0F, 1.0F}},
                SpriteRenderer{.spritePath = "assets/joel.png"},
                Player{
                    .inOverworld = false
                }
            );

            tile.occupant = player;
        }

        if (tile.position == pos && overworld) {
            const Entity player = world.Registry().Create(
                Transform{.position = Vector3f{tile.position}, .scale = {0.62F, 1.0F, 1.0F}},
                SpriteRenderer{.spritePath = "assets/joel.png"},
                Player{
                    .inOverworld = true
                }
            );

            tile.occupant = player;
        }

        if (c == 'f' && !overworld) {
            world.Registry().Create(
                Transform{
                    .position = Vector3f{tile.position},
                    .scale    = {0.62F, 1.0F, 1.0F}
                },
                SpriteRenderer{.spritePath = "assets/fren.png"},
                Fren{}
            );
        }

        if (tile.position == prevPos && overworld) {
            world.Registry().Create(
                Transform{
                    .position = Vector3f{tile.position},
                    .scale    = {0.62F, 1.0F, 1.0F}
                },
                SpriteRenderer{.spritePath = "assets/fren.png"},
                Fren{}
            );
        }

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

        if (c == 'p') {
            CreateMaggie(world, tile);
        }

        if (c == 'J') {
            CreateJack(world, tile);
        }

        if (c == 'g') {
            CreateGrill(world, tile);
        }

        if (c == 'B') {
            CreateStatuette(world, tile);
        }

        if (c == 'b') {
            CreateVerse(world, tile);
        }

        if (c == 'r') {
            CreateRadio(world, tile);
        }

        if (c == 'm') {
            CreateMaxwell(world, tile);
        }

        if (c == 'c') {
            CreateCd(world, tile);
        }

        if (c == '0') {
            CreateDoor(world, tile, "assets/map.txt");
        }

        if (c > '0' && c <= '9') {
            std::string path = "assets/";
            path             += c;
            path             += ".txt";
            CreateDoor(world, tile, path);
        }

        x++;
    }
}

#endif //MAP_HPP
