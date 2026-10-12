#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_ai_record.h"
#include "battle_controllers.h"
#include "battle_message.h"
#include "battle_setup.h"
#include "battle_special.h"
#include "battle_z_move.h"
#include "data.h"
#include "event_data.h"
#include "frontier_util.h"
#include "graphics.h"
#include "international_string_util.h"
#include "item.h"
#include "link.h"
#include "menu.h"
#include "palette.h"
#include "recorded_battle.h"
#include "string_util.h"
#include "strings.h"
#include "test_runner.h"
#include "text.h"
#include "trainer_hill.h"
#include "trainer_slide.h"
#include "trainer_tower.h"
#include "window.h"
#include "line_break.h"
#include "constants/abilities.h"
#include "constants/battle_dome.h"
#include "constants/battle_string_ids.h"
#include "constants/frontier_util.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/opponents.h"
#include "constants/species.h"
#include "constants/trainers.h"
#include "constants/trainer_hill.h"
#include "constants/weather.h"

struct BattleWindowText
{
    u8 fillValue;
    u8 fontId;
    u8 x;
    u8 y;
    union {
        struct {
            DEPRECATED("Use color.background instead") u8 bgColor;
            DEPRECATED("Use color.foreground instead") u8 fgColor;
            DEPRECATED("Use color.shadow instead") u8 shadowColor;
            DEPRECATED("Use color.accent instead") u8 accentColor;
        };
        union TextColor color;
    };
    u8 letterSpacing;
    u8 lineSpacing;
    u8 speed;
};

#if TESTING
EWRAM_DATA u16 sBattlerAbilities[MAX_BATTLERS_COUNT] = {0};
#else
static EWRAM_DATA u16 sBattlerAbilities[MAX_BATTLERS_COUNT] = {0};
#endif
EWRAM_DATA struct BattleMsgData *gBattleMsgDataPtr = NULL;

// todo: make some of those names less vague: attacker/target vs pkmn, etc.

static const u8 sText_EmptyString4[] = _("");

const u8 gText_PkmnShroudedInMist[] = _("¡{B_ATK_NAME_WITH_PREFIX} se rodeó de una niebla protectora!");
const u8 gText_PkmnGettingPumped[] = _("¡{B_DEF_NAME_WITH_PREFIX} se está preparando para luchar!");
const u8 gText_PkmnsXPreventsSwitching[] = _("¡{B_LAST_ABILITY} de {B_BUFF1} impide el cambio!\p");
const u8 gText_StatSharply[] = _("mucho");
const u8 gText_StatRose[] = _("subió");
const u8 gText_StatFell[] = _("bajó");
const u8 gText_DefendersStatRose[] = _("¡{B_BUFF1} de {B_DEF_NAME_WITH_PREFIX} subió{B_BUFF2}!");
static const u8 sText_GotAwaySafely[] = _("{PLAY_SE SE_FLEE}¡Escapaste sin problemas!\p");
static const u8 sText_PlayerDefeatedLinkTrainer[] = _("¡Derrotaste a {B_LINK_OPPONENT1_NAME}!");
static const u8 sText_TwoLinkTrainersDefeated[] = _("¡Derrotaste a {B_LINK_OPPONENT1_NAME} y {B_LINK_OPPONENT2_NAME}!");
static const u8 sText_PlayerLostAgainstLinkTrainer[] = _("¡Has perdido contra {B_LINK_OPPONENT1_NAME}!");
static const u8 sText_PlayerLostToTwo[] = _("¡Has perdido contra {B_LINK_OPPONENT1_NAME} y {B_LINK_OPPONENT2_NAME}!");
static const u8 sText_PlayerBattledToDrawLinkTrainer[] = _("¡{B_LINK_OPPONENT1_NAME} ha empatado contigo!");
static const u8 sText_PlayerBattledToDrawVsTwo[] = _("¡{B_LINK_OPPONENT1_NAME} y {B_LINK_OPPONENT2_NAME} han empatado contigo!");
static const u8 sText_WildFled[] = _("{PLAY_SE SE_FLEE}¡{B_LINK_OPPONENT1_NAME} ha huido!"); //not in gen 5+, replaced with match was forfeited text
static const u8 sText_TwoWildFled[] = _("{PLAY_SE SE_FLEE}¡{B_LINK_OPPONENT1_NAME} y {B_LINK_OPPONENT2_NAME} han huido!"); //not in gen 5+, replaced with match was forfeited text
static const u8 sText_PlayerDefeatedLinkTrainerTrainer1[] = _("¡Derrotaste a {B_TRAINER1_NAME_WITH_CLASS}!\p");
static const u8 sText_OpponentMon1Appeared[] = _("¡{B_OPPONENT_MON1_NAME} apareció!\p");
static const u8 sText_WildPkmnAppeared[] = _("¡Un {B_OPPONENT_MON1_NAME} salvaje!\p");
static const u8 sText_LegendaryPkmnAppeared[] = _("¡Un {B_OPPONENT_MON1_NAME} salvaje!\p");
static const u8 sText_WildPkmnAppearedPause[] = _("¡Un {B_OPPONENT_MON1_NAME} salvaje!{PAUSE 127}");
static const u8 sText_TwoWildPkmnAppeared[] = _("¡Un {B_OPPONENT_MON1_NAME} y un {B_OPPONENT_MON2_NAME} salvajes!\p");
static const u8 sText_GhostAppearedCantId[] = _("¡Apareció el FANTASMA!\p¡Vaya!\n¡No se puede identificar!\p");
static const u8 sText_TheGhostAppeared[] = _("¡Apareció el FANTASMA!\p");
static const u8 sText_Trainer1WantsToBattle[] = _("¡{B_TRAINER1_NAME_WITH_CLASS} te desafía!\p");
static const u8 sText_LinkTrainerWantsToBattle[] = _("¡{B_LINK_OPPONENT1_NAME} quiere luchar!");
static const u8 sText_TwoLinkTrainersWantToBattle[] = _("¡{B_LINK_OPPONENT1_NAME} y {B_LINK_OPPONENT2_NAME} quieren luchar!");
static const u8 sText_Trainer1SentOutPkmn[] = _("{B_TRAINER1_NAME_WITH_CLASS} sent out {B_OPPONENT_MON1_NAME}!");
static const u8 sText_Trainer1SentOutTwoPkmn[] = _("{B_TRAINER1_NAME_WITH_CLASS} sent out {B_OPPONENT_MON1_NAME} and {B_OPPONENT_MON2_NAME}!");
static const u8 sText_Trainer1SentOutPkmn2[] = _("{B_TRAINER1_NAME_WITH_CLASS} sent out {B_BUFF1}!");
static const u8 sText_LinkTrainerIntroSendOutPkmn[] = _("{B_LINK_OPPONENT1_NAME} sent out {B_LINK_OPPONENT_MON1_NAME}!");
static const u8 sText_LinkTrainerSentOutPkmn[] = _("{B_LINK_OPPONENT1_NAME} sent out {B_BUFF1}!");
static const u8 sText_LinkTrainer2SentOutPkmn2[] = _("{B_LINK_OPPONENT2_NAME} sent out {B_BUFF1}!");
static const u8 sText_LinkTrainerSentOutTwoPkmn[] = _("¡{B_LINK_OPPONENT1_NAME} envió a {B_OPPONENT_MON1_NAME} y {B_OPPONENT_MON2_NAME}!");
static const u8 sText_TwoLinkTrainersIntroSendOutPkmn[] = _("{B_LINK_OPPONENT1_NAME} sent out {B_LINK_OPPONENT_MON1_NAME}! {B_LINK_OPPONENT2_NAME} sent out {B_LINK_OPPONENT_MON2_NAME}!");
static const u8 sText_LinkTrainerSentOutPkmn2[] = _("{B_LINK_OPPONENT1_NAME} sent out {B_LINK_OPPONENT_MON2_NAME}!");
static const u8 sText_LinkTrainerMultiSentOutPkmn[] = _("¡{B_LINK_SCR_TRAINER_NAME} envió a {B_BUFF1}!");
static const u8 sText_GoPkmn[] = _("¡Adelante, {B_PLAYER_MON1_NAME}!");
static const u8 sText_GoTwoPkmn[] = _("¡Adelante, {B_PLAYER_MON1_NAME} y {B_PLAYER_MON2_NAME}!");
static const u8 sText_GoPkmn2[] = _("¡Adelante, {B_BUFF1}!");
static const u8 sText_DoItPkmn[] = _("¡Vamos, {B_BUFF1}!");
static const u8 sText_GoForItPkmn[] = _("¡Tu puedes, {B_BUFF1}!");
static const u8 sText_BeCarefulPkmn[] = _("Be careful, {B_PLAYER_MON1_NAME}!");
static const u8 sText_JustALittleMorePkmn[] = _("Just a little more! Hang in there, {B_BUFF1}!"); //currently unused, will require code changes
static const u8 sText_YourFoesWeakGetEmPkmn[] = _("¡Tu rival está débil! ¡A por él, {B_BUFF1}!");
static const u8 sText_LinkPartnerSentOutPkmn1GoPkmn[] = _("{B_LINK_PARTNER_NAME} sent out {B_LINK_PLAYER_MON1_NAME}! Go! {B_LINK_PLAYER_MON2_NAME}!");
static const u8 sText_LinkPartnerSentOutPkmn2GoPkmn[] = _("{B_LINK_PARTNER_NAME} sent out {B_LINK_PLAYER_MON2_NAME}! Go! {B_LINK_PLAYER_MON1_NAME}!");
static const u8 sText_LinkPartnerSentOutPkmn1[] = _("{B_LINK_PARTNER_NAME} sent out {B_BUFF1}!");
static const u8 sText_LinkPartnerSentOutPkmn2[] = _("{B_LINK_PARTNER_NAME} sent out {B_BUFF1}!");
static const u8 sText_LinkPartnerWithdrewPkmn1[] = _("{B_LINK_PARTNER_NAME} withdrew {B_LINK_PLAYER_MON1_NAME}!");
static const u8 sText_LinkPartnerWithdrewPkmn2[] = _("{B_LINK_PARTNER_NAME} withdrew {B_LINK_PLAYER_MON2_NAME}!");
static const u8 sText_PkmnSwitchOut[] = _("{B_BUFF1}, switch out! Come back!"); //currently unused, I believe its used for when you switch on a Pokémon in shift mode
static const u8 sText_PkmnThatsEnough[] = _("¡Ya vale, {B_BUFF1} ¡Ven aquí!");
static const u8 sText_PkmnComeBack[] = _("¡{B_BUFF1}, ven aquí!");
static const u8 sText_PkmnOkComeBack[] = _("¡Bien hecho, {B_BUFF1}! ¡Ven aquí!");
static const u8 sText_PkmnGoodComeBack[] = _("¡Muy bien, {B_BUFF1}! ¡Ven aquí!");
static const u8 sText_Trainer1WithdrewPkmn[] = _("{B_TRAINER1_NAME_WITH_CLASS} withdrew {B_BUFF1}!");
static const u8 sText_Trainer2WithdrewPkmn[] = _("{B_TRAINER2_NAME_WITH_CLASS} withdrew {B_BUFF1}!");
static const u8 sText_LinkTrainer1WithdrewPkmn[] = _("¡{B_LINK_OPPONENT1_NAME} retiró a {B_BUFF1}!");
static const u8 sText_LinkTrainer2WithdrewPkmn[] = _("{B_LINK_OPPONENT2_NAME} withdrew {B_BUFF1}!");
static const u8 sText_WildPkmnPrefix[] = _("salvaje");
static const u8 sText_FoePkmnPrefix[] = _("enemigo");
static const u8 sText_WildPkmnPrefixLower[] = _("the wild ");
static const u8 sText_FoePkmnPrefixLower[] = _("the opposing ");
static const u8 sText_EmptyString8[] = _("");
static const u8 sText_FoePkmnPrefix2[] = _("enemigo");
static const u8 sText_AllyPkmnPrefix[] = _("amigo");
static const u8 sText_FoePkmnPrefix3[] = _("enemigo");
static const u8 sText_AllyPkmnPrefix2[] = _("amigo");
static const u8 sText_FoePkmnPrefix4[] = _("enemigo");
static const u8 sText_AllyPkmnPrefix3[] = _("amigo");
static const u8 sText_AttackerUsedX[] = _("¡{B_ATK_NAME_WITH_PREFIX} usó {B_BUFF3}!");
static const u8 sText_ExclamationMark[] = _("!");
static const u8 sText_ExclamationMark2[] = _("!");
static const u8 sText_ExclamationMark3[] = _("!");
static const u8 sText_ExclamationMark4[] = _("!");
static const u8 sText_ExclamationMark5[] = _("!");
static const u8 sText_HP[] = _("PS");
static const u8 sText_Attack[] = _("Ataque");
static const u8 sText_Defense[] = _("Defensa");
static const u8 sText_Speed[] = _("Velocidad");
static const u8 sText_SpAttack[] = _("At. Esp.");
static const u8 sText_SpDefense[] = _("Def. Esp.");
static const u8 sText_Accuracy[] = _("Precisión");
static const u8 sText_Evasiveness[] = _("Evasión");

const u8 *const gStatNamesTable[NUM_BATTLE_STATS] =
{
    [STAT_HP]      = sText_HP,
    [STAT_ATK]     = sText_Attack,
    [STAT_DEF]     = sText_Defense,
    [STAT_SPEED]   = sText_Speed,
    [STAT_SPATK]   = sText_SpAttack,
    [STAT_SPDEF]   = sText_SpDefense,
    [STAT_ACC]     = sText_Accuracy,
    [STAT_EVASION] = sText_Evasiveness,
};
const u8 *const gPokeblockWasTooXStringTable[FLAVOR_COUNT] =
{
    [FLAVOR_SPICY]  = COMPOUND_STRING("demasiado picante!"),
    [FLAVOR_DRY]    = COMPOUND_STRING("demasiado seca!"),
    [FLAVOR_SWEET]  = COMPOUND_STRING("demasiado dulce!"),
    [FLAVOR_BITTER] = COMPOUND_STRING("demasiado amarga!"),
    [FLAVOR_SOUR]   = COMPOUND_STRING("demasiado ácida!"),
};

static const u8 sText_Someones[] = _("alguien");
static const u8 sText_Lanettes[] = _("Aredia"); //no decapitalize until it is everywhere
static const u8 sText_Bills[] = _("BILL's");
static const u8 sText_EnigmaBerry[] = _("Baya Enigma"); //no decapitalize until it is everywhere
static const u8 sText_BerrySuffix[] = _("Baya"); //no decapitalize until it is everywhere
const u8 gText_EmptyString3[] = _("");

static const u8 sText_TwoInGameTrainersDefeated[] = _("Has vencido a {B_TRAINER1_NAME_WITH_CLASS} y {B_TRAINER2_NAME_WITH_CLASS}!\p");

// New battle strings.
const u8 gText_drastically[] = _(" muchísimo");
const u8 gText_severely[] = _(" muchísimo");
static const u8 sText_TerrainReturnedToNormal[] = _("¡El terreno volvió a la normalidad!"); // Unused

const u8 *const gBattleStringsTable[STRINGID_COUNT] =
{
    [STRINGID_TRAINER1LOSETEXT]                     = COMPOUND_STRING("{B_TRAINER1_LOSE_TEXT}"),
    [STRINGID_PKMNGAINEDEXP]                        = COMPOUND_STRING("{B_BUFF1} ha ganado {B_BUFF3} puntos de experiencia{B_BUFF2}."),
    [STRINGID_PKMNGREWTOLV]                         = COMPOUND_STRING("¡{B_BUFF1} subió al nivel {B_BUFF2}!{WAIT_SE}"),
    [STRINGID_PKMNLEARNEDMOVE]                      = COMPOUND_STRING("¡{B_BUFF1} aprendió {B_BUFF2}!{WAIT_SE}\p"),
    [STRINGID_TRYTOLEARNMOVE1]                      = COMPOUND_STRING("{B_BUFF1} intenta aprender {B_BUFF2}.\p"),
    [STRINGID_TRYTOLEARNMOVE2]                      = COMPOUND_STRING("Pero {B_BUFF1} no puede aprender más de cuatro movimientos.\p"),
    [STRINGID_TRYTOLEARNMOVE3]                      = COMPOUND_STRING("¿Quieres sustituir uno de esos movimientos por {B_BUFF2}?"),
    [STRINGID_PKMNFORGOTMOVE]                       = COMPOUND_STRING("{B_BUFF1} olvidó {B_BUFF2}.\p"),
    [STRINGID_STOPLEARNINGMOVE]                     = COMPOUND_STRING("{PAUSE 32}¿Quieres que {B_BUFF1} deje de intentar aprender {B_BUFF2}?"),
    [STRINGID_DIDNOTLEARNMOVE]                      = COMPOUND_STRING("{B_BUFF1} no aprendió {B_BUFF2}.\p"),
    [STRINGID_PKMNLEARNEDMOVE2]                     = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} aprendió {B_BUFF1}!"),
    [STRINGID_PKMNPROTECTEDITSELF]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} protected itself!"),
    [STRINGID_ITDOESNTAFFECT]                       = COMPOUND_STRING("It doesn't affect {B_DEF_NAME_WITH_PREFIX2}…"),
    [STRINGID_ITDOESNTAFFECTSCR]                    = COMPOUND_STRING("It doesn't affect {B_SCR_NAME_WITH_PREFIX2}…"),
    [STRINGID_BATTLERFAINTED]                       = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} se debilitó!\p"),
    [STRINGID_PLAYERGOTMONEY]                       = COMPOUND_STRING("¡Ganaste ¥{B_BUFF1} por vencer!\p"),
    [STRINGID_PLAYERWHITEOUT]                       = COMPOUND_STRING("¡No tienes más Pokémon que puedan combatir!\p"),
    [STRINGID_PLAYERWHITEOUT2_WILD]                 = COMPOUND_STRING("Saliste corriendo y perdiste ¥{B_BUFF1}…"),
    [STRINGID_PLAYERWHITEOUT2_TRAINER]              = COMPOUND_STRING("Le diste ¥{B_BUFF1} al ganador…"),
    [STRINGID_PLAYERWHITEOUT3]                      = COMPOUND_STRING("¡Quedaste abrumado por la derrota!"),
    [STRINGID_PREVENTSESCAPE]                       = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} impide escapar con {B_SCR_ABILITY}!\p"),
    [STRINGID_HITXTIMES]                            = COMPOUND_STRING("¡Recibió {B_BUFF1} golpe{B_BUFF2}!"),
    [STRINGID_PKMNFELLASLEEP]                       = COMPOUND_STRING("¡{B_EFF_NAME_WITH_PREFIX} se durmió!"),
    [STRINGID_PKMNMADESLEEP]                        = COMPOUND_STRING("¡{B_BUFF1} de {B_SCR_NAME_WITH_PREFIX} durmió a {B_EFF_NAME_WITH_PREFIX2}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNALREADYASLEEP]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} is already asleep!"),
    [STRINGID_PKMNALREADYASLEEP2]                   = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} está dormido!"),
    [STRINGID_PKMNWASPOISONED]                      = COMPOUND_STRING("¡{B_EFF_NAME_WITH_PREFIX} fue envenenado!"),
    [STRINGID_PKMNPOISONEDBY]                       = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} was poisoned by {B_SCR_NAME_WITH_PREFIX2}'s {B_BUFF1}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNHURTBYPOISON]                     = COMPOUND_STRING("¡El veneno resta salud a {B_ATK_NAME_WITH_PREFIX}!"),
    [STRINGID_PKMNALREADYPOISONED]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} is already poisoned!"),
    [STRINGID_PKMNBADLYPOISONED]                    = COMPOUND_STRING("¡{B_EFF_NAME_WITH_PREFIX} fue gravemente envenenado!"),
    [STRINGID_PKMNENERGYDRAINED]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} had its energy drained!"),
    [STRINGID_PKMNWASBURNED]                        = COMPOUND_STRING("¡{B_EFF_NAME_WITH_PREFIX} se ha quemado!"),
    [STRINGID_PKMNBURNEDBY]                         = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_BUFF1} burned {B_EFF_NAME_WITH_PREFIX2}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNHURTBYBURN]                       = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} se resiente de la quemadura!"),
    [STRINGID_PKMNWASFROZEN]                        = COMPOUND_STRING("¡{B_EFF_NAME_WITH_PREFIX} fue congelado!"),
    [STRINGID_PKMNFROZENBY]                         = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_BUFF1} froze {B_EFF_NAME_WITH_PREFIX2} solid!"), //not in gen 5+, ability popup
    [STRINGID_PKMNISFROZEN]                         = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} está congelado!"),
    [STRINGID_PKMNWASDEFROSTED]                     = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} thawed out!"),
    [STRINGID_PKMNWASDEFROSTEDBY]                   = COMPOUND_STRING("¡{B_CURRENT_MOVE} de {B_SCR_NAME_WITH_PREFIX} derritió el hielo!"),
    [STRINGID_PKMNWASPARALYZED]                     = COMPOUND_STRING("¡{B_EFF_NAME_WITH_PREFIX} está paralizado! ¡Quizás no se mueva!"),
    [STRINGID_PKMNWASPARALYZEDBY]                   = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_BUFF1} paralyzed {B_EFF_NAME_WITH_PREFIX2}, so it may be unable to move!"), //not in gen 5+, ability popup
    [STRINGID_PKMNISPARALYZED]                      = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} está paralizado! ¡No se puede mover!"),
    [STRINGID_PKMNISALREADYPARALYZED]               = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} is already paralyzed!"),
    [STRINGID_PKMNHEALEDPARALYSIS]                  = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} ya no está paralizado!"),
    [STRINGID_STATSWONTINCREASE]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_BUFF1} won't go any higher!"),
    [STRINGID_STATSWONTDECREASE]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_BUFF1} won't go any lower!"),
    [STRINGID_PKMNISCONFUSED]                       = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} está confuso!"),
    [STRINGID_PKMNHEALEDCONFUSION]                  = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} ya no está confuso!"),
    [STRINGID_PKMNWASCONFUSED]                      = COMPOUND_STRING("¡{B_EFF_NAME_WITH_PREFIX} se encuentra confuso!"),
    [STRINGID_PKMNALREADYCONFUSED]                  = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} ya está confuso!"),
    [STRINGID_PKMNFELLINLOVE]                       = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} se ha enamorado!"),
    [STRINGID_PKMNINLOVE]                           = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} se enamoró de {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNIMMOBILIZEDBYLOVE]                = COMPOUND_STRING("¡El amor impide que {B_ATK_NAME_WITH_PREFIX} ataque!"),
    [STRINGID_PKMNCHANGEDTYPE]                      = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} ha cambiado al tipo {B_BUFF1}!"),
    [STRINGID_PKMNFLINCHED]                         = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} retrocedió!"),
    [STRINGID_PKMNREGAINEDHEALTH]                   = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} recuperó salud!"),
    [STRINGID_PKMNHPFULL]                           = COMPOUND_STRING("¡Los PS de {B_DEF_NAME_WITH_PREFIX} están al máximo!"),
    [STRINGID_PKMNRAISEDSPDEF]                      = COMPOUND_STRING("Light Screen made {B_ATK_TEAM2} side stronger against special moves!"),
    [STRINGID_PKMNRAISEDDEF]                        = COMPOUND_STRING("Reflect made {B_ATK_TEAM2} side stronger against physical moves!"),
    [STRINGID_PKMNAURORAVEIL]                       = COMPOUND_STRING("Aurora Veil made {B_ATK_TEAM2} side stronger against physical and special moves!"),
    [STRINGID_PKMNCOVEREDBYVEIL]                    = COMPOUND_STRING("{B_ATK_TEAM1} side became cloaked in a mystical veil!"),
    [STRINGID_PKMNUSEDSAFEGUARD]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} is protected by Safeguard!"),
    [STRINGID_PKMNSAFEGUARDEXPIRED]                 = COMPOUND_STRING("¡El equipo {B_ATK_TEAM1} ya no está protegido por el velo!"),
    [STRINGID_PKMNWENTTOSLEEP]                      = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} se fue a dormir!"), //not in gen 5+
    [STRINGID_PKMNSLEPTHEALTHY]                     = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} recuperó salud durmiendo!"),
    [STRINGID_PKMNWHIPPEDWHIRLWIND]                 = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} provocó un remolino!"),
    [STRINGID_PKMNTOOKSUNLIGHT]                     = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} absorbió luz solar!"),
    [STRINGID_PKMNLOWEREDHEAD]                      = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} bajó la cabeza!"),
    [STRINGID_PKMNFLEWHIGH]                         = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} voló muy alto!"),
    [STRINGID_PKMNDUGHOLE]                          = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} se ocultó en un agujero!"),
    [STRINGID_PKMNSQUEEZEDBYBIND]                   = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} was squeezed by {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNTRAPPEDINVORTEX]                  = COMPOUND_STRING("¡{B_EFF_NAME_WITH_PREFIX} quedó atrapado en el torbellino!"),
    [STRINGID_PKMNWRAPPEDBY]                        = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} was wrapped by {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNCLAMPED]                          = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} clamped down on {B_EFF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNHURTBY]                           = COMPOUND_STRING("¡{B_BUFF1} ha herido a {B_ATK_NAME_WITH_PREFIX}!"),
    [STRINGID_PKMNFREEDFROM]                        = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} se liberó de {B_BUFF1}!"),
    [STRINGID_PKMNCRASHED]                          = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} falló y se cayó!"),
    [STRINGID_PKMNSHROUDEDINMIST]                   = gText_PkmnShroudedInMist,
    [STRINGID_PKMNPROTECTEDBYMIST]                  = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} se ha protegido con Neblina!"),
    [STRINGID_PKMNGETTINGPUMPED]                    = gText_PkmnGettingPumped,
    [STRINGID_PKMNHITWITHRECOIL]                    = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} también se ha hecho daño!"),
    [STRINGID_PKMNPROTECTEDITSELF2]                 = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} se está protegiendo!"),
    [STRINGID_PKMNBUFFETEDBYSANDSTORM]              = COMPOUND_STRING("¡Tormenta Arena zarandea a {B_ATK_NAME_WITH_PREFIX}!"),
    [STRINGID_PKMNPELTEDBYHAIL]                     = COMPOUND_STRING("¡Granizo golpea a {B_ATK_NAME_WITH_PREFIX}!"),
    [STRINGID_PKMNSEEDED]                           = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} fue infectado!"),
    [STRINGID_PKMNAVOIDEDATTACK]                    = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} evitó el ataque!"),
    [STRINGID_BATTLERAVOIDEDATTACK]                 = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} evitó el ataque!"),
    [STRINGID_PKMNSAPPEDBYLEECHSEED]                = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s health is sapped by Leech Seed!"),
    [STRINGID_PKMNFASTASLEEP]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} está dormido como un tronco."),
    [STRINGID_PKMNWOKEUP]                           = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} se despertó!"),
    [STRINGID_PKMNWOKEUPINUPROAR]                   = COMPOUND_STRING("¡Alboroto despertó a {B_EFF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNCAUSEDUPROAR]                     = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} caused an uproar!"),
    [STRINGID_PKMNMAKINGUPROAR]                     = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} está montando un Alboroto!"),
    [STRINGID_PKMNCALMEDDOWN]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} se tranquilizó."),
    [STRINGID_PKMNSTOCKPILED]                       = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} reservó {B_BUFF1}!"),
    [STRINGID_PKMNCANTSLEEPINUPROAR2]               = COMPOUND_STRING("¡Pero {B_DEF_NAME_WITH_PREFIX2} no puede dormir con el alboroto!"),
    [STRINGID_UPROARKEPTPKMNAWAKE]                  = COMPOUND_STRING("¡El alboroto mantuvo despierto a {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNSTAYEDAWAKEUSING]                 = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} stayed awake!"),
    [STRINGID_PKMNSTORINGENERGY]                    = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} está acumulando energía!"),
    [STRINGID_PKMNUNLEASHEDENERGY]                  = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} liberó energía!"),
    [STRINGID_PKMNFATIGUECONFUSION]                 = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} became confused due to fatigue!"),
    [STRINGID_PLAYERPICKEDUPMONEY]                  = COMPOUND_STRING("¡Recogiste ¥{B_BUFF1}!\p"),
    [STRINGID_PKMNUNAFFECTED]                       = COMPOUND_STRING("¡No afectó a {B_DEF_NAME_WITH_PREFIX}!"),
    [STRINGID_PKMNTRANSFORMEDINTO]                  = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} se transformó en {B_BUFF1}!"),
    [STRINGID_PKMNMADESUBSTITUTE]                   = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} creó un Sustituto!"),
    [STRINGID_PKMNHASSUBSTITUTE]                    = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} ya tiene un Sustituto!"),
    [STRINGID_SUBSTITUTEDAMAGED]                    = COMPOUND_STRING("¡El sustituto recibió el daño por {B_DEF_NAME_WITH_PREFIX2}!\p"),
    [STRINGID_PKMNSUBSTITUTEFADED]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s substitute faded!\p"),
    [STRINGID_PKMNMUSTRECHARGE]                     = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} necesita recuperarse de su ataque!"),
    [STRINGID_PKMNRAGEBUILDING]                     = COMPOUND_STRING("¡La Furia de {B_DEF_NAME_WITH_PREFIX} está creciendo!"),
    [STRINGID_PKMNMOVEWASDISABLED]                  = COMPOUND_STRING("¡{B_BUFF1} de {B_DEF_NAME_WITH_PREFIX} fue desactivado por Anulación!"),
    [STRINGID_PKMNMOVEISDISABLED]                   = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} no puede usar {B_CURRENT_MOVE} por culpa de Anulación!\p"),
    [STRINGID_PKMNMOVEDISABLEDNOMORE]               = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s move is no longer disabled!"),
    [STRINGID_PKMNGOTENCORE]                        = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} sufrió los efectos de Otra Vez!"),
    [STRINGID_PKMNGOTENCOREDMOVE]                   = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} can only use {B_CURRENT_MOVE}!\p"),
    [STRINGID_PKMNENCOREENDED]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} ended its encore!"),
    [STRINGID_PKMNTOOKAIM]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} took aim at {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNSKETCHEDMOVE]                     = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} usó Esquema en {B_BUFF1}!"),
    [STRINGID_PKMNTRYINGTOTAKEFOE]                  = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} intenta llevarse a su rival!"),
    [STRINGID_PKMNTOOKFOE]                          = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} se llevó a su atacante consigo!"),
    [STRINGID_PKMNREDUCEDPP]                        = COMPOUND_STRING("¡Redujo {B_BUFF1} de {B_DEF_NAME_WITH_PREFIX} en {B_BUFF2}!"),
    [STRINGID_PKMNSTOLEITEM]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} stole {B_BUFF2}'s {B_LAST_ITEM}!"),
    [STRINGID_TARGETCANTESCAPENOW]                  = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} no puede escapar!"),
    [STRINGID_PKMNFELLINTONIGHTMARE]                = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} cae en una Pesadilla!"),
    [STRINGID_PKMNLOCKEDINNIGHTMARE]                = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} está inmerso en una Pesadilla!"),
    [STRINGID_PKMNLAIDCURSE]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} cut its own HP and put a curse on {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNAFFLICTEDBYCURSE]                 = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} es víctima de una Maldición!"),
    [STRINGID_SPIKESSCATTERED]                      = COMPOUND_STRING("¡Hay púas esparcidas alrededor del equipo {B_DEF_TEAM2}!"),
    [STRINGID_PKMNHURTBYSPIKES]                     = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} ha sido herido por Púas!"),
    [STRINGID_PKMNIDENTIFIED]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} was identified!"),
    [STRINGID_PKMNPERISHCOUNTFELL]                  = COMPOUND_STRING("¡Contador de salud de {B_ATK_NAME_WITH_PREFIX} bajó a {B_BUFF1}!"),
    [STRINGID_PKMNBRACEDITSELF]                     = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} se ha fortalecido!"),
    [STRINGID_PKMNENDUREDHIT]                       = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} aguantó el golpe!"),
    [STRINGID_MAGNITUDESTRENGTH]                    = COMPOUND_STRING("¡Magnitud {B_BUFF1}!"),
    [STRINGID_PKMNCUTHPMAXEDATTACK]                 = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} redujo sus PS y mejoró su Ataque!"),
    [STRINGID_PKMNCOPIEDSTATCHANGES]                = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} copied {B_EFF_NAME_WITH_PREFIX2}'s stat changes!"),
    [STRINGID_PKMNGOTFREE]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} was freed from {B_BUFF1}!"),
    [STRINGID_PKMNSHEDLEECHSEED]                    = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} se liberó de Drenadoras!"),
    [STRINGID_PKMNBLEWAWAYSPIKES]                   = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} se liberó de Púas!"), // Not in gen 5+
    [STRINGID_PKMNFLEDFROMBATTLE]                   = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} huyó del combate!"),
    [STRINGID_PKMNFORESAWATTACK]                    = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} previó un ataque!"),
    [STRINGID_PKMNTOOKATTACK]                       = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} tomó el ataque de {B_BUFF1}!"),
    [STRINGID_PKMNATTACK]                           = COMPOUND_STRING("¡Ataque de {B_BUFF1}!"), // Not in gen 5+
    [STRINGID_PKMNCENTERATTENTION]                  = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} se convirtió en el centro de atención!"),
    [STRINGID_PKMNCHARGINGPOWER]                    = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} comenzó a cargar energía!"),
    [STRINGID_NATUREPOWERTURNEDINTO]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s Nature Power turned into {B_CURRENT_MOVE}!"),
    [STRINGID_PKMNSTATUSNORMAL]                     = COMPOUND_STRING("¡El estado de {B_ATK_NAME_WITH_PREFIX} regresó a la normalidad!"),
    [STRINGID_PKMNHASNOMOVESLEFT]                   = COMPOUND_STRING("¡A {B_ATK_NAME_WITH_PREFIX} no le quedan movimientos para usar!\p"),
    [STRINGID_PKMNSUBJECTEDTOTORMENT]               = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} es víctima de Tormento!"),
    [STRINGID_PKMNCANTUSEMOVETORMENT]               = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} no puede usar dos veces seguidas el movimiento por Tormento!\p"),
    [STRINGID_PKMNTIGHTENINGFOCUS]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} is tightening its focus!"),
    [STRINGID_PKMNFELLFORTAUNT]                     = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} se dejó engañar por Mofa!"),
    [STRINGID_PKMNCANTUSEMOVETAUNT]                 = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} no puede usar {B_CURRENT_MOVE} después de Mofa!\p"),
    [STRINGID_PKMNREADYTOHELP]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is ready to help {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNSWITCHEDITEMS]                    = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} provocó un cambio de objeto!"),
    [STRINGID_PKMNCOPIEDFOE]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} copied {B_DEF_NAME_WITH_PREFIX2}'s Ability!"),
    [STRINGID_PKMNWISHCAMETRUE]                     = COMPOUND_STRING("¡El Deseo de {B_BUFF1} se hizo realidad!"),
    [STRINGID_PKMNPLANTEDROOTS]                     = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} echó raíces!"),
    [STRINGID_PKMNABSORBEDNUTRIENTS]                = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} absorbió nutrientes con las raíces!"),
    [STRINGID_PKMNANCHOREDITSELF]                   = COMPOUND_STRING("¡{B_EFF_NAME_WITH_PREFIX} se fijó al suelo con sus raíces!"),
    [STRINGID_PKMNWASMADEDROWSY]                    = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} comenzó a sentirse somnoliento!"),
    [STRINGID_PKMNKNOCKEDOFF]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} knocked off {B_EFF_NAME_WITH_PREFIX2}'s {B_LAST_ITEM}!"),
    [STRINGID_PKMNSWAPPEDABILITIES]                 = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} intercambió habilidades con su objetivo!"),
    [STRINGID_PKMNSEALEDOPPONENTMOVE]               = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} selló cualquier movimiento que comparte con su objetivo!"),
    [STRINGID_PKMNCANTUSEMOVESEALED]                = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} no puede usar su movimiento sellado {B_CURRENT_MOVE}!\p"),
    [STRINGID_PKMNWANTSGRUDGE]                      = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} quiere que su objetivo guarde rencor!"),
    [STRINGID_PKMNLOSTPPGRUDGE]                     = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} perdió todos los PP de {B_BUFF1} debido al rencor!"),
    [STRINGID_PKMNSHROUDEDITSELF]                   = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} se envolvió con un Manto Espejo!"),
    [STRINGID_PKMNMOVEBOUNCED]                      = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} devolvió {B_CURRENT_MOVE}!"),
    [STRINGID_PKMNWAITSFORTARGET]                   = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} espera a que su objetivo haga un movimiento!"),
    [STRINGID_PKMNSNATCHEDMOVE]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} snatched {B_SCR_NAME_WITH_PREFIX2}'s move!"),
    [STRINGID_PKMNMADEITRAIN]                       = COMPOUND_STRING("¡{B_SCR_ABILITY} de {B_SCR_NAME_WITH_PREFIX} provocó la lluvia!"), //not in gen 5+, ability popup
    [STRINGID_PKMNPROTECTEDBY]                      = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} fue protegido por {B_DEF_ABILITY}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNPREVENTSUSAGE]                    = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} prevents {B_ATK_NAME_WITH_PREFIX2} from using {B_CURRENT_MOVE}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNRESTOREDHPUSING]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} had its HP restored."),
    [STRINGID_PKMNCHANGEDTYPEWITH]                  = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}'s type changed to {B_BUFF1}!"),
    [STRINGID_PKMNPREVENTSROMANCEWITH]              = COMPOUND_STRING("¡{B_DEF_ABILITY} de {B_DEF_NAME_WITH_PREFIX} impide que se enamore!"), //not in gen 5+, ability popup
    [STRINGID_PKMNPREVENTSCONFUSIONWITH]            = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} no puede confundirse!"),
    [STRINGID_PKMNRAISEDFIREPOWERWITH]              = COMPOUND_STRING("¡Los movimientos de tipo Fuego de {B_SCR_NAME_WITH_PREFIX} ganaron potencia!"),
    [STRINGID_PKMNANCHORSITSELFWITH]                = COMPOUND_STRING("¡{B_EFF_NAME_WITH_PREFIX} se fijó al suelo con sus ventosas!"),
    [STRINGID_PKMNPREVENTSSTATLOSSWITH]             = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s stats were not lowered!"),
    [STRINGID_PKMNHURTSWITH]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} was hurt by {B_DEF_NAME_WITH_PREFIX2}'s {B_BUFF1}!"),
    [STRINGID_PKMNTRACED]                           = COMPOUND_STRING("It traced {B_BUFF1}'s {B_BUFF2}!"),
    [STRINGID_STATSHARPLY]                          = gText_StatSharply,
    [STRINGID_STATHARSHLY]                          = COMPOUND_STRING(" mucho"),
    [STRINGID_STATROSE]                             = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_BUFF1} rose{B_BUFF2}!"),
    [STRINGID_STATFELL]                             = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_BUFF1} {B_BUFF2}fell!"),
    [STRINGID_CRITICALHIT]                          = COMPOUND_STRING("¡Un golpe crítico!"),
    [STRINGID_ONEHITKO]                             = COMPOUND_STRING("¡K.O. en 1 golpe!"),
    [STRINGID_123POOF]                              = COMPOUND_STRING("1…{PAUSE 10}2…{PAUSE 10}and…{PAUSE 10}{PAUSE 20}{PLAY_SE SE_BALL_BOUNCE_1}¡puf!\p"),
    [STRINGID_ANDELLIPSIS]                          = COMPOUND_STRING("Y…\p"),
    [STRINGID_NOTVERYEFFECTIVE]                     = COMPOUND_STRING("No es muy eficaz…"),
    [STRINGID_SUPEREFFECTIVE]                       = COMPOUND_STRING("¡Es muy eficaz!"),
    [STRINGID_GOTAWAYSAFELY]                        = sText_GotAwaySafely,
    [STRINGID_WILDPKMNFLED]                         = COMPOUND_STRING("{PLAY_SE SE_FLEE}¡{B_BUFF1} salvaje ha huido!"),
    [STRINGID_NORUNNINGFROMTRAINERS]                = COMPOUND_STRING("¡No puedes huir de un combate contra un Entrenador!\p"),
    [STRINGID_CANTESCAPE]                           = COMPOUND_STRING("¡No puedes huir!\p"),
    [STRINGID_DONTLEAVEBIRCH]                       = COMPOUND_STRING("Prof. Abedul: ¡¡¡No me dejes así!!!\p"), //no decapitalize until it is everywhere
    [STRINGID_BUTNOTHINGHAPPENED]                   = COMPOUND_STRING("¡Pero no tuvo ningún efecto!"),
    [STRINGID_BUTITFAILED]                          = COMPOUND_STRING("¡Pero falló!"),
    [STRINGID_ITHURTCONFUSION]                      = COMPOUND_STRING("¡Está tan confuso que se hirió a sí mismo!"),
    [STRINGID_STARTEDTORAIN]                        = COMPOUND_STRING("¡Ha empezado a llover!"),
    [STRINGID_DOWNPOURSTARTED]                      = COMPOUND_STRING("¡Comenzó a caer un chaparrón!"), // corresponds to DownpourText in pokegold and pokecrystal and is used by Rain Dance in GSC
    [STRINGID_RAINCONTINUES]                        = COMPOUND_STRING("Sigue lloviendo…"), //not in gen 5+
    [STRINGID_DOWNPOURCONTINUES]                    = COMPOUND_STRING("El chaparrón continúa…"), // unused
    [STRINGID_RAINSTOPPED]                          = COMPOUND_STRING("Ha dejado de llover."),
    [STRINGID_SANDSTORMBREWED]                      = COMPOUND_STRING("¡Se acerca una tormenta de arena!"),
    [STRINGID_SANDSTORMRAGES]                       = COMPOUND_STRING("La tormenta de arena arrecia…"),
    [STRINGID_SANDSTORMSUBSIDED]                    = COMPOUND_STRING("La tormenta de arena amainó."),
    [STRINGID_SUNLIGHTGOTBRIGHT]                    = COMPOUND_STRING("¡El sol está brillando!"),
    [STRINGID_SUNLIGHTSTRONG]                       = COMPOUND_STRING("Hace mucho sol…"), //not in gen 5+
    [STRINGID_SUNLIGHTFADED]                        = COMPOUND_STRING("Se ha ido el sol."),
    [STRINGID_STARTEDHAIL]                          = COMPOUND_STRING("¡Ha empezado a granizar!"),
    [STRINGID_HAILCONTINUES]                        = COMPOUND_STRING("Sigue granizando…"),
    [STRINGID_HAILSTOPPED]                          = COMPOUND_STRING("Ha dejado de granizar."),
    [STRINGID_STATCHANGESGONE]                      = COMPOUND_STRING("¡Se han eliminado todos los cambios en las características!"),
    [STRINGID_COINSSCATTERED]                       = COMPOUND_STRING("¡Hay monedas por todas partes!"),
    [STRINGID_TOOWEAKFORSUBSTITUTE]                 = COMPOUND_STRING("¡Estaba demasiado débil para crear un Sustituto!"),
    [STRINGID_SHAREDPAIN]                           = COMPOUND_STRING("¡Los combatientes comparten el daño sufrido!"),
    [STRINGID_BELLCHIMED]                           = COMPOUND_STRING("¡Ha repicado una campana!"),
    [STRINGID_FAINTINTHREE]                         = COMPOUND_STRING("¡Los Pokémon de ambas partes se debilitarán dentro de 3 turnos!"),
    [STRINGID_NOPPLEFT]                             = COMPOUND_STRING("¡No quedan PP para este movimiento!\p"), //not in gen 5+
    [STRINGID_BUTNOPPLEFT]                          = COMPOUND_STRING("¡Pero no quedan PP para este movimiento!"),
    [STRINGID_PLAYERUSEDITEM]                       = COMPOUND_STRING("¡Usaste {B_LAST_ITEM}!"),
    [STRINGID_TRAINERBLOCKEDBALL]                   = COMPOUND_STRING("El entrenador bloqueó tú Poké Ball!"),
    [STRINGID_DONTBEATHIEF]                         = COMPOUND_STRING("¡Robar está mal!"),
    [STRINGID_ITDODGEDBALL]                         = COMPOUND_STRING("¡Esquivó la Ball! ¡No has podido atrapar a este Pokémon!"),
    [STRINGID_PKMNBROKEFREE]                        = COMPOUND_STRING("¡Oh, no! ¡El Pokémon se ha escapado!"),
    [STRINGID_ITAPPEAREDCAUGHT]                     = COMPOUND_STRING("¡Vaya! ¡Parecía que lo habías atrapado!"),
    [STRINGID_AARGHALMOSTHADIT]                     = COMPOUND_STRING("¡Qué pena! ¡Te faltó poco!"),
    [STRINGID_SHOOTSOCLOSE]                         = COMPOUND_STRING("¡Uy! ¡Casi lo consigues!"),
    [STRINGID_GOTCHAPKMNCAUGHTPLAYER]               = COMPOUND_STRING("¡Ya está! ¡{B_DEF_NAME} atrapado!{WAIT_SE}{PLAY_BGM MUS_CAUGHT}\p"),
    [STRINGID_GOTCHAPKMNCAUGHTWALLY]                = COMPOUND_STRING("¡Ya está! ¡{B_DEF_NAME} atrapado!{WAIT_SE}{PLAY_BGM MUS_CAUGHT}{PAUSE 127}"),
    [STRINGID_GIVENICKNAMECAPTURED]                 = COMPOUND_STRING("¿Quieres ponerle un mote a {B_DEF_NAME}?"),
    [STRINGID_PKMNDATAADDEDTODEX]                   = COMPOUND_STRING("Registrados en la Pokédex los datos de {B_DEF_NAME}.\p"),
    [STRINGID_ITISRAINING]                          = COMPOUND_STRING("Está lloviendo…"),
    [STRINGID_SANDSTORMISRAGING]                    = COMPOUND_STRING("La tormenta de arena cobra fuerza…"),
    [STRINGID_CANTESCAPE2]                          = COMPOUND_STRING("¡No puedes huir!\p"),
    [STRINGID_PKMNIGNORESASLEEP]                    = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} ignoró las órdenes porque está dormido!"),
    [STRINGID_PKMNIGNOREDORDERS]                    = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} ignoró las órdenes!"),
    [STRINGID_PKMNBEGANTONAP]                       = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} se fue a dormir!"),
    [STRINGID_PKMNLOAFING]                          = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} está holgazaneando!"),
    [STRINGID_PKMNWONTOBEY]                         = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} no quiere obedecer!"),
    [STRINGID_PKMNTURNEDAWAY]                       = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} se alejó!"),
    [STRINGID_PKMNPRETENDNOTNOTICE]                 = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} fingió no darse cuenta!"),
    [STRINGID_ENEMYABOUTTOSWITCHPKMN]               = COMPOUND_STRING("{B_TRAINER1_NAME_WITH_CLASS} va a sacar a {B_BUFF2}. ¿Quieres cambiar de Pokémon?"),
    [STRINGID_CREPTCLOSER]                          = COMPOUND_STRING("¡{B_PLAYER_NAME} se acercó sigilosamente a {B_OPPONENT_MON1_NAME}!"), //safari
    [STRINGID_CANTGETCLOSER]                        = COMPOUND_STRING("¡{B_PLAYER_NAME} no se puede acercar más!"), //safari
    [STRINGID_PKMNWATCHINGCAREFULLY]                = COMPOUND_STRING("¡{B_OPPONENT_MON1_NAME} te observa atentamente!"), //safari
    [STRINGID_PKMNCURIOUSABOUTX]                    = COMPOUND_STRING("¡{B_OPPONENT_MON1_NAME} siente curiosidad por el {B_BUFF1}!"), //safari
    [STRINGID_PKMNENTHRALLEDBYX]                    = COMPOUND_STRING("¡{B_OPPONENT_MON1_NAME} está embelesado con el {B_BUFF1}!"), //safari
    [STRINGID_PKMNIGNOREDX]                         = COMPOUND_STRING("¡{B_OPPONENT_MON1_NAME} ignoró completamente el {B_BUFF1}!"), //safari
    [STRINGID_THREWPOKEBLOCKATPKMN]                 = COMPOUND_STRING("¡{B_PLAYER_NAME} lanzó un {POKEBLOCK} a {B_OPPONENT_MON1_NAME}!"), //safari
    [STRINGID_OUTOFSAFARIBALLS]                     = COMPOUND_STRING("{PLAY_SE SE_DING_DONG}Encargado: ¡No te quedan más Safari Balls! ¡Se acabó el tiempo!\p"), //safari
    [STRINGID_PKMNSITEMCUREDPARALYSIS]              = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} se curó de la parálisis con {B_LAST_ITEM}!"),
    [STRINGID_PKMNSITEMCUREDPOISON]                 = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} se curó del envenenamiento con {B_LAST_ITEM}!"),
    [STRINGID_PKMNSITEMHEALEDBURN]                  = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} se curó las quemaduras con {B_LAST_ITEM}!"),
    [STRINGID_PKMNSITEMDEFROSTEDIT]                 = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} se descongeló con {B_LAST_ITEM}!"),
    [STRINGID_PKMNSITEMWOKEIT]                      = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} se despertó con {B_LAST_ITEM}!"),
    [STRINGID_PKMNSITEMSNAPPEDOUT]                  = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} se libró de la confusión con {B_LAST_ITEM}!"),
    [STRINGID_PKMNSITEMCUREDPROBLEM]                = COMPOUND_STRING("¡{B_LAST_ITEM} de {B_SCR_NAME_WITH_PREFIX} curó su problema de {B_BUFF1}!"), // Not in Gen 5+
    [STRINGID_PKMNSITEMRESTOREDHEALTH]              = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} restauró  salud con {B_LAST_ITEM}!"),
    [STRINGID_PKMNSITEMRESTOREDPP]                  = COMPOUND_STRING("¡{B_LAST_ITEM} de {B_SCR_NAME_WITH_PREFIX} restauró los PP de {B_BUFF1}!"),
    [STRINGID_PKMNSITEMRESTOREDSTATUS]              = COMPOUND_STRING("¡{B_LAST_ITEM} de {B_SCR_NAME_WITH_PREFIX} restauró sus características!"),
    [STRINGID_PKMNSITEMRESTOREDHPALITTLE]           = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} restauró algo sus PS con {B_LAST_ITEM}!"),
    [STRINGID_ITEMALLOWSONLYYMOVE]                  = COMPOUND_STRING("¡{B_LAST_ITEM} solo permite el uso de {B_CURRENT_MOVE}!\p"),
    [STRINGID_PKMNHUNGONWITHX]                      = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} resistió usando su {B_LAST_ITEM}!"),
    [STRINGID_EMPTYSTRING3]                         = gText_EmptyString3,
    [STRINGID_PKMNSXRESTOREDHPALITTLE2]             = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} had its HP restored."),
    [STRINGID_PKMNSXWHIPPEDUPSANDSTORM]             = COMPOUND_STRING("¡{B_SCR_ABILITY} de {B_SCR_NAME_WITH_PREFIX} levantó la tormenta de arena!"), //not in gen 5+, ability popup
    [STRINGID_PKMNSXPREVENTSYLOSS]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_BUFF1} was not lowered!"),
    [STRINGID_PKMNSXINFATUATEDY]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} fell in love!"),
    [STRINGID_PKMNSXMADEYINEFFECTIVE]               = COMPOUND_STRING("¡No se puede quitar el objeto de {B_SCR_NAME_WITH_PREFIX}!"),
    [STRINGID_ITSUCKEDLIQUIDOOZE]                   = COMPOUND_STRING("¡{B_EFF_NAME_WITH_PREFIX} absorbió el lodo líquido!"),
    [STRINGID_PKMNTRANSFORMED]                      = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} se transformó!"),
    [STRINGID_ELECTRICITYWEAKENED]                  = COMPOUND_STRING("¡Se han debilitado los ataques Eléctricos!"),
    [STRINGID_FIREWEAKENED]                         = COMPOUND_STRING("¡Se han debilitado los ataques de Fuego!"),
    [STRINGID_PKMNHIDUNDERWATER]                    = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} se ocultó bajo el agua!"),
    [STRINGID_PKMNSPRANGUP]                         = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} dió salto tremendo!"),
    [STRINGID_HMMOVESCANTBEFORGOTTEN]               = COMPOUND_STRING("Los movimientos MO no se pueden olvidar así.\p"),
    [STRINGID_XFOUNDONEY]                           = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} encontró una unidad de {B_LAST_ITEM}!"),
    [STRINGID_PLAYERDEFEATEDTRAINER1]               = sText_PlayerDefeatedLinkTrainerTrainer1,
    [STRINGID_SOOTHINGAROMA]                        = COMPOUND_STRING("¡Un balsámico aroma impregnó la zona!"),
    [STRINGID_ITEMSCANTBEUSEDNOW]                   = COMPOUND_STRING("Aquí no se pueden usar objetos.{PAUSE 64}"), // Not present in Gen 5+
    [STRINGID_USINGITEMSTATOFPKMNROSE]              = COMPOUND_STRING("¡{B_LAST_ITEM}{B_BUFF2} aumentó {B_BUFF1} de {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_USINGITEMSTATOFPKMNFELL]              = COMPOUND_STRING("¡{B_LAST_ITEM}{B_BUFF2} redujo {B_BUFF1} de {B_SCR_NAME_WITH_PREFIX2}!"), // This string does not exist in Gen 5+. Used to print more info that's otherwise obscured such as using Room Service
    [STRINGID_PKMNUSEDXTOGETPUMPED]                 = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} usa {B_LAST_ITEM} para potenciar los golpes críticos!"),
    [STRINGID_PKMNSXMADEYUSELESS]                   = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} made {B_CURRENT_MOVE} useless!"), //not in gen 5+, ability popup
    [STRINGID_PKMNTRAPPEDBYSANDTOMB]                = COMPOUND_STRING("¡{B_EFF_NAME_WITH_PREFIX} quedó atrapado en las arenas movedizas!"),
    [STRINGID_EMPTYSTRING4]                         = COMPOUND_STRING(""),
    [STRINGID_ABOOSTED]                             = COMPOUND_STRING(" adicionales"),
    [STRINGID_PKMNSXINTENSIFIEDSUN]                 = COMPOUND_STRING("¡{B_SCR_ABILITY} de {B_SCR_NAME_WITH_PREFIX} intensificó los rayos solares!"), //not in gen 5+, ability popup
    [STRINGID_YOUTHROWABALLNOWRIGHT]                = COMPOUND_STRING("Ahora debo lanzar una Ball, ¿no? ¡Intentaré hacerlo lo mejor posible!"),
    [STRINGID_PKMNSXTOOKATTACK]                     = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} recibió el ataque!"),
    [STRINGID_PKMNCHOSEXASDESTINY]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} chose Doom Desire as its destiny!"),
    [STRINGID_PKMNLOSTFOCUS]                        = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} se desconcentró y quedó inmovilizado!"),
    [STRINGID_USENEXTPKMN]                          = COMPOUND_STRING("¿Usas el siguiente Pokémon?"),
    [STRINGID_PKMNFLEDUSINGITS]                     = COMPOUND_STRING("{PLAY_SE SE_FLEE}¡{B_ATK_NAME_WITH_PREFIX} escapó usando su {B_LAST_ITEM}!\p"),
    [STRINGID_PKMNFLEDUSING]                        = COMPOUND_STRING("{PLAY_SE SE_FLEE}¡{B_ATK_NAME_WITH_PREFIX} escapó usando su {B_ATK_ABILITY}!\p"), //not in gen 5+
    [STRINGID_PKMNWASDRAGGEDOUT]                    = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} fue arrastrado al combate!\p\p"),
    [STRINGID_PKMNSITEMNORMALIZEDSTATUS]            = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} normalizó su estado con {B_LAST_ITEM}!"), // Not in Gen 5+
    [STRINGID_TRAINER1USEDITEM]                     = COMPOUND_STRING("¡{B_ATK_TRAINER_NAME_WITH_CLASS} usó {B_LAST_ITEM}!"),
    [STRINGID_BOXISFULL]                            = COMPOUND_STRING("¡Las CAJAS están llenas! ¡No puedes atrapar ninguno más!\p"),
    [STRINGID_PKMNSXMADEITINEFFECTIVE]              = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} made it ineffective!"),
    [STRINGID_PKMNSXPREVENTSFLINCHING]              = COMPOUND_STRING("¡{B_EFF_ABILITY} de {B_EFF_NAME_WITH_PREFIX} impide el retroceso!"), //not in gen 5+, ability popup
    [STRINGID_PKMNALREADYHASBURN]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} ya está quemado."),
    [STRINGID_PKMNSXBLOCKSY]                        = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} blocks {B_CURRENT_MOVE}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNSXWOREOFF]                        = COMPOUND_STRING("{B_ATK_TEAM1} side's {B_BUFF1} wore off!"),
    [STRINGID_THEWALLSHATTERED]                     = COMPOUND_STRING("¡Destruyó la protección!"), //not in gen5+, uses "your teams light screen wore off!" etc instead
    [STRINGID_PKMNSXCUREDITSYPROBLEM]               = COMPOUND_STRING("¡{B_SCR_ABILITY} de {B_SCR_NAME_WITH_PREFIX} curó su problema de {B_BUFF1}!"), //not in gen 5+, ability popup
    [STRINGID_ATTACKERCANTESCAPE]                   = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} no puede escapar!\p"),
    [STRINGID_PKMNOBTAINEDX]                        = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} obtuvo {B_BUFF1}."),
    [STRINGID_PKMNOBTAINEDX2]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} obtuvo {B_BUFF2}."),
    [STRINGID_PKMNOBTAINEDXYOBTAINEDZ]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} obtuvo {B_BUFF1}.\p{B_DEF_NAME_WITH_PREFIX} obtuvo {B_BUFF2}."),
    [STRINGID_BUTNOEFFECT]                          = COMPOUND_STRING("¡Pero no surtió efecto!"),
    [STRINGID_TWOENEMIESDEFEATED]                   = sText_TwoInGameTrainersDefeated,
    [STRINGID_TRAINER2LOSETEXT]                     = COMPOUND_STRING("{B_TRAINER2_LOSE_TEXT}"),
    [STRINGID_PKMNINCAPABLEOFPOWER]                 = COMPOUND_STRING("¡Parece que {B_ATK_NAME_WITH_PREFIX} no es capaz de usar su poder!"),
    [STRINGID_GLINTAPPEARSINEYE]                    = COMPOUND_STRING("A glint appears in {B_SCR_NAME_WITH_PREFIX2}'s eyes!"),
    [STRINGID_PKMNGETTINGINTOPOSITION]              = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} está preparándose!"),
    [STRINGID_PKMNBEGANGROWLINGDEEPLY]              = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} ha empezado a gruñir con fuerza!"),
    [STRINGID_PKMNEAGERFORMORE]                     = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} no se da por satisfecho!"),
    [STRINGID_DEFEATEDOPPONENTBYREFEREE]            = COMPOUND_STRING("Por decisión del Juez, ¡{B_PLAYER_MON1_NAME} ha ganado a su rival {B_OPPONENT_MON1_NAME}!"),
    [STRINGID_LOSTTOOPPONENTBYREFEREE]              = COMPOUND_STRING("Por decisión del Juez, ¡{B_PLAYER_MON1_NAME} ha perdido ante su rival {B_OPPONENT_MON1_NAME}!"),
    [STRINGID_TIEDOPPONENTBYREFEREE]                = COMPOUND_STRING("Por decisión del Juez, ¡{B_PLAYER_MON1_NAME} y {B_OPPONENT_MON1_NAME} han empatado!"),
    [STRINGID_QUESTIONFORFEITMATCH]                 = COMPOUND_STRING("¿Quieres abandonar el encuentro y salir?"),
    [STRINGID_FORFEITEDMATCH]                       = COMPOUND_STRING("Se abandonó el combate."),
    [STRINGID_PKMNTRANSFERREDSOMEONESPC]            = gText_PkmnTransferredSomeonesPC,
    [STRINGID_PKMNTRANSFERREDLANETTESPC]            = gText_PkmnTransferredLanettesPC,
    [STRINGID_PKMNBOXSOMEONESPCFULL]                = gText_PkmnTransferredSomeonesPCBoxFull,
    [STRINGID_PKMNBOXLANETTESPCFULL]                = gText_PkmnTransferredLanettesPCBoxFull,
    [STRINGID_TRAINER1WINTEXT]                      = COMPOUND_STRING("{B_TRAINER1_WIN_TEXT}"),
    [STRINGID_TRAINER2WINTEXT]                      = COMPOUND_STRING("{B_TRAINER2_WIN_TEXT}"),
    [STRINGID_ENDUREDSTURDY]                        = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} aguantó el golpe con {B_DEF_ABILITY}!"),
    [STRINGID_POWERHERB]                            = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} fue cargado gracias a {B_LAST_ITEM}!"),
    [STRINGID_HURTBYITEM]                           = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} ha resultado herido por {B_LAST_ITEM}!"),
    [STRINGID_GRAVITYINTENSIFIED]                   = COMPOUND_STRING("¡La gravedad se ha incrementado!"),
    [STRINGID_TARGETWOKEUP]                         = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} woke up!"),
    [STRINGID_TAILWINDBLEW]                         = COMPOUND_STRING("¡El viento sopla a favor del equipo {B_ATK_TEAM2}!"),
    [STRINGID_PKMNWENTBACK]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} went back to {B_ATK_TRAINER_NAME}!"),
    [STRINGID_PKMNCANTUSEITEMSANYMORE]              = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} no puede usar objetos!"),
    [STRINGID_PKMNFLUNG]                            = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} flung its {B_LAST_ITEM}!"),
    [STRINGID_PKMNPREVENTEDFROMHEALING]             = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} no puede curarse!"),
    [STRINGID_PKMNSWITCHEDATKANDDEF]                = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} ha intercambiado su ataque y defensa!"),
    [STRINGID_PKMNSABILITYSUPPRESSED]               = COMPOUND_STRING("¡La habilidad de {B_DEF_NAME_WITH_PREFIX} fue suprimida!"),
    [STRINGID_SHIELDEDFROMCRITICALHITS]             = COMPOUND_STRING("Lucky Chant shielded {B_ATK_TEAM2} side from critical hits!"), // Currently not present in Champions
    [STRINGID_PKMNACQUIREDABILITY]                  = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} obtuvo {B_DEF_ABILITY}!"),
    [STRINGID_POISONSPIKESSCATTERED]                = COMPOUND_STRING("¡Hay púas tóxicas alrededor del equipo {B_DEF_TEAM2}!"),
    [STRINGID_PKMNSWITCHEDSTATCHANGES]              = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} ha intercambiado los cambios de características con el\pobjetivo!"),
    [STRINGID_PKMNSURROUNDEDWITHVEILOFWATER]        = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} se ha rodeado con un velo de agua!"),
    [STRINGID_PKMNLEVITATEDONELECTROMAGNETISM]      = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} levita con electromagnetismo!"),
    [STRINGID_PKMNTWISTEDDIMENSIONS]                = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} ha alterado las dimensiones!"),
    [STRINGID_POINTEDSTONESFLOAT]                   = COMPOUND_STRING("¡Se han esparcido rocas alrededor del equipo {B_DEF_TEAM2}!"),
    [STRINGID_TRAPPEDBYSWIRLINGMAGMA]               = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} became trapped by swirling magma!"),
    [STRINGID_VANISHEDINSTANTLY]                    = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} desaparece en un abrir y cerrar de ojos!"),
    [STRINGID_PROTECTEDTEAM]                        = COMPOUND_STRING("¡{B_CURRENT_MOVE} protegió al equipo {B_ATK_TEAM2}!"),
    [STRINGID_SHAREDITSGUARD]                       = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} ha compartido sus defensas con el objetivo!"),
    [STRINGID_SHAREDITSPOWER]                       = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} ha compartido su poder con el objetivo!"),
    [STRINGID_SWAPSDEFANDSPDEFOFALLPOKEMON]         = COMPOUND_STRING("¡Se ha creado un espacio en que defensa y defensa especial se invierten!"),
    [STRINGID_BECAMENIMBLE]                         = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} became nimble!"),
    [STRINGID_HURLEDINTOTHEAIR]                     = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} ha sido lanzado por los aires!"),
    [STRINGID_HELDITEMSLOSEEFFECTS]                 = COMPOUND_STRING("¡Se ha creado un espacio en el que el efecto de los objetos desaparece!"),
    [STRINGID_FELLSTRAIGHTDOWN]                     = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} fell straight down!"),
    [STRINGID_TARGETCHANGEDTYPE]                    = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} se ha transformado en el tipo {B_BUFF1}!"),
    [STRINGID_KINDOFFER]                            = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} ha aceptado la propuesta!"),
    [STRINGID_RESETSTARGETSSTATLEVELS]              = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX}'s stat changes were removed!"),
    [STRINGID_ALLYSWITCHPOSITION]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} and {B_SCR_NAME_WITH_PREFIX2} switched places!"),
    [STRINGID_REFLECTTARGETSTYPE]                   = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} adoptó el tipo de {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_EMBARGOENDS]                          = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} ya puede usar objetos de nuevo!"),
    [STRINGID_ELECTROMAGNETISM]                     = COMPOUND_STRING("electromagnetismo"),
    [STRINGID_BUFFERENDS]                           = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_BUFF1} wore off!"),
    [STRINGID_TELEKINESISENDS]                      = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} se liberó de la telequinesis!"),
    [STRINGID_TAILWINDENDS]                         = COMPOUND_STRING("¡Ha dejado de soplar el viento que favorecía al equipo {B_ATK_TEAM1}!"),
    [STRINGID_LUCKYCHANTENDS]                       = COMPOUND_STRING("¡El efecto de Conjuro se ha desvanecido en el equipo {B_ATK_TEAM1}!"),
    [STRINGID_TRICKROOMENDS]                        = COMPOUND_STRING("¡Se han restaurado las dimensiones alteradas!"),
    [STRINGID_WONDERROOMENDS]                       = COMPOUND_STRING("¡Los efectos de Zona extraña sobre la Defensa y la Defensa Especial han\pdesaparecido!"),
    [STRINGID_MAGICROOMENDS]                        = COMPOUND_STRING("¡Los efectos de Zona mágica sobre los objetos han desaparecido!"),
    [STRINGID_MUDSPORTENDS]                         = COMPOUND_STRING("Chapoteolodo ha dejado de surtir efecto."),
    [STRINGID_WATERSPORTENDS]                       = COMPOUND_STRING("Hidrochorro ha dejado de surtir efecto."),
    [STRINGID_GRAVITYENDS]                          = COMPOUND_STRING("¡La gravedad ha vuelto a su estado normal!"),
    [STRINGID_AQUARINGHEAL]                         = COMPOUND_STRING("A veil of water restored {B_ATK_NAME_WITH_PREFIX2}'s HP!"),
    [STRINGID_ELECTRICTERRAINENDS]                  = COMPOUND_STRING("El campo de corriente eléctrica ha desaparecido."),
    [STRINGID_MISTYTERRAINENDS]                     = COMPOUND_STRING("La niebla se ha disipado."),
    [STRINGID_PSYCHICTERRAINENDS]                   = COMPOUND_STRING("Ha desaparecido la extraña sensación que se percibía en el terreno\pde combate."),
    [STRINGID_GRASSYTERRAINENDS]                    = COMPOUND_STRING("La hierba ha desaparecido."),
    [STRINGID_TARGETABILITYSTATRAISE]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} {B_BUFF2}raised its {B_BUFF1}!"), // Not in Gen 5+
    [STRINGID_STATWASMAXEDOUT]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} maxed its {B_BUFF1}!"),
    [STRINGID_ATTACKERABILITYSTATRAISE]             = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s {B_ATK_ABILITY} {B_BUFF2}raised its {B_BUFF1}!"), // Not in Gen 5+
    [STRINGID_POISONHEALHPUP]                       = COMPOUND_STRING("¡El veneno curó un poco a {B_ATK_NAME_WITH_PREFIX2}!"), // Not in Gen 5+
    [STRINGID_BADDREAMSDMG]                         = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} is tormented!"),
    [STRINGID_MOLDBREAKERENTERS]                    = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} ha usado Rompemoldes!"),
    [STRINGID_TERAVOLTENTERS]                       = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} desprende un aura chisporroteante!"),
    [STRINGID_TURBOBLAZEENTERS]                     = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} desprende un aura llameante!"),
    [STRINGID_SLOWSTARTENTERS]                      = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} no rinde todo lo que podría!"),
    [STRINGID_SLOWSTARTEND]                         = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} vuelve a ir a por todas!"),
    [STRINGID_SOLARPOWERHPDROP]                     = COMPOUND_STRING("¡{B_ATK_ABILITY} de {B_ATK_NAME_WITH_PREFIX} hace que pierda unos pocos PS!"), // Not in Gen 5+
    [STRINGID_PKMNWASHURT]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} was hurt!"),
    [STRINGID_ANTICIPATIONACTIVATES]                = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} se ha estremecido!"),
    [STRINGID_FOREWARNACTIVATES]                    = COMPOUND_STRING("{B_SCR_ABILITY} alerted {B_SCR_NAME_WITH_PREFIX2} to {B_EFF_NAME_WITH_PREFIX2}'s {B_BUFF1}!"),
    [STRINGID_ICEBODYHPGAIN]                        = COMPOUND_STRING("¡{B_ATK_ABILITY} de {B_ATK_NAME_WITH_PREFIX} hizo que recuperara unos pocos PS"), // Not in Gen 5+
    [STRINGID_SNOWWARNINGHAIL]                      = COMPOUND_STRING("¡Ha empezado a granizar!"),
    [STRINGID_FRISKACTIVATES]                       = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} was frisked, revealing its {B_LAST_ITEM}!"),
    [STRINGID_UNNERVEENTERS]                        = COMPOUND_STRING("{B_EFF_TEAM1} side is too nervous to eat Berries!"),
    [STRINGID_HARVESTBERRY]                         = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} ha reciclado {B_LAST_ITEM}!"),
    [STRINGID_PROTEANTYPECHANGE]                    = COMPOUND_STRING("¡{B_ATK_ABILITY} de {B_ATK_NAME_WITH_PREFIX} lo ha cambiado a tipo {B_BUFF1}!"),
    [STRINGID_SYMBIOSISITEMPASS]                    = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} compartió su {B_LAST_ITEM} con {B_EFF_NAME_WITH_PREFIX2}!"),
    [STRINGID_STEALTHROCKDMG]                       = COMPOUND_STRING("Pointed stones dug into {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_TOXICSPIKESABSORBED]                  = COMPOUND_STRING("¡Desaparecieron las púas tóxicas del equipo {B_EFF_TEAM2}!"),
    [STRINGID_TOXICSPIKESPOISONED]                  = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} ha sido envenenado!"),
    [STRINGID_TOXICSPIKESBADLYPOISONED]             = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} fue gravemente envenenado!"),
    [STRINGID_STICKYWEBSWITCHIN]                    = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} was caught in a sticky web!"),
    [STRINGID_HEALINGWISHCAMETRUE]                  = COMPOUND_STRING("¡Se cumplió el deseo de curación de {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_HEALINGWISHHEALED]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} regained health!"),
    [STRINGID_LUNARDANCECAMETRUE]                   = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} became cloaked in mystical moonlight!"),
    [STRINGID_CURSEDBODYDISABLED]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s {B_BUFF1} was disabled!"),
    [STRINGID_ATTACKERACQUIREDABILITY]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} acquired {B_ATK_ABILITY}!"), // Not in Gen 5+
    [STRINGID_TARGETABILITYSTATLOWER]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY} {B_BUFF2}lowered its {B_BUFF1}!"), // Not in Gen 5+
    [STRINGID_TARGETSTATWONTGOHIGHER]               = COMPOUND_STRING("¡{B_BUFF1} de {B_DEF_NAME_WITH_PREFIX} no puede aumentar más!"),
    [STRINGID_PKMNMOVEBOUNCEDABILITY]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s {B_CURRENT_MOVE} was bounced back!"),
    [STRINGID_IMPOSTERTRANSFORM]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} transformed into {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_ASSAULTVESTDOESNTALLOW]               = COMPOUND_STRING("¡El efecto de {B_LAST_ITEM} impide la ejecución de movimientos de estado.\p"),
    [STRINGID_GRAVITYPREVENTSUSAGE]                 = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} no puede usar {B_CURRENT_MOVE} debido a la fuerza de la gravedad!\p"),
    [STRINGID_HEALBLOCKPREVENTSUSAGE]               = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} no puede curarse debido a Anticura!\p"),
    [STRINGID_NOTDONEYET]                           = COMPOUND_STRING("¡El efecto de este movimiento no está programado aún!"),
    [STRINGID_STICKYWEBUSED]                        = COMPOUND_STRING("¡Una red viscosa se extiende a los pies del equipo {B_DEF_TEAM2}!"),
    [STRINGID_QUASHSUCCESS]                         = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s move was postponed!"),
    [STRINGID_PKMNBLEWAWAYTOXICSPIKES]              = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} ha retirado las púas tóxicas!"),
    [STRINGID_PKMNBLEWAWAYSTICKYWEB]                = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} ha retirado la red viscosa!"),
    [STRINGID_PKMNBLEWAWAYSTEALTHROCK]              = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} ha retirado las piedras puntiagudas!"),
    [STRINGID_IONDELUGEON]                          = COMPOUND_STRING("¡Una lluvia de electrones cae sobre el terreno de combate!"),
    [STRINGID_TOPSYTURVYSWITCHEDSTATS]              = COMPOUND_STRING("All stat changes on {B_DEF_NAME_WITH_PREFIX2} were inverted!"),
    [STRINGID_TERRAINBECOMESMISTY]                  = COMPOUND_STRING("¡La niebla ha envuelto el terreno de combate!"),
    [STRINGID_TERRAINBECOMESGRASSY]                 = COMPOUND_STRING("¡El terreno de combate se ha cubierto de hierba!"),
    [STRINGID_TERRAINBECOMESELECTRIC]               = COMPOUND_STRING("¡Se ha formado un campo de corriente eléctrica en el terreno de combate!"),
    [STRINGID_TERRAINBECOMESPSYCHIC]                = COMPOUND_STRING("¡El terreno de combate se ha vuelto muy extraño!"),
    [STRINGID_TARGETELECTRIFIED]                    = COMPOUND_STRING("¡Electrificación hace que el siguiente movimiento de {B_DEF_NAME_WITH_PREFIX} sea de tipo Eléctrico!"),
    [STRINGID_MEGAEVOREACTING]                      = COMPOUND_STRING("¡{B_LAST_ITEM} de {B_ATK_NAME_WITH_PREFIX} reacciona ante el Mega Aro de {B_ATK_TRAINER_NAME}!"), //actually displays the type of mega ring in inventory, but we didnt implement them :(
    [STRINGID_MEGAEVOEVOLVED]                       = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} ha evolucionado a Mega-{B_BUFF1}!"),
    [STRINGID_DRASTICALLY]                          = gText_drastically,
    [STRINGID_SEVERELY]                             = gText_severely,
    [STRINGID_INFESTATION]                          = COMPOUND_STRING("¡{B_EFF_NAME_WITH_PREFIX} sufrió la infestación de {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_NOEFFECTONTARGET]                     = COMPOUND_STRING("It won't have any effect on {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_BURSTINGFLAMESHIT]                    = COMPOUND_STRING("¡Las llamas alcanzaron a {B_EFF_NAME_WITH_PREFIX2}!"),
    [STRINGID_BESTOWITEMGIVING]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} received {B_LAST_ITEM} from {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_THIRDTYPEADDED]                       = COMPOUND_STRING("{B_BUFF1} type was added to {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_FELLFORFEINT]                         = COMPOUND_STRING("¡{B_EFF_NAME_WITH_PREFIX} cayó en la finta!"),
    [STRINGID_POKEMONCANNOTUSEMOVE]                 = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} no puede usar {B_CURRENT_MOVE}!"),
    [STRINGID_COVEREDINPOWDER]                      = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} está cubierto de polvo!"),
    [STRINGID_POWDEREXPLODES]                       = COMPOUND_STRING("¡El polvo ha reaccionado con las llamas y ha explotado!"),
    [STRINGID_BELCHCANTSELECT]                      = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} no ha comido ninguna baya equipada y no puede eructar!\p"),
    [STRINGID_SPECTRALTHIEFSTEAL]                   = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} se ha apropiado de las mejoras en las características del rival!"),
    [STRINGID_GRAVITYGROUNDING]                     = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} no ha podido mantenerse en el aire debido al efecto de la gravedad!"),
    [STRINGID_MISTYTERRAINPREVENTS]                 = COMPOUND_STRING("¡El campo de niebla ha protegido a {B_DEF_NAME_WITH_PREFIX}!"),
    [STRINGID_GRASSYTERRAINHEALS]                   = COMPOUND_STRING("¡El campo de hierba ha curado a {B_ATK_NAME_WITH_PREFIX}"),
    [STRINGID_ELECTRICTERRAINPREVENTS]              = COMPOUND_STRING("¡El campo eléctrico ha protegido a {B_DEF_NAME_WITH_PREFIX}!"),
    [STRINGID_PSYCHICTERRAINPREVENTS]               = COMPOUND_STRING("¡El campo psíquico protege a {B_SCR_NAME_WITH_PREFIX}!"),
    [STRINGID_SAFETYGOGGLESPROTECTED]               = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} is not affected thanks to its {B_LAST_ITEM}!"),
    [STRINGID_FLOWERVEILPROTECTED]                  = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} se rodeó de un velo de pétalos!"),
    [STRINGID_FLOWERVEILPROTECTEDTARGET]            = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} se rodeó de un velo de pétalos!"),
    [STRINGID_AROMAVEILPROTECTED]                   = COMPOUND_STRING("¡Velo Aroma ha protegido a {B_DEF_NAME_WITH_PREFIX}!"),
    [STRINGID_CELEBRATEMESSAGE]                     = COMPOUND_STRING("¡Felicidades, {B_PLAYER_NAME}!"),
    [STRINGID_USEDINSTRUCTEDMOVE]                   = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} siguió las instrucciones de {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_THROATCHOPENDS]                       = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} ya puede volver a usar movimientos sonoros!"),
    [STRINGID_PKMNCANTUSEMOVETHROATCHOP]            = COMPOUND_STRING("¡El efecto de Golpe Mordaza impide que {B_ATK_NAME_WITH_PREFIX2} use ciertos movimientos!\p"),
    [STRINGID_LASERFOCUS]                           = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} agudiza la mente!"),
    [STRINGID_GEMACTIVATES]                         = COMPOUND_STRING("¡{B_LAST_ITEM} aumentó la potencia de {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_BERRYDMGREDUCES]                      = COMPOUND_STRING("¡{B_LAST_ITEM} de {B_SCR_NAME_WITH_PREFIX} redujo el daño recibido!"),
    [STRINGID_AIRBALLOONFLOAT]                      = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} está flotando con un globo!"),
    [STRINGID_AIRBALLOONPOP]                        = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s Air Balloon popped!"),
    [STRINGID_INCINERATEBURN]                       = COMPOUND_STRING("¡{B_LAST_ITEM} de {B_EFF_NAME_WITH_PREFIX} se ha quemado!"),
    [STRINGID_BUGBITE]                              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} stole and ate its target's {B_LAST_ITEM}!"),
    [STRINGID_ILLUSIONWOREOFF]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s illusion wore off!"),
    [STRINGID_ATTACKERCUREDTARGETSTATUS]            = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} cured {B_DEF_NAME_WITH_PREFIX2}'s problem!"),
    [STRINGID_ATTACKERLOSTFIRETYPE]                 = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} burned itself out!"),
    [STRINGID_HEALERCURE]                           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} was cured of {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_SCRIPTINGABILITYSTATRAISE]            = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_SCR_ABILITY} {B_BUFF2}raised its {B_BUFF1}!"),
    [STRINGID_RECEIVERABILITYTAKEOVER]              = COMPOUND_STRING("¡La {B_SCR_ABILITY} de {B_SCR_NAME_WITH_PREFIX} fue tomada!"),
    [STRINGID_PKNMABSORBINGPOWER]                   = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} está absorbiendo energía!"),
    [STRINGID_NOONEWILLBEABLETORUNAWAY]             = COMPOUND_STRING("¡Nadie podrá huir durante el próximo turno!"),
    [STRINGID_DESTINYKNOTACTIVATES]                 = COMPOUND_STRING("¡{B_DEF_NAME_WITH_PREFIX} se enamoró por el efecto de {B_LAST_ITEM}!"),
    [STRINGID_CLOAKEDINAFREEZINGLIGHT]              = COMPOUND_STRING("¡Una luz fría envuelve a {B_ATK_NAME_WITH_PREFIX}!"),
    [STRINGID_CLEARAMULETWONTLOWERSTATS]            = COMPOUND_STRING("¡{B_LAST_ITEM} de {B_SCR_NAME_WITH_PREFIX2} impide que bajen sus estadísticas!"),
    [STRINGID_FERVENTWISHREACHED]                   = COMPOUND_STRING("{B_ATK_TRAINER_NAME}'s fervent wish has reached {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_AIRLOCKACTIVATES]                     = COMPOUND_STRING("¡Las misteriosas turbulencias protegen a los Pokémon de tipo Volador!"),
    [STRINGID_PRESSUREENTERS]                       = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} ejerce presión!"),
    [STRINGID_DARKAURAENTERS]                       = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} irradia un aura oscura!"),
    [STRINGID_FAIRYAURAENTERS]                      = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} irradia un aura feérica!"),
    [STRINGID_AURABREAKENTERS]                      = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} ha invertido todas las auras!"),
    [STRINGID_COMATOSEENTERS]                       = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} está sumido en un profundo letargo!"),
    [STRINGID_SCREENCLEANERENTERS]                  = COMPOUND_STRING("¡Todas las pantallas se han disipado!"),
    [STRINGID_FETCHEDPOKEBALL]                      = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} ha encontrado {B_LAST_ITEM}!"),
    [STRINGID_ASANDSTORMKICKEDUP]                   = COMPOUND_STRING("¡Se ha desatado una tormenta de arena!"),
    [STRINGID_PKMNSWILLPERISHIN3TURNS]              = COMPOUND_STRING("¡Ambos Pokémon se debilitarán dentro de tres turnos!"),
    [STRINGID_AURAFLAREDTOLIFE]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s aura flared to life!"),
    [STRINGID_ASONEENTERS]                          = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} tiene dos habilidades!"),
    [STRINGID_CURIOUSMEDICINEENTERS]                = COMPOUND_STRING("¡Los cambios de estadísticas de {B_EFF_NAME_WITH_PREFIX} se han restablecido!"),
    [STRINGID_CANACTFASTERTHANKSTO]                 = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} puede actuar más rápido gracias a {B_BUFF1}!"),
    [STRINGID_MICLEBERRYACTIVATES]                  = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} mejoró la precisión de su próximo movimiento usando {B_LAST_ITEM}!"),
    [STRINGID_PKMNSHOOKOFFTHETAUNT]                 = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} se olvidó de la provocación!"),
    [STRINGID_PKMNGOTOVERITSINFATUATION]            = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} superó su enamoramiento!"),
    [STRINGID_ITEMCANNOTBEREMOVED]                  = COMPOUND_STRING("¡No se puede quitar el objeto de {B_ATK_NAME_WITH_PREFIX}!"),
    [STRINGID_STICKYBARBTRANSFER]                   = COMPOUND_STRING("¡{B_LAST_ITEM} se pegó a {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNBURNHEALED]                       = COMPOUND_STRING("La quemadura de {B_DEF_NAME_WITH_PREFIX} fue curada."),
    [STRINGID_REDCARDACTIVATE]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} held up its Red Card against {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_EJECTBUTTONACTIVATE]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} es cambiado con el {B_LAST_ITEM}."),
    [STRINGID_ATKGOTOVERINFATUATION]                = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} cured its infatuation status using its {B_LAST_ITEM}!"),
    [STRINGID_TORMENTEDNOMORE]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} is no longer tormented!"),
    [STRINGID_HEALBLOCKEDNOMORE]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} is no longer prevented from healing!"),
    [STRINGID_ATTACKERBECAMEFULLYCHARGED]           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} se cargó completamente gracias a su vínculo con su entrenador.\p"),
    [STRINGID_ATTACKERBECAMEASHSPECIES]             = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} se convirtió en Ash-Greninja.\p"),
    [STRINGID_EXTREMELYHARSHSUNLIGHT]               = COMPOUND_STRING("¡La luz del sol se volvió extremadamente intensa!"),
    [STRINGID_EXTREMESUNLIGHTFADED]                 = COMPOUND_STRING("La luz solar extrema se desvaneció."),
    [STRINGID_MOVEEVAPORATEDINTHEHARSHSUNLIGHT]     = COMPOUND_STRING("El ataque de tipo Agua se evaporó bajo la luz solar intensa."),
    [STRINGID_EXTREMELYHARSHSUNLIGHTWASNOTLESSENED] = COMPOUND_STRING("La luz solar extremadamente intensa no se debilitó en absoluto."),
    [STRINGID_HEAVYRAIN]                            = COMPOUND_STRING("¡Comenzó a caer una intensa lluvia!"),
    [STRINGID_HEAVYRAINLIFTED]                      = COMPOUND_STRING("¡La intensa lluvia ha cesado!"),
    [STRINGID_MOVEFIZZLEDOUTINTHEHEAVYRAIN]         = COMPOUND_STRING("¡El ataque de tipo Fuego se disipó en la fuerte lluvia!"),
    [STRINGID_NORELIEFROMHEAVYRAIN]                 = COMPOUND_STRING("¡No hay alivio de esta intensa lluvia!"),
    [STRINGID_MYSTERIOUSAIRCURRENT]                 = COMPOUND_STRING("¡Una corriente de aire misteriosa protege a los Pokémon de tipo Volador!"),
    [STRINGID_STRONGWINDSDISSIPATED]                = COMPOUND_STRING("¡Los fuertes vientos misteriosos se han disipado!"),
    [STRINGID_MYSTERIOUSAIRCURRENTBLOWSON]          = COMPOUND_STRING("¡La corriente de aire misteriosa sopla sin importar qué!"),
    [STRINGID_ATTACKWEAKENEDBSTRONGWINDS]           = COMPOUND_STRING("¡Los fuertes vientos misteriosos han debilitado el ataque!"),
    [STRINGID_STUFFCHEEKSCANTSELECT]                = COMPOUND_STRING("¡Mejillas llenas no se pueden seleccionar sin una Baya!\p"),
    [STRINGID_PKMNREVERTEDTOPRIMAL]                 = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s Primal Reversion! It reverted to its primal state!"),
    [STRINGID_BUTPOKEMONCANTUSETHEMOVE]             = COMPOUND_STRING("¡Pero {B_ATK_NAME_WITH_PREFIX2} no puede usar el movimiento!"),
    [STRINGID_BUTHOOPACANTUSEIT]                    = COMPOUND_STRING("¡Pero {B_ATK_NAME_WITH_PREFIX2} no puede usarlo en su estado actual!"),
    [STRINGID_BROKETHROUGHPROTECTION]               = COMPOUND_STRING("It broke through {B_EFF_NAME_WITH_PREFIX2}'s protection!"),
    [STRINGID_ABILITYALLOWSONLYMOVE]                = COMPOUND_STRING("{B_ATK_ABILITY} permite el uso solo de {B_CURRENT_MOVE}!\p"),
    [STRINGID_SWAPPEDABILITIES]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} intercambió habilidades con su objetivo."),
    [STRINGID_PKMNHEALEDPOISON]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} was cured of its poisoning!"),
    [STRINGID_BATTLERTYPECHANGEDTO]                 = COMPOUND_STRING("¡El tipo de {B_SCR_NAME_WITH_PREFIX} ha cambiado a {B_BUFF1}!"),
    [STRINGID_BOTHCANNOLONGERESCAPE]                = COMPOUND_STRING("¡Ningún Pokémon puede huir!"),
    [STRINGID_CANTESCAPEDUETOUSEDMOVE]              = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} ya no puede huir tras usar Bastión Final!"),
    [STRINGID_PKMNBECAMEWEAKERTOFIRE]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} se volvió más débil contra el fuego."),
    [STRINGID_ABOUTTOUSEPOLTERGEIST]                = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} is about to be attacked by its {B_LAST_ITEM}!"),
    [STRINGID_CANTESCAPEBECAUSEOFCURRENTMOVE]       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} can no longer escape because of Octolock!"),
    [STRINGID_NEUTRALIZINGGASENTERS]                = COMPOUND_STRING("Un Gas Neutralizante llenó la zona."),
    [STRINGID_NEUTRALIZINGGASOVER]                  = COMPOUND_STRING("Los efectos del Gas Neutralizante se disiparon."),
    [STRINGID_TARGETTOOHEAVY]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} is too heavy to be lifted!"),
    [STRINGID_PKMNTOOKTARGETHIGH]                   = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} llevó a {B_DEF_NAME_WITH_PREFIX2} al cielo!"),
    [STRINGID_PKMNINSNAPTRAP]                       = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} got trapped by a snap trap!"),
    [STRINGID_METEORBEAMCHARGING]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} está rebosante de energía espacial."),
    [STRINGID_HEATUPBEAK]                           = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} started heating up its beak!"),
    [STRINGID_COURTCHANGE]                          = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} ha intercambiado los efectos del campo!"),
    [STRINGID_ZPOWERSURROUNDS]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} se rodea de su Poder Z."),
    [STRINGID_ZMOVEUNLEASHED]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} desata su movimiento Z a toda potencia."),
    [STRINGID_ZMOVERESETSSTATS]                     = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} devuelve sus estadísticas a la normalidad con su Poder Z."),
    [STRINGID_ZMOVEALLSTATSUP]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} aumentó todas sus estadísticas usando su Poder Z."),
    [STRINGID_ZMOVEZBOOSTCRIT]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} aumentó su relación de golpes críticos usando su Poder Z."),
    [STRINGID_ZMOVERESTOREHP]                       = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} restauró sus PS usando su Poder Z."),
    [STRINGID_ZMOVESTATUP]                          = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} aumentó sus estadísticas usando su Poder Z."),
    [STRINGID_ZMOVEHPTRAP]                          = COMPOUND_STRING("¡La salud de {B_SCR_NAME_WITH_PREFIX} fue restaurada por el Poder Z!"),
    [STRINGID_ATTACKEREXPELLEDTHEPOISON]            = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} logró desprenderse del veneno."),
    [STRINGID_ATTACKERSHOOKITSELFAWAKE]             = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} se sacudió para despertarse."),
    [STRINGID_ATTACKERBROKETHROUGHPARALYSIS]        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} reunió toda su energía para superar su parálisis."),
    [STRINGID_ATTACKERHEALEDITSBURN]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} curó su quemadura con pura determinación."),
    [STRINGID_ATTACKERMELTEDTHEICE]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} derritió el hielo con su ardiente determinación."),
    [STRINGID_TARGETTOUGHEDITOUT]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} resistió para mostrarte su mejor lado."),
    [STRINGID_ATTACKERLOSTELECTRICTYPE]             = COMPOUND_STRING("¡{B_EFF_NAME_WITH_PREFIX} agotó toda su electricidad!"),
    [STRINGID_ATTACKERSWITCHEDSTATWITHTARGET]       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} intercambió {B_BUFF1} con su objetivo."),
    [STRINGID_BEINGHITCHARGEDPKMNWITHPOWER]         = COMPOUND_STRING("¡{B_CURRENT_MOVE} cargó de energía a {B_EFF_NAME_WITH_PREFIX2}!"),
    [STRINGID_SUNLIGHTACTIVATEDABILITY]             = COMPOUND_STRING("¡El sol intenso activó Paleosíntesis de {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_ORICHALCUMPULSEACTIVATES]             = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} intensificó el sol y su pulso ancestral!"),
    [STRINGID_ORICHALCUMPULSEACTIVATESINSUN]        = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} intensificó su pulso ancestral bajo el sol!"),
    [STRINGID_STATWASHEIGHTENED]                    = COMPOUND_STRING("¡{B_BUFF1} de {B_SCR_NAME_WITH_PREFIX} aumentó!"),
    [STRINGID_ELECTRICTERRAINACTIVATEDABILITY]      = COMPOUND_STRING("¡El campo eléctrico activó Carga Cuark de {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_HADRONENGINEACTIVATES]                = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} creó un campo eléctrico y cargó su motor futurista!"),
    [STRINGID_HADRONENGINEACTIVATESINTERRAIN]       = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} cargó su motor futurista con el campo eléctrico!"),
    [STRINGID_ABILITYWEAKENEDSURROUNDINGMONSSTAT]   = COMPOUND_STRING("¡{B_SCR_ABILITY} de {B_SCR_NAME_WITH_PREFIX} redujo {B_BUFF1} de los demás Pokémon!\p"),
    [STRINGID_ATTACKERGAINEDSTRENGTHFROMTHEFALLEN]  = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} ganó fuerza gracias a los caídos!"),
    [STRINGID_PKMNSABILITYPREVENTSABILITY]          = COMPOUND_STRING("¡La {B_SCR_ABILITY} de {B_SCR_NAME_WITH_PREFIX} impide que la {B_DEF_ABILITY} de {B_DEF_NAME_WITH_PREFIX2} funcione!"), //not in gen 5+, ability popup
    [STRINGID_PREPARESHELLTRAP]                     = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} set a shell trap!"),
    [STRINGID_SHELLTRAPDIDNTWORK]                   = COMPOUND_STRING("Trampa de concha de {B_ATK_NAME_WITH_PREFIX} no funcionó."),
    [STRINGID_SPIKESDISAPPEAREDFROMTEAM]            = COMPOUND_STRING("¡Las puás desaparecieron del suelo alrededor de {B_ATK_TEAM2} equipo!"),
    [STRINGID_TOXICSPIKESDISAPPEAREDFROMTEAM]       = COMPOUND_STRING("¡Las puás tóxicas desaparecieron del suelo alrededor de {B_ATK_TEAM2} equipo!"),
    [STRINGID_STICKYWEBDISAPPEAREDFROMTEAM]         = COMPOUND_STRING("¡La telaraña desapareció del suelo alrededor de {B_ATK_TEAM2} equipo!"),
    [STRINGID_STEALTHROCKDISAPPEAREDFROMTEAM]       = COMPOUND_STRING("¡Las piedras desaparecieron de alrededor {B_ATK_TEAM2} equipo!"),
    [STRINGID_COULDNTFULLYPROTECT]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} no pudo protegerse totalmente y resultó herido."),
    [STRINGID_STOCKPILEDEFFECTWOREOFF]              = COMPOUND_STRING("¡El efecto acumulado de {B_ATK_NAME_WITH_PREFIX} caducó!"),
    [STRINGID_PKMNREVIVEDREADYTOFIGHT]              = COMPOUND_STRING("{B_BUFF1} fue revivido y está listo para luchar de nuevo."),
    [STRINGID_ITEMRESTOREDSPECIESHEALTH]            = COMPOUND_STRING("{B_BUFF1} recuperó sus puntos de salud."),
    [STRINGID_ITEMCUREDSPECIESSTATUS]               = COMPOUND_STRING("{B_BUFF1} sanó de su estado alterado."), // Not in Gen 5+
    [STRINGID_ITEMRESTOREDSPECIESPP]                = COMPOUND_STRING("¡Se recuperaron los PP de {B_BUFF2} de {B_BUFF1}!"),
    [STRINGID_THUNDERCAGETRAPPED]                   = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} trapped {B_EFF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNHURTBYFROSTBITE]                  = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} se hirió por la congelación!"),
    [STRINGID_PKMNGOTFROSTBITE]                     = COMPOUND_STRING("¡{B_EFF_NAME_WITH_PREFIX} se congeló!"),
    [STRINGID_PKMNSITEMHEALEDFROSTBITE]             = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} se descongeló con {B_LAST_ITEM}!"),
    [STRINGID_ATTACKERHEALEDITSFROSTBITE]           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} curó su congelación con pura determinación."),
    [STRINGID_PKMNFROSTBITEHEALED]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s frostbite was cured!"),
    [STRINGID_PKMNFROSTBITEHEALEDBY]                = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s {B_CURRENT_MOVE} cured its frostbite!"),
    [STRINGID_MIRRORHERBCOPIED]                     = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} copió los cambios de estadísticas del rival con su Hierba Copia!"),
    [STRINGID_STARTEDSNOW]                          = COMPOUND_STRING("¡Ha empezado a nevar!"),
    [STRINGID_SNOWCONTINUES]                        = COMPOUND_STRING("Sigue nevando…"), //not in gen 5+ (lol)
    [STRINGID_SNOWSTOPPED]                          = COMPOUND_STRING("Ha dejado de nevar."),
    [STRINGID_SNOWWARNINGSNOW]                      = COMPOUND_STRING("¡Ha empezado a nevar!"),
    [STRINGID_PKMNITEMMELTED]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} corroded {B_DEF_NAME_WITH_PREFIX2}'s {B_LAST_ITEM}!"),
    [STRINGID_ULTRABURSTREACTING]                   = COMPOUND_STRING("Bright light is about to burst out of {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_ULTRABURSTCOMPLETED]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} recuperó su verdadero poder a través de Ultraexplosión."),
    [STRINGID_TEAMGAINEDEXP]                        = COMPOUND_STRING("¡El resto de tu equipo ganó EXP. ¡Puntos gracias a Repartir Exp.!\p"),
    [STRINGID_CURRENTMOVECANTSELECT]                = COMPOUND_STRING("{B_BUFF1} no puede ser usado.\p"),
    [STRINGID_TARGETISBEINGSALTCURED]               = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} is being salt cured!"),
    [STRINGID_TARGETISHURTBYSALTCURE]               = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} resulta herido por {B_BUFF1}."),
    [STRINGID_TARGETCOVEREDINSTICKYCANDYSYRUP]      = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} got covered in sticky candy syrup!"),
    [STRINGID_SHARPSTEELFLOATS]                     = COMPOUND_STRING("¡Afilado acero flota alrededor del equipo {B_DEF_TEAM2}!"),
    [STRINGID_SHARPSTEELDMG]                        = COMPOUND_STRING("¡El acero afilado hirió a {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNBLEWAWAYSHARPSTEEL]               = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} disipó el acero afilado."),
    [STRINGID_SHARPSTEELDISAPPEAREDFROMTEAM]        = COMPOUND_STRING("¡El acero afilado desapareció del suelo alrededor del equipo {B_ATK_TEAM2}!"),
    [STRINGID_TEAMTRAPPEDWITHVINES]                 = COMPOUND_STRING("¡Los Pokémon del equipo {B_EFF_TEAM1} quedaron atrapados entre lianas!"),
    [STRINGID_PKMNHURTBYVINES]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} resulta herido por el latigazo enredador de G-Max."),
    [STRINGID_TEAMCAUGHTINVORTEX]                   = COMPOUND_STRING("{B_EFF_TEAM1} Pokémon got caught in a vortex of water!"),
    [STRINGID_PKMNHURTBYVORTEX]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} resulta herido por el cañonazo de G-Max."),
    [STRINGID_TEAMSURROUNDEDBYFIRE]                 = COMPOUND_STRING("{B_EFF_TEAM1} Pokémon were surrounded by fire!"),
    [STRINGID_PKMNBURNINGUP]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} arde en las llamas de G-Max."),
    [STRINGID_TEAMSURROUNDEDBYROCKS]                = COMPOUND_STRING("{B_EFF_TEAM1} Pokémon became surrounded by rocks!"),
    [STRINGID_PKMNHURTBYROCKSTHROWN]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} resulta herido por las rocas lanzadas por G-Max."),
    [STRINGID_MOVEBLOCKEDBYDYNAMAX]                 = COMPOUND_STRING("El movimiento fue bloqueado por el poder de Dynamax."),
    [STRINGID_ZEROTOHEROTRANSFORMATION]             = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} underwent a heroic transformation!"),
    [STRINGID_THETWOMOVESBECOMEONE]                 = COMPOUND_STRING("¡Los dos movimientos se fusionan! ¡Es un movimiento combinado!{PAUSE 16}"),
    [STRINGID_ARAINBOWAPPEAREDONSIDE]               = COMPOUND_STRING("¡Un arcoíris apareció sobre el equipo {B_EFF_TEAM2}!"),
    [STRINGID_THERAINBOWDISAPPEARED]                = COMPOUND_STRING("El arco iris en el equipo {B_ATK_TEAM2} desapareció."),
    [STRINGID_WAITINGFORPARTNERSMOVE]               = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} está esperando el movimiento de {B_ATK_PARTNER_NAME}...{PAUSE 16}"),
    [STRINGID_SEAOFFIREENVELOPEDSIDE]               = COMPOUND_STRING("A sea of fire enveloped {B_EFF_TEAM2} side!"),
    [STRINGID_HURTBYTHESEAOFFIRE]                   = COMPOUND_STRING("¡El mar de fuego hirió a {B_ATK_NAME_WITH_PREFIX}!"),
    [STRINGID_THESEAOFFIREDISAPPEARED]              = COMPOUND_STRING("El mar de fuego alrededor del equipo {B_ATK_TEAM2} desapareció."),
    [STRINGID_SWAMPENVELOPEDSIDE]                   = COMPOUND_STRING("A swamp enveloped {B_EFF_TEAM2} side!"),
    [STRINGID_THESWAMPDISAPPEARED]                  = COMPOUND_STRING("El pantano alrededor del equipo {B_ATK_TEAM2} desapareció."),
    [STRINGID_PKMNTELLCHILLINGRECEPTIONJOKE]        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} se prepara para contar un chiste escalofriantemente malo."),
    [STRINGID_HOSPITALITYRESTORATION]               = COMPOUND_STRING("¡{B_EFF_NAME_WITH_PREFIX} bebió todo el té que preparó {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_ELECTROSHOTCHARGING]                  = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} absorbió la electricidad!"),
    [STRINGID_ITEMWASUSEDUP]                        = COMPOUND_STRING("{B_LAST_ITEM} ya no quedan..."),
    [STRINGID_ATTACKERLOSTITSTYPE]                  = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} lost its {B_BUFF1} type!"),
    [STRINGID_SHEDITSTAIL]                          = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} se deshizo de su cola para crear un señuelo!"),
    [STRINGID_CLOAKEDINAHARSHLIGHT]                 = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} se envolvió en una luz cegadora!"),
    [STRINGID_SUPERSWEETAROMAWAFTS]                 = COMPOUND_STRING("¡El jarabe de {B_EFF_NAME_WITH_PREFIX2} desprende un aroma muy dulce!"),
    [STRINGID_DIMENSIONSWERETWISTED]                = COMPOUND_STRING("Se han alterado las dimensiones!"),
    [STRINGID_BIZARREARENACREATED]                  = COMPOUND_STRING("¡Se ha creado una zona extraña! ¡Los objetos equipados perdieron sus efectos!"),
    [STRINGID_BIZARREAREACREATED]                   = COMPOUND_STRING("¡Se ha creado una zona extraña en la que la defensa y defensa especial se intercambian!"),
    [STRINGID_TIDYINGUPCOMPLETE]                    = COMPOUND_STRING("¡Limpieza completada!"),
    [STRINGID_PKMNTERASTALLIZEDINTO]                = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} se teracristalizó  en el tipo {B_BUFF1}!"), // Does not exist, meant to mimic form change strings
    [STRINGID_BOOSTERENERGYACTIVATES]               = COMPOUND_STRING("¡{B_SCR_NAME_WITH_PREFIX} usó su {B_LAST_ITEM} para activar {B_SCR_ABILITY}!"),
    [STRINGID_FOGCREPTUP]                           = COMPOUND_STRING("¡Una niebla tan espesa como la sopa apareció!"),
    [STRINGID_FOGISDEEP]                            = COMPOUND_STRING("La niebla es densa…"),
    [STRINGID_FOGLIFTED]                            = COMPOUND_STRING("La niebla se disipó."),
    [STRINGID_PKMNMADESHELLGLEAM]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} hizo brillar su caparazón! ¡Está distorsionando las compatibilidades de tipos!"),
    [STRINGID_FICKLEBEAMDOUBLED]                    = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} va con todo con este ataque!"),
    [STRINGID_COMMANDERACTIVATES]                   = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} was swallowed by {B_BUFF1} and became {B_BUFF1}'s commander!"),
    [STRINGID_POKEFLUTECATCHY]                      = COMPOUND_STRING("¡{B_PLAYER_NAME} tocó la {B_LAST_ITEM}.\p¡Esa es una melodía pegadiza!"),
    [STRINGID_POKEFLUTE]                            = COMPOUND_STRING("¡{B_PLAYER_NAME} tocó la {B_LAST_ITEM}."),
    [STRINGID_MONHEARINGFLUTEAWOKE]                 = COMPOUND_STRING("¡El Pokémon que escuchó la flauta despertó!"),
    [STRINGID_SUNLIGHTISHARSH]                      = COMPOUND_STRING("¡La luz del sol es intensa!"),
    [STRINGID_ITISHAILING]                          = COMPOUND_STRING("¡Está granizando!"),
    [STRINGID_ITISSNOWING]                          = COMPOUND_STRING("¡Está nevando!"),
    [STRINGID_ISCOVEREDWITHGRASS]                   = COMPOUND_STRING("¡El campo de batalla está cubierto de hierba!"),
    [STRINGID_MISTSWIRLSAROUND]                     = COMPOUND_STRING("¡Una niebla gira alrededor del campo de batalla!"),
    [STRINGID_ELECTRICCURRENTISRUNNING]             = COMPOUND_STRING("¡Una corriente eléctrica recorre el campo de batalla!"),
    [STRINGID_SEEMSWEIRD]                           = COMPOUND_STRING("¡El campo de batalla parece extraño!"),
    [STRINGID_WAGGLINGAFINGER]                      = COMPOUND_STRING("¡Moviendo un dedo usó {B_CURRENT_MOVE}!"),
    [STRINGID_BLOCKEDBYSLEEPCLAUSE]                 = COMPOUND_STRING("Sleep Clause kept {B_DEF_NAME_WITH_PREFIX2} awake!"),
    [STRINGID_SUPEREFFECTIVETWOFOES]                = COMPOUND_STRING("It's super effective on {B_DEF_NAME_WITH_PREFIX2} and {B_DEF_PARTNER_NAME}!"),
    [STRINGID_NOTVERYEFFECTIVETWOFOES]              = COMPOUND_STRING("It's not very effective on {B_DEF_NAME_WITH_PREFIX2} and {B_DEF_PARTNER_NAME}."),
    [STRINGID_ITDOESNTAFFECTTWOFOES]                = COMPOUND_STRING("It doesn't affect {B_DEF_NAME_WITH_PREFIX2} and {B_DEF_PARTNER_NAME}…"),
    [STRINGID_SENDCAUGHTMONPARTYORBOX]              = COMPOUND_STRING("¿Quieres añadir a {B_DEF_NAME} al equipo?"),
    [STRINGID_PKMNSENTTOPCAFTERCATCH]               = gText_PkmnSentToPCAfterCatch,
    [STRINGID_PKMNDYNAMAXED]                        = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} creció enormemente adoptando su forma Dinamax!"),
    [STRINGID_PKMNGIGANTAMAXED]                     = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} creció enormemente adoptando su forma Gigamax!"),
    [STRINGID_TIMETODYNAMAX]                        = COMPOUND_STRING("¡Es hora de Dinamaxizar!"),
    [STRINGID_TIMETOGIGANTAMAX]                     = COMPOUND_STRING("¡Es hora de Gigamaxizar!"),
    [STRINGID_QUESTIONFORFEITBATTLE]                = COMPOUND_STRING("¿Quieres rendirte y abandonar el combate ahora? Abandonar el combate cuenta como una derrota."),
    [STRINGID_POWERCONSTRUCTPRESENCEOFMANY]         = COMPOUND_STRING("¡Sientes la presencia de muchos!"),
    [STRINGID_POWERCONSTRUCTTRANSFORM]              = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} se transformó en su Forma Completa!"),
    [STRINGID_ABILITYSHIELDPROTECTS]                = COMPOUND_STRING("¡La habilidad de {B_ATK_NAME_WITH_PREFIX} está protegida por los efectos de su {B_LAST_ITEM}!"),
    [STRINGID_MONTOOSCAREDTOMOVE]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} is too scared to move!"),
    [STRINGID_GHOSTGETOUTGETOUT]                    = COMPOUND_STRING("GHOST: Get out…… Get out……"),
    [STRINGID_SILPHSCOPEUNVEILED]                   = COMPOUND_STRING("¡El SCOPE SILPH reveló la\nidentidad del FANTASMA!"),
    [STRINGID_GHOSTWASMAROWAK]                      = COMPOUND_STRING("¡El FANTASMA era MAROWAK!\p"),
    [STRINGID_TRAINER1MON1COMEBACK]                 = COMPOUND_STRING("{B_TRAINER1_NAME}: {B_OPPONENT_MON1_NAME}, come back!"),
    [STRINGID_THREWROCK]                            = COMPOUND_STRING("¡{B_PLAYER_NAME} lanzó una PIEDRA\na {B_OPPONENT_MON1_NAME}!"),
    [STRINGID_THREWBAIT]                            = COMPOUND_STRING("¡{B_PLAYER_NAME} lanzó CEBO\na {B_OPPONENT_MON1_NAME}!"),
    [STRINGID_PKMNANGRY]                            = COMPOUND_STRING("{B_OPPONENT_MON1_NAME} is angry!"),
    [STRINGID_PKMNEATING]                           = COMPOUND_STRING("{B_OPPONENT_MON1_NAME} is eating!"),
    [STRINGID_PKMNDISGUISEWASBUSTED]                = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s disguise was busted!"),
    [STRINGID_ZENMODETRIGGERED]                     = COMPOUND_STRING("{B_SCR_ABILITY} triggered!"),
    [STRINGID_ZENMODEENDED]                         = COMPOUND_STRING("{B_SCR_ABILITY} ended!"),
    [STRINGID_SCRCUREDPARALYSIS]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} was cured of paralysis!"),
    [STRINGID_SCRCUREDPOISON]                       = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} was cured of its poisoning!"),
    [STRINGID_SCRCUREDBURN]                         = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX}'s burn was cured!"),
    [STRINGID_SCRCUREDSLEEP]                        = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} woke up!"),
    [STRINGID_SCRCUREDCONFUSION]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} snapped out of its confusion!"),
    [STRINGID_PARTYCUREDPARALYSIS]                  = COMPOUND_STRING("{B_BUFF1} was cured of paralysis!"),
    [STRINGID_PARTYCUREDPOISON]                     = COMPOUND_STRING("{B_BUFF1} was cured of its poisoning!"),
    [STRINGID_PARTYCUREDBURN]                       = COMPOUND_STRING("{B_BUFF1}'s burn was cured!"),
    [STRINGID_PARTYCUREDSLEEP]                      = COMPOUND_STRING("{B_BUFF1} woke up!"),
    [STRINGID_PARTYCUREDFREEZE]                     = COMPOUND_STRING("{B_BUFF1} thawed out!"),
    [STRINGID_PARTYCUREDFROSTBITE]                  = COMPOUND_STRING("{B_BUFF1}'s frostbite was cured!"),
    [STRINGID_PKMNATKNOTLOWERED]                    = COMPOUND_STRING("¡El Ataque de {B_SCR_NAME_WITH_PREFIX} no bajó!"),
    [STRINGID_VICTORYCATCH]                         = COMPOUND_STRING("{B_DEF_NAME} is weak!\nThrow a Poké Ball now!"),
    [STRINGID_CANTUSEMOVE]                          = COMPOUND_STRING("¡No se puede usar este movimiento!\p"),
    [STRINGID_REFLECTWOREOFF]                       = COMPOUND_STRING("{B_DEF_TEAM1} side's Reflect wore off!"),
    [STRINGID_LIGHTSCREENWOREOFF]                   = COMPOUND_STRING("{B_DEF_TEAM1} side's Light Screen wore off!"),
    [STRINGID_AURORAVEILWOREOFF]                    = COMPOUND_STRING("{B_DEF_TEAM1} side's Aurora Veil wore off!"),
    [STRINGID_MOSTLYINEFFECTIVE]                    = COMPOUND_STRING("It's mostly ineffective…"),
    [STRINGID_EXTREMELYEFFECTIVE]                   = COMPOUND_STRING("It's extremely effective!"),
    [STRINGID_NOTVERYEFFECTIVEONDEF]                = COMPOUND_STRING("It's not very effective on {B_DEF_NAME_WITH_PREFIX2}."),
    [STRINGID_SUPEREFFECTIVEONDEF]                  = COMPOUND_STRING("It's super effective on {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_MOSTLYINEFFECTIVEONDEF]               = COMPOUND_STRING("It's mostly ineffective on {B_DEF_NAME_WITH_PREFIX2}."),
    [STRINGID_EXTREMELYEFFECTIVEONDEF]              = COMPOUND_STRING("It's extremely effective on {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_EXTREMELYEFFECTIVETWOFOES]            = COMPOUND_STRING("It's extremely effective on {B_DEF_NAME_WITH_PREFIX2} and {B_DEF_PARTNER_NAME}!"),
    [STRINGID_MOSTLYINEFFECTIVETWOFOES]             = COMPOUND_STRING("It's mostly ineffective on {B_DEF_NAME_WITH_PREFIX2} and {B_DEF_PARTNER_NAME}."),
    [STRINGID_CRITICALHITONDEF]                     = COMPOUND_STRING("A critical hit on {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_S]                                    = COMPOUND_STRING("s"),
    [STRINGID_LOSTSOMEOFITSHP]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} lost some of its HP!"),
    [STRINGID_BELCHCANTUSE]                         = COMPOUND_STRING("¡{B_ATK_NAME_WITH_PREFIX} no ha comido ninguna baya equipada y no puede eructar!\p"),
};

const u16 gTrainerUsedItemStringIds[] =
{
    STRINGID_PLAYERUSEDITEM, STRINGID_TRAINER1USEDITEM
};

const u16 gZEffectStringIds[] =
{
    [B_MSG_Z_RESET_STATS] = STRINGID_ZMOVERESETSSTATS,
    [B_MSG_Z_ALL_STATS_UP]= STRINGID_ZMOVEALLSTATSUP,
    [B_MSG_Z_BOOST_CRITS] = STRINGID_ZMOVEZBOOSTCRIT,
    [B_MSG_Z_FOLLOW_ME]   = STRINGID_PKMNCENTERATTENTION,
    [B_MSG_Z_RECOVER_HP]  = STRINGID_ZMOVERESTOREHP,
    [B_MSG_Z_STAT_UP]     = STRINGID_ZMOVESTATUP,
    [B_MSG_Z_HP_TRAP]     = STRINGID_ZMOVEHPTRAP,
};

const u16 gMentalHerbCureStringIds[] =
{
    [B_MSG_MENTALHERBCURE_INFATUATION] = STRINGID_ATKGOTOVERINFATUATION,
    [B_MSG_MENTALHERBCURE_TORMENT]     = STRINGID_TORMENTEDNOMORE,
    [B_MSG_MENTALHERBCURE_DISABLE]     = STRINGID_PKMNMOVEDISABLEDNOMORE,
    [B_MSG_MENTALHERBCURE_HEALBLOCK]   = STRINGID_HEALBLOCKEDNOMORE,
    [B_MSG_MENTALHERBCURE_ENCORE]      = STRINGID_PKMNENCOREENDED,
    [B_MSG_MENTALHERBCURE_TAUNT]       = STRINGID_PKMNSHOOKOFFTHETAUNT,
};

const u16 gStartingStatusStringIds[B_MSG_STARTING_STATUS_COUNT] =
{
    [B_MSG_TERRAIN_SET_MISTY]    = STRINGID_TERRAINBECOMESMISTY,
    [B_MSG_TERRAIN_SET_ELECTRIC] = STRINGID_TERRAINBECOMESELECTRIC,
    [B_MSG_TERRAIN_SET_PSYCHIC]  = STRINGID_TERRAINBECOMESPSYCHIC,
    [B_MSG_TERRAIN_SET_GRASSY]   = STRINGID_TERRAINBECOMESGRASSY,
    [B_MSG_SET_TRICK_ROOM]       = STRINGID_DIMENSIONSWERETWISTED,
    [B_MSG_SET_MAGIC_ROOM]       = STRINGID_BIZARREARENACREATED,
    [B_MSG_SET_WONDER_ROOM]      = STRINGID_BIZARREAREACREATED,
    [B_MSG_SET_TAILWIND]         = STRINGID_TAILWINDBLEW,
    [B_MSG_SET_RAINBOW]          = STRINGID_ARAINBOWAPPEAREDONSIDE,
    [B_MSG_SET_SEA_OF_FIRE]      = STRINGID_SEAOFFIREENVELOPEDSIDE,
    [B_MSG_SET_SWAMP]            = STRINGID_SWAMPENVELOPEDSIDE,
    [B_MSG_SET_SPIKES]           = STRINGID_SPIKESSCATTERED,
    [B_MSG_SET_POISON_SPIKES]    = STRINGID_POISONSPIKESSCATTERED,
    [B_MSG_SET_STICKY_WEB]       = STRINGID_STICKYWEBUSED,
    [B_MSG_SET_STEALTH_ROCK]     = STRINGID_POINTEDSTONESFLOAT,
    [B_MSG_SET_SHARP_STEEL]      = STRINGID_SHARPSTEELFLOATS,
};

const u16 gTerrainStringIds[B_MSG_TERRAIN_COUNT] =
{
    [B_MSG_TERRAIN_SET_MISTY] = STRINGID_TERRAINBECOMESMISTY,
    [B_MSG_TERRAIN_SET_ELECTRIC] = STRINGID_TERRAINBECOMESELECTRIC,
    [B_MSG_TERRAIN_SET_PSYCHIC] = STRINGID_TERRAINBECOMESPSYCHIC,
    [B_MSG_TERRAIN_SET_GRASSY] = STRINGID_TERRAINBECOMESGRASSY,
    [B_MSG_TERRAIN_END_MISTY] = STRINGID_MISTYTERRAINENDS,
    [B_MSG_TERRAIN_END_ELECTRIC] = STRINGID_ELECTRICTERRAINENDS,
    [B_MSG_TERRAIN_END_PSYCHIC] = STRINGID_PSYCHICTERRAINENDS,
    [B_MSG_TERRAIN_END_GRASSY] = STRINGID_GRASSYTERRAINENDS,
};

const u16 gTerrainPreventsStringIds[] =
{
    [B_MSG_TERRAINPREVENTS_MISTY]    = STRINGID_MISTYTERRAINPREVENTS,
    [B_MSG_TERRAINPREVENTS_ELECTRIC] = STRINGID_ELECTRICTERRAINPREVENTS,
    [B_MSG_TERRAINPREVENTS_PSYCHIC]  = STRINGID_PSYCHICTERRAINPREVENTS
};

const u16 gHealingWishStringIds[] =
{
    STRINGID_HEALINGWISHCAMETRUE,
    STRINGID_LUNARDANCECAMETRUE
};

const u16 gDmgHazardsStringIds[] =
{
    [B_MSG_PKMNHURTBYSPIKES]   = STRINGID_PKMNHURTBYSPIKES,
    [B_MSG_STEALTHROCKDMG]     = STRINGID_STEALTHROCKDMG,
    [B_MSG_SHARPSTEELDMG]      = STRINGID_SHARPSTEELDMG,
    [B_MSG_POINTEDSTONESFLOAT] = STRINGID_POINTEDSTONESFLOAT,
    [B_MSG_SPIKESSCATTERED]    = STRINGID_SPIKESSCATTERED,
    [B_MSG_SHARPSTEELFLOATS]   = STRINGID_SHARPSTEELFLOATS,
};

const u16 gSwitchInAbilityStringIds[] =
{
    [B_MSG_SWITCHIN_MOLDBREAKER] = STRINGID_MOLDBREAKERENTERS,
    [B_MSG_SWITCHIN_TERAVOLT] = STRINGID_TERAVOLTENTERS,
    [B_MSG_SWITCHIN_TURBOBLAZE] = STRINGID_TURBOBLAZEENTERS,
    [B_MSG_SWITCHIN_SLOWSTART] = STRINGID_SLOWSTARTENTERS,
    [B_MSG_SWITCHIN_UNNERVE] = STRINGID_UNNERVEENTERS,
    [B_MSG_SWITCHIN_ANTICIPATION] = STRINGID_ANTICIPATIONACTIVATES,
    [B_MSG_SWITCHIN_FOREWARN] = STRINGID_FOREWARNACTIVATES,
    [B_MSG_SWITCHIN_PRESSURE] = STRINGID_PRESSUREENTERS,
    [B_MSG_SWITCHIN_DARKAURA] = STRINGID_DARKAURAENTERS,
    [B_MSG_SWITCHIN_FAIRYAURA] = STRINGID_FAIRYAURAENTERS,
    [B_MSG_SWITCHIN_AURABREAK] = STRINGID_AURABREAKENTERS,
    [B_MSG_SWITCHIN_COMATOSE] = STRINGID_COMATOSEENTERS,
    [B_MSG_SWITCHIN_SCREENCLEANER] = STRINGID_SCREENCLEANERENTERS,
    [B_MSG_SWITCHIN_ASONE] = STRINGID_ASONEENTERS,
    [B_MSG_SWITCHIN_CURIOUS_MEDICINE] = STRINGID_CURIOUSMEDICINEENTERS,
    [B_MSG_SWITCHIN_PASTEL_VEIL] = STRINGID_PKMNHEALEDPOISON,
    [B_MSG_SWITCHIN_NEUTRALIZING_GAS] = STRINGID_NEUTRALIZINGGASENTERS,
};

const u16 gNoEscapeStringIds[] =
{
    [B_MSG_CANT_ESCAPE]          = STRINGID_CANTESCAPE,
    [B_MSG_DONT_LEAVE_BIRCH]     = STRINGID_DONTLEAVEBIRCH,
    [B_MSG_PREVENTS_ESCAPE]      = STRINGID_PREVENTSESCAPE,
    [B_MSG_CANT_ESCAPE_2]        = STRINGID_CANTESCAPE2,
    [B_MSG_ATTACKER_CANT_ESCAPE] = STRINGID_ATTACKERCANTESCAPE
};

const u16 gMoveWeatherChangeStringIds[] =
{
    [B_MSG_STARTED_RAIN]      = STRINGID_STARTEDTORAIN,
    [B_MSG_STARTED_DOWNPOUR]  = STRINGID_DOWNPOURSTARTED, // Unused
    [B_MSG_WEATHER_FAILED]    = STRINGID_BUTITFAILED,
    [B_MSG_STARTED_SANDSTORM] = STRINGID_SANDSTORMBREWED,
    [B_MSG_STARTED_SUNLIGHT]  = STRINGID_SUNLIGHTGOTBRIGHT,
    [B_MSG_STARTED_HAIL]      = STRINGID_STARTEDHAIL,
    [B_MSG_STARTED_SNOW]      = STRINGID_STARTEDSNOW,
    [B_MSG_STARTED_FOG]       = STRINGID_FOGCREPTUP, // Unused, can use for custom moves that set fog
};

const u16 gAbilityWeatherChangeStringId[] =
{
    [B_MSG_STARTED_DRIZZLE]        = STRINGID_STARTEDTORAIN,
    [B_MSG_STARTED_SAND_STREAM]    = STRINGID_SANDSTORMBREWED,
    [B_MSG_STARTED_DROUGHT]        = STRINGID_SUNLIGHTGOTBRIGHT,
    [B_MSG_STARTED_HAIL_WARNING]   = STRINGID_STARTEDHAIL,
    [B_MSG_STARTED_SNOW_WARNING]   = STRINGID_STARTEDSNOW,
    [B_MSG_STARTED_DESOLATE_LAND]  = STRINGID_EXTREMELYHARSHSUNLIGHT,
    [B_MSG_STARTED_PRIMORDIAL_SEA] = STRINGID_HEAVYRAIN,
    [B_MSG_STARTED_STRONG_WINDS]   = STRINGID_MYSTERIOUSAIRCURRENT,
};

const u16 gWeatherEndsStringIds[B_MSG_WEATHER_END_COUNT] =
{
    [B_MSG_WEATHER_END_RAIN]                       = STRINGID_RAINSTOPPED,
    [B_MSG_WEATHER_END_SUN]                        = STRINGID_SUNLIGHTFADED,
    [B_MSG_WEATHER_END_SANDSTORM]                  = STRINGID_SANDSTORMSUBSIDED,
    [B_MSG_WEATHER_END_HAIL]                       = STRINGID_HAILSTOPPED,
    [B_MSG_WEATHER_END_SNOW]                       = STRINGID_SNOWSTOPPED,
    [B_MSG_WEATHER_END_FOG]                        = STRINGID_FOGLIFTED,
    [B_MSG_WEATHER_END_EXTREMELY_HARSH_SUNLIGHT]   = STRINGID_EXTREMESUNLIGHTFADED,
    [B_MSG_WEATHER_END_HEAVY_RAIN]                 = STRINGID_HEAVYRAINLIFTED,
    [B_MSG_WEATHER_END_STRONG_WINDS]               = STRINGID_STRONGWINDSDISSIPATED,
};

const u16 gWeatherTurnStringIds[] =
{
    [B_MSG_WEATHER_TURN_RAIN]         = STRINGID_RAINCONTINUES,
    [B_MSG_WEATHER_TURN_DOWNPOUR]     = STRINGID_DOWNPOURCONTINUES,
    [B_MSG_WEATHER_TURN_SUN]          = STRINGID_SUNLIGHTSTRONG,
    [B_MSG_WEATHER_TURN_SANDSTORM]    = STRINGID_SANDSTORMRAGES,
    [B_MSG_WEATHER_TURN_HAIL]         = STRINGID_HAILCONTINUES,
    [B_MSG_WEATHER_TURN_SNOW]         = STRINGID_SNOWCONTINUES,
    [B_MSG_WEATHER_TURN_FOG]          = STRINGID_FOGISDEEP,
    [B_MSG_WEATHER_TURN_STRONG_WINDS] = STRINGID_MYSTERIOUSAIRCURRENTBLOWSON,
};

const u16 gSandStormHailDmgStringIds[] =
{
    [B_MSG_SANDSTORM] = STRINGID_PKMNBUFFETEDBYSANDSTORM,
    [B_MSG_HAIL]      = STRINGID_PKMNPELTEDBYHAIL
};

const u16 gProtectLikeUsedStringIds[] =
{
    [B_MSG_PROTECTED_ITSELF] = STRINGID_PKMNPROTECTEDITSELF2,
    [B_MSG_BRACED_ITSELF]    = STRINGID_PKMNBRACEDITSELF,
    [B_MSG_PROTECTED_TEAM]   = STRINGID_PROTECTEDTEAM,
};

const u16 gBrokeProtectionStringIds[] =
{
    [B_MSG_FEINT]                 = STRINGID_FELLFORFEINT,
    [B_MSG_BROKE_THROUGH_PROTECT] = STRINGID_BROKETHROUGHPROTECTION,
};

const u16 gReflectLightScreenSafeguardStringIds[] =
{
    [B_MSG_SIDE_STATUS_FAILED]     = STRINGID_BUTITFAILED,
    [B_MSG_SET_REFLECT_SINGLE]     = STRINGID_PKMNRAISEDDEF,
    [B_MSG_SET_REFLECT_DOUBLE]     = STRINGID_PKMNRAISEDDEF,
    [B_MSG_SET_LIGHTSCREEN_SINGLE] = STRINGID_PKMNRAISEDSPDEF,
    [B_MSG_SET_LIGHTSCREEN_DOUBLE] = STRINGID_PKMNRAISEDSPDEF,
    [B_MSG_SET_SAFEGUARD]          = STRINGID_PKMNCOVEREDBYVEIL,
    [B_MSG_SET_AURORA_VEIL]        = STRINGID_PKMNAURORAVEIL,
};

const u16 gLeechSeedStringIds[] =
{
    [B_MSG_LEECH_SEED_SET]   = STRINGID_PKMNSEEDED,
    [B_MSG_LEECH_SEED_MISS]  = STRINGID_PKMNAVOIDEDATTACK,
    [B_MSG_LEECH_SEED_FAIL]  = STRINGID_ITDOESNTAFFECT,
    [B_MSG_LEECH_SEED_DRAIN] = STRINGID_PKMNSAPPEDBYLEECHSEED,
    [B_MSG_LEECH_SEED_OOZE]  = STRINGID_ITSUCKEDLIQUIDOOZE,
};

const u16 gRestUsedStringIds[] =
{
    [B_MSG_REST]          = STRINGID_PKMNWENTTOSLEEP,
    [B_MSG_REST_STATUSED] = STRINGID_PKMNSLEPTHEALTHY
};

const u16 gUproarOverTurnStringIds[] =
{
    [B_MSG_UPROAR_CONTINUES] = STRINGID_PKMNMAKINGUPROAR,
    [B_MSG_UPROAR_ENDS]      = STRINGID_PKMNCALMEDDOWN
};

const u16 gWokeUpStringIds[] =
{
    [B_MSG_WOKE_UP]        = STRINGID_PKMNWOKEUP,
    [B_MSG_WOKE_UP_UPROAR] = STRINGID_PKMNWOKEUPINUPROAR
};

const u16 gUproarAwakeStringIds[] =
{
    [B_MSG_CANT_SLEEP_UPROAR]  = STRINGID_PKMNCANTSLEEPINUPROAR2,
    [B_MSG_UPROAR_KEPT_AWAKE]  = STRINGID_UPROARKEPTPKMNAWAKE,
};

const u16 gStatUpStringIds[] =
{
    [B_MSG_STAT_CHANGED]            = STRINGID_STATROSE,
    [B_MSG_STAT_WONT_CHANGE]        = STRINGID_STATSWONTINCREASE,
    [B_MSG_STAT_MAXED]              = STRINGID_STATWASMAXEDOUT,
    [B_MSG_STAT_CHANGE_EMPTY]       = STRINGID_EMPTYSTRING3,
    [B_MSG_STAT_CHANGED_ITEM]       = STRINGID_USINGITEMSTATOFPKMNROSE,
    [B_MSG_STAT_CHANGED_BELLY_DRUM] = STRINGID_PKMNCUTHPMAXEDATTACK,
    [B_MSG_USED_DIRE_HIT]           = STRINGID_PKMNUSEDXTOGETPUMPED,
};

// Mostly redundant, combine with above in a future pr
const u16 gStatDownStringIds[] =
{
    [B_MSG_STAT_CHANGED]            = STRINGID_STATFELL,
    [B_MSG_STAT_WONT_CHANGE]        = STRINGID_STATSWONTDECREASE,
    [B_MSG_STAT_CHANGE_EMPTY]       = STRINGID_EMPTYSTRING3,
    [B_MSG_STAT_CHANGED_ITEM]       = STRINGID_USINGITEMSTATOFPKMNFELL,
    [B_MSG_STAT_CHANGED_BELLY_DRUM] = STRINGID_PKMNCUTHPMAXEDATTACK, // Message for contrary is still printed
};

// Index copied from move's index in sTrappingMoves
const u16 gWrappedStringIds[NUM_TRAPPING_MOVES] =
{
    [B_MSG_WRAPPED_BIND]        = STRINGID_PKMNSQUEEZEDBYBIND,     // MOVE_BIND
    [B_MSG_WRAPPED_WRAP]        = STRINGID_PKMNWRAPPEDBY,          // MOVE_WRAP
    [B_MSG_WRAPPED_FIRE_SPIN]   = STRINGID_PKMNTRAPPEDINVORTEX,    // MOVE_FIRE_SPIN
    [B_MSG_WRAPPED_CLAMP]       = STRINGID_PKMNCLAMPED,            // MOVE_CLAMP
    [B_MSG_WRAPPED_WHIRLPOOL]   = STRINGID_PKMNTRAPPEDINVORTEX,    // MOVE_WHIRLPOOL
    [B_MSG_WRAPPED_SAND_TOMB]   = STRINGID_PKMNTRAPPEDBYSANDTOMB,  // MOVE_SAND_TOMB
    [B_MSG_WRAPPED_MAGMA_STORM] = STRINGID_TRAPPEDBYSWIRLINGMAGMA, // MOVE_MAGMA_STORM
    [B_MSG_WRAPPED_INFESTATION] = STRINGID_INFESTATION,            // MOVE_INFESTATION
    [B_MSG_WRAPPED_SNAP_TRAP]   = STRINGID_PKMNINSNAPTRAP,         // MOVE_SNAP_TRAP
    [B_MSG_WRAPPED_THUNDER_CAGE]= STRINGID_THUNDERCAGETRAPPED,     // MOVE_THUNDER_CAGE
};

const u16 gMistUsedStringIds[] =
{
    [B_MSG_SET_MIST]    = STRINGID_PKMNSHROUDEDINMIST,
    [B_MSG_MIST_FAILED] = STRINGID_BUTITFAILED
};

const u16 gFocusEnergyUsedStringIds[] =
{
    [B_MSG_GETTING_PUMPED]      = STRINGID_PKMNGETTINGPUMPED,
    [B_MSG_FOCUS_ENERGY_FAILED] = STRINGID_BUTITFAILED
};

const u16 gTransformUsedStringIds[] =
{
    [B_MSG_TRANSFORMED]      = STRINGID_PKMNTRANSFORMEDINTO,
    [B_MSG_TRANSFORM_FAILED] = STRINGID_BUTITFAILED
};

const u16 gSubstituteUsedStringIds[] =
{
    [B_MSG_SET_SUBSTITUTE]    = STRINGID_PKMNMADESUBSTITUTE,
    [B_MSG_SUBSTITUTE_FAILED] = STRINGID_TOOWEAKFORSUBSTITUTE
};

const u16 gGotPoisonedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASPOISONED,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNPOISONEDBY
};

const u16 gGotParalyzedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASPARALYZED,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNWASPARALYZEDBY
};

const u16 gFellAsleepStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNFELLASLEEP,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNMADESLEEP,
};

const u16 gGotBurnedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASBURNED,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNBURNEDBY
};

const u16 gGotFrostbiteStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNGOTFROSTBITE,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNGOTFROSTBITE,
};

const u16 gFrostbiteHealedStringIds[] =
{
    [B_MSG_FROSTBITE_HEALED]         = STRINGID_PKMNFROSTBITEHEALED,
    [B_MSG_FROSTBITE_HEALED_BY_MOVE] = STRINGID_PKMNFROSTBITEHEALEDBY
};

const u16 gGotFrozenStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASFROZEN,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNFROZENBY
};

const u16 gGotDefrostedStringIds[] =
{
    [B_MSG_DEFROSTED]         = STRINGID_PKMNWASDEFROSTED,
    [B_MSG_DEFROSTED_BY_MOVE] = STRINGID_PKMNWASDEFROSTEDBY
};

const u16 gKOFailedStringIds[] =
{
    [B_MSG_KO_MISS]       = STRINGID_PKMNAVOIDEDATTACK,
    [B_MSG_KO_UNAFFECTED] = STRINGID_PKMNUNAFFECTED
};

const u16 gAttractUsedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNFELLINLOVE,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNSXINFATUATEDY
};

const u16 gAbsorbDrainStringIds[] =
{
    [B_MSG_ABSORB]      = STRINGID_PKMNENERGYDRAINED,
    [B_MSG_ABSORB_OOZE] = STRINGID_ITSUCKEDLIQUIDOOZE
};

const u16 gSportsUsedStringIds[] =
{
    [B_MSG_WEAKEN_ELECTRIC] = STRINGID_ELECTRICITYWEAKENED,
    [B_MSG_WEAKEN_FIRE]     = STRINGID_FIREWEAKENED
};

const u16 gPartyStatusHealStringIds[] =
{
    [B_MSG_BELL]                     = STRINGID_BELLCHIMED,
    [B_MSG_BELL_SOUNDPROOF_ATTACKER] = STRINGID_BELLCHIMED,
    [B_MSG_BELL_SOUNDPROOF_PARTNER]  = STRINGID_BELLCHIMED,
    [B_MSG_BELL_BOTH_SOUNDPROOF]     = STRINGID_BELLCHIMED,
    [B_MSG_SOOTHING_AROMA]           = STRINGID_SOOTHINGAROMA
};

const u16 gFutureMoveUsedStringIds[] =
{
    [B_MSG_FUTURE_SIGHT] = STRINGID_PKMNFORESAWATTACK,
    [B_MSG_DOOM_DESIRE]  = STRINGID_PKMNCHOSEXASDESTINY
};

const u16 gBallEscapeStringIds[] =
{
    [BALL_NO_SHAKES]     = STRINGID_PKMNBROKEFREE,
    [BALL_1_SHAKE]       = STRINGID_ITAPPEAREDCAUGHT,
    [BALL_2_SHAKES]      = STRINGID_AARGHALMOSTHADIT,
    [BALL_3_SHAKES_FAIL] = STRINGID_SHOOTSOCLOSE
};

// Overworld weathers that don't have an associated battle weather default to "It is raining."
const u16 gWeatherStartsStringIds[] =
{
    [WEATHER_NONE]               = STRINGID_ITISRAINING,
    [WEATHER_SUNNY_CLOUDS]       = STRINGID_ITISRAINING,
    [WEATHER_SUNNY]              = STRINGID_ITISRAINING,
    [WEATHER_RAIN]               = STRINGID_ITISRAINING,
    [WEATHER_SNOW]               = (B_OVERWORLD_SNOW >= GEN_9 ? STRINGID_ITISSNOWING : STRINGID_ITISHAILING),
    [WEATHER_RAIN_THUNDERSTORM]  = STRINGID_ITISRAINING,
    [WEATHER_FOG_HORIZONTAL]     = STRINGID_FOGISDEEP,
    [WEATHER_VOLCANIC_ASH]       = STRINGID_ITISRAINING,
    [WEATHER_SANDSTORM]          = STRINGID_SANDSTORMISRAGING,
    [WEATHER_FOG_DIAGONAL]       = STRINGID_FOGISDEEP,
    [WEATHER_UNDERWATER]         = STRINGID_ITISRAINING,
    [WEATHER_SHADE]              = STRINGID_ITISRAINING,
    [WEATHER_DROUGHT]            = STRINGID_SUNLIGHTISHARSH,
    [WEATHER_DOWNPOUR]           = STRINGID_ITISRAINING,
    [WEATHER_UNDERWATER_BUBBLES] = STRINGID_ITISRAINING,
    [WEATHER_ABNORMAL]           = STRINGID_ITISRAINING
};

const u16 gTerrainStartsStringIds[] =
{
    [B_MSG_TERRAIN_SET_MISTY]    = STRINGID_MISTSWIRLSAROUND,
    [B_MSG_TERRAIN_SET_ELECTRIC] = STRINGID_ELECTRICCURRENTISRUNNING,
    [B_MSG_TERRAIN_SET_PSYCHIC]  = STRINGID_SEEMSWEIRD,
    [B_MSG_TERRAIN_SET_GRASSY]   = STRINGID_ISCOVEREDWITHGRASS,
};

const u16 gPrimalWeatherBlocksStringIds[] =
{
    [B_MSG_PRIMAL_WEATHER_FIZZLED_BY_RAIN]      = STRINGID_MOVEFIZZLEDOUTINTHEHEAVYRAIN,
    [B_MSG_PRIMAL_WEATHER_EVAPORATED_IN_SUN]    = STRINGID_MOVEEVAPORATEDINTHEHARSHSUNLIGHT,
};

const u16 gInobedientStringIds[] =
{
    [B_MSG_LOAFING]            = STRINGID_PKMNLOAFING,
    [B_MSG_WONT_OBEY]          = STRINGID_PKMNWONTOBEY,
    [B_MSG_TURNED_AWAY]        = STRINGID_PKMNTURNEDAWAY,
    [B_MSG_PRETEND_NOT_NOTICE] = STRINGID_PKMNPRETENDNOTNOTICE,
    [B_MSG_INCAPABLE_OF_POWER] = STRINGID_PKMNINCAPABLEOFPOWER
};

const u16 gSafariReactionStringIds[NUM_SAFARI_REACTIONS] =
{
    [B_MSG_MON_WATCHING] = STRINGID_PKMNWATCHINGCAREFULLY,
    [B_MSG_MON_ANGRY]    = STRINGID_PKMNANGRY,
    [B_MSG_MON_EATING]   = STRINGID_PKMNEATING
};

const u16 gSafariGetNearStringIds[] =
{
    [B_MSG_CREPT_CLOSER]    = STRINGID_CREPTCLOSER,
    [B_MSG_CANT_GET_CLOSER] = STRINGID_CANTGETCLOSER
};

const u16 gSafariPokeblockResultStringIds[] =
{
    [B_MSG_MON_CURIOUS]    = STRINGID_PKMNCURIOUSABOUTX,
    [B_MSG_MON_ENTHRALLED] = STRINGID_PKMNENTHRALLEDBYX,
    [B_MSG_MON_IGNORED]    = STRINGID_PKMNIGNOREDX
};

const u16 CureStatusBerryEffectStringID[] =
{
    [B_MSG_CURED_PARALYSIS] = STRINGID_PKMNSITEMCUREDPARALYSIS,
    [B_MSG_CURED_POISON] = STRINGID_PKMNSITEMCUREDPOISON,
    [B_MSG_CURED_BURN] = STRINGID_PKMNSITEMHEALEDBURN,
    [B_MSG_CURED_FREEZE] = STRINGID_PKMNSITEMDEFROSTEDIT,
    [B_MSG_CURED_FROSTBITE] = STRINGID_PKMNSITEMHEALEDFROSTBITE,
    [B_MSG_CURED_SLEEP] = STRINGID_PKMNSITEMWOKEIT,
    [B_MSG_CURED_CONFUSION] = STRINGID_PKMNSITEMSNAPPEDOUT,
};

const u16 gItemSwapStringIds[] =
{
    [B_MSG_ITEM_SWAP_TAKEN] = STRINGID_PKMNOBTAINEDX,
    [B_MSG_ITEM_SWAP_GIVEN] = STRINGID_PKMNOBTAINEDX2,
    [B_MSG_ITEM_SWAP_BOTH]  = STRINGID_PKMNOBTAINEDXYOBTAINEDZ
};

const u16 gFlashFireStringIds[] =
{
    [B_MSG_FLASH_FIRE_BOOST]    = STRINGID_PKMNRAISEDFIREPOWERWITH,
    [B_MSG_FLASH_FIRE_NO_BOOST] = STRINGID_PKMNSXMADEITINEFFECTIVE
};

const u16 gCaughtMonStringIds[] =
{
    [B_MSG_SENT_SOMEONES_PC]   = STRINGID_PKMNTRANSFERREDSOMEONESPC,
    [B_MSG_SENT_LANETTES_PC]   = STRINGID_PKMNTRANSFERREDLANETTESPC,
    [B_MSG_SOMEONES_BOX_FULL]  = STRINGID_PKMNBOXSOMEONESPCFULL,
    [B_MSG_LANETTES_BOX_FULL]  = STRINGID_PKMNBOXLANETTESPCFULL,
    [B_MSG_SWAPPED_INTO_PARTY] = STRINGID_PKMNSENTTOPCAFTERCATCH,
};

const u16 gRoomsStringIds[] =
{
    STRINGID_PKMNTWISTEDDIMENSIONS, STRINGID_TRICKROOMENDS,
    STRINGID_SWAPSDEFANDSPDEFOFALLPOKEMON, STRINGID_WONDERROOMENDS,
    STRINGID_HELDITEMSLOSEEFFECTS, STRINGID_MAGICROOMENDS,
    STRINGID_EMPTYSTRING3
};

const u16 gStatusConditionsStringIds[] =
{
    STRINGID_PKMNWASPOISONED, STRINGID_PKMNBADLYPOISONED, STRINGID_PKMNWASBURNED, STRINGID_PKMNWASPARALYZED, STRINGID_PKMNFELLASLEEP, STRINGID_PKMNGOTFROSTBITE
};

const u16 gDamageNonTypesStartStringIds[] =
{
    [B_MSG_TRAPPED_WITH_VINES]  = STRINGID_TEAMTRAPPEDWITHVINES,
    [B_MSG_CAUGHT_IN_VORTEX]    = STRINGID_TEAMCAUGHTINVORTEX,
    [B_MSG_SURROUNDED_BY_FIRE]  = STRINGID_TEAMSURROUNDEDBYFIRE,
    [B_MSG_SURROUNDED_BY_ROCKS] = STRINGID_TEAMSURROUNDEDBYROCKS,
};

const u16 gDamageNonTypesDmgStringIds[] =
{
    [B_MSG_HURT_BY_VINES]        = STRINGID_PKMNHURTBYVINES,
    [B_MSG_HURT_BY_VORTEX]       = STRINGID_PKMNHURTBYVORTEX,
    [B_MSG_BURNING_UP]           = STRINGID_PKMNBURNINGUP,
    [B_MSG_HURT_BY_ROCKS_THROWN] = STRINGID_PKMNHURTBYROCKSTHROWN,
};

const u16 gRemoveHazardsStringIds[] =
{
    [HAZARDS_SPIKES] = STRINGID_SPIKESDISAPPEAREDFROMTEAM,
    [HAZARDS_STICKY_WEB] = STRINGID_STICKYWEBDISAPPEAREDFROMTEAM,
    [HAZARDS_TOXIC_SPIKES] = STRINGID_TOXICSPIKESDISAPPEAREDFROMTEAM,
    [HAZARDS_STEALTH_ROCK] = STRINGID_STEALTHROCKDISAPPEAREDFROMTEAM,
    [HAZARDS_STEELSURGE] = STRINGID_SHARPSTEELDISAPPEAREDFROMTEAM,
};

const u16 gZenModeStringIds[] =
{
    [B_MSG_ZEN_MODE_TRIGGERED] = STRINGID_ZENMODETRIGGERED,
    [B_MSG_ZEN_MODE_ENDED] = STRINGID_ZENMODEENDED
};

const u16 gCureStatusStringIds[] =
{
    [B_MSG_CURED_PARALYSIS] = STRINGID_SCRCUREDPARALYSIS,
    [B_MSG_CURED_POISON] = STRINGID_SCRCUREDPOISON,
    [B_MSG_CURED_BURN] = STRINGID_SCRCUREDBURN,
    [B_MSG_CURED_SLEEP] = STRINGID_SCRCUREDSLEEP,
    [B_MSG_CURED_FREEZE] = STRINGID_PKMNWASDEFROSTED,
    [B_MSG_CURED_FROSTBITE] = STRINGID_PKMNFROSTBITEHEALED,
    [B_MSG_CURED_CONFUSION] = STRINGID_SCRCUREDCONFUSION,
    [B_MSG_CURED_INFATUATION] = STRINGID_PKMNGOTOVERITSINFATUATION,
    [B_MSG_CURED_TAUNT] = STRINGID_PKMNSHOOKOFFTHETAUNT,
};

const u16 gPartyCureStatusStringIds[] =
{
    [B_MSG_CURED_PARALYSIS] = STRINGID_PARTYCUREDPARALYSIS,
    [B_MSG_CURED_POISON] = STRINGID_PARTYCUREDPOISON,
    [B_MSG_CURED_BURN] = STRINGID_PARTYCUREDBURN,
    [B_MSG_CURED_SLEEP] = STRINGID_PARTYCUREDSLEEP,
    [B_MSG_CURED_FREEZE] = STRINGID_PARTYCUREDFREEZE,
    [B_MSG_CURED_FROSTBITE] = STRINGID_PARTYCUREDFROSTBITE,
    [B_MSG_CURED_CONFUSION] = STRINGID_SCRCUREDCONFUSION,
    [B_MSG_CURED_INFATUATION] = STRINGID_PKMNGOTOVERITSINFATUATION,
    [B_MSG_CURED_TAUNT] = STRINGID_PKMNSHOOKOFFTHETAUNT,
};

const u16 gHurtByStringIds[] =
{
    [B_MSG_HURT] = STRINGID_PKMNWASHURT,
    [B_MSG_HURT_BY_ITEM] = STRINGID_PKMNHURTSWITH,
};

const u16 gBreakScreensStringIds[] =
{
    [B_MSG_BREAK_REFLECT] = STRINGID_REFLECTWOREOFF,
    [B_MSG_BREAK_LIGHT_SCREEN] = STRINGID_LIGHTSCREENWOREOFF,
    [B_MSG_BREAK_AURORA_VEIL] = STRINGID_AURORAVEILWOREOFF,
};

const u8 gText_PkmnIsEvolving[] = _("¡Anda!\n¡{STR_VAR_1} está evolucionando!");
const u8 gText_CongratsPkmnEvolved[] = _("¡Enhorabuena! ¡Tu {STR_VAR_1}\nse ha convertido en {STR_VAR_2}!{WAIT_SE}\p");
const u8 gText_PkmnStoppedEvolving[] = _("¿Eh? ¡La evolución de\n{STR_VAR_1} se ha detenido!\p");
const u8 gText_EllipsisQuestionMark[] = _("¿……?\p");
const u8 gText_WhatWillPkmnDo[] = _("¿Qué debería hacer\n{B_BUFF1}?");
const u8 gText_WhatWillPkmnDo2[] = _("What will\n{B_PLAYER_NAME} do?");
const u8 gText_WhatWillWallyDo[] = _("¿¿Qué debería hacer\nBlasco?");
const u8 gText_LinkStandby[] = _("{PAUSE 16}Esperando conexión…");
const u8 gText_BattleMenu[] = _("Lucha{CLEAR_TO 56}Mochila\nPokémon{CLEAR_TO 56}Huida");
const u8 gText_SafariZoneMenu[] = _("Ball{CLEAR_TO 56}{POKEBLOCK}\nGo Near{CLEAR_TO 56}Run");
const u8 gText_SafariZoneMenuFrlg[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW 13 14 15}BALL{CLEAR_TO 56}BAIT\nROCK{CLEAR_TO 56}RUN");
const u8 gText_MoveInterfacePP[] = _("PP ");
const u8 gText_MoveInterfaceType[] = _("Tipo/");
const u8 gText_MoveInterfacePPType[] = _("{PALETTE 5}{BACKGROUND DYNAMIC_COLOR5}{TEXT_COLORS DYNAMIC_COLOR4 DYNAMIC_COLOR6 DYNAMIC_COLOR5}PP\nTYPE/");
const u8 gText_MoveInterfaceDynamicColors[] = _("{PALETTE 5}{BACKGROUND DYNAMIC_COLOR5}{TEXT_COLORS DYNAMIC_COLOR4 DYNAMIC_COLOR6 DYNAMIC_COLOR5}");
const u8 gText_WhichMoveToForget4[] = _("{PALETTE 5}{BACKGROUND DYNAMIC_COLOR5}{TEXT_COLORS DYNAMIC_COLOR4 DYNAMIC_COLOR6 DYNAMIC_COLOR5}Which move should\nbe forgotten?");
const u8 gText_BattleCatchOrNot[] = _("{PALETTE 5}{BACKGROUND DYNAMIC_COLOR5}{TEXT_COLORS DYNAMIC_COLOR4 DYNAMIC_COLOR6 DYNAMIC_COLOR5}Catch\nDon't catch");
const u8 gText_BattleYesNoChoice[] = _("{PALETTE 5}{BACKGROUND DYNAMIC_COLOR5}{TEXT_COLORS DYNAMIC_COLOR4 DYNAMIC_COLOR6 DYNAMIC_COLOR5}Yes\nNo");
const u8 gText_BattleSwitchWhich[] = _("{PALETTE 5}{BACKGROUND DYNAMIC_COLOR5}{TEXT_COLORS DYNAMIC_COLOR4 DYNAMIC_COLOR6 DYNAMIC_COLOR5}Switch\nwhich?");
const u8 gText_BattleSwitchWhich2[] = _("{PALETTE 5}{BACKGROUND DYNAMIC_COLOR5}{TEXT_COLORS DYNAMIC_COLOR4 DYNAMIC_COLOR6 DYNAMIC_COLOR5}");
const u8 gText_BattleSwitchWhich3[] = _("{UP_ARROW}");
const u8 gText_BattleSwitchWhich4[] = _("{ESCAPE 4}");
const u8 gText_BattleSwitchWhich5[] = _("-");
const u8 gText_SafariBalls[] = _("{HIGHLIGHT DARK_GRAY}Safari Balls");
const u8 gText_SafariBallLeft[] = _("{HIGHLIGHT DARK_GRAY}Tienes: ${HIGHLIGHT DARK_GRAY}");
const u8 gText_Sleep[] = _("sueño");
const u8 gText_Poison[] = _("envenenamiento");
const u8 gText_Burn[] = _("quemaduras");
const u8 gText_Paralysis[] = _("parálisis");
const u8 gText_Ice[] = _("congelación");
const u8 gText_Confusion[] = _("confusión");
const u8 gText_Love[] = _("enamoramiento");
const u8 gText_SpaceAndSpace[] = _(" y ");
const u8 gText_CommaSpace[] = _(", ");
const u8 gText_Space2[] = _(" ");
const u8 gText_LineBreak[] = _(" ");
const u8 gText_NewLine[] = _("\n");
const u8 gText_Are[] = _("no pueden");
const u8 gText_Are2[] = _("no pueden");
const u8 gText_BadEgg[] = _("Huevo malo");
const u8 gText_BattleWallyName[] = _("Blasco");
const u8 gText_Win[] = _("{BACKGROUND TRANSPARENT}{ACCENT TRANSPARENT}Win");
const u8 gText_Loss[] = _("{BACKGROUND TRANSPARENT}{ACCENT TRANSPARENT}Loss");
const u8 gText_Draw[] = _("{BACKGROUND TRANSPARENT}{ACCENT TRANSPARENT}Draw");
static const u8 sText_SpaceIs[] = _(" es");
static const u8 sText_ApostropheS[] = _("de");
const u8 gText_BattleTourney[] = _("Torneo de Combates");

const u8 *const gRoundsStringTable[DOME_ROUNDS_COUNT] =
{
    [DOME_ROUND1]    = COMPOUND_STRING("Ronda 1"),
    [DOME_ROUND2]    = COMPOUND_STRING("Ronda 2"),
    [DOME_SEMIFINAL] = COMPOUND_STRING("Semifinal"),
    [DOME_FINAL]     = COMPOUND_STRING("Final"),
};

const u8 gText_TheGreatNewHope[] = _("¡La nueva esperanza!\p");
const u8 gText_WillChampionshipDreamComeTrue[] = _("¡¿El sueño de campeón se hará realidad?!\p");
const u8 gText_AFormerChampion[] = _("¡Un antiguo Campeón!\p");
const u8 gText_ThePreviousChampion[] = _("¡El Campeón anterior!\p");
const u8 gText_TheUnbeatenChampion[] = _("¡El Campeón imbatido!\p");
const u8 gText_PlayerMon1Name[] = _("{B_PLAYER_MON1_NAME}");
const u8 gText_Vs[] = _("VS");
const u8 gText_OpponentMon1Name[] = _("{B_OPPONENT_MON1_NAME}");
const u8 gText_Mind[] = _("Mente");
const u8 gText_Skill[] = _("Habilidad");
const u8 gText_Body[] = _("Cuerpo");
const u8 gText_Judgment[] = _("{B_BUFF1}{CLEAR 13}Juicio{CLEAR 13}{B_BUFF2}");
static const u8 sText_TwoTrainersSentPkmn[] = _("{B_TRAINER1_NAME_WITH_CLASS} sent out {B_OPPONENT_MON1_NAME}!\p{B_TRAINER2_NAME_WITH_CLASS} sent out {B_OPPONENT_MON2_NAME}!");
static const u8 sText_Trainer2SentOutPkmn[] = _("{B_TRAINER2_NAME_WITH_CLASS} sent out {B_BUFF1}!");
static const u8 sText_TwoTrainersWantToBattle[] = _("¡{B_TRAINER1_NAME_WITH_CLASS} y {B_TRAINER2_NAME_WITH_CLASS} te desafían!\p");
static const u8 sText_InGamePartnerSentOutZGoN[] = _("{B_PARTNER_NAME_WITH_CLASS} sent out {B_PLAYER_MON2_NAME}! Go, {B_PLAYER_MON1_NAME}!");
static const u8 sText_InGamePartnerSentOutNGoZ[] = _("{B_PARTNER_NAME_WITH_CLASS} sent out {B_PLAYER_MON1_NAME}! Go, {B_PLAYER_MON2_NAME}!");
static const u8 sText_InGamePartnerSentOutPkmn1[] = _("{B_PARTNER_NAME_WITH_CLASS} sent out {B_PLAYER_MON1_NAME}!");
static const u8 sText_InGamePartnerSentOutPkmn2[] = _("{B_PARTNER_NAME_WITH_CLASS} sent out {B_PLAYER_MON2_NAME}!");
static const u8 sText_InGamePartnerWithdrewPkmn1[] = _("{B_PARTNER_NAME_WITH_CLASS} withdrew {B_PLAYER_MON1_NAME}!");
static const u8 sText_InGamePartnerWithdrewPkmn2[] = _("{B_PARTNER_NAME_WITH_CLASS} withdrew {B_PLAYER_MON2_NAME}!");

const u16 gBattlePalaceFlavorTextTable[] =
{
    [B_MSG_GLINT_IN_EYE]   = STRINGID_GLINTAPPEARSINEYE,
    [B_MSG_GETTING_IN_POS] = STRINGID_PKMNGETTINGINTOPOSITION,
    [B_MSG_GROWL_DEEPLY]   = STRINGID_PKMNBEGANGROWLINGDEEPLY,
    [B_MSG_EAGER_FOR_MORE] = STRINGID_PKMNEAGERFORMORE,
};

const u8 *const gRefereeStringsTable[] =
{
    [B_MSG_REF_NOTHING_IS_DECIDED] = COMPOUND_STRING("Juez: Si la cosa no se decide en las 3 próximas rondas, emitiremos un juicio!"),
    [B_MSG_REF_THATS_IT]           = COMPOUND_STRING("Juez: ¡Se acabó! Vamos a determinar quién consideramos que ha ganado"),
    [B_MSG_REF_JUDGE_MIND]         = COMPOUND_STRING("Juez: Lo 1.º en valorar es la mente: qué POKéMON ha tenido más coraje.\p"),
    [B_MSG_REF_JUDGE_SKILL]        = COMPOUND_STRING("Juez: Lo 2.º, la habilidad: qué POKéMON ha usado mejor sus ataques.\p"),
    [B_MSG_REF_JUDGE_BODY]         = COMPOUND_STRING("Juez: Lo 3.º, el cuerpo: qué POKéMON está más entero.\p"),
    [B_MSG_REF_PLAYER_WON]         = COMPOUND_STRING("Juez: El resultado es {B_BUFF1} a {B_BUFF2}! ¡Ha ganado {B_PLAYER_MON1_NAME}, de {B_PLAYER_NAME}!\p"),
    [B_MSG_REF_OPPONENT_WON]       = COMPOUND_STRING("Juez: El resultado es ¡{B_BUFF1} a {B_BUFF2}! ¡Ha ganado {B_OPPONENT_MON1_NAME}, de {B_TRAINER1_NAME}!\p"),
    [B_MSG_REF_DRAW]               = COMPOUND_STRING("Juez: El resultado es 3 a 3… ¡Eso es empate!\p"),
    [B_MSG_REF_COMMENCE_BATTLE]    = COMPOUND_STRING("Juez: ¡Comienza el encuentro {B_PLAYER_MON1_NAME} contra {B_OPPONENT_MON1_NAME}!"),
};

static const u8 sText_Trainer1Fled[] = _( "{PLAY_SE SE_FLEE}{B_TRAINER1_NAME_WITH_CLASS} fled!");
static const u8 sText_PlayerLostAgainstTrainer1[] = _("¡Perdiste contra {B_TRAINER1_NAME_WITH_CLASS}!");
static const u8 sText_PlayerBattledToDrawTrainer1[] = _("¡Empataste contra {B_TRAINER1_NAME_WITH_CLASS}!");
const u8 gText_RecordBattleToPass[] = _("¿Quieres grabar el combate\nen el Pase del Frente?");
const u8 gText_BattleRecordedOnPass[] = _("El combate de {B_PLAYER_NAME} se ha\ngrabado en el Pase del Frente.");
static const u8 sText_LinkTrainerWantsToBattlePause[] = _("Has sido retado por {B_LINK_OPPONENT1_NAME}!\p");
static const u8 sText_TwoLinkTrainersWantToBattlePause[] = _("Has sido retado por {B_LINK_OPPONENT1_NAME} y {B_LINK_OPPONENT2_NAME}!\p");
static const u8 sText_Your1[] = _("aliado");
static const u8 sText_Opposing1[] = _("enemigo");
static const u8 sText_Your2[] = _("aliado");
static const u8 sText_Opposing2[] = _("enemigo");
static const u8 sText_EmptyStatus[] = _("$$$$$$$");

static const struct BattleWindowText sTextOnWindowsInfo_Normal[] =
{
    [B_WIN_MSG] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 1,
        .color.foreground = 1,
        .color.background = 15,
        .color.accent = 15,
        .color.shadow = 6,
    },
    [B_WIN_ACTION_PROMPT] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 1,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.background = 15,
        .color.accent = 15,
        .color.shadow = 6,
    },
    [B_WIN_ACTION_MENU] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_MOVE_NAME_1] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_MOVE_NAME_2] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_MOVE_NAME_3] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_MOVE_NAME_4] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_PP] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = B_SHOW_EFFECTIVENESS != SHOW_EFFECTIVENESS_NEVER ? 13 : 12,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = B_SHOW_EFFECTIVENESS != SHOW_EFFECTIVENESS_NEVER ? 15 : 11,
    },
    [B_WIN_DUMMY] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_PP_REMAINING] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 2,
        .y = 1,
        .speed = 0,
        .color.foreground = 12,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 11,
    },
    [B_WIN_MOVE_TYPE] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_SWITCH_PROMPT] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_YESNO] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_LEVEL_UP_BOX] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_LEVEL_UP_BANNER] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = 32,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.shadow = 2,
    },
    [B_WIN_VS_PLAYER] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_VS_OPPONENT] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_1] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_2] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_3] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_4] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_VS_OUTCOME_DRAW] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.shadow = 6,
    },
    [B_WIN_VS_OUTCOME_LEFT] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.shadow = 6,
    },
    [B_WIN_VS_OUTCOME_RIGHT] = {
        .fillValue = PIXEL_FILL(0x0),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.shadow = 6,
    },
    [B_WIN_MOVE_DESCRIPTION] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .color.foreground = TEXT_DYNAMIC_COLOR_4,
        .color.background = TEXT_DYNAMIC_COLOR_5,
        .color.accent = TEXT_DYNAMIC_COLOR_5,
        .color.shadow = TEXT_DYNAMIC_COLOR_6,
    },
    [B_CATCH_OR_NOT] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
};

static const struct BattleWindowText sTextOnWindowsInfo_KantoTutorial[] =
{
    [B_WIN_MSG] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 1,
        .color.foreground = 1,
        .color.background = 15,
        .color.accent = 15,
        .color.shadow = 6,
    },
    [B_WIN_ACTION_PROMPT] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 1,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.background = 15,
        .color.accent = 15,
        .color.shadow = 6,
    },
    [B_WIN_ACTION_MENU] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_MOVE_NAME_1] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_MOVE_NAME_2] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_MOVE_NAME_3] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_MOVE_NAME_4] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_PP] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = B_SHOW_EFFECTIVENESS != SHOW_EFFECTIVENESS_NEVER ? 13 : 12,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = B_SHOW_EFFECTIVENESS != SHOW_EFFECTIVENESS_NEVER ? 15 : 11,
    },
    [B_WIN_DUMMY] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_PP_REMAINING] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 2,
        .y = 1,
        .speed = 0,
        .color.foreground = 12,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 11,
    },
    [B_WIN_MOVE_TYPE] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_SWITCH_PROMPT] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_YESNO] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_LEVEL_UP_BOX] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_LEVEL_UP_BANNER] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = 32,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.shadow = 2,
    },
    [B_WIN_VS_PLAYER] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_VS_OPPONENT] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_1] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_2] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_3] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_4] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_VS_OUTCOME_DRAW] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.shadow = 6,
    },
    [B_WIN_VS_OUTCOME_LEFT] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.shadow = 6,
    },
    [B_WIN_VS_OUTCOME_RIGHT] = {
        .fillValue = PIXEL_FILL(0x0),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.shadow = 6,
    },
    [B_WIN_MOVE_DESCRIPTION] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .color.foreground = TEXT_DYNAMIC_COLOR_4,
        .color.background = TEXT_DYNAMIC_COLOR_5,
        .color.accent = TEXT_DYNAMIC_COLOR_5,
        .color.shadow = TEXT_DYNAMIC_COLOR_6,
    },
    [B_WIN_OAK_OLD_MAN] = {
        .fillValue = PIXEL_FILL(0x1),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 1,
        .speed = 1,
        .fgColor = 2,
        .bgColor = 1,
        .shadowColor = 3,
    },
};

static const struct BattleWindowText sTextOnWindowsInfo_Arena[] =
{
    [B_WIN_MSG] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 1,
        .color.foreground = 1,
        .color.background = 15,
        .color.accent = 15,
        .color.shadow = 6,
    },
    [B_WIN_ACTION_PROMPT] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 1,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.background = 15,
        .color.accent = 15,
        .color.shadow = 6,
    },
    [B_WIN_ACTION_MENU] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_MOVE_NAME_1] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_MOVE_NAME_2] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_MOVE_NAME_3] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_MOVE_NAME_4] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_PP] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = B_SHOW_EFFECTIVENESS != SHOW_EFFECTIVENESS_NEVER ? 13 : 12,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = B_SHOW_EFFECTIVENESS != SHOW_EFFECTIVENESS_NEVER ? 15 : 11,
    },
    [B_WIN_DUMMY] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_PP_REMAINING] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 2,
        .y = 1,
        .speed = 0,
        .color.foreground = 12,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 11,
    },
    [B_WIN_MOVE_TYPE] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_SWITCH_PROMPT] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_YESNO] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_LEVEL_UP_BOX] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [B_WIN_LEVEL_UP_BANNER] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = 32,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.shadow = 2,
    },
    [ARENA_WIN_PLAYER_NAME] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 1,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [ARENA_WIN_VS] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [ARENA_WIN_OPPONENT_NAME] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [ARENA_WIN_MIND] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [ARENA_WIN_SKILL] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [ARENA_WIN_BODY] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [ARENA_WIN_JUDGMENT_TITLE] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .color.foreground = 13,
        .color.background = 14,
        .color.accent = 14,
        .color.shadow = 15,
    },
    [ARENA_WIN_JUDGMENT_TEXT] = {
        .fillValue = PIXEL_FILL(0x1),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 1,
        .color.foreground = 2,
        .color.background = 1,
        .color.accent = 1,
        .color.shadow = 3,
    },
    [B_WIN_MOVE_DESCRIPTION] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .color.foreground = TEXT_DYNAMIC_COLOR_4,
        .color.background = TEXT_DYNAMIC_COLOR_5,
        .color.accent = TEXT_DYNAMIC_COLOR_5,
        .color.shadow = TEXT_DYNAMIC_COLOR_6,
    },
};

static const struct BattleWindowText *const sBattleTextOnWindowsInfo[] =
{
    [B_WIN_TYPE_NORMAL] = sTextOnWindowsInfo_Normal,
    [B_WIN_TYPE_ARENA]  = sTextOnWindowsInfo_Arena,
    [B_WIN_TYPE_KANTO_TUTORIAL] = sTextOnWindowsInfo_KantoTutorial,
};

static const u8 sRecordedBattleTextSpeeds[] = {8, 4, 1, 0};

void BufferStringBattle(enum StringID stringID, enum BattlerId battler)
{
    s32 i;
    const u8 *stringPtr = NULL;

    gBattleMsgDataPtr = (struct BattleMsgData *)(&gBattleResources->bufferA[battler][4]);
    gLastUsedItem = gBattleMsgDataPtr->lastItem;
    gLastUsedAbility = gBattleMsgDataPtr->lastAbility;
    gBattleScripting.battler = gBattleMsgDataPtr->scrActive;
    gBattleStruct->scriptPartyIdx = gBattleMsgDataPtr->bakScriptPartyIdx;
    gBattleStruct->hpScale = gBattleMsgDataPtr->hpScale;
    gPotentialItemEffectBattler = gBattleMsgDataPtr->itemEffectBattler;
    gBattleStruct->stringMoveType = gBattleMsgDataPtr->moveType;

    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        sBattlerAbilities[i] = gBattleMsgDataPtr->abilities[i];
    }
    for (i = 0; i < TEXT_BUFF_ARRAY_COUNT; i++)
    {
        gBattleTextBuff1[i] = gBattleMsgDataPtr->textBuffs[0][i];
        gBattleTextBuff2[i] = gBattleMsgDataPtr->textBuffs[1][i];
        gBattleTextBuff3[i] = gBattleMsgDataPtr->textBuffs[2][i];
    }

    switch (stringID)
    {
    case STRINGID_INTROMSG: // first battle msg
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
        {
            if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                {
                    stringPtr = sText_TwoTrainersWantToBattle;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                {
                    stringPtr = sText_TwoLinkTrainersWantToBattle;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                {
                    if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
                    {
                        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
                            stringPtr = sText_LinkTrainerWantsToBattle;
                        else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                            stringPtr = sText_TwoTrainersWantToBattle;
                        else if (!(gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS))
                            stringPtr = sText_LinkTrainerWantsToBattlePause;
                        else
                            stringPtr = sText_TwoLinkTrainersWantToBattlePause;
                    }
                    else
                    {
                        stringPtr = sText_TwoLinkTrainersWantToBattle;
                    }
                }
                else
                {
                    if (TRAINER_BATTLE_PARAM.opponentA == TRAINER_UNION_ROOM)
                        stringPtr = sText_Trainer1WantsToBattle;
                    else if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
                        stringPtr = sText_LinkTrainerWantsToBattlePause;
                    else
                        stringPtr = sText_LinkTrainerWantsToBattle;
                }
            }
            else
            {
                if (BATTLE_TWO_VS_ONE_OPPONENT)
                    stringPtr = sText_Trainer1WantsToBattle;
                else if (gBattleTypeFlags & (BATTLE_TYPE_MULTI | BATTLE_TYPE_INGAME_PARTNER))
                    stringPtr = sText_TwoTrainersWantToBattle;
                else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                    stringPtr = sText_TwoTrainersWantToBattle;
                else
                    stringPtr = sText_Trainer1WantsToBattle;
            }
        }
        else
        {
            if (IsGhostBattleWithoutScope())
                stringPtr = sText_GhostAppearedCantId;
            else if (gBattleTypeFlags & BATTLE_TYPE_GHOST)
                stringPtr = sText_TheGhostAppeared;
            else if (gBattleTypeFlags & BATTLE_TYPE_LEGENDARY)
                stringPtr = sText_LegendaryPkmnAppeared;
            else if (IsDoubleBattle() && IsValidForBattle(GetBattlerMon(GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT))))
                stringPtr = sText_TwoWildPkmnAppeared;
            else if (gBattleTypeFlags & BATTLE_TYPE_CATCH_TUTORIAL)
                stringPtr = sText_WildPkmnAppearedPause;
            else
                stringPtr = sText_WildPkmnAppeared;
        }
        break;
    case STRINGID_INTROSENDOUT: // poke first send-out
        if (IsOnPlayerSide(battler))
        {
            if (IsDoubleBattle() && IsValidForBattle(GetBattlerMon(GetPartnerBattler(battler))))
            {
                if (gBattleTypeFlags & BATTLE_TYPE_MULTI && (gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK || gBattleTypeFlags & BATTLE_TYPE_LINK))
                {
                    if (BattlerIsPlayer(battler))
                        stringPtr = sText_LinkPartnerSentOutPkmn2GoPkmn; // Player is on left
                    else
                        stringPtr = sText_LinkPartnerSentOutPkmn1GoPkmn; // Link Partner on left
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
                {
                    if (BattlerIsPlayer(battler) && (battler & BIT_FLANK) == B_FLANK_LEFT)
                        stringPtr = sText_InGamePartnerSentOutZGoN; // Player is on left
                    else
                        stringPtr = sText_InGamePartnerSentOutNGoZ; // Partner on left
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_RAID)
                {
                    stringPtr = sText_BeCarefulPkmn;
                }
                else
                {
                    stringPtr = sText_GoTwoPkmn;
                }
            }
            else
            {
                stringPtr = sText_GoPkmn;
            }
        }
        else
        {
            if (IsDoubleBattle() && IsValidForBattle(GetBattlerMon(GetPartnerBattler(battler))))
            {
                if (gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK && BATTLE_TWO_VS_ONE_OPPONENT)
                    stringPtr = sText_LinkTrainerSentOutTwoPkmn;
                else if (BATTLE_TWO_VS_ONE_OPPONENT)
                    stringPtr = sText_Trainer1SentOutTwoPkmn;
                else if ((gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK && gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS) || (gBattleTypeFlags & BATTLE_TYPE_MULTI && (gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK || gBattleTypeFlags & BATTLE_TYPE_LINK)))
                    stringPtr = sText_TwoLinkTrainersIntroSendOutPkmn;
                else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS || gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                    stringPtr = sText_TwoTrainersSentPkmn;
                else if (BattlerIsLink(battler) || (BattlerIsRecorded(battler) && BattlerIsOpponent(battler))) // Link Opponent doubles and test opponent
                    stringPtr = sText_LinkTrainerSentOutTwoPkmn;
                else
                    stringPtr = sText_Trainer1SentOutTwoPkmn;
            }
            else if (BattlerIsLink(battler) || (BattlerIsRecorded(battler) && BattlerIsOpponent(battler)))
            {
                if (TRAINER_BATTLE_PARAM.opponentA == TRAINER_UNION_ROOM)
                    stringPtr = sText_Trainer1SentOutPkmn;
                else
                    stringPtr = sText_LinkTrainerIntroSendOutPkmn;
            }
            else
            {
                stringPtr = sText_Trainer1SentOutPkmn;
            }
        }
        break;
    case STRINGID_RETURNMON: // sending poke to ball msg
        if ((GetBattlerPosition(battler) & BIT_FLANK) == B_FLANK_LEFT) // battler 0 and 1
        {
            if (BattlerIsPlayer(battler) || BattlerIsWally(battler)) // Player
            {
                if (*(&gBattleStruct->hpScale) == 0)
                    stringPtr = sText_PkmnThatsEnough;
                else if (*(&gBattleStruct->hpScale) == 1 || IsDoubleBattle())
                    stringPtr = sText_PkmnComeBack;
                else if (*(&gBattleStruct->hpScale) == 2)
                    stringPtr = sText_PkmnOkComeBack;
                else
                    stringPtr = sText_PkmnGoodComeBack;
            }
            else if (BattlerIsPartner(battler)) // Link or Ingame Partner
            {
                if (BattlerIsLink(battler) || gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
                    stringPtr = sText_LinkPartnerWithdrewPkmn1;
                else
                    stringPtr = sText_InGamePartnerWithdrewPkmn1;
            }
            else if (TRAINER_BATTLE_PARAM.opponentA == TRAINER_LINK_OPPONENT
             || gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK) // Link Opponent A and test opponent
            {
                stringPtr = sText_LinkTrainer1WithdrewPkmn;
            }
            else // Opponent A
            {
                stringPtr = sText_Trainer1WithdrewPkmn;
            }
        }
        else // battler 2 and 3
        {
            if (BattlerIsPlayer(battler)) // Player
            {
                if (*(&gBattleStruct->hpScale) == 0)
                    stringPtr = sText_PkmnThatsEnough;
                else if (*(&gBattleStruct->hpScale) == 1 || IsDoubleBattle())
                    stringPtr = sText_PkmnComeBack;
                else if (*(&gBattleStruct->hpScale) == 2)
                    stringPtr = sText_PkmnOkComeBack;
                else
                    stringPtr = sText_PkmnGoodComeBack;
            }
            else if (BattlerIsPartner(battler)) // Link or Ingame Partner
            {
                if (BattlerIsLink(battler) || gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
                    stringPtr = sText_LinkPartnerWithdrewPkmn2;
                else
                    stringPtr = sText_InGamePartnerWithdrewPkmn2;
            }
            else if (TRAINER_BATTLE_PARAM.opponentA == TRAINER_LINK_OPPONENT
             || gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK) // Link Opponent B and test opponent
            {
                if (BattleSideHasTwoTrainers(B_SIDE_OPPONENT))
                    stringPtr = sText_LinkTrainer2WithdrewPkmn;
                else
                    stringPtr = sText_LinkTrainer1WithdrewPkmn;
            }
            else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS) // Opponent B
            {
                stringPtr = sText_Trainer2WithdrewPkmn;
            }
            else // Opponent A
            {
                stringPtr = sText_Trainer1WithdrewPkmn;
            }
        }
        break;
    case STRINGID_SWITCHINMON: // switch-in msg
        if ((GetBattlerPosition(gBattleScripting.battler) & BIT_FLANK) == B_FLANK_LEFT) // battler 0 and 1
        {
            if (BattlerIsPlayer(gBattleScripting.battler)) // Player
            {
                if (*(&gBattleStruct->hpScale) == 0)
                    stringPtr = sText_GoPkmn2;
                else if (*(&gBattleStruct->hpScale) == 1 || IsDoubleBattle())
                    stringPtr = sText_DoItPkmn;
                else if (*(&gBattleStruct->hpScale) == 2)
                    stringPtr = sText_GoForItPkmn;
                else
                    stringPtr = sText_YourFoesWeakGetEmPkmn;
            }
            else if (BattlerIsPartner(gBattleScripting.battler)) // Link or Ingame Partner
            {
                if (BattlerIsLink(gBattleScripting.battler) || gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
                    stringPtr = sText_LinkPartnerSentOutPkmn1;
                else
                    stringPtr = sText_InGamePartnerSentOutPkmn1;
            }
            else if (TRAINER_BATTLE_PARAM.opponentA == TRAINER_LINK_OPPONENT
             || gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK) // Link Opponent A and test opponent
            {
                stringPtr = sText_LinkTrainerSentOutPkmn;
            }
            else // Opponent A
            {
                stringPtr = sText_Trainer1SentOutPkmn;
            }
        }
        else // battler 2 and 3
        {
            if (BattlerIsPlayer(gBattleScripting.battler)) // Player
            {
                if (*(&gBattleStruct->hpScale) == 0)
                    stringPtr = sText_GoPkmn2;
                else if (*(&gBattleStruct->hpScale) == 1 || IsDoubleBattle())
                    stringPtr = sText_DoItPkmn;
                else if (*(&gBattleStruct->hpScale) == 2)
                    stringPtr = sText_GoForItPkmn;
                else
                    stringPtr = sText_YourFoesWeakGetEmPkmn;
            }
            else if (BattlerIsPartner(gBattleScripting.battler)) // Link or Ingame Partner
            {
                if (BattlerIsLink(gBattleScripting.battler) || gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
                    stringPtr = sText_LinkPartnerSentOutPkmn2;
                else
                    stringPtr = sText_InGamePartnerSentOutPkmn2;
            }
            else if (TRAINER_BATTLE_PARAM.opponentA == TRAINER_LINK_OPPONENT
             || gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK) // Link Opponent B and test opponent
            {
                if (BattleSideHasTwoTrainers(B_SIDE_OPPONENT))
                    stringPtr = sText_LinkTrainer2SentOutPkmn2;
                else
                    stringPtr = sText_LinkTrainerSentOutPkmn2;
            }
            else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS) // Opponent B
            {
                stringPtr = sText_Trainer2SentOutPkmn;
            }
            else // Single trainer double Opponent A
            {
                stringPtr = sText_Trainer1SentOutPkmn2;
            }
        }
        break;
    case STRINGID_USEDMOVE: // Pokémon used a move msg
        if (gBattleMsgDataPtr->currentMove >= MOVES_COUNT
         && !IsZMove(gBattleMsgDataPtr->currentMove)
         && !IsMaxMove(gBattleMsgDataPtr->currentMove))
            StringCopy(gBattleTextBuff3, gTypesInfo[*(&gBattleStruct->stringMoveType)].generic);
        else
            StringCopy(gBattleTextBuff3, GetMoveName(gBattleMsgDataPtr->currentMove));
        stringPtr = sText_AttackerUsedX;
        break;
    case STRINGID_BATTLEEND: // battle end
        if (gBattleTextBuff1[0] & B_OUTCOME_LINK_BATTLE_RAN)
        {
            gBattleTextBuff1[0] &= ~(B_OUTCOME_LINK_BATTLE_RAN);
            if (!(BattlerIsPlayer(battler) || BattlerIsPlayer(GetPartnerBattler(battler))) && gBattleTextBuff1[0] != B_OUTCOME_DREW)
                gBattleTextBuff1[0] ^= (B_OUTCOME_LOST | B_OUTCOME_WON);

            if (gBattleTextBuff1[0] == B_OUTCOME_LOST || gBattleTextBuff1[0] == B_OUTCOME_DREW)
                stringPtr = sText_GotAwaySafely;
            else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                stringPtr = sText_TwoWildFled;
            else
                stringPtr = sText_WildFled;
        }
        else
        {
            if (!(BattlerIsPlayer(battler) || BattlerIsPlayer(GetPartnerBattler(battler))) && gBattleTextBuff1[0] != B_OUTCOME_DREW)
                gBattleTextBuff1[0] ^= (B_OUTCOME_LOST | B_OUTCOME_WON);

            if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                        stringPtr = sText_TwoInGameTrainersDefeated;
                    else
                        stringPtr = sText_TwoLinkTrainersDefeated;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostToTwo;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawVsTwo;
                    break;
                }
            }
            else if (TRAINER_BATTLE_PARAM.opponentA == TRAINER_UNION_ROOM)
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    stringPtr = sText_PlayerDefeatedLinkTrainerTrainer1;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostAgainstTrainer1;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawTrainer1;
                    break;
                }
            }
            else
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    stringPtr = sText_PlayerDefeatedLinkTrainer;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostAgainstLinkTrainer;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawLinkTrainer;
                    break;
                }
            }
        }
        break;
    case STRINGID_TRAINERSLIDE:
        stringPtr = gBattleStruct->trainerSlideMsg;
        break;
    default: // load a string from the table
        if (stringID >= STRINGID_COUNT)
        {
            gDisplayedStringBattle[0] = EOS;
            return;
        }
        else
        {
            stringPtr = gBattleStringsTable[stringID];
        }
        break;
    }

    BattleStringExpandPlaceholdersToDisplayedString(stringPtr);
}

u32 BattleStringExpandPlaceholdersToDisplayedString(const u8 *src)
{
#ifndef NDEBUG
    u32 j, strWidth;
    u32 dstID = BattleStringExpandPlaceholders(src, gDisplayedStringBattle, sizeof(gDisplayedStringBattle));
    for (j = 1;; j++)
    {
        strWidth = GetStringLineWidth(0, gDisplayedStringBattle, 0, j, sizeof(gDisplayedStringBattle));
        if (strWidth == 0)
            break;
    }
    return dstID;
#else
    return BattleStringExpandPlaceholders(src, gDisplayedStringBattle, sizeof(gDisplayedStringBattle));
#endif
}

static const u8 *TryGetStatusString(u8 *src)
{
    u32 i;
    u8 status[8];
    u32 chars1, chars2;
    u8 *statusPtr;

    memcpy(status, sText_EmptyStatus, min(ARRAY_COUNT(status), ARRAY_COUNT(sText_EmptyStatus)));

    statusPtr = status;
    for (i = 0; i < ARRAY_COUNT(status); i++)
    {
        if (*src == EOS) break; // one line required to match -g
        *statusPtr = *src;
        src++;
        statusPtr++;
    }

    chars1 = *(u32 *)(&status[0]);
    chars2 = *(u32 *)(&status[4]);

    for (i = 0; i < ARRAY_COUNT(gStatusConditionStringsTable); i++)
    {
        if (chars1 == *(u32 *)(&gStatusConditionStringsTable[i][0][0])
            && chars2 == *(u32 *)(&gStatusConditionStringsTable[i][0][4]))
            return gStatusConditionStringsTable[i][1];
    }
    return NULL;
}

static void GetBattlerNick(enum BattlerId battler, u8 *dst)
{
    struct Pokemon *illusionMon = GetIllusionMonPtr(battler);
    struct Pokemon *mon = GetBattlerMon(battler);

    if (illusionMon != NULL)
        mon = illusionMon;
    GetMonData(mon, MON_DATA_NICKNAME, dst);
    StringGet_Nickname(dst);
}

#define HANDLE_NICKNAME_STRING_CASE(battler)                            \
    if (!IsOnPlayerSide(battler))                                       \
    {                                                                   \
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)                     \
            toCpy = sText_FoePkmnPrefix;                                \
        else                                                            \
            toCpy = sText_WildPkmnPrefix;                               \
        while (*toCpy != EOS)                                           \
        {                                                               \
            dst[dstID] = *toCpy;                                        \
            dstID++;                                                    \
            toCpy++;                                                    \
        }                                                               \
    }                                                                   \
    GetBattlerNick(battler, text);                                      \
    toCpy = text;

#define HANDLE_NICKNAME_STRING_LOWERCASE(battler)                       \
    if (!IsOnPlayerSide(battler))                       \
    {                                                                   \
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)                     \
            toCpy = sText_FoePkmnPrefixLower;                           \
        else                                                            \
            toCpy = sText_WildPkmnPrefixLower;                          \
        while (*toCpy != EOS)                                           \
        {                                                               \
            dst[dstID] = *toCpy;                                        \
            dstID++;                                                    \
            toCpy++;                                                    \
        }                                                               \
    }                                                                   \
    GetBattlerNick(battler, text);                                      \
    toCpy = text;

static const u8 *BattleStringGetOpponentNameByTrainerId(u16 trainerId, u8 *text, u8 multiplayerId, enum BattlerId battler)
{
    const u8 *toCpy = NULL;

    if (gBattleTypeFlags & BATTLE_TYPE_SECRET_BASE)
    {
        u32 i;
        for (i = 0; i < ARRAY_COUNT(gBattleResources->secretBase->trainerName); i++)
            text[i] = gBattleResources->secretBase->trainerName[i];
        text[i] = EOS;
        ConvertInternationalString(text, gBattleResources->secretBase->language);
        toCpy = text;
    }
    else if (trainerId == TRAINER_UNION_ROOM)
    {
        toCpy = gLinkPlayers[multiplayerId ^ BIT_SIDE].name;
    }
    else if (trainerId == TRAINER_LINK_OPPONENT)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
            toCpy = gLinkPlayers[GetBattlerMultiplayerId(battler)].name;
        else
            toCpy = gLinkPlayers[GetBattlerMultiplayerId(battler) & BIT_SIDE].name;
    }
    else if (trainerId == TRAINER_FRONTIER_BRAIN)
    {
        CopyFrontierBrainTrainerName(text);
        toCpy = text;
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
    {
        GetFrontierTrainerName(text, trainerId);
        toCpy = text;
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_TOWER && gMapHeader.regionMapSectionId == MAPSEC_TRAINER_TOWER_2)
    {
        GetTrainerTowerOpponentName(text);
        toCpy = text;
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
    {
        GetTrainerHillTrainerName(text, trainerId);
        toCpy = text;
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_EREADER_TRAINER)
    {
        GetEreaderTrainerName(text);
        toCpy = text;
    }
    else
    {
        enum TrainerClassID trainerClass = GetTrainerClassFromId(TRAINER_BATTLE_PARAM.opponentA);

        if (trainerClass == TRAINER_CLASS_RIVAL_EARLY_FRLG || trainerClass == TRAINER_CLASS_RIVAL_LATE_FRLG || trainerClass == TRAINER_CLASS_CHAMPION_FRLG)
            toCpy = GetExpandedPlaceholder(PLACEHOLDER_ID_RIVAL);
        else
            toCpy = GetTrainerNameFromId(trainerId);
    }

    assertf(DoesStringProperlyTerminate(toCpy, TRAINER_NAME_LENGTH + 1),"Opponent needs a valid name")
    {
        return sText_EmptyString4;
    }

    return toCpy;
}

static const u8 *BattleStringGetOpponentName(u8 *text, u8 multiplayerId, enum BattlerId battler)
{
    const u8 *toCpy = NULL;

    switch (GetBattlerPosition(battler))
    {
    case B_POSITION_OPPONENT_LEFT:
        toCpy = BattleStringGetOpponentNameByTrainerId(TRAINER_BATTLE_PARAM.opponentA, text, multiplayerId, battler);
        break;
    case B_POSITION_OPPONENT_RIGHT:
        if (gBattleTypeFlags & (BATTLE_TYPE_TWO_OPPONENTS | BATTLE_TYPE_MULTI) && !BATTLE_TWO_VS_ONE_OPPONENT)
            toCpy = BattleStringGetOpponentNameByTrainerId(TRAINER_BATTLE_PARAM.opponentB, text, multiplayerId, battler);
        else
            toCpy = BattleStringGetOpponentNameByTrainerId(TRAINER_BATTLE_PARAM.opponentA, text, multiplayerId, battler);
        break;
    default:
        break;
    }

    return toCpy;
}

static const u8 *BattleStringGetPlayerName(u8 *text, enum BattlerId battler)
{
    const u8 *toCpy = NULL;

    switch (GetBattlerPosition(battler))
    {
    case B_POSITION_PLAYER_LEFT:
        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
            toCpy = gLinkPlayers[0].name;
        else
            toCpy = gSaveBlock2Ptr->playerName;
        break;
    case B_POSITION_PLAYER_RIGHT:
        if (((gBattleTypeFlags & BATTLE_TYPE_RECORDED) && !(gBattleTypeFlags & (BATTLE_TYPE_MULTI | BATTLE_TYPE_INGAME_PARTNER)))
            || gTestRunnerEnabled)
        {
            toCpy = gLinkPlayers[0].name;
        }
        else if ((gBattleTypeFlags & BATTLE_TYPE_LINK) && gBattleTypeFlags & (BATTLE_TYPE_RECORDED | BATTLE_TYPE_MULTI))
        {
            toCpy = gLinkPlayers[2].name;
        }
        else if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
        {
            GetFrontierTrainerName(text, gPartnerTrainerId);
            toCpy = text;
        }
        else
        {
            toCpy = gSaveBlock2Ptr->playerName;
        }
        break;
    default:
        break;
    }

    return toCpy;
}

static const u8 *BattleStringGetTrainerName(u8 *text, u8 multiplayerId, enum BattlerId battler)
{
    if (IsOnPlayerSide(battler))
        return BattleStringGetPlayerName(text, battler);
    else
        return BattleStringGetOpponentName(text, multiplayerId, battler);
}

static const u8 *BattleStringGetOpponentClassByTrainerId(u16 trainerId)
{
    const u8 *toCpy;

    if (gBattleTypeFlags & BATTLE_TYPE_SECRET_BASE)
        toCpy = gTrainerClasses[GetSecretBaseTrainerClass()].name;
    else if (trainerId == TRAINER_UNION_ROOM)
        toCpy = gTrainerClasses[GetUnionRoomTrainerClass()].name;
    else if (trainerId == TRAINER_FRONTIER_BRAIN)
        toCpy = gTrainerClasses[GetFrontierBrainTrainerClass()].name;
    else if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
        toCpy = gTrainerClasses[GetFrontierOpponentClass(trainerId)].name;
    else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_TOWER && gMapHeader.regionMapSectionId == MAPSEC_TRAINER_TOWER_2)
        toCpy = gTrainerClasses[GetTrainerTowerOpponentClass()].name;
    else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
        toCpy = gTrainerClasses[GetTrainerHillOpponentClass(trainerId)].name;
    else if (gBattleTypeFlags & BATTLE_TYPE_EREADER_TRAINER)
        toCpy = gTrainerClasses[GetEreaderTrainerClassId()].name;
    else if (trainerId == TRAINER_LINK_OPPONENT)
        toCpy = gTrainerClasses[TRAINER_NONE].name;
    else
        toCpy = gTrainerClasses[GetTrainerClassFromId(trainerId)].name;

    return toCpy;
}

// Ensure the defined length for an item name can contain the full defined length of a berry name.
// This ensures that custom Enigma Berry names will fit in the text buffer at the top of BattleStringExpandPlaceholders.
STATIC_ASSERT(BERRY_NAME_LENGTH + ARRAY_COUNT(sText_BerrySuffix) <= ITEM_NAME_LENGTH, BerryNameTooLong);

u32 BattleStringExpandPlaceholders(const u8 *src, u8 *dst, u32 dstSize)
{
    u32 dstID = 0; // if they used dstID, why not use srcID as well?
    const u8 *toCpy = NULL;
    u8 text[max(max(max(32, TRAINER_NAME_LENGTH + 1), POKEMON_NAME_LENGTH + 1), ITEM_NAME_LENGTH)];
    u8 *textStart = &text[0];
    u8 multiplayerId;
    u8 fontId = FONT_NORMAL;

    if (gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
        multiplayerId = gRecordedBattleMultiplayerId;
    else
        multiplayerId = GetMultiplayerId();

    // Clear destination first
    while (dstID < dstSize)
    {
        dst[dstID] = EOS;
        dstID++;
    }

    dstID = 0;
    while (*src != EOS)
    {
        toCpy = NULL;

        if (*src == PLACEHOLDER_BEGIN)
        {
            src++;
            u32 classLength = 0;
            u32 nameLength = 0;
            const u8 *classString;
            const u8 *nameString;
            switch (*src)
            {
            case B_TXT_BUFF1:
                if (gBattleTextBuff1[0] == B_BUFF_PLACEHOLDER_BEGIN)
                {
                    ExpandBattleTextBuffPlaceholders(gBattleTextBuff1, gStringVar1);
                    toCpy = gStringVar1;
                }
                else
                {
                    toCpy = TryGetStatusString(gBattleTextBuff1);
                    if (toCpy == NULL)
                        toCpy = gBattleTextBuff1;
                }
                break;
            case B_TXT_BUFF2:
                if (gBattleTextBuff2[0] == B_BUFF_PLACEHOLDER_BEGIN)
                {
                    ExpandBattleTextBuffPlaceholders(gBattleTextBuff2, gStringVar2);
                    toCpy = gStringVar2;
                }
                else
                {
                    toCpy = gBattleTextBuff2;
                }
                break;
            case B_TXT_BUFF3:
                if (gBattleTextBuff3[0] == B_BUFF_PLACEHOLDER_BEGIN)
                {
                    ExpandBattleTextBuffPlaceholders(gBattleTextBuff3, gStringVar3);
                    toCpy = gStringVar3;
                }
                else
                {
                    toCpy = gBattleTextBuff3;
                }
                break;
            case B_TXT_COPY_VAR_1:
                toCpy = gStringVar1;
                break;
            case B_TXT_COPY_VAR_2:
                toCpy = gStringVar2;
                break;
            case B_TXT_COPY_VAR_3:
                toCpy = gStringVar3;
                break;
            case B_TXT_PLAYER_MON1_NAME: // first player poke name
                GetBattlerNick(GetBattlerAtPosition(B_POSITION_PLAYER_LEFT), text);
                toCpy = text;
                break;
            case B_TXT_OPPONENT_MON1_NAME: // first enemy poke name
                GetBattlerNick(GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), text);
                toCpy = text;
                break;
            case B_TXT_PLAYER_MON2_NAME: // second player poke name
                GetBattlerNick(GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT), text);
                toCpy = text;
                break;
            case B_TXT_OPPONENT_MON2_NAME: // second enemy poke name
                GetBattlerNick(GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT), text);
                toCpy = text;
                break;
            case B_TXT_LINK_PLAYER_MON1_NAME: // link first player poke name
                GetBattlerNick(GetBattlerAtPosition(B_POSITION_PLAYER_LEFT), text);
                toCpy = text;
                break;
            case B_TXT_LINK_OPPONENT_MON1_NAME: // link first opponent poke name
                GetBattlerNick(GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), text);
                toCpy = text;
                break;
            case B_TXT_LINK_PLAYER_MON2_NAME: // link second player poke name
                GetBattlerNick(GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT), text);
                toCpy = text;
                break;
            case B_TXT_LINK_OPPONENT_MON2_NAME: // link second opponent poke name
                GetBattlerNick(GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT), text);
                toCpy = text;
                break;
            case B_TXT_ATK_NAME_WITH_PREFIX_MON1: // Unused, to change into sth else.
                break;
            case B_TXT_ATK_PARTNER_NAME: // attacker partner name
                GetBattlerNick(GetPartnerBattler(gBattlerAttacker), text);
                toCpy = text;
                break;
            case B_TXT_ATK_NAME_WITH_PREFIX: // attacker name with prefix
                HANDLE_NICKNAME_STRING_CASE(gBattlerAttacker)
                break;
            case B_TXT_DEF_NAME_WITH_PREFIX: // target name with prefix
                HANDLE_NICKNAME_STRING_CASE(gBattlerTarget)
                break;
            case B_TXT_DEF_NAME: // target name
                GetBattlerNick(gBattlerTarget, text);
                toCpy = text;
                break;
            case B_TXT_DEF_PARTNER_NAME: // partner target name
                GetBattlerNick(GetPartnerBattler(gBattlerTarget), text);
                toCpy = text;
                break;
            case B_TXT_EFF_NAME_WITH_PREFIX: // effect battler name with prefix
                HANDLE_NICKNAME_STRING_CASE(gEffectBattler)
                break;
            case B_TXT_SCR_ACTIVE_NAME_WITH_PREFIX: // scripting active battler name with prefix
                HANDLE_NICKNAME_STRING_CASE(gBattleScripting.battler)
                break;
            case B_TXT_CURRENT_MOVE: // current move name
                if (gBattleMsgDataPtr->currentMove >= MOVES_COUNT
                 && !IsZMove(gBattleMsgDataPtr->currentMove)
                 && !IsMaxMove(gBattleMsgDataPtr->currentMove))
                    toCpy = gTypesInfo[gBattleStruct->stringMoveType].generic;
                else
                    toCpy = GetMoveName(gBattleMsgDataPtr->currentMove);
                break;
            case B_TXT_LAST_MOVE: // originally used move name
                if (gBattleMsgDataPtr->originallyUsedMove >= MOVES_COUNT
                 && !IsZMove(gBattleMsgDataPtr->currentMove)
                 && !IsMaxMove(gBattleMsgDataPtr->currentMove))
                    toCpy = gTypesInfo[gBattleStruct->stringMoveType].generic;
                else
                    toCpy = GetMoveName(gBattleMsgDataPtr->originallyUsedMove);
                break;
            case B_TXT_LAST_ITEM: // last used item
                if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
                {
                    if (gLastUsedItem == ITEM_ENIGMA_BERRY_E_READER)
                    {
                        if (!(gBattleTypeFlags & BATTLE_TYPE_MULTI))
                        {
                            if ((gBattleScripting.multiplayerId != 0 && (gPotentialItemEffectBattler & BIT_SIDE))
                                || (gBattleScripting.multiplayerId == 0 && !(gPotentialItemEffectBattler & BIT_SIDE)))
                            {
                                StringCopy(text, gEnigmaBerries[gPotentialItemEffectBattler].name);
                                StringAppend(text, sText_BerrySuffix);
                                toCpy = text;
                            }
                            else
                            {
                                toCpy = sText_EnigmaBerry;
                            }
                        }
                        else
                        {
                            if (gLinkPlayers[gBattleScripting.multiplayerId].id == gPotentialItemEffectBattler)
                            {
                                StringCopy(text, gEnigmaBerries[gPotentialItemEffectBattler].name);
                                StringAppend(text, sText_BerrySuffix);
                                toCpy = text;
                            }
                            else
                            {
                                toCpy = sText_EnigmaBerry;
                            }
                        }
                    }
                    else
                    {
                        CopyItemName(gLastUsedItem, text);
                        toCpy = text;
                    }
                }
                else
                {
                    CopyItemName(gLastUsedItem, text);
                    toCpy = text;
                }
                break;
            case B_TXT_LAST_ABILITY: // last used ability
                toCpy = gAbilitiesInfo[gLastUsedAbility].name;
                break;
            case B_TXT_ATK_ABILITY: // attacker ability
                toCpy = gAbilitiesInfo[sBattlerAbilities[gBattlerAttacker]].name;
                break;
            case B_TXT_DEF_ABILITY: // target ability
                toCpy = gAbilitiesInfo[sBattlerAbilities[gBattlerTarget]].name;
                break;
            case B_TXT_SCR_ACTIVE_ABILITY: // scripting active ability
                toCpy = gAbilitiesInfo[sBattlerAbilities[gBattleScripting.battler]].name;
                break;
            case B_TXT_EFF_ABILITY: // effect battler ability
                toCpy = gAbilitiesInfo[sBattlerAbilities[gEffectBattler]].name;
                break;
            case B_TXT_TRAINER1_CLASS: // trainer class name
                toCpy = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentA);
                break;
            case B_TXT_TRAINER1_NAME: // trainer1 name
                toCpy = BattleStringGetOpponentNameByTrainerId(TRAINER_BATTLE_PARAM.opponentA, text, multiplayerId, GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT));
                break;
            case B_TXT_TRAINER1_NAME_WITH_CLASS: // trainer1 name with trainer class
                toCpy = textStart;
                classString = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentA);
                while (classString[classLength] != EOS)
                {
                    textStart[classLength] = classString[classLength];
                    classLength++;
                }
                textStart[classLength] = CHAR_SPACE;
                textStart += classLength + 1;
                nameString = BattleStringGetOpponentNameByTrainerId(TRAINER_BATTLE_PARAM.opponentA, textStart, multiplayerId, GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT));
                if (nameString != textStart)
                {
                    while (nameString[nameLength] != EOS)
                    {
                        textStart[nameLength] = nameString[nameLength];
                        nameLength++;
                    }
                    textStart[nameLength] = EOS;
                }
                break;
            case B_TXT_LINK_PLAYER_NAME: // link player name
                toCpy = gLinkPlayers[multiplayerId].name;
                break;
            case B_TXT_LINK_PARTNER_NAME: // link partner name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(GetPartnerPosition(gLinkPlayers[multiplayerId].id))].name;
                break;
            case B_TXT_LINK_OPPONENT1_NAME: // link opponent 1 name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(GetBattlerLeftFoe(gLinkPlayers[multiplayerId].id))].name;
                break;
            case B_TXT_LINK_OPPONENT2_NAME: // link opponent 2 name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(GetBattlerRightFoe(gLinkPlayers[multiplayerId].id))].name;
                break;
            case B_TXT_LINK_SCR_TRAINER_NAME: // link scripting active name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(gBattleScripting.battler)].name;
                break;
            case B_TXT_PLAYER_NAME: // player name
                toCpy = BattleStringGetPlayerName(text, GetBattlerAtPosition(B_POSITION_PLAYER_LEFT));
                break;
            case B_TXT_TRAINER1_LOSE_TEXT: // trainerA lose text
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_WON_TEXT, TRAINER_BATTLE_PARAM.opponentA);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_TOWER && gMapHeader.regionMapSectionId == MAPSEC_TRAINER_TOWER_2)
                {
                    GetTrainerTowerOpponentLoseText(gStringVar4, 0);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_WON, TRAINER_BATTLE_PARAM.opponentA);
                    toCpy = gStringVar4;
                }
                else
                {
                    toCpy = GetTrainerALoseText();
                }
                break;
            case B_TXT_TRAINER1_WIN_TEXT: // trainerA win text
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_LOST_TEXT, TRAINER_BATTLE_PARAM.opponentA);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_TOWER && gMapHeader.regionMapSectionId == MAPSEC_TRAINER_TOWER_2)
                {
                    GetTrainerTowerOpponentWinText(gStringVar4, 0);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_LOST, TRAINER_BATTLE_PARAM.opponentA);
                    toCpy = gStringVar4;
                }
                else
                {
                    toCpy = GetTrainerWonSpeech();
                }
                break;
            case B_TXT_26: // ?
                if (!IsOnPlayerSide(gBattleScripting.battler))
                {
                    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
                        toCpy = sText_FoePkmnPrefix;
                    else
                        toCpy = sText_WildPkmnPrefix;
                    while (*toCpy != EOS)
                    {
                        dst[dstID] = *toCpy;
                        dstID++;
                        toCpy++;
                    }
                }
                GetMonData(&GetBattlerParty(gBattleScripting.battler)[gBattleStruct->scriptPartyIdx], MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_PC_CREATOR_NAME: // lanette pc
                if (FlagGet(FLAG_SYS_PC_LANETTE))
                    toCpy = IS_FRLG ? sText_Bills : sText_Lanettes;
                else
                    toCpy = sText_Someones;
                break;
            case B_TXT_ATK_PREFIX2:
                if (IsOnPlayerSide(gBattlerAttacker))
                    toCpy = sText_AllyPkmnPrefix2;
                else
                    toCpy = sText_FoePkmnPrefix3;
                break;
            case B_TXT_DEF_PREFIX2:
                if (IsOnPlayerSide(gBattlerTarget))
                    toCpy = sText_AllyPkmnPrefix2;
                else
                    toCpy = sText_FoePkmnPrefix3;
                break;
            case B_TXT_ATK_PREFIX1:
                if (IsOnPlayerSide(gBattlerAttacker))
                    toCpy = sText_AllyPkmnPrefix;
                else
                    toCpy = sText_FoePkmnPrefix2;
                break;
            case B_TXT_DEF_PREFIX1:
                if (IsOnPlayerSide(gBattlerTarget))
                    toCpy = sText_AllyPkmnPrefix;
                else
                    toCpy = sText_FoePkmnPrefix2;
                break;
            case B_TXT_ATK_PREFIX3:
                if (IsOnPlayerSide(gBattlerAttacker))
                    toCpy = sText_AllyPkmnPrefix3;
                else
                    toCpy = sText_FoePkmnPrefix4;
                break;
            case B_TXT_DEF_PREFIX3:
                if (IsOnPlayerSide(gBattlerTarget))
                    toCpy = sText_AllyPkmnPrefix3;
                else
                    toCpy = sText_FoePkmnPrefix4;
                break;
            case B_TXT_TRAINER2_CLASS:
                toCpy = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentB);
                break;
            case B_TXT_TRAINER2_NAME:
                toCpy = BattleStringGetOpponentNameByTrainerId(TRAINER_BATTLE_PARAM.opponentB, text, multiplayerId, GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT));
                break;
            case B_TXT_TRAINER2_NAME_WITH_CLASS:
                toCpy = textStart;
                classString = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentB);
                while (classString[classLength] != EOS)
                {
                    textStart[classLength] = classString[classLength];
                    classLength++;
                }
                textStart[classLength] = CHAR_SPACE;
                textStart += classLength + 1;
                nameString = BattleStringGetOpponentNameByTrainerId(TRAINER_BATTLE_PARAM.opponentB, textStart, multiplayerId, GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT));
                if (nameString != textStart)
                {
                    while (nameString[nameLength] != EOS)
                    {
                        textStart[nameLength] = nameString[nameLength];
                        nameLength++;
                    }
                    textStart[nameLength] = EOS;
                }
                break;
            case B_TXT_TRAINER2_LOSE_TEXT:
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_WON_TEXT, TRAINER_BATTLE_PARAM.opponentB);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_TOWER && gMapHeader.regionMapSectionId == MAPSEC_TRAINER_TOWER_2)
                {
                    GetTrainerTowerOpponentLoseText(gStringVar4, 1);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_WON, TRAINER_BATTLE_PARAM.opponentB);
                    toCpy = gStringVar4;
                }
                else
                {
                    toCpy = GetTrainerBLoseText();
                }
                break;
            case B_TXT_TRAINER2_WIN_TEXT:
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_LOST_TEXT, TRAINER_BATTLE_PARAM.opponentB);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_TOWER && gMapHeader.regionMapSectionId == MAPSEC_TRAINER_TOWER_2)
                {
                    GetTrainerTowerOpponentWinText(gStringVar4, 1);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_LOST, TRAINER_BATTLE_PARAM.opponentB);
                    toCpy = gStringVar4;
                }
                break;
            case B_TXT_PARTNER_CLASS:
                toCpy = gTrainerClasses[GetFrontierOpponentClass(gPartnerTrainerId)].name;
                break;
            case B_TXT_PARTNER_NAME:
                toCpy = BattleStringGetPlayerName(text, GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT));
                break;
            case B_TXT_PARTNER_NAME_WITH_CLASS:
                toCpy = textStart;
                classString = gTrainerClasses[GetFrontierOpponentClass(gPartnerTrainerId)].name;
                while (classString[classLength] != EOS)
                {
                    textStart[classLength] = classString[classLength];
                    classLength++;
                }
                textStart[classLength] = CHAR_SPACE;
                textStart += classLength + 1;
                nameString = BattleStringGetPlayerName(textStart, GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT));
                if (nameString != textStart)
                {
                    while (nameString[nameLength] != EOS)
                    {
                        textStart[nameLength] = nameString[nameLength];
                        nameLength++;
                    }
                    textStart[nameLength] = EOS;
                }
                break;
            case B_TXT_ATK_TRAINER_NAME:
                toCpy = BattleStringGetTrainerName(text, multiplayerId, gBattlerAttacker);
                break;
            case B_TXT_ATK_TRAINER_CLASS:
                switch (GetBattlerPosition(gBattlerAttacker))
                {
                case B_POSITION_PLAYER_RIGHT:
                    if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
                        toCpy = gTrainerClasses[GetFrontierOpponentClass(gPartnerTrainerId)].name;
                    break;
                case B_POSITION_OPPONENT_LEFT:
                    toCpy = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentA);
                    break;
                case B_POSITION_OPPONENT_RIGHT:
                    if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS && !BATTLE_TWO_VS_ONE_OPPONENT)
                        toCpy = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentB);
                    else
                        toCpy = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentA);
                    break;
                default:
                    break;
                }
                break;
            case B_TXT_ATK_TRAINER_NAME_WITH_CLASS:
                toCpy = textStart;
                if (gBattleTypeFlags & BATTLE_TYPE_CATCH_TUTORIAL)
                {
                    if (IS_FRLG)
                        textStart = StringCopy(textStart, COMPOUND_STRING("El anciano"));
                    else
                        textStart = StringCopy(textStart, COMPOUND_STRING("WALLY"));
                }
                else if (GetBattlerPosition(gBattlerAttacker) == B_POSITION_PLAYER_LEFT)
                {
                    textStart = StringCopy(textStart, BattleStringGetTrainerName(textStart, multiplayerId, gBattlerAttacker));
                }
                else
                {
                    classString = NULL;
                    switch (GetBattlerPosition(gBattlerAttacker))
                    {
                    case B_POSITION_PLAYER_RIGHT:
                        if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
                            classString = gTrainerClasses[GetFrontierOpponentClass(gPartnerTrainerId)].name;
                        break;
                    case B_POSITION_OPPONENT_LEFT:
                        classString = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentA);
                        break;
                    case B_POSITION_OPPONENT_RIGHT:
                        if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS && !BATTLE_TWO_VS_ONE_OPPONENT)
                            classString = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentB);
                        else
                            classString = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentA);
                        break;
                    default:
                        break;
                    }
                    classLength = 0;
                    nameLength = 0;
                    while (classString[classLength] != EOS)
                    {
                        textStart[classLength] = classString[classLength];
                        classLength++;
                    }
                    textStart[classLength] = CHAR_SPACE;
                    textStart += 1 + classLength;
                    nameString = BattleStringGetTrainerName(textStart, multiplayerId, gBattlerAttacker);
                    if (nameString != textStart)
                    {
                        while (nameString[nameLength] != EOS)
                        {
                            textStart[nameLength] = nameString[nameLength];
                            nameLength++;
                        }
                        textStart[nameLength] = EOS;
                    }
                }
                break;
            case B_TXT_ATK_TEAM1:
                if (IsOnPlayerSide(gBattlerAttacker))
                    toCpy = sText_Your1;
                else
                    toCpy = sText_Opposing1;
                break;
            case B_TXT_ATK_TEAM2:
                if (IsOnPlayerSide(gBattlerAttacker))
                    toCpy = sText_Your2;
                else
                    toCpy = sText_Opposing2;
                break;
            case B_TXT_DEF_TEAM1:
                if (IsOnPlayerSide(gBattlerTarget))
                    toCpy = sText_Your1;
                else
                    toCpy = sText_Opposing1;
                break;
            case B_TXT_DEF_TEAM2:
                if (IsOnPlayerSide(gBattlerTarget))
                    toCpy = sText_Your2;
                else
                    toCpy = sText_Opposing2;
                break;
            case B_TXT_EFF_TEAM1:
                if (IsOnPlayerSide(gEffectBattler))
                    toCpy = sText_Your1;
                else
                    toCpy = sText_Opposing1;
                break;
            case B_TXT_EFF_TEAM2:
                if (IsOnPlayerSide(gEffectBattler))
                    toCpy = sText_Your2;
                else
                    toCpy = sText_Opposing2;
                break;
            case B_TXT_ATK_NAME_WITH_PREFIX2:
                HANDLE_NICKNAME_STRING_LOWERCASE(gBattlerAttacker)
                break;
            case B_TXT_DEF_NAME_WITH_PREFIX2:
                HANDLE_NICKNAME_STRING_LOWERCASE(gBattlerTarget)
                break;
            case B_TXT_EFF_NAME_WITH_PREFIX2:
                HANDLE_NICKNAME_STRING_LOWERCASE(gEffectBattler)
                break;
            case B_TXT_SCR_ACTIVE_NAME_WITH_PREFIX2:
                HANDLE_NICKNAME_STRING_LOWERCASE(gBattleScripting.battler)
                break;
            }

            if (toCpy != NULL)
            {
                while (*toCpy != EOS)
                {
                    if (*toCpy == CHAR_SPACE)
                        dst[dstID] = CHAR_NBSP;
                    else
                        dst[dstID] = *toCpy;
                    dstID++;
                    toCpy++;
                }
            }

            if (*src == B_TXT_TRAINER1_LOSE_TEXT || *src == B_TXT_TRAINER2_LOSE_TEXT
                || *src == B_TXT_TRAINER1_WIN_TEXT || *src == B_TXT_TRAINER2_WIN_TEXT)
            {
                dst[dstID] = EXT_CTRL_CODE_BEGIN;
                dstID++;
                dst[dstID] = EXT_CTRL_CODE_PAUSE_UNTIL_PRESS;
                dstID++;
            }
        }
        else
        {
            dst[dstID] = *src;
            dstID++;
        }
        src++;
    }

    dst[dstID] = *src;
    dstID++;

    BreakStringAutomatic(dst, BATTLE_MSG_MAX_WIDTH, BATTLE_MSG_MAX_LINES, fontId, SHOW_SCROLL_PROMPT);

    return dstID;
}

static void IllusionNickHack(enum BattlerId battler, u32 partyId, u8 *dst)
{
    u32 id = PARTY_SIZE;
    struct Pokemon *party = GetBattlerParty(battler);
    struct Pokemon *mon = &party[partyId], *partnerMon;

    if (GetMonAbility(mon) == ABILITY_ILLUSION)
    {
        if (IsBattlerAlive(GetPartnerBattler(battler)))
            partnerMon = GetBattlerMon(GetPartnerBattler(battler));
        else
            partnerMon = mon;

        id = GetIllusionMonPartyId(party, mon, partnerMon, battler);
    }

    if (id != PARTY_SIZE)
        GetMonData(&party[id], MON_DATA_NICKNAME, dst);
    else
        GetMonData(mon, MON_DATA_NICKNAME, dst);
}

void ExpandBattleTextBuffPlaceholders(const u8 *src, u8 *dst)
{
    u32 srcID = 1;
    u32 value = 0;
    u8 nickname[POKEMON_NAME_LENGTH + 1];
    u16 hword;

    *dst = EOS;
    while (src[srcID] != B_BUFF_EOS)
    {
        switch (src[srcID])
        {
        case B_BUFF_STRING: // battle string
            hword = T1_READ_16(&src[srcID + 1]);
            StringAppend(dst, gBattleStringsTable[hword]);
            srcID += 3;
            break;
        case B_BUFF_NUMBER: // int to string
            switch (src[srcID + 1])
            {
            case 1:
                value = src[srcID + 3];
                break;
            case 2:
                value = T1_READ_16(&src[srcID + 3]);
                break;
            case 4:
                value = T1_READ_32(&src[srcID + 3]);
                break;
            }
            ConvertIntToDecimalStringN(dst, value, STR_CONV_MODE_LEFT_ALIGN, src[srcID + 2]);
            srcID += src[srcID + 1] + 3;
            break;
        case B_BUFF_MOVE: // move name
            StringAppend(dst, GetMoveName(T1_READ_16(&src[srcID + 1])));
            srcID += 3;
            break;
        case B_BUFF_TYPE: // type name
            StringAppend(dst, gTypesInfo[src[srcID + 1]].name);
            srcID += 2;
            break;
        case B_BUFF_MON_NICK_WITH_PREFIX: // poke nick with prefix
        case B_BUFF_MON_NICK_WITH_PREFIX_LOWER: // poke nick with lowercase prefix
            if (!IsOnPlayerSide(src[srcID + 1]))
            {
                if (src[srcID] == B_BUFF_MON_NICK_WITH_PREFIX_LOWER)
                {
                    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
                        StringAppend(dst, sText_FoePkmnPrefixLower);
                    else
                        StringAppend(dst, sText_WildPkmnPrefixLower);
                }
                else
                {
                    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
                        StringAppend(dst, sText_FoePkmnPrefix);
                    else
                        StringAppend(dst, sText_WildPkmnPrefix);
                }
            }
            GetMonData(&GetBattlerParty(src[srcID + 1])[src[srcID + 2]], MON_DATA_NICKNAME, nickname);
            StringGet_Nickname(nickname);
            StringAppend(dst, nickname);
            srcID += 3;
            break;
        case B_BUFF_STAT: // stats
            StringAppend(dst, gStatNamesTable[src[srcID + 1]]);
            srcID += 2;
            break;
        case B_BUFF_SPECIES: // species name
            StringCopy(dst, GetSpeciesName(T1_READ_16(&src[srcID + 1])));
            srcID += 3;
            break;
        case B_BUFF_MON_NICK: // poke nick without prefix
            if (src[srcID + 2] == gBattlerPartyIndexes[src[srcID + 1]])
            {
                GetBattlerNick(src[srcID + 1], dst);
            }
            else if (gBattleScripting.illusionNickHack) // for STRINGID_ENEMYABOUTTOSWITCHPKMN
            {
                gBattleScripting.illusionNickHack = 0;
                IllusionNickHack(src[srcID + 1], src[srcID + 2], dst);
                StringGet_Nickname(dst);
            }
            else
            {
                GetMonData(&GetBattlerParty(src[srcID + 1])[src[srcID + 2]], MON_DATA_NICKNAME, dst);
                StringGet_Nickname(dst);
            }
            srcID += 3;
            break;
        case B_BUFF_NEGATIVE_FLAVOR: // flavor table
            StringAppend(dst, gPokeblockWasTooXStringTable[src[srcID + 1]]);
            srcID += 2;
            break;
        case B_BUFF_ABILITY: // ability names
            StringAppend(dst, gAbilitiesInfo[T1_READ_16(&src[srcID + 1])].name);
            srcID += 3;
            break;
        case B_BUFF_ITEM: // item name
            hword = T1_READ_16(&src[srcID + 1]);
            if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
            {
                if (hword == ITEM_ENIGMA_BERRY_E_READER)
                {
                    if (gLinkPlayers[gBattleScripting.multiplayerId].id == gPotentialItemEffectBattler)
                    {
                        StringCopy(dst, gEnigmaBerries[gPotentialItemEffectBattler].name);
                        StringAppend(dst, sText_BerrySuffix);
                    }
                    else
                    {
                        StringAppend(dst, sText_EnigmaBerry);
                    }
                }
                else
                {
                    CopyItemName(hword, dst);
                }
            }
            else
            {
                CopyItemName(hword, dst);
            }
            srcID += 3;
            break;
        }
    }
}

void BattlePutTextOnWindow(const u8 *text, u8 windowId)
{
    const struct BattleWindowText *textInfo = sBattleTextOnWindowsInfo[gBattleScripting.windowsType];
    bool32 copyToVram;
    struct TextPrinterTemplate printerTemplate;
    u8 speed;

    if (windowId & B_WIN_COPYTOVRAM)
    {
        windowId &= ~B_WIN_COPYTOVRAM;
        copyToVram = FALSE;
    }
    else
    {
        FillWindowPixelBuffer(windowId, textInfo[windowId].fillValue);
        copyToVram = TRUE;
    }

    printerTemplate.currentChar = text;
    printerTemplate.type = WINDOW_TEXT_PRINTER;
    printerTemplate.windowId = windowId;
    printerTemplate.fontId = textInfo[windowId].fontId;
    printerTemplate.x = textInfo[windowId].x;
    printerTemplate.y = textInfo[windowId].y;
    printerTemplate.currentX = printerTemplate.x;
    printerTemplate.currentY = printerTemplate.y;
    printerTemplate.letterSpacing = textInfo[windowId].letterSpacing;
    printerTemplate.lineSpacing = textInfo[windowId].lineSpacing;
    printerTemplate.color = textInfo[windowId].color;

    if (B_WIN_MOVE_NAME_1 <= windowId && windowId <= B_WIN_MOVE_NAME_4)
    {
        // We cannot check the actual width of the window because
        // B_WIN_MOVE_NAME_1 and B_WIN_MOVE_NAME_3 are 16 wide for
        // Z-move details.
        if (gBattleStruct->zmove.viewing && windowId == B_WIN_MOVE_NAME_1)
            printerTemplate.fontId = GetFontIdToFit(text, printerTemplate.fontId, printerTemplate.letterSpacing, 16 * TILE_WIDTH);
        else
            printerTemplate.fontId = GetFontIdToFit(text, printerTemplate.fontId, printerTemplate.letterSpacing, 8 * TILE_WIDTH);
    }

    if (printerTemplate.x == 0xFF)
    {
        u32 width = GetBattleWindowTemplatePixelWidth(gBattleScripting.windowsType, windowId);
        s32 alignX = GetStringCenterAlignXOffsetWithLetterSpacing(printerTemplate.fontId, printerTemplate.currentChar, width, printerTemplate.letterSpacing);
        printerTemplate.x = printerTemplate.currentX = alignX;
    }

    if (windowId == ARENA_WIN_JUDGMENT_TEXT || windowId == B_WIN_OAK_OLD_MAN)
        gTextFlags.useAlternateDownArrow = FALSE;
    else
        gTextFlags.useAlternateDownArrow = TRUE;

    if ((gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED)) || gTestRunnerEnabled || ((gBattleTypeFlags & BATTLE_TYPE_POKEDUDE) && windowId != B_WIN_OAK_OLD_MAN))
        gTextFlags.autoScroll = TRUE;
    else
        gTextFlags.autoScroll = FALSE;

    if (windowId == B_WIN_MSG || windowId == ARENA_WIN_JUDGMENT_TEXT || windowId == B_WIN_OAK_OLD_MAN)
    {
        if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
            speed = 1;
        else if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
            speed = sRecordedBattleTextSpeeds[GetTextSpeedInRecordedBattle()];
        else
            speed = GetPlayerTextSpeedDelay();

        gTextFlags.canABSpeedUpPrint = 1;
    }
    else
    {
        speed = textInfo[windowId].speed;
        gTextFlags.canABSpeedUpPrint = 0;
    }

    AddTextPrinter(&printerTemplate, speed, NULL);

    if (copyToVram)
    {
        PutWindowTilemap(windowId);
        CopyWindowToVram(windowId, COPYWIN_FULL);
    }
}

void SetPPNumbersPaletteInMoveSelection(enum BattlerId battler)
{
    struct ChooseMoveStruct *chooseMoveStruct = (struct ChooseMoveStruct *)(&gBattleResources->bufferA[battler][4]);
    const u16 *palPtr = gPPTextPalette;
    u8 var;

    if (!gBattleStruct->zmove.viewing)
        var = GetCurrentPPToMaxPPState(chooseMoveStruct->currentPP[gMoveSelectionCursor[battler]],
                         chooseMoveStruct->maxPP[gMoveSelectionCursor[battler]]);
    else
        var = 3;

    gPlttBufferUnfaded[BG_PLTT_ID(5) + 12] = palPtr[(var * 2) + 0];
    gPlttBufferUnfaded[BG_PLTT_ID(5) + 11] = palPtr[(var * 2) + 1];

    CpuCopy16(&gPlttBufferUnfaded[BG_PLTT_ID(5) + 12], &gPlttBufferFaded[BG_PLTT_ID(5) + 12], PLTT_SIZEOF(1));
    CpuCopy16(&gPlttBufferUnfaded[BG_PLTT_ID(5) + 11], &gPlttBufferFaded[BG_PLTT_ID(5) + 11], PLTT_SIZEOF(1));
}

u8 GetCurrentPPToMaxPPState(u8 currentPP, u8 maxPP)
{
    if (maxPP == currentPP)
    {
        return 3;
    }
    else if (maxPP <= 2)
    {
        if (currentPP > 1)
            return 3;
        else
            return 2 - currentPP;
    }
    else if (maxPP <= 7)
    {
        if (currentPP > 2)
            return 3;
        else
            return 2 - currentPP;
    }
    else
    {
        if (currentPP == 0)
            return 2;
        if (currentPP <= maxPP / 4)
            return 1;
        if (currentPP > maxPP / 2)
            return 3;
    }

    return 0;
}
