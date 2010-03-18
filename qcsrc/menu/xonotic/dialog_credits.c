#ifdef INTERFACE
CLASS(XonoticCreditsDialog) EXTENDS(XonoticDialog)
	METHOD(XonoticCreditsDialog, fill, void(entity))
	METHOD(XonoticCreditsDialog, focusEnter, void(entity))
	ATTRIB(XonoticCreditsDialog, title, string, "Credits")
	ATTRIB(XonoticCreditsDialog, color, vector, SKINCOLOR_DIALOG_CREDITS)
	ATTRIB(XonoticCreditsDialog, intendedWidth, float, SKINWIDTH_CREDITS)
	ATTRIB(XonoticCreditsDialog, rows, float, SKINROWS_CREDITS)
	ATTRIB(XonoticCreditsDialog, columns, float, 2)
	ATTRIB(XonoticCreditsDialog, creditsList, entity, NULL)
ENDCLASS(XonoticCreditsDialog)
#endif

#ifdef IMPLEMENTATION
void fillXonoticCreditsDialog(entity me)
{
	entity e;
	me.TR(me);
		me.TD(me, me.rows - 1, me.columns, me.creditsList = makeXonoticCreditsList());
	me.gotoRC(me, me.rows - 1, 0);
		me.TD(me, 1, me.columns, e = makeXonoticButton("OK", '0 0 0'));
			e.onClick = Dialog_Close;
			e.onClickEntity = me;
}
void focusEnterXonoticCreditsDialog(entity me)
{
	me.creditsList.scrolling = time + 1;
}
#endif
