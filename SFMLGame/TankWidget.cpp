#include "stdafx.h"
#include "TankWidget.h"


TankWidget::TankWidget( sf::Vector2f _pos, float _width, float _height ) : pos( _pos), width( _width ), height( _height )
{
	containerShape.setPosition(pos);
	containerShape.setSize(sf::Vector2f(width, height));
	containerShape.setFillColor(sf::Color::Transparent);
	containerShape.setOutlineThickness(3);
	containerShape.setOutlineColor(sf::Color(250, 250, 250));
	
	amountShape.setFillColor(sf::Color::White); // TODO: This colour should be passed in as a parameter to the widget constructor.
}


TankWidget::~TankWidget()
{
}


void TankWidget::Render(shared_ptr<sf::RenderWindow> pwindow, unsigned int percent)
{
	pwindow->draw(containerShape); // the border of the widget

	if (percent > 0 )
	{
		if (percent > 100)
			percent = 100;

		float h = ( (float)percent * height ) / 100;
		amountShape.setPosition( pos.x, pos.y + height - h );
		amountShape.setSize(sf::Vector2f(width, h));
		pwindow->draw(amountShape); // the actual amount being displayed by the widget.
	}
}