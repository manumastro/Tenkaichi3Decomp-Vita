/*
 * The BT3 PC port (z3xox's Tenkaichi3Decomp, merged in at v0.1.39.6) on the PS Vita: what its PC build's own files give
 * the game, where those files are not in the Vita build. The same list as the BT4 fork's port/vita/vita_bt4.c.
 *
 * Left out on the Vita for now: online play and its lobbies (the next step: docs/vita/online.md), the F1 window
 * (ui.cpp), the screen reader, the script mods, spectating, the PC renderer's own markers and panels, mp3/wav songs
 * and stages added from outside the disc, and the language choice (the Vita reads the one disc in
 * ux0:data/bt3/disc; English).
 *
 * Each function answers as the game without these: no session, nothing added, the game's own settings. A value that
 * is not 0 says why. What none of these covers is a generated stub (port/build/gen/.../stubs.c) that stops the game
 * with its name if it is ever reached.
 */
#include <math.h>
#include <stdint.h>
#include "plat_songs.h"
#include "plat_stages.h"

/* ---- variables of the PC build's files ---- */

/* ---- variables of the PC build's files ---- */
int gPortResim;                    /* gs/state.c: a frame run again after a rollback (never on the Vita) */
int gPortOverlayOpen;              /* gs/gs_input.c: the F1 window or the quit dialog has the input */
volatile int gUiNameIdx, gUiNameReady, gUiSongIdx, gUiSongLit, gUiSongReady; /* gs/gs_draw.c: the PC's name plates */
volatile int gUiNameX, gUiNameY, gUiNameW, gUiNameH, gUiSongX, gUiSongY, gUiSongW, gUiSongH;
int gPortSongCount;                /* plat_songs.c: songs added from outside the disc (none) */
char gPortSongNames[PORT_SONG_MAX][64];
int gPortSongOffsets[PORT_SONG_MAX];
int gPortExtraStageCount;          /* plat_stages.c: stages added from outside the disc (none) */
int gPortExtraStages[PORT_STAGE_MAX];
char gPortStageNames[PORT_STAGE_MAX][64];

/* ---- the game's one double-precision call (plat_libm.c on PC: the replay list's slot number) ---- */
double Port_pow(double a, double b) { return __builtin_pow(a, b); }

/* ---- the list reader's (port/src/gs/gs_core.c is the Vita's own) ---- */
void Gs_RenderListWait(void) {}
const char *Port_GetEnv(const char *name) { extern char *Vita_GsGetenv(const char *name); return Vita_GsGetenv(name); }

/* ---- online play, lobbies, ranked matches, spectators (gs/net*.c, gs/match_supabase.cpp, spec_menu.c) ---- */
int Port_NetActive(void) { return 0; }
int Port_NetMe(void) { return 0; }
int Port_NetSession(void) { return 0; }
int Port_NetSpeedMilli(void) { return 1000; }
int Port_NetSpeedStandard(void) { return 1; }
int Port_NetWarp(void) { return 0; }
void Port_NetArrived(void) {}
void Port_NetRules(int *type, int *dp, int *time) { (void)type; (void)dp; (void)time; }
const char *Port_NetName(int player) { (void)player; return ""; }
void Port_NetNameSet(const char *name) { (void)name; }
void Port_NetOptions(int rollback, int delay) { (void)rollback; (void)delay; }
void Port_NetRulesSet(int type, int dp, int time) { (void)type; (void)dp; (void)time; }
int Port_NetSpecStatus(int *out) { (void)out; return 0; }
void Port_NetSpeedSet(int percent) { (void)percent; }
int Port_NetSpectating(void) { return 0; }
int Port_NetSpecView(void) { return -1; }
int Port_RollCan(void) { return 0; }
const char *Port_OnlineBlocked(void) { return "Online play is not available on the PS Vita."; }
void Port_LobbyCancel(void) {}
const char *Port_LobbyError(void) { return "Online play is not available on the PS Vita."; }
void Port_LobbyLaunch(void) {}
int Port_LobbyPoll(void) { return 0; }
void Port_LobbyQueuesAsk(void) {}
int Port_LobbyQueueWaiting(int queue) { (void)queue; return 0; }
int Port_LobbyRelease(int *min, int *latest) { (void)min; (void)latest; return 0; }
int Port_LobbyStartCode(int host, const char *code) { (void)host; (void)code; return 0; }
int Port_LobbyStartQuick(int queue) { (void)queue; return 0; }
int Port_TrLine(const char *original, char *out, int size) { (void)original; (void)out; (void)size; return 0; }
void Port_StateTouch(void *p, unsigned long n) { (void)p; (void)n; }

/* ---- the F1 window and the PC's presentation (gs/ui.cpp, gs/gs_draw.c) ---- */
int Port_HudLayout(void) { return 0; }
int Port_HudSwap(void) { return 0; }
void Port_UiSaving(int state) { (void)state; }
void Ui_LanguageChosen(const char *locale) { (void)locale; }

/* ---- voice chat, the screen reader ---- */
void PortA11y_Say(const char *text, int interrupt) { (void)text; (void)interrupt; }

/* ---- mp3 / wav / flac songs from outside the disc (gs/snd_ma.c, the PCM cache): none on the Vita ---- */
int PortMa_Format(const char *path) { (void)path; return 0; } /* (0: an ADX of the disc, played as always) */
int PortMa_Blanks(const char *path) { (void)path; return 0; }
int PortMa_AtEnd(void *handle) { (void)handle; return 1; }
void PortMa_Pause(void *handle, int paused) { (void)handle; (void)paused; }
void PortMa_SetMono(int mono) { (void)mono; }
void PortMa_SetPan(void *handle, int pan0, int pan1) { (void)handle; (void)pan0; (void)pan1; }
void PortMa_SetVolume(void *handle, float gain) { (void)handle; (void)gain; }
void PortMa_Stop(void *handle) { (void)handle; }

/* (port/src/a11y_game.c) */
void PortA11y_FontText(int kind, int arg, int flags) {}
void PortA11y_StreamStart(const char *path) {}

/* (port/src/fight_panels.c) */
void Port_HudFeed(int kind, int side, int a, int b) {}

/* (port/src/gs/a11y.c) */
float PortA11y_StreamGain(const void *player) { (void)player; return 1.0f; } /* the game's own volume (no accessibility options on the Vita) */

/* (port/src/gs/gs_draw.c) */
int Port_FxOff(int bit) { return 0; }
void GsGpu_InterpPump(int ahead_ms, int all) {}
void Port_WallMesh(const void *key, int second, int culled, const float *screen, const float *cam, const float *vtx, int quadCount, const void *quads, unsigned long long tex0) {}

/* (port/src/gs/gs_input.c) */
int PortTbo_TextRead(void) { return 0; }
int Port_RumbleTest(void) { return 0; }
void PortInput_Fresh(void) {}
void PortTbo_Copy(const char *text) {}
void PortTbo_Paste(void) {}
void PortTbo_PasteText(void) {}
void PortTbo_TextMode(int on) {}
void Port_ClashLog(int player, const char *what, int fromInput, int total, int frame) {}
void Port_PadVibrate(int socket, int small, int large) {}

/* (port/src/gs/menu_text.c) */
void MenuText_BootLanguageChosen(void) {}
void MenuText_RegisterGlyphs(int tbp, int cbp, const void *glyphs, int count, int lineHeight) {}

/* (port/src/gs/menu_translation.c) */
void MenuTranslation_SaveChoice(const char *locale) {}

/* (port/src/gs/namefont.c) */
void Port_NameFontSheets(int stage, int song, int songLit) {}

/* (port/src/gs/net.c) */
const char * Port_LobbyRivalRegion(void) { return ""; }
const char * Port_NetLanAddress(void) { return ""; }
const char * Port_NetNameGet(void) { return ""; }
int Port_LobbyInBackground(void) { return 0; }
int Port_LobbyWiden(void) { return 0; }
int Port_NetFixedStart(void) { return 0; }
int Port_NetLobbyOwnerSide(void) { return -1; }
int Port_NetResim(void) { return 0; }
int Port_NetSessionsEnded(void) { return 0; }
int Port_NetSideOptions(int *camera, int *shake) { return 0; }
int Port_NetView(void) { return -1; }
int Port_NetVoiceAlt(void) { return 0; }
unsigned Port_NetSeed(void) { return 0; }
unsigned Port_NetTick(void) { return 0; }
void Port_LobbyBackground(int on) {}
void Port_LobbyQuickArea(const char *area) {}
void Port_NetInput(int player,unsigned char *data) {}
void Port_NetLeave(void) {}
void Port_NetNameSave(const char *name) {}

/* (port/src/gs/net_lobby.c) */
int Port_LobbyCreate(int byCode, int port, int battle, int time, int speed, int rollback, int delay) { return 0; }
int Port_LobbyJoin(const char *address, int port) { return 0; }
int Port_LobbyView(void *out) { return 0; }
int Port_LobbyWantsScreen(void) { return 0; }
void Port_LobbyDo(int what, int a, int b) {}
void Port_LobbySay(const char *text) {}

/* (port/src/gs/state.c) */
void Port_StateLog(unsigned vblank, const void *fight, unsigned fightSize) {}

/* (port/src/gs/tbo_text.c) */
int PortTbo_TextId(const char *text,int kind) { return 0; }
int PortTbo_TextInfo(int id, int what) { return 0; }
int PortTbo_TextMeasure(const char *text,int kind) { return 0; }

/* (port/src/gs/ui.cpp) */
int Ui_QuitAsk(void) { return 0; }

/* (port/src/gs/ui_text_translate.c) */
const uint16_t * UiText_TranslateLine(const uint32_t *table, int line, const uint16_t *original) { (void)table; (void)line; return original; }
const uint16_t * UiText_TranslateString(const uint16_t *original) { return original; }

/* (port/src/mods_game.c) */
int Port_ModsCamCollide(int side) { return 0; }
int Port_ModsCamZoom(int side) { return 0; }
void Port_ModsCamera(int side, int objId, int pos, int rot, int paused) {}

/* (port/src/plat_fastvec.c) */
int Port_FastMtxApply(const uint32_t *r, const uint32_t *v, uint32_t *out) { return 0; }

/* (port/src/plat_fprint.c) */
const char * Port_DataFingerprintText(void) { return ""; }
int Port_DataFingerprint(unsigned long long *out) { return 0; }
int Port_DataFingerprintNeed(void) { return 0; }
int Port_DataFingerprintOriginal(void) { return 0; }

/* (port/src/plat_songs.c) */
int PortSongs_IsFile(const char *path) { return 0; }
int Port_TestBgm(void) { return -1; }
void PortSongs_Init(void) {}
void PortSongs_Refresh(void) {}

/* (port/src/plat_stages.c) */
int Port_StageBufSize(void) { return 0x6CB800; /* the game's own stage buffer (no stages added from outside the disc) */ }
int Port_TestScreen(void) { return -1; }
int Port_TestStage(void) { return -1; }
void PortStages_Init(void) {}

/* (port/src/plat_verify.c) */
void Port_VerifyStart(void) {}

/* (port/src/quit_dialog.c) */
void PortQuit_Draw(int vsyncs) {}

/* (port/src/spec_menu.c) */
int PortSpecMenu_Frame(int vsyncs) { return 0; }
unsigned short * PortSpecMenu_Text(int k) { return 0; }
/* ---- the main menu's "Tenkaichi Budokai Online" label from the disc's letters (gs/menu_text.c): 0, so the menu takes
   the label's ready-made runs (src/menu/port_tbo_label.h); the item itself is not listed on the Vita yet ---- */
int Port_MainItemLabel(int entry, int lit, int out) { (void)entry; (void)lit; (void)out; return 0; }
void Port_LobbyHelloAsk(void) {} /* (src/menu/port_tbo.c: is this release new enough for the matchmaking service) */

/* ---- the language picker at start (gs/menu_translation.c, gs/menu_labels.c): one language, never asked ---- */
int MenuTranslation_Available(void *out, int capacity) { (void)out; (void)capacity; return 0; }
int MenuTranslation_ShouldPrompt(const void *options, int count) { (void)options; (void)count; return 0; }
int MenuLabels_LanguageArtAvailable(void) { return 0; }
