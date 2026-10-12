SootopolisCity_House2_MapScripts::
	.byte 0

SootopolisCity_House2_EventScript_ExpertF::
	lock
	faceplayer
	msgbox SootopolisCity_House2_Text_DidYouKnowAboutMtPyreOrbs, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, SootopolisCity_House2_EventScript_KnowAboutOrbs
	call_if_eq VAR_RESULT, NO, SootopolisCity_House2_EventScript_DontKnowAboutOrbs
	release
	end

SootopolisCity_House2_EventScript_KnowAboutOrbs::
	msgbox SootopolisCity_House2_Text_YesTwoOrbsSideBySide, MSGBOX_DEFAULT
	return

SootopolisCity_House2_EventScript_DontKnowAboutOrbs::
	msgbox SootopolisCity_House2_Text_OughtToVisitAndSee, MSGBOX_DEFAULT
	return

SootopolisCity_House2_Text_DidYouKnowAboutMtPyreOrbs:
	.string "El MONTE PÍRICO…\p¿Sabías que en la cumbre hay\ndos esferas, una al lado de otra?$"
	.string ""
	.string ""

SootopolisCity_House2_Text_YesTwoOrbsSideBySide:
	.string "Sí, dos esferas juntas…\pY cuando las ves te sientes mucho\nmás tranquila, no sé por qué.$"
	.string ""
	.string ""

SootopolisCity_House2_Text_OughtToVisitAndSee:
	.string "¿Sabes una cosa?\nQuizás deberías ir a verlas tú.$"
	.string ""

