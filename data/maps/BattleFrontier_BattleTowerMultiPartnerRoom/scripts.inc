BattleFrontier_BattleTowerMultiPartnerRoom_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattleTowerMultiPartnerRoom_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattleTowerMultiPartnerRoom_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleTowerMultiPartnerRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleTowerMultiPartnerRoom_OnFrame
	.byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_OnResume:
	pyramid_resetparty
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnTransition:
	goto_if_set FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ChosePartner
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_1
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_2
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_3
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_4
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_5
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_6
	setflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_1
	setflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_2
	tower_loadpartners
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ChosePartner::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_2, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_3, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_4, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_5, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_6, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_7, OBJ_EVENT_GFX_BOY_1
	setvar VAR_TEMP_1, 1
	setvar VAR_TEMP_3, 1
	setobjectxyperm LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, 10, 2
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnWarp:
	map_script_2 VAR_TEMP_3, 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TurnPlayerNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnFrame:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterRoom
	map_script_2 VAR_TEMP_3, 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ExitRoom
	.2byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ExitRoom::
	lockall
	setvar VAR_TEMP_3, 0
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterElevator
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterRoom::
	lockall
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterRoom
	waitmovement 0
	applymovement LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantBlockExit
	waitmovement 0
	copyobjectxytoperm LOCALID_TOWER_PARTNER_ROOM_ATTENDANT
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner, MSGBOX_DEFAULT
	special HealPlayerParty
	setvar VAR_TEMP_1, 1
	releaseall
	end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterRoom:
	walk_down
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantBlockExit:
	walk_left
	walk_in_place_faster_down
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Attendant::
	lock
	faceplayer
	message BattleFrontier_BattleTowerMultiPartnerRoom_Text_QuitLookingForPartner
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_QuitChallenge
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner2, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_QuitChallenge::
	frontier_set FRONTIER_DATA_RECORD_DISABLED, TRUE
	goto BattleFrontier_BattleTower_EventScript_WarpToLobbyLost
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterElevator::
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_ThankYouForChoosingPartner, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	opendoor 10, 1
	waitdooranim
	call BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevator
	closedoor 10, 1
	waitdooranim
	warp MAP_BATTLE_FRONTIER_BATTLE_TOWER_ELEVATOR, 1, 6
	waitstate
	releaseall
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevator::
	applymovement LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevator
	waitmovement 0
	return

@ Unused
BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevatorEast:
	applymovement LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevatorEast
	waitmovement 0
	return

@ Unused
BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevatorWest:
	applymovement LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevatorWest
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevator:
	walk_up
	walk_up
	set_invisible
	step_end

@ Functionally unused
BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevatorEast:
	walk_right
	walk_up
	set_invisible
	step_end

@ Functionally unused
BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevatorWest:
	walk_left
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner1::
	lock
	faceplayer
	setvar VAR_TEMP_2, 0
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner::
	goto_if_set FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	tower_dopartnermsg PARTNER_MSGID_INTRO
	waitmessage
	waitbuttonpress
	tower_dopartnermsg PARTNER_MSGID_MON1
	waitmessage
	waitbuttonpress
	tower_dopartnermsg PARTNER_MSGID_MON2_ASK
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	tower_dopartnermsg PARTNER_MSGID_ACCEPT
	waitmessage
	waitbuttonpress
	closemessage
	call_if_ne VAR_FACING, DIR_SOUTH, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExit
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExitSouth
	removeobject VAR_LAST_TALKED
	setflag FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_TOWER_MULTI_PARTNER_ROOM, 10, 3
	waitstate
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner::
	tower_dopartnermsg PARTNER_MSGID_REJECT
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExit::
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExit
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExitSouth::
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExitSouth
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExit:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExitSouth:
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner2::
	lock
	faceplayer
	setvar VAR_TEMP_2, 1
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner3::
	lock
	faceplayer
	setvar VAR_TEMP_2, 2
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner4::
	lock
	faceplayer
	setvar VAR_TEMP_2, 3
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner5::
	lock
	faceplayer
	setvar VAR_TEMP_2, 4
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner6::
	lock
	faceplayer
	setvar VAR_TEMP_2, 5
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner7::
	lock
	faceplayer
	setvar VAR_TEMP_2, 6
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner8::
	lock
	faceplayer
	setvar VAR_TEMP_2, 7
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner:
	.string "Búscate un compañero entre los\nENTRENADORES que hay aquí.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_QuitLookingForPartner:
	.string "¿{PLAYER}, aún no has encontrado\nun compañero para tu equipo?\p¿Qué pasa? ¿Quieres dejar de buscar\ny volver al mostrador de recepción?$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner2:
	.string "Entonces, búscate un compañero entre\nlos ENTRENADORES que hay aquí.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ThankYouForChoosingPartner::
	.string "Bien, veo que ya tienes pareja.\pTe conduciré a la SALA BATALLA\nde COMBATES MÚLTIPLES.$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Intro::
	.string "I’m {STR_VAR_1}’s no. {STR_VAR_2} apprentice.\nYou can call me {STR_VAR_3}!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Mon1::
	.string "On {STR_VAR_1}’s advice, I brought\none {STR_VAR_3} with {STR_VAR_2} and$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Mon2Ask::
	.string "one {STR_VAR_2} with {STR_VAR_1}.\p"
	.string "Please, let me join you as a tag team.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Accept::
	.string "Thank you!\nI’ll go register right now.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Reject::
	.string "I really wanted to form a tag team\n"
	.string "with you, {PLAYER}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Intro::
	.string "I am {STR_VAR_1}’s no. {STR_VAR_2} apprentice.\nMy name is {STR_VAR_3}.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Mon1::
	.string "I got advice from {STR_VAR_1} and chose\n"
	.string "one {STR_VAR_3} with {STR_VAR_2} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Mon2Ask::
	.string "one {STR_VAR_2} with {STR_VAR_1}.\pPlease, let’s form a tag team!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Accept::
	.string "Thank you very much!\nI’ll be done with registration quickly!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Reject::
	.string "{PLAYER}, I was hoping that I could\n"
	.string "partner up with you…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Intro::
	.string "Hola, me llamo {STR_VAR_3},\naprendiz n.º {STR_VAR_2} de {STR_VAR_1}.\pSnif…\p¡Lo siento!\nEs la tensión, que me hace llorar…$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Mon1::
	.string "{STR_VAR_3} me aconsejó que tuviese\nun {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Mon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\pSnif…\n¡Por favor, déjame ser tu pareja!$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Accept::
	.string "¿De verdad? ¿Me eliges a mí?\n¡Genial! ¡Alucinante! ¡Superguay!\pOh… Perdona…\nSon lágrimas de felicidad…\pVoy corriendo a registrarnos.\n¡No empieces sin mí!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Reject::
	.string "Oh, pe-pero…\nSi… ¡Buaaaaaa!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Intro::
	.string "¡Ah, hola! ¡Soy {STR_VAR_3},\naprendiz n.º {STR_VAR_2} de {STR_VAR_1}!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Mon1::
	.string "{STR_VAR_3} me recomendó un tándem.\nUn {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Mon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\n¡Y eso es lo que tengo! Genial, ¿eh?\p¿Qué me dices?\n¿Formamos el equipo invencible?$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Accept::
	.string "¡Yupi! ¡Genial!\nBueno, voy a registrarnos, ¿vale?$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Reject::
	.string "¿Y eso?…\p¡Lástima! ¡Habríamos hecho\nun buen equipo, {PLAYER}!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Intro::
	.string "¡Hola! ¡Soy {STR_VAR_3}, y {STR_VAR_1}\nme eligió como su aprendiz n.º {STR_VAR_2}!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Mon1::
	.string "Le pedí consejo a {STR_VAR_3}.\nUn {STR_VAR_2} con {STR_VAR_1}$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Mon2Ask::
	.string "y un {STR_VAR_2} con {STR_VAR_1},\nésa es mi pareja de POKéMON.\p¿Qué me dices? ¿Te interesa\nformar equipo conmigo?$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Accept::
	.string "¡Gracias! ¡No te arrepentirás!\n¡Voy a registrarnos ahora mismo!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Reject::
	.string "Como quieras, {PLAYER}, pero pocos\ncompañeros encontrarás como yo…$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Intro::
	.string "Eh… Me alegra saber que aún hay gente\ncapaz de confiar en desconocidos.\pMe llamo {STR_VAR_3}. No hace mucho,\n{STR_VAR_1} me nombró su aprendiz n.º {STR_VAR_2}.$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Mon1::
	.string "{STR_VAR_3} me dio un consejo que\nle agradeceré mientras viva.\pMi equipo de POKéMON está formado\npor un {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Mon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\nSé que es mucho pedir…\p¿Te atreves a formar tándem conmigo?$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Accept::
	.string "¿En serio? ¡Qué suerte!\n¡Es un honor que me quieras a tu lado!\l¡No pienso defraudarte!\pEsto…\n¡Voy volando a registrarnos!$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Reject::
	.string "Bueno… Quizás cambies de opinión\ncuando veas a los otros…$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Intro::
	.string "¡Hola, soy {STR_VAR_3},\naprendiz n.º {STR_VAR_2} de {STR_VAR_1}!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Mon1::
	.string "{STR_VAR_3} me dijo que lo mejor\nsería que formase este equipo:\lun {STR_VAR_2} con {STR_VAR_1}$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Mon2Ask::
	.string "y un {STR_VAR_2} que supiese\nusar {STR_VAR_1}.\pNo está mal, ¿eh?\n¿Quieres que luchemos en pareja?$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Accept::
	.string "¡Estupendo!\n¡Ahora sólo espero que no lo estropees!\lVoy a registrarnos.$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Reject::
	.string "¿Cómo? ¿Por qué me rechazas?\n¡Quizás sea lo mejor!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Intro::
	.string "Soy {STR_VAR_3}, renombrado TRIATLETA.\nMe paso todo el día corriendo,\lentrenando y practicando.\pTambién soy aprendiz de {STR_VAR_1},\nsu n.º {STR_VAR_2}, para ser exactos.$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Mon1::
	.string "{STR_VAR_3} me recomendó este equipo:\nUn {STR_VAR_2} con {STR_VAR_1}$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Mon2Ask::
	.string "y un {STR_VAR_2} con {STR_VAR_1}.\pMe he esforzado por entrenarlos bien,\ny eso que soy una persona muy ocupada.\p¿Y si nos juntamos a ver qué tal?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Accept::
	.string "¡Así me gusta! ¡Gracias!\nPrepárate, que voy a registrarnos, ¿eh?$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Reject::
	.string "¡Hice un hueco en mi agenda sólo para\nluchar contigo! ¡Me la has hecho buena!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Intro::
	.string "¡Hola!\n¿Qué te cuentas?\pSoy {STR_VAR_3}, aprendiz n.º {STR_VAR_2}\nde {STR_VAR_1}. ¡Un placer conocerte!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Mon1::
	.string "¡Oye, oye! Mira qué POKéMON\nme recomendó tener {STR_VAR_3}.\lUn {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Mon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\n¡Ni que decir tiene que los entrené yo!\p¿Qué tal si hacemos pareja?\n¡Creo que nos haríamos estrellas!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Accept::
	.string "Bien dicho, ¡nos vamos a divertir!\n¡Voy a registrarnos!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Reject::
	.string "¡Vaya, no me lo esperaba de ti!\nHay quien piensa que valgo, ¿sabes?$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Intro::
	.string "Permíteme que me presente.\nSoy {STR_VAR_3}.\pEjerzo de aprendiz n.º {STR_VAR_2} de {STR_VAR_1}.$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Mon1::
	.string "Seguí el sabio consejo de {STR_VAR_3}\ny ahora tengo en mi estupendo equipo\lun {STR_VAR_2} con {STR_VAR_1}$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Mon2Ask::
	.string "y un {STR_VAR_2} con {STR_VAR_1}.\p¡Anda, hagamos equipo!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Accept::
	.string "Oh… ¡Eso es estupendo!\n¡Prometo que daré el máximo de mí!\p¡Voy a registrarnos ahora mismo!\n¡Prepárate!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Reject::
	.string "Esperaba que dijeses que sí,\n{PLAYER}…$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Intro::
	.string "¡Eh! ¡Has venido a hablar tú conmigo!\n¡Menos mal, porque yo no me atrevía!\p¡Soy {STR_VAR_3}! ¡{STR_VAR_1} me eligió\ncomo su aprendiz n.º {STR_VAR_2}!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Mon1::
	.string "He seguido los consejo de {STR_VAR_3}.\pAhora estoy entrenando\na un {STR_VAR_2} con {STR_VAR_1}$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Mon2Ask::
	.string "y a un {STR_VAR_2} con {STR_VAR_1}.\pPor favor, concédeme el honor\nde luchar junto a ti. ¿Lo harás?$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Accept::
	.string "¡Sí! ¡Es… genial!\n¡Un millón de gracias!\l¡Voy pitando a registrarnos!$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Reject::
	.string "¡Buaaa!…\p¿No sientes remordimientos, verdad?\nSi es que encima eso te hace más guay…$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Intro::
	.string "¡Ah! ¡Yo soy el aprendiz n.º {STR_VAR_2}\nde {STR_VAR_1}!\pMe llamo {STR_VAR_3}. ¡Hola!$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Mon1::
	.string "A mí, {STR_VAR_3} me recomendó\nun {STR_VAR_2} con {STR_VAR_1}$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Mon2Ask::
	.string "y un {STR_VAR_2} con {STR_VAR_1}.\p¿Suena bien, verdad?\n¿A que te apuntas conmigo?$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Accept::
	.string "¡Perfecto!\n¡Voy a registrarnos ahora mismo!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Reject::
	.string "¡Vaya tela, {PLAYER}!\nNo te andas con rodeos, ¿eh?$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Intro::
	.string "¡Eh! ¡Dicen que soy un exagerado,\npero hoy voy a cerrar la TORRE BATALLA!\pMmm…\n¡Es una broma!\pLa gente me llama {STR_VAR_3}, \n¡y yo también, claro!\p¡Soy el aprendiz n.º 1.000\nde {STR_VAR_1}!\p¡Bueno, vale, en realidad\nsoy el n.º {STR_VAR_2}!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Mon1::
	.string "{STR_VAR_3} me dio un buen consejo.\nBusca un {STR_VAR_2} con {STR_VAR_1}$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Mon2Ask::
	.string "y un {STR_VAR_2} con {STR_VAR_1}.\n¡Tengo diez de cada!\l¡Bueno, uno de cada, quiero decir!\p¿Qué te parece?\n¿Nos ponemos a pelear juntos?$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Accept::
	.string "¡Estupendo!\n¡Voy a darte un POKéMON por enrollarte!\p¡Que es broma! Pero lo que sí es verdad\nes que voy a registrarnos, ¿vale?$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Reject::
	.string "¡Me dejas helado! ¡Sólo por eso\nvoy a destruir esta TORRE BATALLA!\p¡Naa! ¡Claro que no!$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Intro::
	.string "¡Eh, tú! ¡A mis POKéMON les gusta el mar\nporque cada día los llevo a navegar!\pSoy {STR_VAR_3}, un avezado MARINERO.\n¡No me tomes por el pito de un sereno!\pSoy el aprendiz n.º {STR_VAR_2} de {STR_VAR_1}.\n¡Ahí es nada!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Mon1::
	.string "¡Gracias a {STR_VAR_3} y sus consejos\nhe hecho un equipo sin complejos!\lUn {STR_VAR_2} con {STR_VAR_1}$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Mon2Ask::
	.string "y un {STR_VAR_2} que usa {STR_VAR_1}.\p¡Celebremos este feliz encuentro\ny luchemos codo con codo ahí dentro!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Accept::
	.string "¡Me alegra que luchemos juntos!\n¡Ahora mismo voy y nos apunto!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Reject::
	.string "¡Vaya, {PLAYER}, me dejas de piedra!\n¡Por mí puedes irte a paseo!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Intro::
	.string "¡Qué onda!\n¿Ya me ha llegado a mí la ronda?\p¡Ea, me presento! ¡Me llamo {STR_VAR_3}!\n¡Soy el aprendiz n.º {STR_VAR_2} de {STR_VAR_1}!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Mon1::
	.string "{STR_VAR_3} me dijo lo que debía buscar:\nun {STR_VAR_2} que usase {STR_VAR_1}$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Mon2Ask::
	.string "y un {STR_VAR_2} con {STR_VAR_1}.\p¡Deja de mirarme como un búho\ny anímate a formar conmigo un dúo!\p¡No veas lo bien que suena mi guitarra\ncuando otra buena la acompaña!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Accept::
	.string "¡Ay! ¡Voy a ponerme a cantar!\n¡No quepo en mí de felicidad!\p¡Pero antes de luchar,\nnos debemos registrar!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Reject::
	.string "¿{PLAYER}, de verdad me vas a rechazar?\n¡Ahora sí que voy a tener que llorar!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Intro::
	.string "¡Achís!\pOh, lo siento, tengo catarro.\nPero mis POKéMON están bien.\pMe llamo {STR_VAR_3}, aprendiz\nn.º {STR_VAR_2} de {STR_VAR_1}. ¡Achís!$"
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Mon1::
	.string "Seguí el consejo de {STR_VAR_3} y junté\nun {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Mon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\pLos entreno todos los días,\naunque llueva o nieve.\pPor eso he pillado este catarro.\n¡Achís!\pBueno, ésas son mis cartas.\n¿Te animas a combatir a mi lado?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Accept::
	.string "¡Gracias, se agradece la confianza!\n¡Achís!\l¡Voy corriendo a registrarnos!$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Reject::
	.string "Lástima, {PLAYER}…\nHabríamos hecho una buena pareja.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Intro::
	.string "¡Oh, hola!\nTodo esto me pone de los nervios.\pSoy {STR_VAR_3}, aprendiz\nn.º {STR_VAR_2} de {STR_VAR_1}.$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Mon1::
	.string "{STR_VAR_3} me aconsejó este equipo:\nun {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Mon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\pMe da un poco de reparo preguntar,\npero ¿querrías combatir a mi lado?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Accept::
	.string "¡Oh, guay, eso es genial!\n¡Espero poder estar a la altura!\pYo me encargo del papeleo.$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Reject::
	.string "¡No, por favor, no digas que no!\nYa tenía suficientes dudas sobre mí…$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Intro::
	.string "Me llamo {STR_VAR_3},\npero hay nombres peores.\p{STR_VAR_1} me hizo su aprendiz n.º {STR_VAR_2}.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Mon1::
	.string "{STR_VAR_3} me recomendó este equipo.\pComo parecía un buen consejo,\ndecidí seguirlo al pie de la letra:\ltengo un {STR_VAR_2} con {STR_VAR_1}$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Mon2Ask::
	.string "y un {STR_VAR_2} con {STR_VAR_1}.\pSi no es mucho pedir,\nme gustaría luchar a tu lado.$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Accept::
	.string "¿Me aceptas de verdad?\nMenos mal, lo hubiese pasado fatal…\p¡Pero me has aceptado!\n¡Voy corriendo a registrarnos!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Reject::
	.string "¿Mm? ¿Y se puede saber por qué no?\n¿Te piensas que tiene gracia?$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassIntro::
	.string "¡Soy {STR_VAR_1}, una CHICA!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassMon1::
	.string "Lo que tengo aquí es un {STR_VAR_2}\nque usa {STR_VAR_1} y un$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassMon2Ask::
	.string "{STR_VAR_2} que usa {STR_VAR_1}.\nEs lo que me he traído.\p¿Quieres que seamos equipo?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassAccept::
	.string "¡Muchas gracias!\n¡Voy a registrarnos!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassReject::
	.string "¿Conque no soy buena para ti?\n¡Pues que sepas que lo vas a lamentar!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterIntro::
	.string "¡Hola!\p¡Soy el JOVEN {STR_VAR_1}!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterMon1::
	.string "¿Quieres saber lo que llevo conmigo?\n¡Un {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}!\pQuieres hacer un equipo conmigo,\n¿verdad?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterAccept::
	.string "¡Lo sabía!\n¡Voy a apuntarnos ahora mismo!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterReject::
	.string "¡Qué palo! ¡Si formáramos un dúo\ntú y yo, no nos ganaría nadie!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerIntro::
	.string "¡Eco, eeeecooo!\n¡Soy el MONTAÑERO {STR_VAR_1}!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerMon1::
	.string "¿Te interesa lo que llevo?\n¡Mi {STR_VAR_2} usa {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerMon2Ask::
	.string "mi {STR_VAR_2}, {STR_VAR_1}!\pNo está mal, ¿eh?\n¿Formamos un equipo?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerAccept::
	.string "¡Jaroleri-leri-o!\n¡Voy a registrarnos antes \lde que cambies de opinión!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerReject::
	.string "Qué pena, me habría gustado\ncombatir a tu lado.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyIntro::
	.string "¡Hola!\n¡Soy la BELLA {STR_VAR_1}!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyMon1::
	.string "¿Quieres ver lo que estoy entrenando?\n¡Un {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}!\p¿Qué opinas?\n¿Los quieres en tu equipo?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyAccept::
	.string "¡Qué estupendo!\n¡No te muevas, yo voy a registrarnos!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyReject::
	.string "¡Pues qué mal!\p¡Podríamos haber hecho algo especial!$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanIntro::
	.string "¡Hola!\p¿Sabes quién soy?\n¡Soy {STR_VAR_1}, el PESCADOR!$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanMon1::
	.string "¡Tengo dos ejemplares de escándalo!\nUn {STR_VAR_2} que sabe {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanMon2Ask::
	.string "un {STR_VAR_2} que sabe {STR_VAR_1}.\pNo está mal, ¿eh?\n¿Vienes a pescar victorias conmigo?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanAccept::
	.string "¡Bien, bien!\n¡Déjalo de mi cuenta!\pVoy a registrarnos ahora mismo.$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanReject::
	.string "Lástima, éramos tal para cual…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyIntro::
	.string "Encantada de conocerte.\nSoy {STR_VAR_1}, una DAMISELA.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyMon1::
	.string "En mi maravilloso equipo tengo\nun {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\pEspero que te agraden, pues nada me\nharía más feliz que combatir a tu lado.$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyAccept::
	.string "Te estoy agradecida.\nVoy a formalizar los trámites.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyReject::
	.string "Humildemente, siento que terminarás\npor lamentar semejante decisión.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFIntro::
	.string "¡Soy {STR_VAR_1}, una TRIATLETA!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFMon1::
	.string "A ver qué tengo aquí…\n¡Un {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}!\n¡Menuda pareja!\pAhora, dime, ¿formamos un equipo?$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFAccept::
	.string "¡Perfecto!\n¡Voy corriendo a apuntarnos!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFReject::
	.string "Oh. ¡Tú y yo podríamos\nhaber hecho historia!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherIntro::
	.string "¿Qué tal?\n¡Soy el CAZABICHOS {STR_VAR_1}!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherMon1::
	.string "¡Mira lo que traigo en el morral!\n¡Un {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}!\pAsí que escucha:\n¿Qué tal si unimos fuerzas?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherAccept::
	.string "¡Te pillé!\p¡Voy volando a registrarnos!$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherReject::
	.string "¿Cómo? ¿Con los POKéMON que tengo?\n¡Ya veremos si no te arrepientes!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMIntro::
	.string "¡Hola, hola! ¡Soy {STR_VAR_1},\nun ESCOLAR con mucha escuela!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMMon1::
	.string "Ahora estoy entrenando a un\n{STR_VAR_2} que usa {STR_VAR_1}$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMMon2Ask::
	.string "y a un {STR_VAR_2}\nque usa {STR_VAR_1}.\pEnvidia, ¿eh? Bueno, si quieres,\nnos unimos para luchar…$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMAccept::
	.string "¡Bien dicho!\n¡Voy a rellenar la solicitud!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMReject::
	.string "No esperaba oír eso…\pMe hubiese gustado aprender\nalgo de ti…$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyIntro::
	.string "Tú también sabes quién soy, ¿verdad?\n¡Soy {STR_VAR_1}, un NIÑO BIEN!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyMon1::
	.string "¡Yo siempre tengo lo mejor!\n¡Un {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}!\pTe voy a dar la oportunidad\nde luchar a mi lado.$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyAccept::
	.string "¡Qué superguay!\pEspabila y prepárate mientras\nyo voy a registrarnos.$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyReject::
	.string "¿Que vas tú y me rechazas?\n¡No! ¡Te rechazo yo antes a ti!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltIntro::
	.string "¡Kiaaaaaa!\nSoy el KARATEKA {STR_VAR_1}.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltMon1::
	.string "Yo estoy luchando con\nun {STR_VAR_2} que usa {STR_VAR_1}$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltMon2Ask::
	.string "y un {STR_VAR_2} que usa {STR_VAR_1}.\p¡Venga, concédeme este honor!\n¡Combatamos codo con codo!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltAccept::
	.string "¡Kiaaaaaaa!\n¡Voy corriendo a registrarnos!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltReject::
	.string "Bien… Quizás cambies\nde opinión la próxima vez…$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFIntro::
	.string "¡Hola, caracola!\n¡Soy {STR_VAR_1}, una PLAYERA!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFMon1::
	.string "Te enseño lo que llevo.\n¡Un {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}!\n¿Me aceptas a tu lado?$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFAccept::
	.string "¡Guay!\n¡Voy ahora mismo a apuntarnos!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFReject::
	.string "¡Si hubieses dicho que sí,\ntendríamos más futuro!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacIntro::
	.string "Je, je. Hola…\nSoy la BRUJITA {STR_VAR_1}…$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacMon1::
	.string "Hoy llevo conmigo un {STR_VAR_2}\ncon {STR_VAR_1} y también un$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacMon2Ask::
	.string "{STR_VAR_2} que usa {STR_VAR_1}…\pTe lo suplico…\nFormemos un equipo…$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacAccept::
	.string "Je, je. Gracias…\nVoy por los formularios…$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacReject::
	.string "Vaya, debe de haber\nun conjuro contra mi…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMIntro::
	.string "Encantado. ¡Me llamo {STR_VAR_1},\ny soy un CRIAPOKéMON!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMMon1::
	.string "¡Tengo dos POKéMON invencibles!\n¡Un {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}!\p¿A que suena bien?\nNo te cortes y lucha a mi lado.$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMAccept::
	.string "¡Qué buena noticia!\p¡Voy a ocuparme del papeleo!$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMReject::
	.string "Con las ganas que tenía\nde luchar a tu lado…$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFIntro::
	.string "¡Hola, hola!\n¡Soy la TRIATLETA {STR_VAR_1}!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFMon1::
	.string "¿Sabes con qué compito? ¡Con\nun {STR_VAR_2} que usa {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFMon2Ask::
	.string "un {STR_VAR_2} que usa {STR_VAR_1}!\p¿Y bien?\n¿Formamos un equipo?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFAccept::
	.string "¡Estupendo!\p¡Voy volando a registrarnos!$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFReject::
	.string "Tú y yo habríamos batido récords.\nQué pena…$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMIntro::
	.string "¡Hola! ¡Me llamo {STR_VAR_1}!\n¡Soy un TRIATLETA!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMMon1::
	.string "Éstas son mis dos liebres:\n¡un {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}!\pSi nos juntamos, podemos\nganarlo todo. ¿Qué me dices?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMAccept::
	.string "¡La victoria es nuestra!\n¡Voy raudo y veloz a registrarnos!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMReject::
	.string "Estaba dispuesto a darlo todo\na tu lado…$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlIntro::
	.string "¡Soy la LUCHADORA {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlMon1::
	.string "¡He estado entrenando a\nun {STR_VAR_2} que usa {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlMon2Ask::
	.string "a un {STR_VAR_2} con {STR_VAR_1}!\p¿Formamos equipo?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlAccept::
	.string "¡Bien dicho!\pYa que tú te has decidido,\n¡yo iré a registrarnos!$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlReject::
	.string "No pierdo la esperanza, quizás\nvuelvas en otra ocasión…$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMIntro::
	.string "¡Soy un TRIATLETA\ny me llamo {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMMon1::
	.string "Yo voy al gimnasio con un {STR_VAR_2}\nque sabe usar {STR_VAR_1}$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMMon2Ask::
	.string "y con un {STR_VAR_2} con {STR_VAR_1}.\pCreo que formaríamos un buen equipo.\nTú decides…$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMAccept::
	.string "¡Lo conseguí!\p¡Voy a registrarnos ya mismo!$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMReject::
	.string "Oh, qué pena. Me había hecho ilusiones.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMIntro::
	.string "¿Yo?\n¡Soy {STR_VAR_1}, todo un PLAYERO!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMMon1::
	.string "¿Que qué tengo aquí?\nPues un {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\pAhora que lo sabes, supongo\nque querrás combatir a mi lado, ¿no?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMAccept::
	.string "¡Lo sabía!\p¡Voy a apuntarnos!\n¡Vamos a hacer algo grande!$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMReject::
	.string "Con lo fuertes que son mis POKéMON…\nCreo que te has precipitado.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristIntro::
	.string "¡A las muy buenas!\n¡Llámame GUITARRISTA {STR_VAR_1}!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristMon1::
	.string "¡Mira qué banda he formado!\n¡Un {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}!\p¿Suena bien, eh?\n¿Hacemos un dueto?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristAccept::
	.string "¡Música para mis oídos!\n¡Yo me encargo del papeleo!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristReject::
	.string "¡Vaya! ¡No reconocerías a un genio\nni aunque lo tuvieses delante!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanIntro::
	.string "Es un honor.\nSoy el CABALLERO {STR_VAR_1}.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanMon1::
	.string "Tengo dos buenos escuderos:\nun {STR_VAR_2} que usa {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanMon2Ask::
	.string "un {STR_VAR_2} que usa {STR_VAR_1}.\p¿Osarías embarcarte conmigo\nen esta arriesgada empresa?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanAccept::
	.string "Será un honor combatir a tu lado.\nDeja que yo me ocupe de la burocracia.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanReject::
	.string "Qué desafortunada elección…\pEspero con impaciencia nuestro\npróximo encuentro…$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMIntro::
	.string "Hola, soy {STR_VAR_1},\ny soy un POKéFAN.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMMon1::
	.string "Tengo un {STR_VAR_2} que sabe\nel movimiento {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p¿Te gusta lo que ofrezco?\n¿Por qué no nos unimos?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMAccept::
	.string "¡Excelente!\n¡Voy a registrarnos!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMReject::
	.string "Mis POKéMON son de lo mejor que hay…\nEs una pena que no sepas apreciarlos.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMIntro::
	.string "¡Mm!\nSoy {STR_VAR_1}, un POKéABU.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMMon1::
	.string "Los POKéMON que entreno son\nun {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p¿Te alías con un experto como yo?$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMAccept::
	.string "¡Mm!\n¡Voy a registrarnos!\l¡Espero que tengamos suerte!$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMReject::
	.string "Espero que tu elección sea la\nmás adecuada para ti…$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFIntro::
	.string "Hola, hola.\nSoy {STR_VAR_1}, una POKéABU.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFMon1::
	.string "He entrenado mis POKéMON a conciencia.\nUn {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}:\neso es lo que tengo.\p¿Querrías aliarte conmigo?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFAccept::
	.string "Bien, bien, bien.\nYo me encargo del papeleo.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFReject::
	.string "Quizás podamos formar\nun equipo la próxima vez.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerIntro::
	.string "¡Soy el DOMADRAGÓN {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerMon1::
	.string "El equipo que he entrenado es\nun {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p¡Apuesto a que te gusta!\n¿Combatimos como equipo?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerAccept::
	.string "¡Genial, voy a esforzarme de verdad!\nPrepárate, que voy a registrarnos.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerReject::
	.string "¡Te va a ser difícil encontrar a\nmejores ENTRENADORES que yo!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperIntro::
	.string "¡Soy el ORNITÓLOGO {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperMon1::
	.string "¿Que cuáles son mis POKéMON?\nUn {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p¿No te parece que haríamos\nun equipo fuera de serie?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperAccept::
	.string "¡Genial, a mí también!\n¡Yo me encargo de rellenar los papeles!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperReject::
	.string "Mis POKéMON y yo somos muy buenos.\n¡Menuda decepción!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyIntro::
	.string "¡Soy {STR_VAR_1}, un CHICO NINJA!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyMon1::
	.string "Mi equipo de POKéMON está formado por\nun {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p¡Vamos juntos a por todas!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyAccept::
	.string "¡Sí!\n¡Voy a registrarnos ahora mismo!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyReject::
	.string "¡Creo que vas a echar de menos a mis\nPOKéMON antes de lo que piensas!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyIntro::
	.string "¡Hola!\n¡Soy la DAMA PARASOL {STR_VAR_1}!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyMon1::
	.string "Haciéndome compañía están un\n{STR_VAR_2} que usa {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyMon2Ask::
	.string "un {STR_VAR_2} que usa {STR_VAR_1}.\p¿A que son preciosos?\n¿Desearías ir de la mano conmigo?$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyAccept::
	.string "¡Sabia decisión!\pVoy en volandas a registrarnos.\n¡Esperemos no fallarnos mutuamente!$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyReject::
	.string "Mis POKéMON no son sólo hermosos,\ntambién son fuertes. ¡Ignorante!…$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacIntro::
	.string "Hola. Soy {STR_VAR_1},\n¡un auténtico BICHOMANÍACO!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacMon1::
	.string "Ya tengo mis POKéMON, sí.\nUn {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}:\nno hay nada mejor allá donde busques.\p¿Vas a aprovechar esta oportunidad\núnica que te doy de combatir conmigo?$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacAccept::
	.string "¡Genial!\n¡Comprendido!\p¡No tardaré en registrarnos!$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacReject::
	.string "Con los POKéMON que he encontrado,\nno perderíamos nunca…$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorIntro::
	.string "¡Echa el ancla!\n¡Soy el MARINERO {STR_VAR_1}!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorMon1::
	.string "¡Déjame mostrarte mi mercancía!\n¡Un {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}!\p¿Zarpamos juntos hacia la victoria?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorAccept::
	.string "¡Bien dicho!\n¡Voy ahora mismo a registrarnos!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorReject::
	.string "Has tirado por la borda una\nbuena oportunidad, ¡no lo olvides!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorIntro::
	.string "Hola, me llamo {STR_VAR_1}.\nSoy un POKéCOLECTOR.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorMon1::
	.string "Las joyas de mi colección son\nmi {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorMon2Ask::
	.string "mi {STR_VAR_2} con {STR_VAR_1}.\p¿Brillantes, eh?\nDeberíamos formar un equipo.$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorAccept::
	.string "¡Maravilloso!\pVenga, no perdamos tiempo.\nVoy a registrarnos.$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorReject::
	.string "Pues que sepas que has perdido\nuna ocasión de oro.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMIntro::
	.string "¡Choca ésa! ¡Me llamo {STR_VAR_1}!\nSoy un POKéGUARDA.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMMon1::
	.string "Tengo a mi cargo un\n{STR_VAR_2} que usa {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\pPor poco que tengas tú, seguro\nque podemos hacer un buen equipo.$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMAccept::
	.string "¡Así se habla!\n¡Déjame encargarme del registro!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMReject::
	.string "La próxima vez no te equivoques.\nElige a mis POKéMON, ¿vale?$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFIntro::
	.string "Me llamo {STR_VAR_1}.\n¡Soy una POKéGUARDA!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFMon1::
	.string "Te resumo brevemente mi equipo:\n¡un {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}!\p¿Quieres hacer piña conmigo?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFAccept::
	.string "¡Nos vamos a salir, ya verás!\n¡Yo me encargo de registrarnos!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFReject::
	.string "Espero que la próxima vez elijas\nmis POKéMON, se lo merecen.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyIntro::
	.string "Encantada. Soy {STR_VAR_1}.\nSoy una SRTA. AROMA, a mucha honra.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyMon1::
	.string "Siempre viajo con mi {STR_VAR_2},\nque usa {STR_VAR_1}, y con$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyMon2Ask::
	.string "mi {STR_VAR_2}, que usa {STR_VAR_1}.\pEspero que sean de tu agrado.\n¿Y si formamos pareja?$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyAccept::
	.string "Me halaga tu elección.\nTardaré sólo un minuto en registrarnos.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyReject::
	.string "Sería estupendo que cambiases\nde opinión para la próxima vez.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacIntro::
	.string "¿Sabes quién soy yo?\nSoy {STR_VAR_1}, ¡un RUINAMANÍACO!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacMon1::
	.string "Los POKéMON que tengo ahora son\nun {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\pIntrigante, ¿verdad?\n¿Conquistamos juntos esta torre?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacAccept::
	.string "¡Bien! ¡Alea jacta est!\nYo me ocupo de los papeles.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacReject::
	.string "Habríamos hecho un equipo cuya fama\nperduraría por los siglos de los siglos.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMIntro::
	.string "¡Soy {STR_VAR_1}, un ENTRENADOR GUAY!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMMon1::
	.string "Los POKéMON que tengo ahora a mi cargo\nson un {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\n¿Molan, eh?\pCreo que, si formamos un equipo,\nseremos la envidia de todos.$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMAccept::
	.string "¡Guay!\n¡Voy pitando a hacer el papeleo!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMReject::
	.string "Mis POKéMON te habrían flipado…$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFIntro::
	.string "¡Hola, me llamo {STR_VAR_1}!\n¡Soy una ENTRENADORA GUAY!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFMon1::
	.string "El equipo que estoy formando tiene\nun {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\pNo te quejarás, ¿verdad?\n¿A que quieres combatir a mi lado?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFAccept::
	.string "¡Bien por ese espíritu ganador!\nVoy a apuntarnos.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFReject::
	.string "Jamás creí que me rechazarías…$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacIntro::
	.string "¡Buenas!\n¡Soy {STR_VAR_1}, un POKéMANÍACO!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacMon1::
	.string "¡Estoy encantado con mi\n{STR_VAR_2} con {STR_VAR_1} y con$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacMon2Ask::
	.string "mi {STR_VAR_2} con {STR_VAR_1}!\p¡Venga, vamos!\n¡Vamos a hacer un equipo juntos!$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacAccept::
	.string "¡Bien dicho!\n¡Voy volando a registrarnos!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacReject::
	.string "¡Mis POKéMON son los mejores!\n¡No me digas que no te avisé!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerIntro::
	.string "¡Eh, hooola!\n¡Soy el FOGONERO {STR_VAR_1}!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerMon1::
	.string "Tengo una receta infalible para ganar:\n¡un {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}!\p¿Qué me dices?\n¿Formamos una piña?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerAccept::
	.string "¡Vamos a darnos una panzada de ganar!\n¡Yo me encargo de registrarnos!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerReject::
	.string "Espero que cambies de opinión\nla próxima vez que nos veamos.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperIntro::
	.string "¡Soy {STR_VAR_1}, un CAMPISTA!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperMon1::
	.string "He estado entrenando un {STR_VAR_2}\nque usa {STR_VAR_1} y un$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperMon2Ask::
	.string "{STR_VAR_2} que usa {STR_VAR_1}.\p¿Te apetece que salgamos\njuntos al campo de batalla?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperAccept::
	.string "¡Bravo!\n¡Voy corriendo a registrarnos!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperReject::
	.string "Bueno, quizás la próxima vez, ¿vale?\nEstoy deseando combatir junto a ti.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerIntro::
	.string "¡Hola! ¡Me llamo {STR_VAR_1}, y confieso\nque soy una auténtica DOMINGUERA!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerMon1::
	.string "Los POKéMON que llevo son\nun {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p¿Te interesa formar\nun equipo conmigo?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerAccept::
	.string "¿En serio? ¡Genial!\n¡Yo me encargo de los papeles!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerReject::
	.string "Bueno, no pierdo la esperanza.\nQuizás la próxima vez.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMIntro::
	.string "¡Soy {STR_VAR_1}, un MÉDIUM!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMMon1::
	.string "He establecido contacto con\nun {STR_VAR_2} que usa {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMMon2Ask::
	.string "un {STR_VAR_2} que usa {STR_VAR_1}.\p¿Quieres formar un vínculo conmigo\npara combatir juntos en el “más aquí”?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMAccept::
	.string "¡Lo sabía antes de que lo dijeses!\n¡Voy a registrarnos!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMReject::
	.string "Vaya, no me lo esperaba.\nMe han fallado mis dotes adivinatorias.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFIntro::
	.string "¡Soy {STR_VAR_1}, una MÉDIUM!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFMon1::
	.string "Un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}:\nésos son mis dos discípulos.\p¿Quieres combatir junto a mí?$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFAccept::
	.string "¡Así sea, pues!\n¡Voy a registrarnos!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFReject::
	.string "Quizás haya otra ocasión\npara unir nuestras fuerzas.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFIntro::
	.string "¡Soy {STR_VAR_1}, una ESCOLAR!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFMon1::
	.string "Un {STR_VAR_2} que usa {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFMon2Ask::
	.string "y un {STR_VAR_2} que usa {STR_VAR_1}:\nésos son mis dos POKéMON.\p¿Quieres combatir a mi lado\na ver hasta dónde llegamos?$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFAccept::
	.string "¡Ooh, muchas gracias!\n¡Voy a registrarnos ahora mismo!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFReject::
	.string "¿Me dejarás combatir junto a ti\nla próxima vez? Anda, porfa…$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFIntro::
	.string "¡Eh! ¡Me llamo {STR_VAR_1}!\n¡Soy una CRIAPOKéMON!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFMon1::
	.string "Los POKéMON que he criado son\nun {STR_VAR_2} que usa {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFMon2Ask::
	.string "un {STR_VAR_2} que usa {STR_VAR_1}.\p¿Suena interesante?\nPues ¿por qué no unimos fuerzas?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFAccept::
	.string "¡Qué genial!\n¡Deja de mi cuenta lo de registrarnos!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFReject::
	.string "Pero, entonces, cuento contigo\npara la próxima vez, ¿de acuerdo?$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFIntro::
	.string "Soy {STR_VAR_1}, y puedo decir con\norgullo que soy una POKéFAN.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFMon1::
	.string "Estoy enamorada de mis dos POKéMON:\nun {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p¿A que son dos auténticas monadas?\n¡Tú y yo tenemos que hacer un equipo!$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFAccept::
	.string "¡Qué estupendísimo!\n¡Voy a registrarnos en un plis!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFReject::
	.string "¿Cómo te atreves a hacerles ese feo\na mis POKéMON? ¡No tienes perdón!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFIntro::
	.string "Hola, soy la NADADORA {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFMon1::
	.string "Un {STR_VAR_2} que usa {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFMon2Ask::
	.string "y un {STR_VAR_2} que usa {STR_VAR_1}:\nésos son los POKéMON que entreno.\p¿Nos lanzamos a la piscina?\n¡Podemos ser la bomba!$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFAccept::
	.string "¡De cabeza, eso es!\n¡Voy corriendo a hacer el papeleo!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFReject::
	.string "¡Menudo jarro de agua fría!\n¡Bueno, la próxima vez, entonces!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMIntro::
	.string "¿Qué tal?\nSoy {STR_VAR_1}, un TRIATLETA.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMMon1::
	.string "Tengo un par de POKéMON decentes.\n¡Un {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}!\p¡Me encantaría formar un equipo\ncontigo! ¿Qué me dices?$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMAccept::
	.string "¡Estupendo!\nVoy a registrarnos, ¿vale?$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMReject::
	.string "Espero que cambies de opinión\nla próxima vez que nos veamos.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFIntro::
	.string "¡Soy la TRIATLETA {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFMon1::
	.string "Un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFMon2Ask::
	.string "otro {STR_VAR_2} que sabe usar\n{STR_VAR_1}. Ésa es mi pareja.\pNo está nada mal, ¿eh?\nHaríamos un buen equipo, ¿qué me dices?$"
	.string ""
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFAccept::
	.string "¡Ésa es la respuesta que esperaba!\n¡Un segundo, que voy a registrarnos!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFReject::
	.string "Bueno, espero que la próxima vez\nme des una oportunidad.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMIntro::
	.string "¡Hola! ¿Cómo te va?\nSoy {STR_VAR_1}, y soy un NADADOR.$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMMon1::
	.string "¡Alucina con lo que tengo!\n¡Un {STR_VAR_2} con {STR_VAR_1} y$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}!\p¿Una pareja guapa, eh?\n¡Estamos listos para formar equipo!$"
	.string ""
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMAccept::
	.string "¡Menuda oportunidad!\n¡Gracias, voy a registrarnos!$"
	.string ""

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMReject::
	.string "Si nos volvemos a ver,\nvas a decir que sí, ¿verdad?$"
	.string ""

