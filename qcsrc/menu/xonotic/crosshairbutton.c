#ifdef INTERFACE
CLASS(XonoticCrosshairButton) EXTENDS(RadioButton)
	METHOD(XonoticCrosshairButton, configureXonoticCrosshairButton, void(entity, float, float))
	METHOD(XonoticCrosshairButton, setChecked, void(entity, float))
	METHOD(XonoticCrosshairButton, draw, void(entity))
	ATTRIB(XonoticCrosshairButton, fontSize, float, SKINFONTSIZE_NORMAL)
	ATTRIB(XonoticCrosshairButton, image, string, SKINGFX_CROSSHAIRBUTTON)

	ATTRIB(XonoticCrosshairButton, useDownAsChecked, float, 1)
	ATTRIB(XonoticCrosshairButton, src3, string, string_null)

	ATTRIB(XonoticCrosshairButton, cvarName, string, string_null)
	ATTRIB(XonoticCrosshairButton, cvarValueFloat, float, 0)
	METHOD(XonoticCrosshairButton, loadCvars, void(entity))
	METHOD(XonoticCrosshairButton, saveCvars, void(entity))
ENDCLASS(XonoticCrosshairButton)
entity makeXonoticCrosshairButton(float, float);
#endif

#ifdef IMPLEMENTATION
entity makeXonoticCrosshairButton(float theGroup, float theCrosshair)
{
	entity me;
	me = spawnXonoticCrosshairButton();
	me.configureXonoticCrosshairButton(me, theGroup, theCrosshair);
	return me;
}
void configureXonoticCrosshairButtonXonoticCrosshairButton(entity me, float theGroup, float theCrosshair)
{
	me.cvarName = "crosshair";
	me.cvarValueFloat = theCrosshair;
	me.loadCvars(me);
	me.configureRadioButton(me, string_null, me.fontSize, me.image, theGroup, 0);
	me.srcMulti = 1;
	me.src3 = strzone(strcat("/gfx/crosshair", ftos(me.cvarValueFloat)));
}
void setCheckedXonoticCrosshairButton(entity me, float val)
{
	if(val != me.checked)
	{
		me.checked = val;
		me.saveCvars(me);
	}
}
void loadCvarsXonoticCrosshairButton(entity me)
{
	if not(me.cvarName)
		return;

	me.checked = (cvar(me.cvarName) == me.cvarValueFloat);
}
void saveCvarsXonoticCrosshairButton(entity me)
{
	if not(me.cvarName)
		return;

	if(me.checked)
		cvar_set(me.cvarName, ftos(me.cvarValueFloat));
	// TODO on an apply button, read _cl_color and execute the color command for it
}
void drawXonoticCrosshairButton(entity me)
{
	vector sz, rgb;
	float a;

	rgb = eX * cvar("crosshair_color_red") + eY * cvar("crosshair_color_green") + eZ * cvar("crosshair_color_blue");
	a = cvar("crosshair_color_alpha");

	if(!me.checked && !me.focused)
	{
		a *= me.disabledAlpha;
		rgb = '1 1 1';
	}

	drawCheckBox(me);

	sz = draw_PictureSize(me.src3);
	sz = globalToBoxSize(sz, draw_scale);
	sz = sz * cvar("crosshair_size");
	if(sz_x > 0.95)
		sz = sz * (0.95 / sz_x);
	if(sz_y > 0.95)
		sz = sz * (0.95 / sz_y);

	draw_Picture('0.5 0.5 0' - 0.5 * sz, me.src3, sz, rgb, a);
}
#endif
