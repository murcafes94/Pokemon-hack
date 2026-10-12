EverGrandeCity_ChampionsRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_ChampionsRoom_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_ChampionsRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_ChampionsRoom_OnFrame
	.byte 0

EverGrandeCity_ChampionsRoom_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	end

EverGrandeCity_ChampionsRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_ChampionsRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_ChampionsRoom_EventScript_PlayerTurnNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

EverGrandeCity_ChampionsRoom_OnFrame:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_ChampionsRoom_EventScript_EnterRoom
	.2byte 0

EverGrandeCity_ChampionsRoom_EventScript_EnterRoom::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp4
	waitmovement 0
	delay 40
	applymovement LOCALID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerApproachWallace
	waitmovement 0
	setvar VAR_TEMP_1, 1
	goto EverGrandeCity_ChampionsRoom_EventScript_Wallace
	releaseall
	end

EverGrandeCity_ChampionsRoom_Movement_PlayerApproachWallace:
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_EventScript_Wallace::
	playbgm MUS_ENCOUNTER_CHAMPION, FALSE
	msgbox EverGrandeCity_ChampionsRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLACE, EverGrandeCity_ChampionsRoom_Text_Defeat
	goto EverGrandeCity_ChampionsRoom_EventScript_Defeated
	end

EverGrandeCity_ChampionsRoom_EventScript_Defeated::
	playse SE_DOOR
	setmetatile 6, 1, METATILE_EliteFour_OpenDoorChampion_Frame, FALSE
	setmetatile 6, 2, METATILE_EliteFour_OpenDoorChampion_Opening, FALSE
	special DrawWholeMapView
	msgbox EverGrandeCity_ChampionsRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	closemessage
	playse SE_DOOR
	checkplayergender
	call_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic
	call_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic
	addobject LOCALID_CHAMPIONS_ROOM_RIVAL
	call EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_MayAdvice
	goto_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_BrendanAdvice
	end

EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, FALSE
	return

EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, FALSE
	return

EverGrandeCity_ChampionsRoom_EventScript_MayAdvice::
	msgbox EverGrandeCity_ChampionsRoom_Text_MayAdvice, MSGBOX_DEFAULT
	delay 40
	playse SE_PIN
	applymovement LOCALID_CHAMPIONS_ROOM_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_CHAMPIONS_ROOM_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth
	msgbox EverGrandeCity_ChampionsRoom_Text_MayItsAlreadyOver, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_BrendanAdvice::
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanAdvice, MSGBOX_DEFAULT
	delay 40
	playse SE_PIN
	applymovement LOCALID_CHAMPIONS_ROOM_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_CHAMPIONS_ROOM_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanYouveWon, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF::
	closemessage
	addobject LOCALID_CHAMPIONS_ROOM_BIRCH
	applymovement LOCALID_CHAMPIONS_ROOM_BIRCH, EverGrandeCity_ChampionsRoom_Movement_BirchArrives
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_BirchArriveRatePokedex, MSGBOX_DEFAULT
	call ProfBirch_EventScript_RatePokedex
	msgbox EverGrandeCity_ChampionsRoom_Text_BirchCongratulations, MSGBOX_DEFAULT
	applymovement LOCALID_CHAMPIONS_ROOM_WALLACE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	applymovement LOCALID_CHAMPIONS_ROOM_WALLACE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_WallaceComeWithMe, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement LOCALID_CHAMPIONS_ROOM_WALLACE, EverGrandeCity_ChampionsRoom_Movement_WallaceExitStart
	applymovement LOCALID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart
	applymovement LOCALID_CHAMPIONS_ROOM_BIRCH, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_CHAMPIONS_ROOM_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalFollows
	waitmovement 0
	delay 20
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_WallaceWaitOutside, MSGBOX_DEFAULT
	checkplayergender
	call_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_MayCongratulations
	call_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_BrendanCongratulations
	closemessage
	applymovement LOCALID_CHAMPIONS_ROOM_WALLACE, EverGrandeCity_ChampionsRoom_Movement_WallaceExit
	applymovement LOCALID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExit
	waitmovement 0
	setflag FLAG_HIDE_PETALBURG_GYM_GREETER
	warp MAP_EVER_GRANDE_CITY_HALL_OF_FAME, 7, 16
	waitstate
	releaseall
	end

EverGrandeCity_ChampionsRoom_EventScript_MayCongratulations::
	msgbox EverGrandeCity_ChampionsRoom_Text_MayCongratulations, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_BrendanCongratulations::
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanCongratulations, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer::
	applymovement LOCALID_CHAMPIONS_ROOM_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalApproachPlayer
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth::
	applymovement LOCALID_CHAMPIONS_ROOM_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalLookBackAndForth
	waitmovement 0
	return

EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart:
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Movement_PlayerExit:
	walk_up
	delay_16
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalApproachPlayer:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	walk_in_place_faster_right
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalLookBackAndForth:
	walk_in_place_faster_up
	delay_16
	walk_in_place_faster_right
	delay_16
	walk_in_place_faster_up
	delay_8
	walk_in_place_faster_right
	delay_16
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalFollows:
	walk_right
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Movement_WallaceExitStart:
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

EverGrandeCity_ChampionsRoom_Movement_WallaceExit:
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_BirchArrives:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_in_place_faster_left
	step_end

EverGrandeCity_ChampionsRoom_Text_IntroSpeech:
	.string "PLUBIO: Hola, {PLAYER}{KUN}.\pEn ARRECÍPOLIS hiciste un gran\ntrabajo. Lograste poner fin a la crisis\lsin ayuda.\pBueno…\pNo sería justo decir que no\ncontaste con ninguna ayuda.\pLo cierto es que lograste superar\nlas dificultades gracias al trabajo\len equipo con tus POKéMON.\pLos ENTRENADORES damos objetos\na nuestros POKéMON y les enseñamos\ltécnicas de lucha para fortalecerlos.\pPero también podemos aprender\nmucho de los POKéMON.\pY es ahí donde hay que demostrar\nlo lejos que se ha llegado con respecto\la otros ENTRENADORES.\p¡Por ejemplo, ahora mismo!\p¿Quién baila con más elegancia\ncon sus POKéMON en HOENN?\p¡Llegó la hora de saberlo!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

EverGrandeCity_ChampionsRoom_Text_Defeat:
	.string "Has derrotado al CAMPEÓN…\pHas hecho un trabajo magnífico.\nTu elegancia ha sido innegable,\lha rozado casi la perfección…\p¡Me inclino ante ti, {PLAYER}{KUN}!\p¡Dominas el arte de entrenar\nPOKéMON!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

EverGrandeCity_ChampionsRoom_Text_PostBattleSpeech:
	.string "PLUBIO: Esos POKéMON que has usado\nen combate…\pA veces danzaban con delicadeza,\ncomo una ligera brisa, y otras\latacaban con la furia del rayo.\pSupiste guiar a tus POKéMON con\nuna elegancia sutil y firme a la par.\p¡Tu magistral ejecución\nme ha deslumbrado incluso a mí!\pPuedes vanagloriarte de haber llegado\na la cima de la LIGA POKéMON.\pLa región de HOENN tiene el orgullo\nde proclamarte…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

EverGrandeCity_ChampionsRoom_Text_MayAdvice:
	.string "AURA: ¡{PLAYER}{KUN}!\pTe voy a dar un consejo antes de que\nte enfrentes al CAMPEÓN, ¿te parece?$"
	.string ""
	.string ""

EverGrandeCity_ChampionsRoom_Text_MayItsAlreadyOver:
	.string "AURA: ¿Eh? ¿Qué ha pasado? ¿Qué?\p{PLAYER}{KUN}…\n¿Entonces ya está?\l¿Lo has logrado?$"
	.string ""
	.string ""
	.string ""
	.string ""

EverGrandeCity_ChampionsRoom_Text_BrendanAdvice:
	.string "BRUNO: ¡{PLAYER}!\p¿Quieres que te dé algún consejo\nantes de enfrentarte al CAMPEÓN?$"
	.string ""
	.string ""

EverGrandeCity_ChampionsRoom_Text_BrendanYouveWon:
	.string "BRUNO: {PLAYER}…\pPero… ¿me estás diciendo…?\n¿Que has vencido al CAMPEÓN?$"
	.string ""
	.string ""

EverGrandeCity_ChampionsRoom_Text_BirchArriveRatePokedex:
	.string "PROF. ABEDUL: ¿Lo ves?\n¿Qué te había dicho, {RIVAL}?\p¿No te dije que no tenías que\npreocuparte por {PLAYER}{KUN}?\pSi yo lo sabía…\n{PLAYER}{KUN}, lo has logrado.\pCuando oí que habías derrotado\na tu propio padre en el GIMNASIO\lde PETALIA, vi tu potencial…\p¡Y ahora te has hecho\ncon el CAMPEONATO!\p¡Qué orgulloso estoy!\p¿Dónde tienes la POKéDEX?\nA ver, déjame ver…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

EverGrandeCity_ChampionsRoom_Text_BirchCongratulations:
	.string "PROF. ABEDUL: Pues eso, ¡felicidades!\pYa puedes entrar con orgullo\nen la última sala.$"
	.string ""
	.string ""

EverGrandeCity_ChampionsRoom_Text_WallaceComeWithMe:
	.string "PLUBIO: {PLAYER}{KUN}…\pA ver si lo digo bien…\p¡El CAMPEONATO es tuyo!\pAcompáñame…$"
	.string ""
	.string ""
	.string ""

EverGrandeCity_ChampionsRoom_Text_WallaceWaitOutside:
	.string "PLUBIO: Lo siento, pero…\psólo los ENTRENADORES que se han\nconvertido en CAMPEONES pueden pasar.\pTendrás que esperar fuera\ncon el PROF. ABEDUL.$"
	.string ""
	.string ""
	.string ""
	.string ""

EverGrandeCity_ChampionsRoom_Text_MayCongratulations:
	.string "AURA: ¿Y por qué?\pBrrrrr…\pBueno, vale, las reglas son las reglas…\p¡{PLAYER}{KUN}!\n¡Felicidades de corazón!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

EverGrandeCity_ChampionsRoom_Text_BrendanCongratulations:
	.string "BRUNO: Pero yo quiero entrar…\pEn fin, si son las reglas…\p¡{PLAYER}, adelante!\n¡Mi más sincera enhorabuena!$"
	.string ""
	.string ""
	.string ""
	.string ""

