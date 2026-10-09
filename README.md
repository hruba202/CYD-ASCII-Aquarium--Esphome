# CYD-ASCII-Aquarium--Esphome ,Aquarium-- Elecrow CrowPanel Advance with a voice assistant.
An ESPHome port of the popular retro ASCII Aquarium and digital clock, fully optimized for the ESP32 CYD (Cheap Yellow Display) boards. Features native switch integration for Home Assistant.
# ESPHome Retro ASCII Aquarium (for ESP32 CYD)

# ESPHome Retro ASCII Aquarium (for ESP32 CYD)

A complete, asynchronous **ESPHome external component** port of the retro ASCII Aquarium and digital clock, optimized specifically for the **ESP32 CYD (Cheap Yellow Display / ESP32-2432S028R)**. 

This project is **inspired by and heavily based on the original standalone Arduino project [POWER-PILL/ASCII-Aquarium](https://github.com/POWER-PILL/ASCII-Aquarium)**. It rewrites the core physics and text-rendering engine to work natively inside the ESPHome ecosystem.

It renders animated text-based fishes, plants, and rising bubbles on the display while exposing a complete set of clean, English-named control entities natively to your **Home Assistant** dashboard.

## 🎛️ Exposed Home Assistant Entities

Once flashed, this project automatically exposes the following native controls to your Home Assistant dashboard:

### Switches
- **Show large clock:** Toggles the massive, central retro ASCII digits on and off.
- **Show a small clock in the corner:** Toggles the time display on the left side of the top header bar.
- **Show date in the header:** Toggles the dynamic date display (`d.m.`) on the right side of the header.
- **Display the clock with the date in a frame:** Draws an elegant geometric blue frame/box around the central large clock for a structured look.

### Controls & Adjustments
- **Number of fish:** A slider to dynamically adjust the fish density inside the tank (supports 1 to 15 animated fishes).
- **Aquarium flow rate:** A step control to adjust the floating simulation speed multiplier of the entire ecosystem.
- **Display backlight:** Standard light entity to dim or boost the screen brightness using native ESP32 PWM (LEDC).

### Actions
- **Pour out the feed:** A button entity that instantly spawns fish-feeding animations, making the school of fish temporarily accelerate.

---

## 📂 Repository Structure

To use this component, map your Home Assistant `/config/esphome/` directory as follows:

```text
├── akvarium.yaml                 # Main configuration YAML file
└── my_components/
    └── ascii_aquarium/
        ├── __init__.py            # Python component environment registry
        └── ascii_aquarium.h        # C++ physics & rendering matrix engine
```

## ⚙️ Layout Specifications

The top status header dynamically scales and auto-centers (`TextAlign::TOP_CENTER`) based on your active switch configurations, offering a smooth layout string format:
`hh:mm -- CYD AQUARIUM -- d.m.`

The giant retro clock digits are bound to a strict multi-dimensional char grid (`const char rows`) inside the C++ engine, preventing text layout shifts, uneven spacing, or missing digit segments across different ESPHome compiler revisions.

## 🎚️ Credits & Inspiration

This project is a full ESPHome port based on:
- **Original Project:** [ASCII-Aquarium by POWER-PILL](https://github.com/POWER-PILL/ASCII-Aquarium) — Exceptional retro standalone firmware for the ESP32 Cheap Yellow Display. 

## 📜 License

This project is open-source under the MIT License. Feel free to fork, customize your own fish strings, and share your setups!


This project is open-source under the MIT License. Feel free to fork, customize your own fish strings, and share your setups!
<img width="1627" height="836" alt="ag1" src="https://github.com/user-attachments/assets/83096b5d-4308-4351-93b6-9359925b5b09" />
<img width="2016" height="1512" alt="ag5" src="https://github.com/user-attachments/assets/90ae8380-2f04-4e8e-9925-b4349141c445" />
<img width="2016" height="1512" alt="ag4" src="https://github.com/user-attachments/assets/b0e9a719-6171-4511-b914-b78559d44441" />
<img width="2016" height="1512" alt="ag3" src="https://github.com/user-attachments/assets/edf49231-201b-44c8-9d23-d44dbffc2135" />
<img width="2016" height="1512" alt="ag2" src="https://github.com/user-attachments/assets/c333d464-5a9a-430e-9ffd-d77443d12ee9" />
