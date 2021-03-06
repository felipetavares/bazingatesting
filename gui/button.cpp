#include "button.h"
#include "../cache.h"
#include "../text.h"
using namespace bazinga;

gui::Button::Button (string text) {
	this->text = text;
	click = false;
	hover = false;
	image = NULL;
}

gui::Button::Button (Path path) {
	click = false;
	hover = false;
	text = "";
	image = cache::getTexture(path);
}

void gui::Button::pack (int w, int h) {
	this->w = w;
	this->h = h;
}

void gui::Button::getPreferredSize (int& w, int& h) {
	auto font = cache::getFont("default");
	font->setSize(16);
	text::setFont(font);
	auto size = text::measureText(text);

	if (text == "") {
		w = 16+12;
	} else {
		w = size.w+12;
	}

	h = 16+12;
}

void gui::Button::getMinSize (int& w, int& h) {
	auto font = cache::getFont("default");
	font->setSize(16);
	text::setFont(font);
	auto size = text::measureText(text);

	w = size.w+12;
	h = 16+12;
}

void gui::Button::setPosition (int x, int y) {
	this->x = x;
	this->y = y;
}

void gui::Button::rrender (int x, int y) {
	video::setColor1(video::Color(0, 0, 0, 0));
	video::setColor2(video::Color(0, 0, 0, 0.2));
	video::shadow(ux, uy, w, h, 1);

	if (click) {
		video::setColor1(*gui::colors["active"]);
		video::setColor2(*gui::colors["active.contrast"]);
	} else if (hover) {
		video::setColor1(*gui::colors["foreground"]);
		video::setColor2(*gui::colors["foreground.contrast"]);
	}
	else {
		video::setColor1(*gui::colors["background"]);
		video::setColor2(*gui::colors["background.contrast"]);
	}

	video::fillVGradient(this->x+x, this->y+y, w, h);

	if (image) {
		image->render(ux+w/2, uy+h/2);
	}

	auto font = cache::getFont("default");
	font->setColor(*gui::colors["text.regular"]);
	font->setSize(16);
	text::setFont(font);
	text::setAlign(text::Center);
	text::setBaseline(text::Middle);
	text::fillText(text, this->x+x+this->w/2, this->y+y+this->h/2);
}

int gui::Button::getW () {
	return w;
}

int gui::Button::getH () {
	return h;
}

void gui::Button::rleave (int x, int y) {
	hover = false;
	click = false;
}

void gui::Button::renter (int x, int y) {
	hover = true;
}

void gui::Button::rclick (int x, int y) {
	click = false;

	if (onClick)
		onClick(this);
}

void gui::Button::ractivate (int x, int y) {
	click = true;
}