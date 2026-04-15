#ifndef MAP_HPP
#define MAP_HPP

#include "AudioHandler.hpp"
#include "Door.hpp"
#include "Flock.hpp"
#include "GameState.hpp"
#include "Tile.hpp"
#include "Using.hpp"

inline void CreateCharacter(World &world, Tile &tile, const std::string &name, const std::vector<Dialogue> &dialogue) {
    const Entity character = world.Registry().Create(
        Transform{},
        SpriteRenderer{.spritePath = "assets/sprites/" + name + ".png"},
        Interactable{
            .name     = name,
            .dialogue = dialogue,
            .isItem   = false,
            .locked   = false,
        }
    );

    tile.occupant = character;
}

inline void CreateItem(World &world, Tile &tile, const std::string &name, const Dialogue &dialogue) {
    const Entity character = world.Registry().Create(
        Transform{},
        SpriteRenderer{.spritePath = "assets/sprites/" + name + ".png"},
        Interactable{
            .name     = name,
            .dialogue = {dialogue},
            .isItem   = true,
            .locked   = true,
        }
    );

    tile.occupant = character;
}

inline void CreateMike(World &world, Tile &tile) {
    CreateCharacter(
        world,
        tile,
        "mike",
        {
            // Initial
            {
                .messages = {
                    Message{
                        .title = "Joel",
                        .text  = "YOOOOOO! My main man, Michael of Jabronos!",
                    },
                    Message{
                        .title = "Mike",
                        .text  = "Joey Vsauce! Hey! Waddup, dude!",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Fren told me there was some sorta curse in the land by some cult or something.",
                    },
                    Message{
                        .title = "Mike",
                        .text  = "A doomsday cult?",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Something like that. You heard anything about it?",
                    },
                    Message{
                        .title = "Mike",
                        .text  = "Naaaah, nothin' like that lately. But hey, man, can you do me a favor?",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Sure, man, anything for my main man Mike!",
                    },
                    Message{
                        .title = "Mike",
                        .text  = "I was at the beach a few days ago, and I lost my favorite body pil- uh, I mean, BEACH TOWEL.",
                    },
                    Message{
                        .title = "Mike",
                        .text  =
                        "It's got Saitama on it, and now I've got nothing to hug when chat calls me 'bald' or 'red' on stream anymore.",
                    },
                    Message{
                        .title = "Mike",
                        .text  = "Also, my GERD gets worse without it.",
                    },
                    Message{
                        .title = "Fren",
                        .text  = "do nat worri, it vill be araund hiere sumwere",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Wait, you're telling me you don't have a security blanket, but a security... beach towel?",
                    },
                    Message{
                        .title = "Mike",
                        .text  = "Uuuhhh yeah, a 'security' beach towel. It's got, like... so many COMFY memories.",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Hey, man, I understand.",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "...Wait a minute, I thought you HATED comfy things.",
                    },
                    Message{
                        .title = "Mike",
                        .text  = "SHADDAP!!! Are you gonna help me or not??",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Yeah! I'm off now! Gonna check the beach for your... uh, beach towel!",
                    },
                    Message{
                        .title  = "Mike",
                        .text   = "Git goin' and good luck!",
                        .events = {"u_pillow"},
                    },
                    // ...
                },
            },
            // Obtain 1st Item (body pillow)
            {
                .messages = {
                    Message{
                        .title  = "Mike",
                        .text   = "Did you find it?",
                        .events = {"r_pillow"},
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Yeah, I think so! ...Though, isn't it kinda thick for a beach tow-",
                    },
                    Message{
                        .title = "Mike",
                        .text  = "Thank you so much, man!!! Thought I lost it for real this time.",
                    },
                    Message{
                        .title  = "Joel",
                        .text   = "Aw, no problem, dude! Hope this helps your GERD get better.",
                        .events = {"b_mike", "a_mike"}
                    },
                }
            },
            {
                .messages = {
                    Message{
                        .title = "Mike",
                        .text  = "WHAT DA HELL?!?",
                    },
                    Message{
                        .title = "Mike",
                        .text  = "Did you do this to me, Joel???",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "BAHAHAHAHAHAHAAAA! BALD!",
                    },
                    Message{
                        .title = "Fren",
                        .text  = "de NO of HAIR! híhí!",
                    },
                    Message{
                        .title = "Mike",
                        .text  = "It's YOU, Joel! YOU'RE the Doomsday cult! You cursed me to be BALD!",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "WHOA! It's nothing like that! I... I just wasn't expecting you to suddenly turn baaalahaHAHAHA!!!",
                    },
                    Message{
                        .title = "Mike",
                        .text  = "YOU KNOW WHAT? SCREW YOU, JOEL!",
                    },
                    Message{
                        .title = "Mike",
                        .text  =
                        "Go find an electric toothbrush for me! They can stimulate blood vessels in the scalp and reverse baldness. Now GO!",
                        .events = {"u_toothbrush"}
                    },
                },
            },
            {
                .messages = {
                    Message{
                        .title  = "Mike",
                        .text   = "Oh thank God, you found the toothbrush, give it to me",
                        .events = {"r_toothbrush"}
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Okay, here ya go.",
                    },
                    Message{
                        .title = "Mike",
                        .text  = "Oooooh, I can feel the hair coming back already.",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Mike, I think it's doing quite the opposite, actually.",
                    },
                    Message{
                        .title = "Mike",
                        .text  = "You don't know shit, Joel, there is definitely something going on up there.",
                    },
                    Message{
                        .title  = "Joel",
                        .text   = "Yeah, I can see that, but you don't.",
                        .events = {"b_mike", "a_mike"}
                    },
                },
            },
            {
                .messages = {
                    Message{
                        .title = "Mike",
                        .text  = "Are you serious? WHAT THE FUCK, JOEY?!!",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Hey, don't blame me, you did this to yourself.",
                    },
                    Message{
                        .title = "Mike",
                        .text  = "Is this gonna be another Wigsaw bit? Is this how you're gonna torture me?",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "I wasn't even planning on that, man...",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "But now that you've mentioned it...",
                    },
                    Message{
                        .title = "Mike",
                        .text  = "Do not even fockin' think about doin' this shit.",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Okay, man, I won't.",
                    },
                    Message{
                        .title  = "Mike",
                        .text   = "If you don't find anything that can remotely cheer me up now, don't even bother coming back.",
                        .events = {"u_statuette"}
                    },
                },
            },
            {
                .messages = {
                    Message{
                        .title  = "Mike",
                        .text   = "What is this?",
                        .events = {"r_statuette"}
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Found this nearby and it reminded me of you.",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "So I've figured it would be great as a gift for you, to make up for the baldness on your head.",
                    },
                    Message{
                        .title = "Mike",
                        .text  =
                        "Oh, Joel, that is actually sweet of you. I wouldn't guess in a million years that you would do such a thing.",
                    },
                    Message{
                        .title = "Mike",
                        .text  = "Thank you",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Yeah, no problem, man. You're still my friend, right?",
                    },
                    Message{
                        .title  = "Mike",
                        .text   = "Of course!",
                        .events = {"b_mike", "a_mike"}
                    },
                },
            },
            // TURBO BALD
            {
                .messages = {
                    Message{
                        .title = "Joel",
                        .text  = "Uh oh.",
                    },
                    Message{
                        .title = "Mike",
                        .text  = "This. Cannot. Be real. HOW IS THIS EVEN POSSIBLE?!!",
                    },
                    Message{
                        .title = "Mike",
                        .text  = "This fockin' sucks, dude…",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Calm down, man. It ain't that horrible.",
                    },
                    Message{
                        .title = "Mike",
                        .text  = "I AM A FOCKIN' SKELETON NOW, JOEL!!!",
                    },
                    Message{
                        .title = "Mike",
                        .text  = "WHY ARE YOU DOING THIS TO ME!",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Mike, look at the bright side (of your head lmfao).",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "The baldness does look good on you. You should embrace it now.",
                    },
                    Message{
                        .title = "Mike",
                        .text  = "I hate you, Joel.",
                    },
                    // ...
                },
            },
        }
    );
}

inline void CreateChris(World &world, Tile &tile) {
    CreateCharacter(
        world,
        tile,
        "chris",

        {
            {
                .messages = {
                    Message{
                        .title = "Chris",
                        .text  = "WHAT’S UP BRO? DO YA WANT TO BECOME A GAJILLIONAIRE JUST LIKE ME?!!",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Wha...",
                    },
                    Message{
                        .title = "Chris",
                        .text  = "IN ORDER TO BE RICH LIKE ME, YA NEED TO INVEST IN VARGCOIN, BRO!",
                    },
                    Message{
                        .title = "Chris",
                        .text  = "IT’S LIKE THE FUTURE, BRO! EVERYONE BASICALLY USES IT NOW!",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Sorry, but I don’t-",
                    },
                    Message{
                        .title = "Chris",
                        .text  = "WHAT? YA THINK THIS IS DUMB OR SOMETHIN', BRO? YA THINK YOU'RE FUNNY?",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "I just don't believe in this kind of creepto scam shit, y'know?",
                    },
                    Message{
                        .title = "Chris",
                        .text  = "SO YA SAYIN' THAT YOU'RE OLD? GET IN WITH THE TIMES, BRO.",
                    },
                    Message{
                        .title = "Chris",
                        .text  = "THOSE STUPID NERD DOLLARS WILL NEVER MATCH THE AURA THE VARGCOIN HAS, BRO.",
                    },
                    Message{
                        .title  = "Joel",
                        .text   = "Whatever...",
                        .events = {"u_coin"},
                    },
                }
            },
            {
                .messages = {
                    Message{
                        .title  = "Chris",
                        .text   = "WHAT THE FUCK IS THIS, BRO? ARE YA STUPID OR SOMETHIN'?",
                        .events = {"r_coin"}
                    },
                    Message{
                        .title = "Fren",
                        .text  = "one dolar"
                    },
                    Message{
                        .title = "Chris",
                        .text  = "I DON’T WANT THIS! THIS IS WORTHLESS!"
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Is it really, though?"
                    },
                    Message{
                        .title = "Chris",
                        .text  = "YEAH, BRO! I KNOW WHAT I'M DOIN'. I'M BASICALLY A GENIUS, BRO!"
                    },
                    Message{
                        .title = "Chris",
                        .text  = "I CAN BE THE NEXT PRESIDENT, BRO!"
                    },
                    Message{
                        .title = "Chris",
                        .text  = "BUT I DON'T WANT TO, BECAUSE I'M VERY RICH NOW!"
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Suuuree...",
                    },
                    Message{
                        .title = "",
                        .text  =
                        "Please imagine that Chris gets balded by a bald eagle flying by, also snatching the dollar from his hand.",
                        .events = {"b_chris"}
                    },
                    Message{
                        .title = "Chris",
                        .text  = "NOOOOOO! MY WIG!!! HOW WILL I SELL MY SCAM COURSES NOW?!!"
                    },
                    Message{
                        .title = "Chris",
                        .text  = "I MEAN, BUSINESS OPPORTUNITIES, HAHA."
                    },
                    Message{
                        .title = "Fren",
                        .text  = "haha :)"
                    },
                    Message{
                        .title = "Chris",
                        .text  = "I GOTTA THINK OF SOMETHIN' TO TAKE ADVANTAGE OF LIKE, RIGHT NOW, BRO."
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Really? You are still gonna do this?"
                    },
                    Message{
                        .title = "Chris",
                        .text  = "YEAH, I LOVE DOIN' THIS SHIT."
                    },
                    Message{
                        .title  = "Chris",
                        .text   = "SEEIN' THEM CRYIN' OVER THEIR LOST MONEY, THAT IS VERY FUNNY, BRO.",
                        .events = {"a_chris"}
                    },
                }
            },
            {
                .messages = {
                    Message{
                        .title = "Chris",
                        .text  = "NOW STAY AWAY FROM ME, BRO. I DON'T WANT TO SEE YA EVER AGAIN.",
                    }
                }
            }
        }
    );
}

inline void CreateSamson(World &world, Tile &tile) {
    CreateCharacter(
        world,
        tile,
        "samson",
        {
            {
                .messages = {
                    Message{
                        .title = "Samson",
                        .text  =
                        "Shalom to you, good sir. I wish I could greet you with more mirth on this day, but alas, I have lost something of great importance.",
                    },
                    Message{
                        .title = "Samson",
                        .text  =
                        "It is as important to me as the locks on my head.",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "/sAnother dude who's all tangled up with his hair...",
                    },
                    Message{
                        .title = "Samson",
                        .text  = "I'm sorry, what was that?",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Oh! Um, ah, I mean, eh... What is you're, ah, looking for, my dude?",
                    },
                    Message{
                        .title = "Samson",
                        .text  = "Have you perhaps stumbled upon a large, leather-bound book by any chance in this area?",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Unfortunately I did not, man. I am sorry about that.",
                    },
                    Message{
                        .title = "Samson",
                        .text  = "That is a real shame...",
                    },
                    Message{
                        .title = "Samson",
                        .text  = "But if you do find it somewhere, please let me know right away.",
                    },
                    Message{
                        .title = "Fren",
                        .text  = "vat hapen if yu do not find it?",
                    },
                    Message{
                        .title = "Samson",
                        .text  = "Are you certain you truly want to know the answer to that, my small gremloid friend?",
                    },
                    Message{
                        .title = "Fren",
                        .text  = "...",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Alright, I'll see what I can do.",
                    },
                    Message{
                        .title  = "Samson",
                        .text   = "Thank you very much. Godspeed on your quest, young men! Shalom!",
                        .events = {"u_jack"}
                    },
                }
            },
            {
                .messages = {
                    Message{
                        .title  = "Samson",
                        .text   = "Hallelujah, my brothers! You have found it!",
                        .events = {"r_verse"}
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Hey, no problem, man. Glad something finally went right today."
                    },
                    Message{
                        .title = "Samson",
                        .text  = "Indeed, young one. Peace be upon you."
                    },
                    Message{
                        .title = "Samson",
                        .text  = "As a reward, I will give you the recipe for my hair oil from this. Just a moment."
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Uhh, I don't think I've seen any notes written on this."
                    },
                    Message{
                        .title = "Samson",
                        .text  = ",,,"
                    },
                    Message{
                        .title = "Samson",
                        .text  = "I regret to tell you this, brothers, but this is not the book I was seeking."
                    },
                    Message{
                        .title = "Fren",
                        .text  = "ooo neeeej"
                    },
                    Message{
                        .title = "Samson",
                        .text  = "But it appears to be a highlighted passage... Leviticus 14:40."
                    },
                    Message{
                        .title = "Samson",
                        .text  = "'If a man's hair falls out from his head, he is bald; he is clean.'"
                    },
                    Message{
                        .title  = "Samson",
                        .text   = "What is so significant about this?",
                        .events = {"b_samson"}
                    },
                    Message{
                        .title = "Fren",
                        .text  = "háhá b a l d"
                    },
                    Message{
                        .title = "Samson",
                        .text  = "What? Are you mocking me???"
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Nononono, that's not true at all! It's totally a misunderstanding. Isn't that right, Fren?"
                    },
                    Message{
                        .title = "Fren",
                        .text  = "háhá myega b a l d"
                    },
                    Message{
                        .title  = "Samson",
                        .text   = "I will not tolerate this ridicule anymore! I curse you in the name of the Lord!",
                        .events = {"b_samson", "a_samson"}
                    },
                }
            },
            {
                .messages = {
                    Message{
                        .title = "Samson",
                        .text  = "Gwrarrhh!!!"
                    }
                }
            }
        }
    );
}

inline void CreateDilto(World &world, Tile &tile) {
    CreateCharacter(
        world,
        tile,
        "dilto",

        {
            {
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
                        .title = "Joel",
                        .text  = "GET AWAY FROM ME NOW!!!",
                    },
                    Message{
                        .title = "D*lto",
                        .text  = "Can yOu HElp mE..?",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "You look like you're already beyond that, man",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Or whatever the hell you are anyways.",
                    },
                    Message{
                        .title = "D*lto",
                        .text  = "Am KiNd of hOmELeSs... NeEd a bED...",
                    },
                    Message{
                        .title = "D*lto",
                        .text  = "PLeAse...",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "If I get you this bed for you, will you leave this bitch of an earth for good?",
                    },
                    Message{
                        .title = "D*lto",
                        .text  = "YeEeSss.. I WilL... LeAve yOu AlOne...",
                    },
                    Message{
                        .title = "Fren",
                        .text  = "butt yu vent tu him frist???",
                    },
                    Message{
                        .title  = "Joel",
                        .text   = "I do not know what you are talking about...",
                        .events = {"u_grill"},
                    },
                }
            },
            {
                .messages = {
                    Message{
                        .title  = "D*lto",
                        .text   = "ThAnk YoU, kINd StrAnGeR...",
                        .events = {"r_grill"}
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Whatever you say, 'buddy'.",
                    },
                    Message{
                        .title = "D*lto",
                        .text  = "fiNAllY... sOmE SlEep...",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Yeah, maybe your last!",
                    },
                    Message{
                        .title  = "D*lto",
                        .text   = "..?",
                        .events = {"b_dilto", "a_dilto"},
                    },
                }
            },
            {
                .messages = {
                    Message{
                        .title = "Fren",
                        .text  = "mmm yummi",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "I didn't trust you in the slightest, so I did what I had to do...",
                    },
                    Message{
                        .title = "D*lto",
                        .text  = "wHaT... dID yoU..?",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Get fucked.",
                    },
                }
            }
        }
    );
}

inline void CreateMaggie(World &world, Tile &tile) {
    CreateCharacter(
        world,
        tile,
        "maggie",

        {
            {
                .messages = {
                    Message{
                        .title = "Joel",
                        .text  = "Uh... hey, magpie lady, are you looking for Zanzibar Island, by any chance?",
                    },
                    Message{
                        .title = "Maggie Pie",
                        .text  = "Oh, hello, young man! No, I actually live here in this house-tree!"
                        "After all, why would I have things monogrammed with my initials everywhere?",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Uh... you just kinda looked like you were in the wrong ga-",
                    },
                    Message{
                        .title = "Maggie Pie",
                        .text  =
                        "Good grief, I forgot to introduce myself! My name is Maggie, Maggie Pie! Nice to meet you, misterrrrr...?",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "...uh, Joel.",
                    },
                    Message{
                        .title = "Joel",
                        .text  =
                        "Nice to meet you, Ms. Pie. By the way, everyone I talk to has lost something or needs an item. Do you need anything?",
                    },
                    Message{
                        .title = "Maggie Pie",
                        .text  = "Please, just call me Maggie! And no, sweetie, I just finished a grocery trip today.",
                    },
                    Message{
                        .title = "Maggie Pie",
                        .text  =
                        "Of course, I won't say no if you found something you'd think I'd like. You're a very sweet young man!",
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
                        .title  = "Joel",
                        .text   = "SHADDAP!!!",
                        .events = {"u_maxwell"},
                    },
                }
            },
            {
                .messages = {
                    Message{
                        .title = "Joel",
                        .text  =
                        "Heyyyyyy, I saw this little boingy boof in my house, and I had no need for him, annnnd he kinda looked like you, so I just want to give him to you as thanks for the pie.",
                        .events = {"r_maxwell"}
                    },
                    Message{
                        .title  = "Maggie Pie",
                        .text   = "Awwww, how sweet of you, baby! He reminds me of my baby Jess before she crossed the Rainbow Ro-",
                        .events = {"b_maggie", "a_maggie"}
                    },
                }
            },
            {
                .messages = {
                    Message{
                        .title = "Joel",
                        .text  = "!!!",
                    },
                    Message{
                        .title = "Fren",
                        .text  = "Hoppsan. :)",
                    },
                    Message{
                        .title = "Maggie Pie",
                        .text  = "M-my hair!",
                    },
                    Message{
                        .title = "Joel",
                        .text  =
                        "Uhhh... l-look... The-there's been re-really weird stuff going on today. You're not the first person this has happened to-",
                    },
                    Message{
                        .title = "Maggie Pie",
                        .text  = "WHY AM I BALD????",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "He-hey! Don't— don't worry! I'm trying to fix it!",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "/sEven though I keep screwing up...",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Wait, you still have all your feathers on your head.",
                    },
                    Message{
                        .title = "Maggie Pie",
                        .text  = "MY HAIR VANISHED!!!",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "But... you're a BIRD? You kinda don't need hair???",
                    },
                    Message{
                        .title = "Maggie Pie",
                        .text  = "WHYYYYYYYIIIIIIEEEEEE",
                    },
                    Message{
                        .title = "Fren",
                        .text  = "give hur yor hat, it vill be happi :)",
                    },
                }
            }
        }
    );
}

inline void CreateJack(World &world, Tile &tile) {
    CreateCharacter(
        world,
        tile,
        "jack",
        {
            {
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
                        .text  =
                        "Don't care, but check this out. I got this super duper awesomesauce CD stashed here somewhere. could you get it for me? Pretty, pretty please?",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Maybe. Depends on what we gain from this...",
                    },
                    Message{
                        .title = "Jack Black™",
                        .text  =
                        "You get to hear the most jawdropping symphony of tunes that your puny mind is even capable of hearing!",
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
                        .title  = "Jack Black™",
                        .text   = "Yeeaaahh, that's what I like to hear! Report to me back once you get it.",
                        .events = {"u_cd"},
                    },
                }
            },
            {
                .messages = {
                    Message{
                        .title  = "Jack Black™",
                        .text   = "WOOOW!!! You are so cool for getting this for me, dudes. Thanks a bunch!",
                        .events = {"r_cd"}
                    },
                    Message{
                        .title  = "Jack Black™",
                        .text   = "Now, behold, the masterpiece that you’re about to have the privilege of hearing",
                        .events = {"dookie"}
                    },
                    Message{
                        .title = "Joel",
                        .text  = "What the hell is this?",
                    },
                    Message{
                        .title = "Fren",
                        .text  = "ouchie mai ears :((",
                    },
                    Message{
                        .title = "Jack Black™",
                        .text  = "What do you mean, guys? This is like, a mankind's achievement in terms of musical arrangements.",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Nah, man. This is shit, my dude.",
                    },
                    Message{
                        .title = "Fren",
                        .text  = "straigt ap dukie nukie :((((((",
                    },
                    Message{
                        .title = "Jack Black™",
                        .text  = "And I thought you would understand the sheer depth of this masterful work.",
                    },
                    Message{
                        .title  = "Jack Black™",
                        .text   = "Everyone's a critic nowadays.",
                        .events = {"b_jack"}
                    },
                    Message{
                        .title  = "Bible Verse",
                        .text   = "Jack Black™ dropped something. you picked up 'Bible Verse', It's a highlighted verse, Leviticus 13:40.",
                        .events = {"a_verse", "a_jack"}
                    },
                }
            },
            {
                .messages = {
                    Message{
                        .title = "Jack Black™",
                        .text  = "Oh yeah! This is the shit!",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Didn't you notice that you have no hair now?",
                    },
                    Message{
                        .title = "Jack Black™",
                        .text  = "So?",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Alright then.",
                    },
                }
            }
        }
    );
}

inline void CreateVinny(World &world, Tile &tile) {
    CreateCharacter(
        world,
        tile,
        "vinny",
        {
            {
                .messages = {
                    Message{
                        .title = "Joel",
                        .text  = "Oh, hey, Vin!"
                    },
                    Message{
                        .title = "Vinny",
                        .text  = "SpEeEeEeEeEeEeEeEe—"
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Hey, Vinny, can you please stop spinning for a sec?"
                    },
                    Message{
                        .title = "Vinny",
                        .text  = "—EeEeEeEeEeEeEeEe—"
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Vinny..."
                    },
                    Message{
                        .title = "Vinny",
                        .text  = "—EeEeEeEeEeEeEeEeEeEeEeEe—"
                    },
                    Message{
                        .title = "Joel",
                        .text  = "VINNAMON TOAST CRUNCH!"
                    },
                    Message{
                        .title = "Vinny",
                        .text  = "—EeEeEeEeEeEeEeNnNn!!!!"
                    },
                    Message{
                        .title = "Joel",
                        .text  = "...You good, man?"
                    },
                    Message{
                        .title = "Vinny",
                        .text  = "Oh. Yeah. Well, except for the fact that my Internet's been down for over a week."
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Is that why you were SPEENing?"
                    },
                    Message{
                        .title = "Vinny",
                        .text  = "NO."
                    },
                    Message{
                        .title = "Vinny",
                        .text  = "..."
                    },
                    Message{
                        .title = "Vinny",
                        .text  = "Okay, maybe."
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Well, that stinks."
                    },
                    Message{
                        .title  = "Vinny",
                        .text   = "Unless you can somehow make my Vinerizon network magically start working again, then not really.",
                        .events = {"u_card"}
                    },
                }
            },
            {
                .messages = {
                    Message{
                        .title = "Joel",
                        .text  = "Hey, Vinny, I think I found the prob—",
                    },
                    Message{
                        .title = "Vinny",
                        .text  = "—eEeEeEeEeEeEeEeEeEeEeEe—",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Not again...",
                    },
                    Message{
                        .title = "Vinny",
                        .text  = "—EeEeEeEeEeEeEeEeEeEeEe—",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Vinny. Viiiiiinnyyyyyy.",
                    },
                    Message{
                        .title = "Vinny",
                        .text  = "—eEeEeEeEeEeEeEeEeEeEe—",
                    },
                    Message{
                        .title  = "Joel",
                        .text   = "*Chucks Vinerizon card at Vinny*",
                        .events = {"r_card"}
                    },
                    Message{
                        .title = "Vinny",
                        .text  = "—EeEeEeEeeeeehuh?",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "FINALLY. Now, is your Internet fixed, man?",
                    },
                    Message{
                        .title = "Vinny",
                        .text  = "Actually, yeah.",
                    },
                    Message{
                        .title  = "Vinny",
                        .text   = "YEEEEAAAAAAH! Finally fixed some AGGA on my own for once!",
                        .events = {"b_vinny", "a_vinny"},
                    },
                }
            },
            {
                .messages = {
                    Message{
                        .title = "Vinny",
                        .text  = "Uhhhh... what's going on here?",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Not sure how to put this gently, but... you're bald now.",
                    },
                    Message{
                        .title = "Vinny",
                        .text  = "Bald?!!",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Yeah...",
                    },
                    Message{
                        .title = "Vinny",
                        .text  = "WHADDYA MEAN I'M BALD???",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "L-look, man! I don't know! All I know is that you're hairless now!",
                    },
                    Message{
                        .title = "Vinny",
                        .text  = "...",
                    },
                    Message{
                        .title = "Vinny",
                        .text  = "Well, at least my Internet's back."
                    },
                    Message{
                        .title = "Vinny",
                        .text  = "4hed now liek vineRizon. híhí.",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "FREN. SHUT UP.",
                    },
                }
            }
        }
    );
}

inline void CreateGirlfren(World &world, Tile &tile) {
    CreateCharacter(
        world,
        tile,
        "girlfren",
        {
            {
                .messages = {
                    Message{
                        .title = "???",
                        .text  = "Hahaha, I've been expecting you... JOEL!!!",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "Who are you?!! And how the FUCK do you know my name?!!"
                    },
                    Message{
                        .title = "???",
                        .text  = "Isn't this already obvious to you by now?",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "...No? How was I supposed to know, there weren't many clues, you know?",
                    },
                    Message{
                        .title  = "???",
                        .text   = "Ah, okay, makes sense. Let me make this very clear to you then.",
                        .events = {"reveal"}
                    },
                    Message{
                        .title = "Fren",
                        .text  = "VAT??? IT VAS YU ALL ALONG???",
                    },
                    Message{
                        .title = "Girlfren",
                        .text  = "Yes, Fren. It was me.",
                    },
                    Message{
                        .title = "Fren",
                        .text  = "BUTT VAI??? VAI YU DO DIS???",
                    },
                    Message{
                        .title = "Girlfren",
                        .text  = "Because I am tired of this. Tired of everyone having lucious hair while I don't!",
                    },
                    Message{
                        .title = "Girlfren",
                        .text  =
                        "Don't people realise that by being bald, they're opening up their souls with their shiny heads to Him?",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "I do not understand ANYTHING you just said. Who is 'Him' anyways?",
                    },
                    Message{
                        .title = "Girlfren",
                        .text  =
                        "When we finally summon Him, we will turn every human, every animal, every living organism into having the no of hair!!!",
                    },
                    Message{
                        .title = "Girlfren",
                        .text  = "And with you already being here, I can start the first phase!",
                    },
                    Message{
                        .title = "Girlfren",
                        .text  = "THEN EVERYONE WILL BOW BEFORE US AND GIVE UP THEIR EXISTENCE TO HIM!!!",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "That is NOT cool of you to do that, so please stop this right away, okay thanks.",
                    },
                    Message{
                        .title = "Fren",
                        .text  = "yeee, vat he sed >:)",
                    },
                    Message{
                        .title = "Girlfren",
                        .text  = "I got everything ready, there's no way of stopping me now...",
                    },
                    Message{
                        .title = "Girlfren",
                        .text  = "RELEASE HIM...",
                    },
                    Message{
                        .title = "Girlfren",
                        .text  = "RELEASE...",
                    },
                    Message{
                        .title  = "Girlfren",
                        .text   = "THE ULTIMATE BALDY!!!",
                        .events = {"steve"}
                    },
                    Message{
                        .title = "STEVE AUSTIN",
                        .text  = "STONE COLD!",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "What?",
                    },
                    Message{
                        .title = "STEVE AUSTIN",
                        .text  = "STONE COLD!!",
                    },
                    Message{
                        .title = "Fren",
                        .text  = "vat?",
                    },
                    Message{
                        .title = "STEVE AUSTIN",
                        .text  = "STONE COLD!!!",
                    },
                    Message{
                        .title = "Girlfren",
                        .text  = "What?",
                    },
                    Message{
                        .title = "STEVE AUSTIN",
                        .text  = "THAT'S ME ALRIGHT!",
                    },
                    Message{
                        .title = "STEVE AUSTIN",
                        .text  = "AND I'M READY TO WHOOP SOME ASS TONIGHT!",
                    },
                    Message{
                        .title = "Girlfren",
                        .text  = "Now, we only need you, Joel...",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "What are you on about?",
                    },
                    Message{
                        .title = "Girlfren",
                        .text  = "Have you thought about as to why you made innocent people here bald before you got here?",
                    },
                    Message{
                        .title = "Fren",
                        .text  = "uhhh idk?",
                    },
                    Message{
                        .title = "Girlfren",
                        .text  = "You, Joel, have the power of 'bald bringing'.",
                    },
                    Message{
                        .title = "Joel",
                        .text  = "The WHAT?",
                    },
                    Message{
                        .title = "STEVE AUSTIN",
                        .text  = "THAT'S RIGHT! WITH YOUR POWERS, WE WILL RULE THE WORLD!",
                    },
                    Message{
                        .title = "Girlfren",
                        .text  = "This is why I summoned Him, your bald bringing is too weak on its own.",
                    },
                    Message{
                        .title = "Girlfren",
                        .text  = "If you combine with Him, you'll have the ultimate power!",
                    },
                    Message{
                        .title   = "Joel",
                        .text    = "But is this what I really want? To make everyone have no hair whatsoever?",
                        .choices = {
                            {
                                .messages = {
                                    Message{
                                        .title = "Joel",
                                        .text  = "Fuck that!!!",
                                    },
                                    Message{
                                        .title = "Joel",
                                        .text  = "AND FUCK BOTH OF YOU!!!",
                                    },
                                    Message{
                                        .title = "Girlfren",
                                        .text  = "Wrong answer.",
                                    },
                                    Message{
                                        .title = "STEVE AUSTIN",
                                        .text  = "YOU LUCKY I DON'T HAVE MY SEMENT TRUCK.",
                                    },
                                    Message{
                                        .title = "STEVE AUSTIN",
                                        .text  = "BECAUSE YOU'D END UP BURIED.",
                                    },
                                    Message{
                                        .title = "STEVE AUSTIN",
                                        .text  = "BUT THE FIRST THING I'M GONNA DO IS TO GET YOU OUT OF THIS PLACE.",
                                    },
                                    Message{
                                        .title = "STEVE AUSTIN",
                                        .text  = "NOT JUST FROM HERE, BUT OUT OF THE FACE OF THE EARTH.",
                                    },
                                    Message{
                                        .title = "Joel",
                                        .text  = "We'll see about that!",
                                    },
                                    Message{
                                        .title = "Girlfren",
                                        .text  = "What are you gonna do? You're weak compared to Him anyways.",
                                    },
                                    Message{
                                        .title = "Joel",
                                        .text  = "OH YEAH?!!",
                                    },
                                    Message{
                                        .title = "Fren",
                                        .text  = "nooooo doo nat doodoo it!!!",
                                    },
                                    Message{
                                        .title = "Joel",
                                        .text  = "PREPARE...",
                                    },
                                    Message{
                                        .title = "Joel",
                                        .text  = "...FOR MY BIG BALD BRINGING BEAM!!!",
                                    },
                                    Message{
                                        .title = "STEVE AUSTIN",
                                        .text  = "NOOOO. WHAT ARE YOU DOING?!!",
                                    },
                                    Message{
                                        .title = "Joel",
                                        .text  =
                                        "Since you're already bald, you're gonna turn to dust from the paradox I'm gonna create!",
                                    },
                                    Message{
                                        .title  = "STEVE AUSTIN",
                                        .text   = "AAAAGGGHHHHHH!!! IT BUURRNNSS!!!",
                                        .events = {"goodend", "beam"}
                                    },
                                    Message{
                                        .title = "Girlfren",
                                        .text  = "Wha... What happened?",
                                    },
                                    Message{
                                        .title = "Fren",
                                        .text  = "looki looki, she got hairÃ©!!!",
                                    },
                                    Message{
                                        .title = "Girlfren",
                                        .text  = "Really? Wow... It looks great!",
                                    },
                                    Message{
                                        .title = "Girlfren",
                                        .text  = "But you, Joel...",
                                    },
                                    Message{
                                        .title = "Joel",
                                        .text  = "What?",
                                    },
                                    Message{
                                        .title = "Fren",
                                        .text  = "HAHA YU BALD GAGAGA!!!",
                                    },
                                    Message{
                                        .title = "Joel",
                                        .text  = "Well, the bald bringing beam took my hair with it, I guess...",
                                    },
                                    Message{
                                        .title = "Joel",
                                        .text  = "But it was worth it.",
                                    },
                                    Message{
                                        .title = "Fren",
                                        .text  = "yeeeee :)))",
                                    },
                                    Message{
                                        .title = "Joel",
                                        .text  = "So, what now? That plan of yours didn't really work out, huh?",
                                    },
                                    Message{
                                        .title = "Girlfren",
                                        .text  = "I'm now realizing what it's like to have hair. And it's really comforting for me.",
                                    },
                                    Message{
                                        .title = "Joel",
                                        .text  = "So no more summoning?",
                                    },
                                    Message{
                                        .title = "Girlfren",
                                        .text  = "Yeah, I'm done with this. Let's go home.",
                                    },
                                    Message{
                                        .title  = "Joel",
                                        .text   = "Finally, I got so tired of running around town. I wanna go beddybyes now...",
                                        .events = {"end"},
                                    },
                                }
                            },
                            {
                                .messages = {
                                    Message{
                                        .title = "Joel",
                                        .text  = "Fuck it, why not?",
                                    },
                                    Message{
                                        .title = "Girlfren",
                                        .text  = "That is what we like to hear.",
                                    },
                                    Message{
                                        .title = "Fren",
                                        .text  = "noo yoey vat yu doin???",
                                    },
                                    Message{
                                        .title = "STEVE AUSTIN",
                                        .text  = "YEAH, NOW WE'RE TALKIN'!",
                                    },
                                    Message{
                                        .title  = "Joel",
                                        .text   = "haha funni.",
                                        .events = {"end"},
                                    },
                                }
                            }
                        }
                    },
                },
            }
        }
    );
}

inline void CreateRadio(World &world, Tile &tile) {
    CreateCharacter(
        world,
        tile,
        "radio",
        {
            {
                .messages = {
                    Message{
                        .title  = "Radio",
                        .text   = "It's a radio.",
                        .events = {"radio"}
                    },
                }
            }
        }
    );
}

inline void CreateGrill(World &world, Tile &tile) {
    CreateItem(world, tile, "grill", {
                   .messages = {
                       Message{
                           .title  = "Grill",
                           .text   = "You obtained 'Grill'. George Foreman branded.",
                           .events = {"a_grill"},
                       },
                   }
               });
}

inline void CreateStatuette(World &world, Tile &tile) {
    CreateItem(world, tile, "statuette", {
                   .messages = {
                       Message{
                           .title  = "Statuette",
                           .text   = "You obtained 'Statuette'. A kitschy, whimsical gift to encourage a bald friend.",
                           .events = {"a_statuette"},
                       },
                   }
               });
}

inline void CreateVerse(World &world, Tile &tile) {
    CreateItem(world, tile, "verse", {
                   .messages = {
                       Message{
                           .title  = "Bible Verse",
                           .text   = "You obtained 'Bible Verse'. It's a highlighted verse, Leviticus 13:40.",
                           .events = {"a_verse"},
                       },
                   }
               });
}

inline void CreateMaxwell(World &world, Tile &tile) {
    CreateItem(world, tile, "maxwell", {
                   .messages = {
                       Message{
                           .title  = "Maxwell",
                           .text   = "You obtained 'Maxwell'. The piebald cat. :3",
                           .events = {"a_maxwell"},
                       },
                   }
               });
}

inline void CreateCd(World &world, Tile &tile) {
    CreateItem(world, tile, "cd", {
                   .messages = {
                       Message{
                           .title = "CD",
                           .text  =
                           "You obtained 'CD'. Contains 'Night on Bald Mountain' compositions, a horribly performed version that'll make your hair fall out.",
                           .events = {"a_cd"},
                       },
                   }
               });
}

inline void CreateBodyPillow(World &world, Tile &tile) {
    CreateItem(world, tile, "pillow", {
                   .messages = {
                       Message{
                           .title = "Saitama Body Pillow",
                           .text  =
                           "You obtained 'Saitama Body Pillow'. Saitama is posed like a French girl, giving 'thumbs up' and saying 'OK.'",
                           .events = {"a_pillow"},
                       },
                   }
               });
}

inline void CreateCoin(World &world, Tile &tile) {
    CreateItem(world, tile, "coin", {
                   .messages = {
                       Message{
                           .title  = "Bald Eagle Coin",
                           .text   = "You obtained 'Bald Eagle Coin'. Smells like FREEDOM and TAX EVASION!",
                           .events = {"a_coin"},
                       },
                   }
               });
}

inline void CreateToothbrush(World &world, Tile &tile) {
    CreateItem(world, tile, "toothbrush", {
                   .messages = {
                       Message{
                           .title = "Electric Toothbrush",
                           .text  =
                           "You obtained 'Electric Toothbrush'. Great for removing plaque and stimulating hair follicles.",
                           .events = {"a_toothbrush"},
                       },
                   }
               });
}

inline void CreateCard(World &world, Tile &tile) {
    CreateItem(world, tile, "card", {
                   .messages = {
                       Message{
                           .title  = "Vinerizon Card",
                           .text   = "You obtained 'Vinerizon Card'. DO NOT PRESUME.",
                           .events = {"a_card"},
                       },
                   }
               });
}

inline void CreateDoor(World &world, Tile &tile, const std::string &mapPath) {
    const Entity door = world.Registry().Create(Transform{}, SpriteRenderer{.spritePath = "assets/sprites/door.png"}, Door{.mapPath = mapPath});
    tile.occupant     = door;
}

inline void LoadMap(World &world, const std::string &mapPath, const bool overworld = false) {
    auto       str = mapPath;
    const auto txt = FileIo::ReadText(mapPath).value();

    world.Registry().ForEach<Entity, Tile>([&](const Entity e, const Tile &tile) {
        if (tile.HasOccupant()) {
            world.Registry().Destroy(tile.occupant);
        }

        world.Registry().Destroy(e);
    });

    world.Registry().All<SpriteRenderer>().ForEach<Entity>([&](const Entity e) {
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

        if (!overworld && str != "assets/6.txt") {
            tile.type = Interior;
        }

        if (!overworld && (str == "assets/3.txt" || str == "assets/5.txt" || str == "assets/6.txt")) {
            tile.type = Stone;
        }

        if (c == ',') {
            tile.type = Trail;
        }

        if (c == 's') {
            tile.type = Sand;
        }

        if (c == '#') {
            tile.type = Wall;
        }

        if (c == '$') {
            tile.type = Tree;
        }

        if (c == '#' && str == "assets/6.txt") {
            tile.type = Mountain;
        }

        if (c == 't') {
            tile.type = Trash;
        }

        if (c == 'o') {
            tile.type = Water;
        }

        if (c == 'x') {
            tile.type = Hidden;
        }

        if (c == '-') {
            tile.type = Bones;
        }

        if (c == '=') {
            tile.type = Guy;
        }

        Vector2i pos     = {world.Resource<PlayerInfo>().overworldPos.x, world.Resource<PlayerInfo>().overworldPos.y};
        Vector2i prevPos = {world.Resource<PlayerInfo>().overworldPrevPos.x, world.Resource<PlayerInfo>().overworldPrevPos.y};

        if (c == 'P' && !overworld) {
            const Entity player = world.Registry().Create(
                Transform{.position = Vector3f{tile.position}},
                SpriteRenderer{.spritePath = "assets/sprites/joel.png"},
                Player{
                    .inOverworld = false
                }
            );

            tile.occupant = player;
        }

        if (c == 'P' && overworld) {
            tile.type = Trail;
        }

        if (tile.position == pos && overworld) {
            const Entity player = world.Registry().Create(
                Transform{.position = Vector3f{tile.position}},
                SpriteRenderer{.spritePath = "assets/sprites/joel.png"},
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
                },
                SpriteRenderer{.spritePath = "assets/sprites/fren.png"},
                Fren{}
            );
        }

        if (tile.position == prevPos && overworld) {
            world.Registry().Create(
                Transform{
                    .position = Vector3f{tile.position},
                },
                SpriteRenderer{.spritePath = "assets/sprites/fren.png"},
                Fren{}
            );
        }

        if (c == 'M') {
            CreateMike(world, tile);
        }

        if (c == 'C') {
            CreateChris(world, tile);
            tile.type = Sand;
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

        if (c == 'V') {
            CreateVinny(world, tile);
        }

        if (c == 'j') {
            CreateJack(world, tile);
        }

        if (c == 'G') {
            CreateGirlfren(world, tile);
        }

        if (c == 'g') {
            CreateGrill(world, tile);
        }

        if (c == 'B') {
            CreateStatuette(world, tile);
        }

        if (c == 'b') {
            CreateBodyPillow(world, tile);
            tile.type = Sand;
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

        if (c == 'e') {
            CreateCoin(world, tile);
        }

        if (c == 'E') {
            CreateToothbrush(world, tile);
        }

        if (c == 'v') {
            CreateCard(world, tile);
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

    if (overworld) {
        world.Registry().Create(
            Transform{
                .position = {4.5F, -3.0f, -4.0F},
                .scale    = {2.8F, 1.4F, 1.0F}
            },
            SpriteRenderer{
                .spritePath = "assets/sprites/dumpster.png"
            }
        );

        world.Registry().Create(
            Transform{
                .position = {11.5F, -7.0F, -4.0F},
                .scale    = {5.0F, 5.0F, 1.0F}
            },
            SpriteRenderer{
                .spritePath = "assets/sprites/maggie_house.png"
            }
        );

        world.Registry().Create(
            Transform{
                .position = {21.5F, -15.5F, -9.5F},
                .scale    = {4.0F, 2.0F, 1.0F}
            },
            SpriteRenderer{
                .spritePath = "assets/sprites/club.png"
            }
        );

        world.Registry().Create(
            Transform{
                .position = {18.0F, -7.0F, -4.0F},
                .scale    = {2.0F, 2.0F, 1.0F}
            },
            SpriteRenderer{
                .spritePath = "assets/sprites/pile.png"
            }
        );

        world.Registry().Create(
            Transform{
                .position = {7.5F, -13.0F, -4.0F},
                .scale    = {6.0F, 3.0F, 1.0F}
            },
            SpriteRenderer{
                .spritePath = "assets/sprites/dilto_house.png"
            }
        );
    }

    ApplyGameState(world, world.Resource<GameState>());

    if (str == "assets/5.txt") {
        world.Registry().ForEach<Interactable>([&](const Interactable &interactable) {
            if (interactable.name != "girlfren") {
                return;
            }

            world.Resource<Dialogue>().messages       = interactable.dialogue[interactable.currentDialogue].messages;
            world.Resource<Dialogue>().currentMessage = 0;
        });
    }

    if (str == "assets/1.txt" || str == "assets/2.txt") {
        world.Resource<AudioHandler>().PlayMusic("assets/music/house.oga");
    } else {
        str = str.substr(7);
        str = str.substr(0, str.size() - 4);
        str = "assets/music/" + str + ".oga";
        world.Resource<AudioHandler>().PlayMusic(str);
    }
}

#endif //MAP_HPP
