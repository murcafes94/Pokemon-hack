MossdeepCity_House4_MapScripts::
	.byte 0

MossdeepCity_House4_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_SYS_GAME_CLEAR, MossdeepCity_House4_EventScript_CanBattleAtSecretBases
	msgbox MossdeepCity_House4_Text_BrotherLikesToFindBases, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House4_EventScript_CanBattleAtSecretBases::
	msgbox MossdeepCity_House4_Text_BrotherLikesToVisitBasesAndBattle, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House4_EventScript_NinjaBoy::
	lock
	faceplayer
	special CheckPlayerHasSecretBase
	goto_if_eq VAR_RESULT, FALSE, MossdeepCity_House4_EventScript_NoSecretBase
	special GetSecretBaseNearbyMapName
	msgbox MossdeepCity_House4_Text_YouMadeSecretBaseNearX, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House4_EventScript_NoSecretBase::
	msgbox MossdeepCity_House4_Text_MakeSecretBase, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House4_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox MossdeepCity_House4_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

MossdeepCity_House4_Text_BrotherLikesToFindBases:
	.string "Mi hermano pequeño dice que quiere\nencontrar las BASES SECRETAS\lde otros ENTRENADORES.$"
	.string ""

MossdeepCity_House4_Text_BrotherLikesToVisitBasesAndBattle:
	.string "Mi hermano pequeño dice que le gusta\nvisitar las BASES SECRETAS de otros\lENTRENADORES y desafiarlos.$"
	.string ""
	.string ""

MossdeepCity_House4_Text_YouMadeSecretBaseNearX:
	.string "¿Tú tienes una BASE SECRETA\nen la {STR_VAR_1}?$"
	.string ""

MossdeepCity_House4_Text_MakeSecretBase:
	.string "Deberías crear una BASE SECRETA\nen alguna parte. ¡Yo iría a buscarla!$"
	.string ""

MossdeepCity_House4_Text_Skitty:
	.string "DELCATTY: ¿Delmiau?$"

