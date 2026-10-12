Route111_Text_MakingRoomUseTMToMakeYourOwn:
	.string "¿Qué es esto?\n¿Qué he hecho?\p¡Anda, qué guay! Me he construido mi\npropio cuartel general aquí gracias a\lun movimiento POKéMON.\p¡Tengo una idea! Te daré esta MT para\nque tú también te construyas el tuyo.$"
	.string ""
	.string ""
	.string ""
	.string ""
	.string ""

Route111_Text_ExplainSecretPower:
	.string "Busca un árbol grande que sea un poco\nmás ancho que todos los demás.\pUsa DAÑO SECRETO delante.\nCaerá una liana y podrás\ltrepar hasta la copa.\pTendrás un montón de espacio\npara poner tus cosas.\pSerá tu cuartel general…\n¡TU BASE SECRETA!\pHazte una corriendo…\pOtra cosa: no hace falta hacerse la\nBASE SECRETA en un árbol.\pUsa DAÑO SECRETO en paredes\nrocosas que tengan muescas.\pYo también voy a buscar lugares\ndonde crear mi base. ¡Me piro!$"
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

Route111_Text_DontWantThis:
	.string "Oh, ¿no lo quieres?\nBueno, aquí estaré por si cambias\lde idea.$"
	.string ""

Route111_Text_DontHaveAnyRoom:
	.string "Vaya, no tienes sitio para esto.\pTe lo voy a guardar, así que vuelve\ncuando quieras a por él, ¿eh?$"
	.string ""
	.string ""

Route111_EventScript_SecretPowerMan::
	lock
	faceplayer
	msgbox Route111_Text_MakingRoomUseTMToMakeYourOwn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route111_EventScript_GiveSecretPower
	msgbox Route111_Text_DontWantThis, MSGBOX_DEFAULT
	release
	end

Route111_EventScript_GiveSecretPower::
	giveitem ITEM_TM_SECRET_POWER
	goto_if_eq VAR_RESULT, FALSE, Route111_EventScript_NoRoomForSecretPower
	msgbox Route111_Text_ExplainSecretPower, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_RECEIVED_SECRET_POWER
	clearflag FLAG_HIDE_SLATEPORT_CITY_TM_SALESMAN
	call_if_eq VAR_FACING, DIR_WEST, Route111_EventScript_SecretPowerManExit
	call_if_eq VAR_FACING, DIR_EAST, Route111_EventScript_SecretPowerManExit
	call_if_eq VAR_FACING, DIR_NORTH, Route111_EventScript_SecretPowerManExitNorth
	removeobject VAR_LAST_TALKED
	release
	end

Route111_EventScript_SecretPowerManExit::
	applymovement VAR_LAST_TALKED, Route111_Movement_SecretPowerManExit
	waitmovement 0
	return

Route111_EventScript_SecretPowerManExitNorth::
	applymovement VAR_LAST_TALKED, Route111_Movement_SecretPowerManExitNorth
	waitmovement 0
	return

Route111_EventScript_NoRoomForSecretPower::
	msgbox Route111_Text_DontHaveAnyRoom, MSGBOX_DEFAULT
	release
	end

Route111_Movement_SecretPowerManExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

Route111_Movement_SecretPowerManExitNorth:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end
