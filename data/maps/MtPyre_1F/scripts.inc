MtPyre_1F_MapScripts::
	.byte 0

MtPyre_1F_EventScript_CleanseTagWoman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CLEANSE_TAG, MtPyre_1F_EventScript_ReceivedCleanseTag
	msgbox MtPyre_1F_Text_TakeThisForYourOwnGood, MSGBOX_DEFAULT
	giveitem ITEM_CLEANSE_TAG
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_CLEANSE_TAG
	release
	end

MtPyre_1F_EventScript_ReceivedCleanseTag::
	msgbox MtPyre_1F_Text_ExplainCleanseTag, MSGBOX_DEFAULT
	release
	end

MtPyre_1F_EventScript_PokefanF::
	msgbox MtPyre_1F_Text_ComeToPayRespects, MSGBOX_NPC
	end

MtPyre_1F_EventScript_Man::
	msgbox MtPyre_1F_Text_RestingPlaceOfZigzagoon, MSGBOX_NPC
	end

MtPyre_1F_Text_TakeThisForYourOwnGood:
	.string "En el MONTE PÍRICO te puedes encontrar\ncon todo tipo de criaturas…\pNunca se sabe qué puede pasar,\nasí que toma esto por tu bien.$"
	.string ""
	.string ""
	.string ""

MtPyre_1F_Text_ExplainCleanseTag:
	.string "Dale este AMULETO a algún\nPOKéMON.\pTe ayudará a mantener alejados\na los POKéMON salvajes.$"
	.string ""
	.string ""

MtPyre_1F_Text_ComeToPayRespects:
	.string "¿Has venido a presentar tus respetos\na las almas de los POKéMON que ya\lno están con nosotros?\pRecuerda que has de cuidar de tus\nPOKéMON con mucho cariño.$"
	.string ""
	.string ""

MtPyre_1F_Text_RestingPlaceOfZigzagoon:
	.string "Aquí descansa en paz mi ZIGZAGOON.\nYo lo quería tanto…$"
	.string ""

