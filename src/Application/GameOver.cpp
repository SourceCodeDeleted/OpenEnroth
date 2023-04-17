#include <string>

#include "GameOver.h"

#include "Engine/AssetsManager.h"
#include "Engine/Engine.h"
#include "Engine/EngineGlobals.h"
#include "Engine/Graphics/IRender.h"
#include "Engine/Graphics/Viewport.h"
#include "Engine/LOD.h"
#include "Engine/Localization.h"
#include "Engine/Party.h"
#include "Engine/SaveLoad.h"
#include "Engine/Time.h"

#include "GUI/GUIButton.h"
#include "GUI/GUIFont.h"
#include "GUI/GUIWindow.h"
#include "GUI/UI/UIPartyCreation.h"
#include "GUI/UI/UIStatusBar.h"
#include "GUI/UI/UIHouses.h"

#include "Io/KeyboardInputHandler.h"
#include "Io/Mouse.h"

#include "Media/Audio/AudioPlayer.h"
#include "Media/MediaPlayer.h"


//----- (004BF91E) --------------------------------------------------------
void GameOver_Loop(int v15) {
    dword_6BE364_game_settings_1 &= ~GAME_SETTINGS_4000;
    bGameoverLoop = true;
    pAudioPlayer->stopSounds();

    CreateWinnerCertificate();

    // break out of house and dialogue
    if (window_SpeakInHouse) window_SpeakInHouse->Release();
    window_SpeakInHouse = nullptr;
    if (pDialogueWindow) pDialogueWindow->Release();
    window_SpeakInHouse = nullptr;
}

void CreateWinnerCertificate() {
    render->Present();
    render->BeginScene2D();
    Image *background = assets->GetImage_PCXFromIconsLOD("winbg.pcx");
    render->DrawTextureNew(0, 0, background);

    GUIWindow *tempwindow_SpeakInHouse = new GUIWindow(WINDOW_Unknown, { 0, 0 }, render->GetRenderDimensions(), 0);
    GUIWindow pWindow;
    pWindow.uFrameX = 75;
    pWindow.uFrameY = 60;
    pWindow.uFrameWidth = 469;
    pWindow.uFrameHeight = 338;
    pWindow.uFrameZ = 543;
    pWindow.uFrameW = 397;
    GUIFont *pFont = GUIFont::LoadFont("endgame.fnt", "FONTPAL");

    const char *pInString = nullptr;
    if (pParty->isPartyGood())
        pInString = localization->GetString(LSTR_GOOD_ENDING);
    else if (pParty->isPartyEvil())
        pInString = localization->GetString(LSTR_EVIL_ENDING);
    else
        assert(false);

    GameTime play_time = pParty->GetPlayingTime();
    play_time.SubtractHours(9);  // game begins at 9 am

    int v19 = play_time.GetDays();
    int v14 = play_time.GetYears();
    int v18 = play_time.GetMonthsOfYear();
    int v17 = play_time.GetDaysOfMonth();
    if (!v19) v19 = 1;

    pWindow.DrawTitleText(
        pFont, 1, 0x23, 1, localization->GetString(LSTR_CONGRATULATIONS), 3
    );
    uint64_t v23 = 0ull;
    int v20 = 0;
    for (uint i = 0; i < 4; i++) {
        pWindow.DrawTitleText(
            pFont, 1,
            i * ((unsigned char)pFont->GetHeight() - 2) +
            (unsigned char)pFont->GetHeight() + 46,
            1,
            localization->FormatString(
                LSTR_FMT_S_THE_LEVEL_D_S,
                pParty->pPlayers[i].pName.c_str(),
                pParty->pPlayers[i].GetBaseLevel(),
                localization->GetClassName(pParty->pPlayers[i].classType)),
            3);
        v23 += pParty->pPlayers[i].uExperience;
    }
    v23 = (int64_t)v23 / v19;
    std::string v6 = pFont->FitTextInAWindow(pInString, pWindow.uFrameWidth, 12);
    pWindow.DrawTitleText(pFont, 1, 5 * (pFont->GetHeight() + 11), 1, v6, 0);

    const char *v7 = localization->GetString(LSTR_DAY_CAPITALIZED);
    if (v17 != 1) v7 = localization->GetString(LSTR_DAYS);

    const char *v8 = localization->GetString(LSTR_MONTH);
    if (v18 != 1) v8 = localization->GetString(LSTR_MONTHS);

    const char *v9 = localization->GetString(LSTR_YEAR);
    if (v14 != 1) v9 = localization->GetString(LSTR_YEARS);

    pWindow.DrawTitleText(
        pFont, 1, pWindow.uFrameHeight - 2 * pFont->GetHeight() - 5, 1,
        fmt::format("{} {} {}, {} {}, {} {} ", localization->GetString(LSTR_TOTAL_TIME), v14, v9, v18, v8, v17, v7), 3);

    pWindow.DrawTitleText(pFont, 1, pWindow.uFrameHeight, 1,
        localization->FormatString(LSTR_FMT_YOUR_SCORE_D, v23), 3);

    dword_6BE364_game_settings_1 |= GAME_SETTINGS_4000;

    // flush draw buffer so cert is drawn
    render->DrawTwodVerts();
    render->EndLines2D();
    render->EndTextNew();
    render->SaveWinnersCertificate("MM7_Win.Pcx");
    free(pFont);
    background->Release();
    background = nullptr;
    tempwindow_SpeakInHouse->Release();
}
