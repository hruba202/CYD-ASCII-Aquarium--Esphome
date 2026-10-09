#pragma once
#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>

namespace esphome {
namespace ascii_aquarium {

struct AsciiClockGlyph {
    char c;
    const char* rows[6];
};

static const AsciiClockGlyph kAsciiClockStandardGlyphs[] = {
    {'0', {"  ___  ", " / _ \\ ", "| | | |", "| |_| |", " \\___/ ", "       "}},
    {'1', {"  _    ", " / |   ", " | |   ", " | |   ", " |_|   ", "       "}},
    {'2', {" ____  ", "|___ \\ ", "  __) |", " / __/ ", "|_____|", "       "}},
    {'3', {" _____ ", "|___ / ", "  |_ \\ ", " ___) |", "|____/ ", "       "}},
    {'4', {" _  _  ", "| || | ", "| || | ", "|___  |", "    |_|", "       "}},
    {'5', {" _____ ", "| ___| ", "|___ \\ ", " ___) |", "|____/ ", "       "}},
    {'6', {"  __   ", " / /_  ", "| '_ \\ ", "| (_) |", " \\___/ ", "       "}},
    {'7', {" _____ ", "|___  |", "   / / ", "  / /  ", " /_/   ", "       "}},
    {'8', {"  ___  ", " ( _ ) ", " / _ \\ ", "| (_) |", " \\___/ ", "       "}},
    {'9', {"  ___  ", " / _ \\ ", "| (_) |", " \\__, |", "   /_/ ", "       "}},
    {':', {"   ", " _ ", "(_)", " _ ", "(_)", "   "}},
    {' ', {"       ", "       ", "       ", "       ", "       ", "       "}},
};

struct Fish {
    float x;
    float y;
    float speed;
    bool direction;
    std::string art;
};

struct Bubble {
    float x;
    float y;
    float speed;
};

struct Food {
    float x;
    float y;
};

class AsciiAquarium : public Component {
public:
    std::vector<Fish> fishes;
    std::vector<Bubble> bubbles;
    std::vector<Food> foods;
    int max_fishes = 6;
    float speed_multiplier = 1.0f;
    bool show_clock = true;
    bool show_small_clock = true;
    bool show_date = true;
    uint32_t last_update = 0;

    void setup() override {
        for (int i = 0; i < max_fishes; i++) {
            spawn_fish(true);
        }
        for (int i = 0; i < 15; i++) {
            bubbles.push_back({(float)(rand() % 320), (float)(rand() % 200 + 20), 0.4f + (rand() % 80) / 100.0f});
        }
        last_update = millis();
    }

    void loop() override {
        uint32_t now = millis();
        if (now - last_update < 30) return;
        last_update = now;
        update_physics();
    }

    void spawn_fish(bool random_x = false) {
        bool dir = rand() % 2;

        std::vector<std::string> fish_types = {
            dir ? "><>" : "<><",
            dir ? ">==*>" : "<*==<",
            dir ? "><(((x>" : "<x)))><",
            dir ? "~~{o}" : "{o}~~",
            dir ? "><(((o>" : "<o)))><",
            dir ? ">(({{*>" : "<*}}))<"
        };

        Fish f;
        f.x = random_x ? (rand() % 260) : (dir ? -60 : 340);
        f.y = 35 + (rand() % 140);
        f.speed = (0.5f + (rand() % 120) / 100.0f);
        f.direction = dir;
        f.art = fish_types[rand() % fish_types.size()];
        fishes.push_back(f);
    }

    // Krmení: nasype vločky z horní části akvária
    void feed_fishes() {
        for (int i = 0; i < 10; i++) {
            if (foods.size() >= 40) break;
            foods.push_back({(float)(10 + rand() % 300), (float)(25 + rand() % 20)});
        }
    }

    void update_physics() {
        // Pohyb ryb
        for (auto it = fishes.begin(); it != fishes.end(); ) {
            if (it->direction) {
                it->x += it->speed * speed_multiplier;
                if (it->x > 340) { it = fishes.erase(it); continue; }
            } else {
                it->x -= it->speed * speed_multiplier;
                if (it->x < -70) { it = fishes.erase(it); continue; }
            }
            it++;
        }
        while ((int) fishes.size() < max_fishes) {
            spawn_fish(false);
        }
        while ((int) fishes.size() > max_fishes) {
            fishes.pop_back();
        }

        // Bubliny
        for (auto &b : bubbles) {
            b.y -= b.speed * speed_multiplier;
            b.x += sin(b.y / 8.0f) * 0.2f;
            if (b.y < 25) {
                b.y = 220;
                b.x = rand() % 320;
            }
        }

        // Padající krmení
        for (size_t i = 0; i < foods.size();) {
            foods[i].y += 0.6f * speed_multiplier;
            if (foods[i].y > 215) {
                foods.erase(foods.begin() + i);
                continue;
            }
            i++;
        }

        // Ryby plavou za nejbližší vločkou a sní ji
        for (auto &f : fishes) {
            if (foods.empty()) break;
            float mouth_x = f.direction ? f.x + f.art.size() * 8.0f : f.x;
            size_t best = 0;
            float bd = 1e9f;
            for (size_t i = 0; i < foods.size(); i++) {
                float d = fabsf(foods[i].x - mouth_x) + fabsf(foods[i].y - f.y);
                if (d < bd) { bd = d; best = i; }
            }
            float dy = foods[best].y - f.y;
            f.y += dy > 0.8f ? 0.8f : (dy < -0.8f ? -0.8f : dy);
            if (f.y < 30) f.y = 30;
            if (fabsf(foods[best].x - mouth_x) < 14 && fabsf(dy) < 8) {
                foods.erase(foods.begin() + best);
            }
        }
    }

    const AsciiClockGlyph& get_glyph(char c) {
        for (const auto& g : kAsciiClockStandardGlyphs) {
            if (g.c == c) return g;
        }
        return kAsciiClockStandardGlyphs[11];
    }

    template<typename DisplayType, typename FontType, typename ColorType, typename AlignType>
    void draw_ascii_clock(DisplayType &it, int start_x, int start_y, const char* time_str, ColorType color, FontType *font, AlignType align_obj) {
        if (!show_clock) return;

        for (int row = 0; row < 6; row++) {
            std::string row_text = "";
            for (size_t i = 0; time_str[i] != '\0'; i++) {
                const auto& glyph = get_glyph(time_str[i]);
                row_text += glyph.rows[row];
            }
            it.print(start_x, start_y + (row * 14), font, color, align_obj, row_text.c_str());
        }
    }
};

}  // namespace ascii_aquarium
}  // namespace esphome