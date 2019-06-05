#pragma once
//---- include section ------
#include "StaticObject.h"
#include "Surprise.h"
#include <string>

//---- using section --------
using std::string;

/*
 * Container class
 */
class Container :
	public StaticObject
{
public:
	// surprises list
	using SurprisesList = std::vector<std::shared_ptr<Surprise>>;
	// get surprises
	const SurprisesList& getSurprises() const { return m_surprises; }
	// check if container is empty
	bool isEmpty() const { return m_surprises.empty(); }
	// pickup content
	virtual void pickup(Player* owner);
	// clear all surprises
	void clearSurprises() { m_surprises.clear(); }
	// convert to string
	virtual string toString() const override;
protected:
	// constructor
	explicit Container(GameScreen& gameScreen);
private:
	// surprises
	SurprisesList m_surprises;
	// random surprises
	static SurprisesList randSurprises();
	// init
	void init();
};

