@ Development-only shortcuts. Included only with DEBUG_OVERWORLD_MENU.

LegacyDebug_EventScript_Kit::
	lockall
	msgbox LegacyDebug_Text_KitConfirm, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LegacyDebug_EventScript_End
	giveitem ITEM_POKE_BALL, 20
	goto_if_eq VAR_RESULT, FALSE, LegacyDebug_EventScript_BagFull
	giveitem ITEM_POTION, 10
	goto_if_eq VAR_RESULT, FALSE, LegacyDebug_EventScript_BagFull
	giveitem ITEM_ANTIDOTE, 10
	goto_if_eq VAR_RESULT, FALSE, LegacyDebug_EventScript_BagFull
	giveitem ITEM_REPEL, 5
	goto_if_eq VAR_RESULT, FALSE, LegacyDebug_EventScript_BagFull
	msgbox LegacyDebug_Text_KitDone, MSGBOX_DEFAULT
	goto LegacyDebug_EventScript_End
LegacyDebug_EventScript_BagFull::
	msgbox LegacyDebug_Text_BagFull, MSGBOX_DEFAULT
	goto LegacyDebug_EventScript_End

LegacyDebug_EventScript_Annex::
	lockall
	goto_if_lt VAR_BIRCH_LAB_STATE, 5, LegacyDebug_EventScript_NotReady
	closemessage
	warp MAP_LITTLEROOT_TOWN_LEGACY_RESEARCH_ANNEX, 6, 8
	waitstate
	goto LegacyDebug_EventScript_End
LegacyDebug_EventScript_Route::
	lockall
	goto_if_unset FLAG_LEGACY_FIELD_ASSIGNED, LegacyDebug_EventScript_NotReady
	closemessage
	warp MAP_ROUTE102, 28, 6
	waitstate
	goto LegacyDebug_EventScript_End
LegacyDebug_EventScript_Woods::
	lockall
	goto_if_unset FLAG_LEGACY_FIELD_REPORTED, LegacyDebug_EventScript_NotReady
	goto_if_lt VAR_PETALBURG_WOODS_STATE, 1, LegacyDebug_EventScript_NotReady
	closemessage
	warp MAP_PETALBURG_WOODS, 18, 34
	waitstate
	goto LegacyDebug_EventScript_End
LegacyDebug_EventScript_Clearing::
	lockall
	goto_if_unset FLAG_LEGACY_FOREST_ASSIGNED, LegacyDebug_EventScript_NotReady
	goto_if_lt VAR_PETALBURG_WOODS_STATE, 1, LegacyDebug_EventScript_NotReady
	closemessage
	warp MAP_PETALBURG_WOODS_LEGACY_CLEARING, 11, 16
	waitstate
	goto LegacyDebug_EventScript_End
LegacyDebug_EventScript_KantoPort::
	lockall
	goto_if_unset FLAG_SYS_GAME_CLEAR, LegacyDebug_EventScript_NotReady
	closemessage
	warp MAP_LILYCOVE_CITY_HARBOR, 5, 13
	waitstate
	goto LegacyDebug_EventScript_End
LegacyDebug_EventScript_KantoStation::
	lockall
	goto_if_unset FLAG_SYS_GAME_CLEAR, LegacyDebug_EventScript_NotReady
	goto_if_unset FLAG_LEGACY_KANTO_VIRIDIAN_VISITED, LegacyDebug_EventScript_NotReady
	closemessage
	warp MAP_LEGACY_KANTO_RESEARCH_STATION, 6, 8
	waitstate
	goto LegacyDebug_EventScript_End
LegacyDebug_EventScript_KantoJournal::
	lockall
	goto_if_unset FLAG_LEGACY_KANTO_VISITED, LegacyDebug_EventScript_NotReady
	goto LegacyKanto_EventScript_Journal
LegacyDebug_EventScript_NotReady::
	msgbox LegacyDebug_Text_NotReady, MSGBOX_DEFAULT
	goto LegacyDebug_EventScript_End

LegacyDebug_EventScript_Journal::
	lockall
	goto Legacy_EventScript_ResearchJournal

LegacyDebug_EventScript_ReplayForest::
	lockall
	goto_if_unset FLAG_LEGACY_FOREST_ASSIGNED, LegacyDebug_EventScript_NotReady
	msgbox LegacyDebug_Text_ReplayConfirm, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LegacyDebug_EventScript_End
	clearflag FLAG_LEGACY_FOREST_SHROOMISH
	clearflag FLAG_LEGACY_FOREST_WURMPLE
	clearflag FLAG_LEGACY_FOREST_REPORTED
	clearflag FLAG_LEGACY_FOREST_DISTANCE
	clearflag FLAG_LEGACY_FOREST_QUIET
	msgbox LegacyDebug_Text_ReplayDone, MSGBOX_DEFAULT
LegacyDebug_EventScript_End::
	releaseall
	end

LegacyDebug_Text_KitConfirm::
	.string "PRUEBA: añadir 20 POKé BALL,\n10 POCIONES, 10 ANTÍDOTOS y 5 REPEL.\pLos objetos quedarán en tu partida\nsi guardas después de recibirlos.\p¿Quieres añadir el kit de prueba?$"
LegacyDebug_Text_KitDone::
	.string "Kit añadido. No se han modificado\nmedallas ni estados de la historia.$"
LegacyDebug_Text_BagFull::
	.string "No hay espacio para todo el kit.\pConservas lo que se pudo añadir.\nLibera espacio antes de intentarlo.$"
LegacyDebug_Text_NotReady::
	.string "Ese punto de prueba aún no está listo.\pCompleta primero sus requisitos\nen la historia de HOENN y LEGACY.$"
LegacyDebug_Text_ReplayConfirm::
	.string "PRUEBA: borrar las dos observaciones\ny el informe del claro del bosque.\pSe conservarán POOCHYENA, ZIGZAGOON\ny el resto de tu aventura.\pSi guardas, el cambio será permanente.\n¿Quieres repetir el estudio del claro?$"
LegacyDebug_Text_ReplayDone::
	.string "Estudio del claro preparado\npara repetir las dos observaciones.$"

LegacyDebug_EventScript_Pewter::
	lockall
	goto_if_unset FLAG_LEGACY_KANTO_PEWTER_VISITED, LegacyDebug_EventScript_NotReady
	closemessage
	warp MAP_LEGACY_KANTO_PEWTERCITY, 12, 18
	waitstate
	goto LegacyDebug_EventScript_End
