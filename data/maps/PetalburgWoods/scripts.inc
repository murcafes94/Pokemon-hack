PetalburgWoods_MapScripts::
	.byte 0

PetalburgWoods_EventScript_DevonResearcherLeft::
	lockall
	call PetalburgWoods_EventScript_DevonResearcherIntro
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherApproachPlayerLeft
	waitmovement 0
	msgbox PetalburgWoods_Text_HaveYouSeenShroomish, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaEntrance
	waitmovement 0
	msgbox PetalburgWoods_Text_IWasGoingToAmbushYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaApproachResearcherLeft
	waitmovement 0
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox PetalburgWoods_Text_HandOverThosePapers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherFleeToPlayerLeft
	waitmovement 0
	msgbox PetalburgWoods_Text_YouHaveToHelpMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaApproachPlayer
	waitmovement 0
	msgbox PetalburgWoods_Text_NoOneCrossesTeamAqua, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_PETALBURG_WOODS, PetalburgWoods_Text_YoureKiddingMe
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaBackOff
	waitmovement 0
	call PetalburgWoods_EventScript_DevonResearcherPostBattle
	applymovement LOCALID_PLAYER, PetalburgWoods_Movement_WatchResearcherLeave
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherExitLeft
	waitmovement 0
	goto PetalburgWoods_EventScript_RemoveDevonResearcher
	end

PetalburgWoods_EventScript_DevonResearcherRight::
	lockall
	call PetalburgWoods_EventScript_DevonResearcherIntro
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherApproachPlayerRight
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox PetalburgWoods_Text_HaveYouSeenShroomish, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaEntrance
	waitmovement 0
	msgbox PetalburgWoods_Text_IWasGoingToAmbushYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaApproachResearcherRight
	waitmovement 0
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox PetalburgWoods_Text_HandOverThosePapers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherFleeToPlayerRight
	waitmovement 0
	msgbox PetalburgWoods_Text_YouHaveToHelpMe, MSGBOX_DEFAULT
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox PetalburgWoods_Text_NoOneCrossesTeamAqua, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_PETALBURG_WOODS, PetalburgWoods_Text_YoureKiddingMe
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaBackOff
	waitmovement 0
	call PetalburgWoods_EventScript_DevonResearcherPostBattle
	applymovement LOCALID_PLAYER, PetalburgWoods_Movement_WatchResearcherLeave
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherExitRight
	waitmovement 0
	goto PetalburgWoods_EventScript_RemoveDevonResearcher
	end

PetalburgWoods_EventScript_DevonResearcherIntro::
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherLookAround
	waitmovement 0
	msgbox PetalburgWoods_Text_NotAOneToBeFound, MSGBOX_DEFAULT
	closemessage
	return

PetalburgWoods_EventScript_DevonResearcherPostBattle::
	msgbox PetalburgWoods_Text_YouveGotSomeNerve, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PETALBURG_WOODS_GRUNT, PetalburgWoods_Movement_AquaRunAway
	waitmovement 0
	removeobject LOCALID_PETALBURG_WOODS_GRUNT
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox PetalburgWoods_Text_ThatWasAwfullyClose, MSGBOX_DEFAULT
	giveitem ITEM_GREAT_BALL
	goto_if_eq VAR_RESULT, FALSE, PetalburgWoods_EventScript_BagFull
	goto PetalburgWoods_EventScript_DevonResearcherFinish
	end

PetalburgWoods_EventScript_BagFull::
	msgbox PetalburgWoods_Text_YoureLoadedWithItems, MSGBOX_DEFAULT
	goto PetalburgWoods_EventScript_DevonResearcherFinish
	end

PetalburgWoods_EventScript_DevonResearcherFinish::
	msgbox PetalburgWoods_Text_TeamAquaAfterSomethingInRustboro, MSGBOX_DEFAULT
	applymovement LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE, PetalburgWoods_Movement_DevonResearcherStartExit
	waitmovement 0
	msgbox PetalburgWoods_Text_ICantBeWastingTime, MSGBOX_DEFAULT
	closemessage
	return

PetalburgWoods_EventScript_RemoveDevonResearcher::
	removeobject LOCALID_PETALBURG_WOODS_DEVON_EMPLOYEE
	setvar VAR_PETALBURG_WOODS_STATE, 1
	releaseall
	end

PetalburgWoods_Movement_DevonResearcherLookAround:
	face_up
	delay_16
	delay_4
	face_right
	delay_16
	delay_8
	face_left
	delay_16
	delay_8
	face_down
	delay_16
	face_right
	delay_16
	delay_8
	face_up
	delay_16
	step_end

PetalburgWoods_Movement_DevonResearcherExitLeft:
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

PetalburgWoods_Movement_DevonResearcherApproachPlayerLeft:
	delay_16
	face_player
	walk_down
	walk_down
	step_end

PetalburgWoods_Movement_DevonResearcherApproachPlayerRight:
	delay_16
	face_player
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

PetalburgWoods_Movement_DevonResearcherExitRight:
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

PetalburgWoods_Movement_WatchResearcherLeave:
	delay_16
	delay_16
	walk_in_place_faster_up
	step_end

PetalburgWoods_Movement_DevonResearcherFleeToPlayerLeft:
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_in_place_faster_up
	step_end

PetalburgWoods_Movement_DevonResearcherFleeToPlayerRight:
	walk_fast_down
	walk_fast_right
	walk_in_place_faster_up
	step_end

PetalburgWoods_Movement_DevonResearcherStartExit:
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	face_up
	step_end

PetalburgWoods_Movement_AquaApproachResearcherLeft:
	walk_fast_down
	walk_fast_down
	step_end

PetalburgWoods_Movement_AquaBackOff:
	lock_facing_direction
	walk_up
	unlock_facing_direction
	step_end

PetalburgWoods_Movement_AquaRunAway:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	delay_16
	delay_16
	step_end

PetalburgWoods_Movement_AquaApproachResearcherRight:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

PetalburgWoods_Movement_AquaEntrance:
	walk_down
	walk_down
	delay_16
	delay_16
	step_end

PetalburgWoods_Movement_AquaApproachPlayer:
	walk_down
	step_end

PetalburgWoods_EventScript_Boy1::
	msgbox PetalburgWoods_Text_StayOutOfTallGrass, MSGBOX_NPC
	end

PetalburgWoods_EventScript_Boy2::
	msgbox PetalburgWoods_Text_HiddenItemsExplanation, MSGBOX_NPC
	end

PetalburgWoods_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_MIRACLE_SEED, PetalburgWoods_EventScript_ExplainMiracleSeed
	msgbox PetalburgWoods_Text_TryUsingThisItem, MSGBOX_DEFAULT
	giveitem ITEM_MIRACLE_SEED
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_MIRACLE_SEED
	release
	end

PetalburgWoods_EventScript_ExplainMiracleSeed::
	msgbox PetalburgWoods_Text_MiracleSeedExplanation, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_Sign1::
	msgbox PetalburgWoods_Text_TrainerTipsExperience, MSGBOX_SIGN
	end

PetalburgWoods_EventScript_Sign2::
	msgbox PetalburgWoods_Text_TrainerTipsPP, MSGBOX_SIGN
	end

PetalburgWoods_EventScript_Lyle::
	trainerbattle_single TRAINER_LYLE, PetalburgWoods_Text_GoBugPokemonTeam, PetalburgWoods_Text_ICouldntWin
	msgbox PetalburgWoods_Text_ImOutOfPokeBalls, MSGBOX_AUTOCLOSE
	end

PetalburgWoods_EventScript_James::
	trainerbattle_single TRAINER_JAMES_1, PetalburgWoods_Text_InstantlyPopularWithBugPokemon, PetalburgWoods_Text_CantBePopularIfILose, PetalburgWoods_EventScript_TryRegisterJames
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, PetalburgWoods_EventScript_JamesRematch
	setvar VAR_0x8004, TRAINER_JAMES_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, PetalburgWoods_EventScript_TryRegisterJames2
	msgbox PetalburgWoods_Text_PeopleRespectYou, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_TryRegisterJames::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, PetalburgWoods_EventScript_RegisterJames
	release
	end

PetalburgWoods_EventScript_RegisterJames::
	msgbox PetalburgWoods_Text_IWantRematch1, MSGBOX_DEFAULT
	register_matchcall TRAINER_JAMES_1
	release
	end

PetalburgWoods_EventScript_TryRegisterJames2::
	goto_if_set FLAG_HAS_MATCH_CALL, PetalburgWoods_EventScript_RegisterJames2
	msgbox PetalburgWoods_Text_PeopleRespectYou, MSGBOX_DEFAULT
	release
	end

PetalburgWoods_EventScript_RegisterJames2::
	msgbox PetalburgWoods_Text_IWantRematch2, MSGBOX_DEFAULT
	register_matchcall TRAINER_JAMES_1
	release
	end

PetalburgWoods_EventScript_JamesRematch::
	trainerbattle_rematch TRAINER_JAMES_1, PetalburgWoods_Text_MyPokemonHaveGrown, PetalburgWoods_Text_CantBePopularIfLose
	msgbox PetalburgWoods_Text_IveBeenTrainingHard, MSGBOX_AUTOCLOSE
	end

PetalburgWoods_Text_NotAOneToBeFound:
	.string "Mmmm…\nNi uno… No hay ni uno…$"
	.string ""

PetalburgWoods_Text_HaveYouSeenShroomish:
	.string "Hola, ¿has visto a un POKéMON\nllamado SHROOMISH por aquí?\pMe encanta ese POKéMON…$"
	.string ""
	.string ""

PetalburgWoods_Text_IWasGoingToAmbushYou:
	.string "Iba a tenderte una emboscada, pero\ntú tenías que eternizarte haciendo\lel tonto en el BOSQUE PETALIA, ¿no?\pYa me he cansado de esperar,\nasí que ¡aquí estoy!$"
	.string ""
	.string ""
	.string ""

PetalburgWoods_Text_HandOverThosePapers:
	.string "¡Tú! ¡INVESTIGADOR de DEVON!\p¡Suelta esos papeles!$"
	.string ""

PetalburgWoods_Text_YouHaveToHelpMe:
	.string "¡Aaaaaaah!\pTú entrenas POKéMON, ¿verdad?\n¡Pues entonces ayúdameeeee!$"
	.string ""
	.string ""

PetalburgWoods_Text_NoOneCrossesTeamAqua:
	.string "¿Eh? ¿Qué crees que estás haciendo?\n¿Tú vas a protegerle?\p¡Nadie que se cruce en el camino\ndel EQUIPO AQUA sale bien librado,\launque no levante dos palmos del suelo!\p¡Ven a que te dé jarabe de palo!$"
	.string ""
	.string ""
	.string ""
	.string ""

PetalburgWoods_Text_YoureKiddingMe:
	.string "¡Esto tiene que ser una broma!\n¡Eres muy fuerte!$"

PetalburgWoods_Text_YouveGotSomeNerve:
	.string "Brrrr… Hay que tener valor para\nentrometerse en los planes del EQUIPO\lAQUA… ¡Vuelve a luchar conmigo!\pBueno, eso me gustaría, pero no me\nqueda ni un POKéMON en forma…\pPues que sepas que los del EQUIPO AQUA\nestamos tras algo en CIUDAD FÉRRICA.\p¡Por hoy te perdono la vida!$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

PetalburgWoods_Text_ThatWasAwfullyClose:
	.string "Huy, huy, huy…\nCasi no lo contamos…\pGracias a ti, ese granuja no me robó\nunos papeles muy importantes.\pPara agradecerte tu ayuda quiero\ndarte esta SUPERBALL.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

PetalburgWoods_Text_TeamAquaAfterSomethingInRustboro:
	.string "¿No ha dicho ese matón del EQUIPO AQUA\nque buscaba algo en CIUDAD FÉRRICA?$"
	.string ""
	.string ""

PetalburgWoods_Text_ICantBeWastingTime:
	.string "Huy, huy, huy… ¡Esto es muy serio!\n¡No hay tiempo que perder!$"
	.string ""

PetalburgWoods_Text_YoureLoadedWithItems:
	.string "Tienes un montón de objetos.\nNo puedo darte la SUPERBALL.$"
	.string ""

PetalburgWoods_Text_GoBugPokemonTeam:
	.string "¡He atrapado un montón de POKéMON!\p¡Adelante, vosotros podéis!\n¡Vivan los POKéMON BICHO!$"
	.string ""
	.string ""

PetalburgWoods_Text_ICouldntWin:
	.string "A pesar de tener todos estos POKéMON,\nhe perdido miserablemente…$"
	.string ""

PetalburgWoods_Text_ImOutOfPokeBalls:
	.string "Como he atrapado tantísimos POKéMON,\nya no me queda ni una POKé BALL.$"
	.string ""

PetalburgWoods_Text_InstantlyPopularWithBugPokemon:
	.string "Si llevas POKéMON BICHO a la escuela,\nte haces con un club de fans.$"
	.string ""

PetalburgWoods_Text_CantBePopularIfILose:
	.string "¡Si quiero conservar mi club de fans,\nno puedo perder!$"

PetalburgWoods_Text_PeopleRespectYou:
	.string "Si tienes un POKéMON BICHO grande,\nla gente parece que te respeta más.$"
	.string ""

PetalburgWoods_Text_IWantRematch1:
	.string "¡Cuando mi POKéMON BICHO crezca,\nme tomaré la revancha!\p¡Te voy a registrar en mi POKéNAV\nya mismo!$"
	.string ""
	.string ""

PetalburgWoods_Text_IWantRematch2:
	.string "¡Cuando mi POKéMON BICHO crezca,\nme tomaré la revancha!\p¡Te voy a registrar en mi POKéNAV\nya mismo!$"
	.string ""
	.string ""

PetalburgWoods_Text_MyPokemonHaveGrown:
	.string "Mis POKéMON BICHO han evolucionado.\n¡Ahora recuperaré mi club de fans!$"
	.string ""

PetalburgWoods_Text_CantBePopularIfLose:
	.string "¡Si quiero conservar mi club de fans,\nno puedo perder!$"

PetalburgWoods_Text_IveBeenTrainingHard:
	.string "Consigues un club de fans si tus\nPOKéMON son fuertes, ¿no es así?\lPor eso me he entrenado mucho.$"
	.string ""
	.string ""

PetalburgWoods_Text_StayOutOfTallGrass:
	.string "¡Hola!\n¿Qué tal están tus POKéMON?\pSi están débiles y quieres evitar\nlos combates, aléjate de las zonas\lcon hierba alta.$"
	.string ""
	.string ""
	.string ""
	.string ""

PetalburgWoods_Text_HiddenItemsExplanation:
	.string "A veces hay cosas en el suelo,\naunque no puedas verlas.\pPor eso siempre tengo los ojos abiertos\ncuando voy de paseo.$"
	.string ""
	.string ""
	.string ""

PetalburgWoods_Text_TryUsingThisItem:
	.string "¡Cómo mola! ¡La MEDALLA del GIMNASIO\nde CIUDAD FÉRRICA!\pTú seguro que entrenas POKéMON.\nPues prueba a usar este objeto.$"
	.string ""
	.string ""
	.string ""

PetalburgWoods_Text_MiracleSeedExplanation:
	.string "Es una SEMILLA MILAGRO.\nDásela a un POKéMON para reforzar\llos movimientos de tipo PLANTA.\pPero creo que hay muchos más objetos\nque puedes dar a los POKéMON.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

PetalburgWoods_Text_TrainerTipsExperience:
	.string "PISTAS para ENTRENADORES\pCuando un POKéMON hace acto\nde presencia en un combate,\lrecibe puntos de EXPERIENCIA.\pSi quieres entrenar sin riesgos\na un POKéMON débil, ponlo al principio\lde la lista del equipo.\pEn cuanto empiece el combate,\nsustitúyelo. Así ganará puntos de\lEXPERIENCIA sin sufrir ningún daño.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

PetalburgWoods_Text_TrainerTipsPP:
	.string "PISTAS para ENTRENADORES\pAdemás de los PUNTOS de SALUD (PS),\nlos POKéMON tienen PUNTOS de PODER\l(PP), que necesitan para realizar\lmovimientos durante el combate.\pSi un POKéMON se queda sin PP,\nhay que llevarlo a un CENTRO POKéMON.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

