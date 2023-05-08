#pragma once

#include <array>
#include <string>

#include "Engine/Time.h"

constexpr unsigned int MAX_SAVE_SLOTS = 45;

struct SaveGameHeader {
    std::string name; // Save name, as displayed in the save list in-game.
    std::string locationName; // Name of the map, e.g. "out01.odm".
    GameTime playingTime; // Game time of the save.
};

struct SavegameList {
    static void Initialize();
    SavegameList();

    void Reset();

    std::array<std::string, MAX_SAVE_SLOTS> pFileList;
    std::array<bool, MAX_SAVE_SLOTS> pSavegameUsedSlots;
    std::array<SaveGameHeader, MAX_SAVE_SLOTS> pSavegameHeader;
    std::array<class Image *, MAX_SAVE_SLOTS> pSavegameThumbnails;

    int numSavegameFiles = 0;
    int selectedSlot = 0;
    int saveListPosition = 0;
    std::string lastLoadedSave{};
};

void LoadGame(unsigned int uSlot);
void SaveGame(bool IsAutoSAve, bool NotSaveWorld);
void DoSavegame(unsigned int uSlot);
bool Initialize_GamesLOD_NewLOD();
void SaveNewGame();

extern struct SavegameList *pSavegameList;
