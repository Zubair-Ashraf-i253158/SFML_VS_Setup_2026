# ❄️ Snow Bros Remake

<div align="center">

![Snow Bros Banner](SFML_VS_Setup_2026/assets/banner.png)

**A modern C++ remake of the classic 1990 arcade game — Snow Bros**

[![Made with SFML](https://img.shields.io/badge/Made%20with-SFML-00ADD8?style=for-the-badge&logo=cplusplus&logoColor=white)](https://www.sfml-dev.org/)
[![Language](https://img.shields.io/badge/Language-C%2B%2B17-blue?style=for-the-badge&logo=cplusplus)](https://en.cppreference.com/)
[![Platform](https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge&logo=windows)](https://www.microsoft.com/windows)
[![OOP Project](https://img.shields.io/badge/OOP-Project-orange?style=for-the-badge)](https://www.nu.edu.pk/)

---

### 👨‍💻 Developed by

| Developer | Roll No | Institution |
|-----------|---------|-------------|
| **Zubair Ashraf** | 3158 | FAST-NU Islamabad |
| **Abdullah Saqib** | 2020 | FAST-NU Islamabad |

**Course:** Object-Oriented Programming (OOP)  Semester Project
**University:** FAST National University of Computer and Emerging Sciences, Islamabad

</div>

---

## 😇 About the Game

Snow Bros Remake is a faithful yet modernized reimagining of the beloved 1990 Toaplan arcade classic. Built entirely in **C++ with SFML**, this project demonstrates the power of **Object-Oriented Programming** through real-world game development.

What makes this remake special? **You play as Naruto Uzumaki** — throwing snowballs instead of kunai, encasing enemies in snow, and kicking them into chain-kill combos across 10 hand-crafted levels.

> *"We took a classic and made it ours,  same soul, new style."*

---

## 💜 Features

###  Gameplay
- **10 full levels** with increasing difficulty and unique enemy variants
- **2 Boss fights** — Mogera (Level 5) and Gamakichi (Level 10) with health bars and attack phases
- **Chain kill system** — kick encased enemies into others for combo kills and bonus drops
- **Bonus levels** (4 & 9) — collect all gems to advance
- **Snow encasement mechanic** — hit enemies twice to fully encase, then kick them

### 🎭 Characters & Customization
- **Play as Naruto Uzumaki** — custom sprite with jump animation
- **Multiplayer support** — Player 2 plays as a cyan-tinted Naruto variant
- **Power-up system** — collect star items for a 5-second speed boost (player turns yellow!)
- **Shop system** — spend gems on Extra Life, Speed Boost, Jump Boost, Snowball Power

### 👾 Enemies
| Enemy | Behavior |
|-------|----------|
| **Bottom** | Ground walker, reverses at walls |
| **Flying Fooga** | Airborne, sine-wave flight pattern |
| **Tornado** | Throws knives at the player |
| **Invisible Enemy** | Appears only when near the player |
| **Mogera** | Boss — spawns babies every 2 seconds |
| **Gamakichi** | Final boss — fires rockets in 5 directions, 3 attack phases |

###  Level Design
- Levels 1–3: Classic enemy mix with increasing counts
- Level 5: **Boss — Mogera** (with baby spawns)
- Levels 6–8: Faster, tougher color variants (green → blue → purple)
- Level 4,9: Bonus level,  all gem collection
- Level 10: **Final Boss  Gamakichi** 

### 🎵 Audio
- **3 dynamic music tracks** that switch automatically:
  -  Menu music (splash, login, menus, shop)
  -  Level music (gameplay levels 1–4, 6–9)
  -  Boss music (levels 5 & 10)
- Music loops seamlessly and never restarts if already playing

###  Account System
- **Login / Signup** with persistent user authentication
- **Leaderboard** — real-time score tracking per user
- Scores saved and updated during gameplay

---

##  Technical Architecture

Built with full **OOP principles**:

```
Enemy (Abstract Base)
├── Botom          ← ground enemy + snow encasement states
├── FlyingFooga    ← flying AI
├── Tornado        ← knife-throwing enemy
├── InvisibleEnemy ← proximity reveal
├── Mogera         ← boss, spawns Mchild babies
│   └── Mchild     ← inherits Bottom
└── Gamakichi      ← final boss, multi-phase rockets
```

### Key OOP Concepts Used
- **Inheritance** — all enemies derive from `Enemy` base class
- **Polymorphism** — `hitByBall()`, `update()`, `draw()` are virtual; each enemy overrides them
- **Encapsulation** — each class manages its own state, textures, and health
- **Composition** — `Mogera` contains `Mchild babies[50]`; `Player` contains `SnowBall ball[10]`
- **Operator Overloading** — copy constructors properly handle SFML texture ownership

### State Machine (Enemy Snow System)
```
State 0 → Normal (walking)
State 1 → Half encased (still moves)
State 2 → Fully encased (frozen, kickable)
State 3 → Rolling (kicked, kills on contact)
State 4 → Melting (snow shrinks, enemy reappears)
```

---

## 🗂️ Project Structure

```
SFML_VS_Setup_2026/
├── assets/
│   ├── FONT/           # BubbleBobble font
│   ├── Music/          # menu.ogg, level.ogg, boss.ogg
│   ├── NARUTO.png      # Player 1 sprite
│   ├── JUMP.png        # Player jump sprite
│   ├── enemy.png       # Botom enemy
│   ├── snow.png        # Full encasement texture
│   ├── half.png        # Half encasement texture
│   ├── snowball.png    # Snowball projectile
│   ├── rocket.png      # Gamakichi rocket
│   ├── gem.png         # Collectible gem
│   ├── star.png        # Power-up star
│   └── lvl1-10.png     # Level backgrounds
├── Player.h / .cpp
├── Enemy.h
├── Botom.h / .cpp
├── FlyingFooga.h / .cpp
├── Tornado.h / .cpp
├── InvisibleEnemy.h / .cpp
├── MOGERA.h / .cpp
├── MogeraBabies.h / .cpp
├── GamaKichi.h / .cpp
├── SnowBall.h / .cpp
├── LevelSystem.h / .cpp
├── HUD.h
├── Shop.h
├── MainMenu.h
├── LoginScreen.h / .cpp
├── SignupScreen.h / .cpp
├── AuthSystem.h / .cpp
├── Leaderboard.h / .cpp
├── LevelSelect.h
├── SplashScreen.h
├── item.h
├── Platform.h
├── Collision.h
└── main.cpp
```

---

##  Getting Started

### Prerequisites
- Windows 10/11 (64-bit)
- Visual Studio 2022
- [SFML 2.6.2 — Visual C++ 17 (64-bit)](https://www.sfml-dev.org/download/sfml/2.6.2/)

### Setup
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/snow-bros-remake.git
   ```

2. Download SFML 2.6.2 (VC17 64-bit) and extract it.

3. In Visual Studio → Project Properties:
   - **Include Directories** → `SFML-2.6.2/include`
   - **Library Directories** → `SFML-2.6.2/lib`
   - **Linker → Additional Dependencies:**
     ```
     sfml-graphics-d.lib
     sfml-window-d.lib
     sfml-system-d.lib
     sfml-audio-d.lib
     sfml-network-d.lib
     ```

4. Copy all DLLs from `SFML-2.6.2/bin/` into your `x64/Debug/` folder:
   ```
   sfml-graphics-d-2.dll
   sfml-window-d-2.dll
   sfml-system-d-2.dll
   sfml-audio-d-2.dll
   sfml-network-d-2.dll
   openal32.dll
   ```

5. Build & Run with **F5** in Visual Studio.

---

## 🎮 Controls

### Player 1
| Action | Key |
|--------|-----|
| Move Left / Right | ← → Arrow Keys |
| Jump | ↑ Arrow |
| Throw Snowball | Space |

### Player 2 (Multiplayer)
| Action | Key |
|--------|-----|
| Move Left / Right | A / D |
| Jump | W |
| Throw Snowball | F |

### General
| Action | Key |
|--------|-----|
| Pause / Unpause | ESC |
| Show Hitboxes (debug) | H |
| Shop (from pause) | S |
| Main Menu (from pause) | M |
| Exit (from pause) | X |
| Back from Shop | ESC / Q |

---

##  Credits & Assets

### 🎨 Art & Visuals
- **Character & Enemy sprites**  sourced from [Pinterest](https://pinterest.com), enhanced and modified using **Google Gemini AI**
- **Level backgrounds**  sourced from Pinterest, upscaled, and stylized with Gemini
- **Boss sprites (Mogera, Gamakichi)** — Pinterest references, AI-enhanced
- All assets were adapted for non-commercial educational use

### 🎵 Music
- **Menu music**  sourced from [Pixabay](https://pixabay.com) (royalty-free)
- **Level music**  sourced from [Zedge](https://www.zedge.net) and [Pixabay](https://pixabay.com)
- **Boss music**  sourced from [Pixabay](https://pixabay.com)
- All music used for non-commercial educational purposes

### 🎮 Original Game
- **Snow Bros** (1990) developed by Toaplan, published by Romstar
- This project is a fan-made educational remake and is not affiliated with or endorsed by the original creators

###  Libraries & Tools
- [SFML](https://www.sfml-dev.org/) — Simple and Fast Multimedia Library (2.6.2)
- [Visual Studio 2022](https://visualstudio.microsoft.com/)
- [Google Gemini](https://gemini.google.com/) — AI image enhancement
- [OpenAL](https://openal.org/) — Audio backend for SFML

---

## 📜 License

This project is developed for **academic purposes only** as part of the OOP course at FAST-NU Islamabad. All original game content belongs to its respective owners. No commercial use intended.

---

<div align="center">

**Made with ❄️ and C++ by Zubair Ashraf & Abdullah Saqib**
*OOP Semester Project*

⭐ If you liked this project, give it a star!

</div>
