MysteryGiftScript_VisitingTrainer::
	setvaddress MysteryGiftScript_VisitingTrainer
	special ValidateEReaderTrainer
	vgoto_if_eq VAR_RESULT, 0, MysteryGiftScript_VisitingTrainerArrived
	lock
	faceplayer
	vmessage sText_MysteryGiftVisitingTrainerInstructions
	waitmessage
	waitbuttonpress
	release
	end

MysteryGiftScript_VisitingTrainerArrived:
	lock
	faceplayer
	vmessage sText_MysteryGiftVisitingTrainerArrived
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftVisitingTrainerInstructions:
	.string "Gracias por usar el sistema\ndel REGALO MISTERIOSO.\pAl llevar la TARJETA MISTERIOSA,\npodrás participar en una encuesta\len la TIENDA POKéMON.\pAprovecha las encuestas para\ninvitar a ENTRENADORES\la ARRECÍPOLIS.\pVoy a darte una contraseña secreta\npara la encuesta:\p“QUIERO ENTRENADORES\nMUY FUERTES”\pEscríbela en un cuestionario y\nenvíala al sistema de comunicación\linalámbrica.$"
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

sText_MysteryGiftVisitingTrainerArrived:
	.string "Gracias por usar el sistema\ndel REGALO MISTERIOSO.\pHa llegado un ENTRENADOR\na ARRECÍPOLIS y te está buscando.\pEsperamos que disfrutes del\ncombate con el ENTRENADOR.\pSi quieres, puedes invitar a más\nENTRENADORES usando otras\lcontraseñas.\pBusca otras contraseñas\nque vayan bien.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""
