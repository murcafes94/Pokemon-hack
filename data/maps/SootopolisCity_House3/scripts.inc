SootopolisCity_House3_MapScripts::
	.byte 0

SootopolisCity_House3_EventScript_Woman::
	lock
	faceplayer
	msgbox SootopolisCity_House3_Text_JuanHasManyFansDoYou, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SootopolisCity_House3_EventScript_HaveFans
	msgbox SootopolisCity_House3_Text_LonesomeTryWorkingHarder, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House3_EventScript_HaveFans::
	msgbox SootopolisCity_House3_Text_YouMustBePrettyStrong, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House3_EventScript_Girl::
	msgbox SootopolisCity_House3_Text_TrainerFanClubWasWild, MSGBOX_NPC
	end

SootopolisCity_House3_Text_JuanHasManyFansDoYou:
	.string "Tú entrenas POKéMON, ¿verdad?\pGALANO, de ARRECÍPOLIS, tiene muchos\nfans. ¡Más que su alumno PLUBIO!\p¿Y tú? ¿Tienes alguno?$"
	.string ""
	.string ""
	.string ""

SootopolisCity_House3_Text_YouMustBePrettyStrong:
	.string "Vaya, pues entonces debes de ser\ntremendamente fuerte…$"

SootopolisCity_House3_Text_LonesomeTryWorkingHarder:
	.string "Oh, qué pena… Todos necesitamos\nque alguien nos apoye…\pPero, si entrenas mucho, seguro\nque consigues algún fan sólo para ti.$"
	.string ""
	.string ""
	.string ""

SootopolisCity_House3_Text_TrainerFanClubWasWild:
	.string "Muchos fans vienen incluso desde\nmás allá de HOENN.\pYo me lo pasé pipa cuando fui\nal CLUB de FANS de ENTRENADORES\lque hay en CALAGUA.$"
	.string ""
	.string ""
	.string ""

