PacifidlogTown_House5_MapScripts::
	.byte 0

PacifidlogTown_House5_EventScript_MirageIslandWatcher::
	lock
	faceplayer
	specialvar VAR_RESULT, IsMirageIslandPresent
	goto_if_eq VAR_RESULT, TRUE, PacifidlogTown_House5_EventScript_MirageIslandPresent
	msgbox PacifidlogTown_House5_Text_CantSeeMirageIslandToday, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House5_EventScript_MirageIslandPresent::
	msgbox PacifidlogTown_House5_Text_CanSeeMirageIslandToday, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House5_EventScript_Gentleman::
	msgbox PacifidlogTown_House5_Text_MirageIslandAppearDependingOnWeather, MSGBOX_NPC
	end

PacifidlogTown_House5_Text_CantSeeMirageIslandToday:
	.string "Hoy no se ve la ISLA ESPEJISMO…$"

PacifidlogTown_House5_Text_CanSeeMirageIslandToday:
	.string "¡Ay, ay, ay! ¡Sí, la veo!\n¡Hoy sí que veo la ISLA ESPEJISMO!$"
	.string ""

PacifidlogTown_House5_Text_MirageIslandAppearDependingOnWeather:
	.string "La ISLA ESPEJISMO…\pes visible o invisible dependiendo de\nlas condiciones meteorológicas que\lprovocan la aparición de espejismos.\p¿O quizás es que aparece y\ndesaparece así, sin más?…$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

