SootopolisCity_LotadAndSeedotHouse_MapScripts::
	.byte 0

SootopolisCity_LotadAndSeedotHouse_EventScript_SeedotBrother::
	special GetSeedotSizeRecordInfo
	lock
	faceplayer
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_PleaseShowMeBigSeedot, MSGBOX_DEFAULT
	setvar VAR_0x8009, SPECIES_SEEDOT
	chooseboxmon SELECT_PC_MON_TRADE
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, SootopolisCity_LotadAndSeedotHouse_EventScript_CancelShowSeedot
	special CompareSeedotSize
	goto_if_eq VAR_RESULT, COMPARE_SIZE_INCORRECT_SPECIES, SootopolisCity_LotadAndSeedotHouse_EventScript_NotSeedot
	goto_if_eq VAR_RESULT, COMPARE_SIZE_SMALLER, SootopolisCity_LotadAndSeedotHouse_EventScript_SmallSeedot
	goto_if_eq VAR_RESULT, COMPARE_SIZE_LARGER, SootopolisCity_LotadAndSeedotHouse_EventScript_BigSeedot
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_CancelShowSeedot::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_DontHaveBigSeedot, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_NotSeedot::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_ThatsNotSeedot, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_SmallSeedot::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_SeenBiggerSeedot, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_BigSeedot::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_GoshMightBeBiggerThanLotad, MSGBOX_DEFAULT
	giveitem ITEM_ELIXIR
	goto_if_eq VAR_RESULT, FALSE, SootopolisCity_LotadAndSeedotHouse_EventScript_NoRoomForElixir1
	closemessage
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_NoRoomForElixir1::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_BagCrammedFull1, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_LotadBrother::
	special GetLotadSizeRecordInfo
	lock
	faceplayer
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_PleaseShowMeBigLotad, MSGBOX_DEFAULT
	setvar VAR_0x8009, SPECIES_LOTAD
	chooseboxmon SELECT_PC_MON_TRADE
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, SootopolisCity_LotadAndSeedotHouse_EventScript_CancelShowLotad
	special CompareLotadSize
	goto_if_eq VAR_RESULT, COMPARE_SIZE_INCORRECT_SPECIES, SootopolisCity_LotadAndSeedotHouse_EventScript_NotLotad
	goto_if_eq VAR_RESULT, COMPARE_SIZE_SMALLER, SootopolisCity_LotadAndSeedotHouse_EventScript_SmallLotad
	goto_if_eq VAR_RESULT, COMPARE_SIZE_LARGER, SootopolisCity_LotadAndSeedotHouse_EventScript_BigLotad
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_CancelShowLotad::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_DontHaveBigLotad, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_NotLotad::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_ThatsNotLotad, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_SmallLotad::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_SeenBiggerLotad, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_BigLotad::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_WowMightBeBiggerThanSeedot, MSGBOX_DEFAULT
	giveitem ITEM_ELIXIR
	goto_if_eq VAR_RESULT, FALSE, SootopolisCity_LotadAndSeedotHouse_EventScript_NoRoomForElixir2
	closemessage
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_NoRoomForElixir2::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_BagCrammedFull2, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_SeedotSizeRecord::
	special GetSeedotSizeRecordInfo
	lockall
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_BiggestSeedotInHistory, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_LotadSizeRecord::
	special GetLotadSizeRecordInfo
	lockall
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_BiggestLotadInHistory, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_LotadAndSeedotHouse_Text_PleaseShowMeBigSeedot:
	.string "¿Conoces el POKéMON SEEDOT?\nApenas se le ve en ARRECÍPOLIS.\pPero igualmente me encanta:\ncuanto más grande, mejor.\pMi hermano pequeño dice que\nLOTAD es más grande.\p¡Qué chorrada! SEEDOT es gigantesco…\pEh… ¿Tienes un SEEDOT?\n¿Me lo puedes enseñar?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SootopolisCity_LotadAndSeedotHouse_Text_GoshMightBeBiggerThanLotad:
	.string "¡{STR_VAR_2} cm!\n¡Pues sí que es enorme!\p¡Puede que incluso sea más grandote\nque el LOTAD que vio mi hermano!\pGracias por dejarme verlo.\nToma esto como agradecimiento.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

@ Unused
SootopolisCity_LotadAndSeedotHouse_Text_ReceivedPotion1:
	.string "{PLAYER} received a POTION.$"

SootopolisCity_LotadAndSeedotHouse_Text_BagCrammedFull1:
	.string "¿Eh? ¡Pero si la MOCHILA\nestá que revienta!$"
	.string ""

SootopolisCity_LotadAndSeedotHouse_Text_SeenBiggerSeedot:
	.string "{STR_VAR_2} cm, ¿no?\pBah… He visto a un SEEDOT\nmás grande que éste.$"
	.string ""
	.string ""

SootopolisCity_LotadAndSeedotHouse_Text_ThatsNotSeedot:
	.string "Mmmm… No está nada mal,\npero no es un SEEDOT.$"
	.string ""

SootopolisCity_LotadAndSeedotHouse_Text_DontHaveBigSeedot:
	.string "¿No tienes un SEEDOT grande?\nQué mala suerte…\pSi consigues uno, ven a verme.$"
	.string ""
	.string ""
	.string ""

SootopolisCity_LotadAndSeedotHouse_Text_BiggestSeedotInHistory:
	.string "¡El mayor SEEDOT jamás visto!\n¡Un gigante de {STR_VAR_3} cm que\lpertenece a {STR_VAR_2}!\p¡Siempre es mucho mejor tener\nun SEEDOT que sea más grande\lque un LOTAD!$"
	.string ""
	.string ""
	.string ""

SootopolisCity_LotadAndSeedotHouse_Text_PleaseShowMeBigLotad:
	.string "¿Conoces el POKéMON LOTAD?\nApenas se le ve en ARRECÍPOLIS.\pPero igualmente me encanta:\ncuanto más grande, mejor.\pMi hermano mayor dice que\nSEEDOT es más grande.\p¡Qué absurdo! Todo el mundo sabe\nque LOTAD es colosal…\pEh… ¿Tienes un LOTAD?\n¿Me lo puedes enseñar?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

SootopolisCity_LotadAndSeedotHouse_Text_WowMightBeBiggerThanSeedot:
	.string "¡{STR_VAR_2} cm!\n¡Pues sí que es enorme!\p¡Puede que incluso sea más grandote\nque el SEEDOT que vio mi hermano!\pGracias por dejarme verlo.\nToma esto como agradecimiento.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

@ Unused
SootopolisCity_LotadAndSeedotHouse_Text_ReceivedPotion2:
	.string "{PLAYER} received a POTION.$"

SootopolisCity_LotadAndSeedotHouse_Text_BagCrammedFull2:
	.string "¿Eh? ¡Pero si la MOCHILA\nestá que revienta!$"
	.string ""

SootopolisCity_LotadAndSeedotHouse_Text_SeenBiggerLotad:
	.string "¿{STR_VAR_2} cm?\pBah… He visto a un LOTAD\nmás grande que éste.$"
	.string ""
	.string ""

SootopolisCity_LotadAndSeedotHouse_Text_ThatsNotLotad:
	.string "Mmmm… No está nada mal,\npero no es un LOTAD.$"
	.string ""

SootopolisCity_LotadAndSeedotHouse_Text_DontHaveBigLotad:
	.string "¿No tienes un LOTAD grande?\nQué decepción…\pSi consigues uno, ven a verme.$"
	.string ""
	.string ""
	.string ""

SootopolisCity_LotadAndSeedotHouse_Text_BiggestLotadInHistory:
	.string "¡El mayor LOTAD jamás visto!\n¡Un coloso de {STR_VAR_3} cm que\lpertenece a {STR_VAR_2}!\p¡Siempre es mucho mejor tener\nun LOTAD que sea más grande\lque un SEEDOT!$"
	.string ""
	.string ""
	.string ""

