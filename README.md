# Aliens Onboard

## Overview
"Aliens Onboard" is a thrilling first-person shooter game inspired by the classic titles "Wolfenstein 3D" and "Doom." Set in a vivid and immersive environment, the game challenges players to navigate through a spacecraft overrun by aliens. With a mix of strategic gameplay, fast-paced action, and retro-style graphics, "Aliens Onboard" offers an exciting experience for both old-school and modern gamers.

## System Requirements
### Windows
- **OS:** Windows 7 or later
- **Processor:** Intel Core i3 or equivalent
- **Memory:** 4 GB RAM
- **Graphics:** DirectX 11 compatible GPU
- **DirectX:** Version 11
- **Storage:** 100 MB available space

### MacOS
- **OS:** MacOS X 10.9 or later
- **Processor:** Intel Core i3 or equivalent
- **Memory:** 4 GB RAM
- **Graphics:** SDL 2.0 compatible GPU
- **Storage:** 100 MB available space

## Setup

### Windows
1. Open the Game folder.
2. Compile the code using `g++ *.cpp -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o a.exe`
3. Run `.\a.exe` to start th game.

### MacOS
1. Open the Game folder.
2. Compile the code using `clang++ *.cpp -o final.out -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_mixer.framework/Headers -I/Libaray/Frameworks/SDL2_image.framework/Headers -F/Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_mixer -rpath /Library/Frameworks -std=c++17`
3. Run `./final.out` to start the game.

## How to Play
- Use **WASD** keys for movement.
- Aim with your mouse and click to shoot.
- Explore the spacecraft, find ammo, health packs, and other items to survive.
- Defeat all aliens to clear each level and progress through the game.
- Find the Flag at the last level to Win!

## Features
- Immersive 3D environments with a retro aesthetic.
- Diverse arsenal of weapons to combat aliens.
- Challenging levels with unique layouts and aliens to discover.
- Engaging soundtrack and sound effects that enhance the gaming experience.
- Easy-to-learn controls and gameplay suitable for all skill levels.

## License
This game is licensed for personal use only. Redistribution or commercial use is prohibited without prior consent from the developers.

## Credits
Developed by Muhammad Saad, Raahim Hashmi, Basil Ali Khan - Students of Habib University.

## Disclaimer
"Aliens Onboard" is a work of fiction. Any resemblance to real persons, living or dead, or actual events is purely coincidental. All trademarks and copyrights are property of their respective owners.

---

Enjoy your journey aboard the spacecraft and good luck defeating the alien threat in "Aliens Onboard"!
