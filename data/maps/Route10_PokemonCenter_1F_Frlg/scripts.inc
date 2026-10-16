.equ REQUIRED_OWNED_MONS, 20

Route10_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route10_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

Route10_PokemonCenter_1F_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_ROUTE10_POKEMON_CENTER_1F
	setrespawn HEAL_LOCATION_ROUTE10
	end

Route10_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

Route10_PokemonCenter_1F_EventScript_FatMan::
	msgbox Route10_PokemonCenter_1F_Text_NuggetUselessSoldFor5000, MSGBOX_NPC
	end

Route10_PokemonCenter_1F_EventScript_Gentleman::
	msgbox Route10_PokemonCenter_1F_Text_EveryTypeStrongerThanOthers, MSGBOX_NPC
	end

Route10_PokemonCenter_1F_EventScript_Youngster::
	msgbox Route10_PokemonCenter_1F_Text_HeardGhostsHauntLavender, MSGBOX_NPC
	end

Route10_PokemonCenter_1F_EventScript_Aide::
	lock
	faceplayer
	call Route10_PokemonCenter_1F_EventScript_GetAideRequestInfo
	goto_if_set FLAG_GOT_EVERSTONE_FROM_OAKS_AIDE, Route10_PokemonCenter_1F_EventScript_AlreadyGotEverstone
	msgbox Route10_PokemonCenter_1F_Text_GiveEverstoneIfCaught20Mons, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Aide_EventScript_DeclineCheckMons
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, GetFrlgPokedexCount
	buffernumberstring STR_VAR_3, VAR_0x8006
	call Route10_PokemonCenter_1F_EventScript_GetAideRequestInfo
	goto_if_lt VAR_0x8006, REQUIRED_OWNED_MONS, Aide_EventScript_HaventCaughtEnough
	msgbox Route10_PokemonCenter_1F_Text_GreatHereYouGo
	checkitemspace ITEM_EVERSTONE
	goto_if_eq VAR_RESULT, FALSE, Aide_EventScript_NoRoomForItem
	giveitem_msg Route10_PokemonCenter_1F_Text_ReceivedEverstoneFromAide, ITEM_EVERSTONE
	setflag FLAG_GOT_EVERSTONE_FROM_OAKS_AIDE
	msgbox Route10_PokemonCenter_1F_Text_ExplainEverstone
	release
	end

Route10_PokemonCenter_1F_EventScript_AlreadyGotEverstone::
	msgbox Route10_PokemonCenter_1F_Text_ExplainEverstone
	release
	end

Route10_PokemonCenter_1F_EventScript_GetAideRequestInfo::
	buffernumberstring STR_VAR_1, REQUIRED_OWNED_MONS
	bufferitemname STR_VAR_2, ITEM_EVERSTONE
	return

Route10_PokemonCenter_1F_Text_EveryTypeStrongerThanOthers::
	.string "Los tipos de POKéMON tienen\ndistintas ventajas entre sí.\pCada tipo es fuerte contra unos\ny débil contra otros.$"
	.string ""
	.string ""
	.string ""

Route10_PokemonCenter_1F_Text_NuggetUselessSoldFor5000::
	.string "Una PEPITA no tiene ninguna utilidad.\nPor eso la vendí por ¥5000.$"
	.string ""

Route10_PokemonCenter_1F_Text_HeardGhostsHauntLavender::
	.string "Dicen que hay fantasmas\nen PUEBLO LAVANDA.$"
	.string ""

Route10_PokemonCenter_1F_Text_GiveEverstoneIfCaught20Mons::
	.string "¡Oh, {PLAYER}!\n¡Te estaba buscando!\pSoy uno de los AYUDANTES\ndel PROF. OAK.\pSi tu POKéDEX tiene datos completos\nde veinte especies, debo darte\lun premio del PROF. OAK.\pMe confió esta\nPIEDRA ETERNA.\pDime, {PLAYER}…\p¿Has reunido datos de al menos\nveinte especies de POKéMON?$"
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

Route10_PokemonCenter_1F_Text_GreatHereYouGo::
	.string "¡Genial! ¡Has tenido o capturado\n{STR_VAR_3} especies de POKéMON!\p¡Felicitaciones!\n¡Aquí tienes!$"
	.string ""
	.string ""
	.string ""

Route10_PokemonCenter_1F_Text_ReceivedEverstoneFromAide::
	.string "¡{PLAYER} recibió la PIEDRA ETERNA\ndel AYUDANTE!$"
	.string ""

Route10_PokemonCenter_1F_Text_ExplainEverstone::
	.string "Evolucionar POKéMON permite\nañadir datos a la POKéDEX.\pPero a veces quizá prefieras\nque un POKéMON no evolucione.\pEn ese caso, dale la PIEDRA ETERNA\na ese POKéMON.\pSegún el PROFESOR,\nimpedirá que evolucione.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

