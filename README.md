# cv64-nx

Native Nintendo Switch (homebrew) port of **Castlevania 64** (N64, 1999), built from the
static recompilation project *Castlevania 64: Recompiled*. Castlevania: Legacy of Darkness has its own
port, [cv64LoD-nx](https://github.com/FurryLilManChild/cv64LoD-nx).

No ROM, and no code generated from a ROM, is included in this repository. You supply your own
legally dumped **Castlevania (USA) v1.0** ROM (`.z64`, SHA-1 `989a28782ed6b0bc489a1bbbd7bec355d8f2707e`).

## How it works

- The game's MIPS code is translated to C ahead of time by
  [N64Recomp](https://github.com/N64Recomp/N64Recomp) and runs natively on the Switch's CPU,
  on top of [N64ModernRuntime](https://github.com/N64Recomp/N64ModernRuntime).
- The PC version draws with RT64, which needs Vulkan/D3D12/Metal. Switch homebrew has none of
  those, so this port draws with [GLideN64](https://github.com/gonetz/GLideN64) on OpenGL
  (Mesa nouveau), with a small layer that understands the PC port's RT64 widescreen commands.
- The Switch platform layer (`switch/`) is adapted from
  [DK64Recomp-NX](https://github.com/Trinalord777/DK64Recomp-NX) by Trinalord777: GLideN64
  renderer context, libnx threading fixes, SDL2 audio/input, the NX Options menu and the
  clock profiles.

## Status

Test release. In testing on a V1 Switch with Atmosphère the game runs at full speed with sound, saves to the
emulated Controller Pak, and supports controller remapping. It has not been played to the end on Switch yet.

Known issues:
- The first time each effect appears the game can stutter briefly while its shader is compiled. Compiled shaders
  are saved to the SD card, so this mostly goes away on later launches.
- Only the USA v1.0 ROM is supported (not Rev 2 or other regions).
- Launching from the Album applet does not work: it has too little memory. Use title takeover.

## Download

Get the latest `.zip` from the [Releases](../../releases) page. It contains the compiled port only; the ROM is not
included and is needed to play.

## Install on the Switch

1. Extract the release zip to the root of your SD card, so that `cv64recomp.nro` ends up in
   `sdmc:/switch/cv64recomp/` (or copy it there yourself).
2. Copy your Castlevania (USA) v1.0 ROM into the same folder (any file name ending in `.z64`,
   `.n64` or `.v64`).
3. Launch it from the Homebrew Menu. Use title takeover (hold R while opening a game) rather than
   the Album applet, so the port gets the full memory.

Saves, settings (`nx_options.txt`) and the shader cache are kept in `sdmc:/switch/cv64recomp/`.
Press **Minus + Plus** together to open the **NX Options** menu (resolution, aspect ratio, frame rate,
clock profile, volume, restart/quit).

Controls default to the Nintendo Switch Online N64 layout: A/B as A/B, ZL as Z, L as L, R/ZR as R,
Plus as Start, the right stick as the C buttons and the D-pad as the D-pad. Every button can be
remapped in NX Options > Settings > Controls.

## Reporting problems

Open an issue with the console model, Atmosphère version, where in the game it happened and the log files from
`sdmc:/switch/cv64recomp/` (`cv64recomp.log`, and `cv64recomp.prev.log` after a crash).

## Building

The Switch build needs devkitA64 plus the portlibs `switch-sdl2`, `switch-mesa`,
`switch-libdrm_nouveau` and `switch-glad`.

1. Generate the recompiled code from your ROM (Linux/WSL):
   `./tools/generate.sh /path/to/castlevania.z64`
2. Build and recompile the patches:
   `make -C patches CC=clang LD=ld.lld` then `N64Recomp patches.toml`
3. Apply the Switch patches to the submodules and build: `switch/build.sh`

See `BUILDING.md` for the upstream PC build.

## Credits

- Castlevania 64: Recompiled: [RevoSucks/CV64Recomp](https://github.com/RevoSucks/CV64Recomp),
  [DankZoneStudios/CV64Recomp](https://github.com/DankZoneStudios/CV64Recomp)
- Castlevania 64 decompilation: [k64ret/cv64](https://github.com/k64ret/cv64)
- N64Recomp, N64ModernRuntime, RT64: Wiseguy, Darío and contributors
- Switch layer: [DK64Recomp-NX](https://github.com/Trinalord777/DK64Recomp-NX) (Trinalord777)
- GLideN64 (gonetz and contributors), devkitPro, libnx, Mesa, SDL

Licensed under the GNU GPL v3, like the projects it is built from (see `COPYING`).
