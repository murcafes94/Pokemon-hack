LilycoveCity_House3_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_House3_OnTransition
	.byte 0

LilycoveCity_House3_OnTransition:
	random 4
	copyvar VAR_TEMP_1, VAR_RESULT
	end

LilycoveCity_House3_EventScript_PokefanF::
	lock
	faceplayer
	msgbox LilycoveCity_House3_Text_LearnFromMasterOfPokeblocks, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LilycoveCity_House3_EventScript_DeclinePokeblockLearn
	msgbox LilycoveCity_House3_Text_ExplainPokeblocks, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_House3_EventScript_DeclinePokeblockLearn::
	msgbox LilycoveCity_House3_Text_OhAreYouSure, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_House3_EventScript_Man::
	lock
	faceplayer
	msgbox LilycoveCity_House3_Text_HappyToHaveQuadruplets, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_House3_EventScript_GameBoyKid1::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_GameBoyKid2::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_GameBoyKid3::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_GameBoyKid4::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_WereDoingMultiBattle::
	msgbox LilycoveCity_House3_Text_GoingToWinMultiBattles, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_EventScript_WereMixingRecords::
	msgbox LilycoveCity_House3_Text_LikeMixingAtRecordCorner, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_EventScript_WereBlendingBerries::
	msgbox LilycoveCity_House3_Text_MakePokeblocksWithBerryBlender, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_EventScript_WereDoingContest::
	msgbox LilycoveCity_House3_Text_GoingToEnterContest, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_Text_LearnFromMasterOfPokeblocks:
	.string "¡Ahí va! ¿Estás viajando sin compañía?\n¡Si eres muy joven! ¡Qué valiente eres!\pSeguro que mis hijos podrían aprender\nun par de cosas de ti.\pYo soy la MAESTRA de los {POKEBLOCK}S.\pSi me pongo un poco en serio, vaya,\nhago unos {POKEBLOCK}S increíbles.\p¿Te apetece aprender un par\nde cosas de mí?$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_House3_Text_OhAreYouSure:
	.string "¿Seguro? ¿De verdad?\p¡A veces también hay que pedir\nayuda a los demás, sabes!$"
	.string ""
	.string ""

LilycoveCity_House3_Text_ExplainPokeblocks:
	.string "¡Muy bien! ¡Se ve que piensas!\nEsto va a ser un poco largo,\lasí que escucha.\p¡Atención, allá voy!\pSi te fijas, verás que los {POKEBLOCK}S\nestán clasificados según su masa.\pCuanta menos masa tengan,\nmejor es el resultado. ¡No lo olvides!\pUn buen {POKEBLOCK} tiene poca\nmasa y mucha eficacia.\pUn POKéMON puede comer más\n{POKEBLOCK}S buenos que {POKEBLOCK}S\lnormales.\pY esto es muy importante…\pSi quieres que tus {POKEBLOCK}S sean\nsuaves, usa diferentes tipos de BAYA.\pRecuerda que el tipo de BAYA influye\nen la suavidad de los {POKEBLOCK}S.\pY otra cosa más…\pCuanta más gente mezcle BAYAS,\nmás suaves serán los {POKEBLOCK}S.\pPor eso debes hablar con la gente\ny hacer {POKEBLOCK}S juntos.\pEso es todo lo que necesitas saber\npara hacer buenos {POKEBLOCK}S.\pSi todos tuvieran POKéMON cariñosos,\n{POKEBLOCK}S suaves y muchos amigos,\lel mundo sería un lugar mejor.\p¡Ánimo y no te rindas!$"
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
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

LilycoveCity_House3_Text_HappyToHaveQuadruplets:
	.string "Cuando mi mujer tuvo cuatrillizos,\ncasi me dio un ataque…\pPero ahora, cuando los veo jugar\njuntos, me siento tan feliz…$"
	.string ""
	.string ""
	.string ""

LilycoveCity_House3_Text_GoingToWinMultiBattles:
	.string "Estamos entablando COMBATES\nMÚLTIPLES y sé que voy a ganar.$"
	.string ""

LilycoveCity_House3_Text_LikeMixingAtRecordCorner:
	.string "Nos encanta mezclar cosas\nen el CENTRO de RÉCORDS.\pPero ¿qué se mezcla allí?$"
	.string ""
	.string ""

LilycoveCity_House3_Text_MakePokeblocksWithBerryBlender:
	.string "Vamos a hacer {POKEBLOCK}S buenísimos\ncon una LICUABAYAS.$"
	.string ""

LilycoveCity_House3_Text_GoingToEnterContest:
	.string "Quiero poder fardar de POKéMON, por\neso vamos a apuntarnos a un CONCURSO.$"
	.string ""
	.string ""

