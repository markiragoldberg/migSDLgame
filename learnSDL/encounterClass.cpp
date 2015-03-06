#include "encounterClass.h"

void dialogueNode::addOption(std::string option)
{
	_options.push_back(option);
}

std::string dialogueNode::id() const
{
	return _id;
}

std::string dialogueNode::trans() const
{
	return _trans;
}

std::string dialogueNode::text() const
{
	return _text;
}

bool dialogueNode::ending() const
{
	return _ending;
}

bool dialogueNode::combat() const
{
	return _combat;
}

std::string dialogueNode::option(unsigned index) const
{
	if (index < _options.size())
	{
		return _options[index];
	}
	return "";
}

void dialogueNode::setId(std::string id)
{
	_id = id;
}

void dialogueNode::setTrans(std::string trans)
{
	_trans = trans;
}

void dialogueNode::setText(std::string text)
{
	_text = text;
}

void dialogueNode::setEnding(bool ending)
{
	_ending = ending;
}

void dialogueNode::setCombat(bool combat)
{
	_combat = combat;
}

dialogueNode::dialogueNode(std::string id, std::string trans, std::string text, bool ending, bool combat)
	: _id(id), _trans(trans), _text(text), _ending(ending), _combat(combat) {};

dialogueNode::dialogueNode()
{
	_id = "Error: no dialogueNode id";
	_trans = "Error: no dialogueNode transition";
	_text = "Error: no dialogueNode text";
	_ending = true;
	_combat = false;
}


//--------------------------------------------------

std::string encounter::name() const
{
	return _name;
}

std::string encounter::monsterType(unsigned index) const
{
	if (_monsterType.size() > index)
	{
		return _monsterType[index];
	}
	return "";
}

unsigned encounter::monsterCount(unsigned index) const
{
	if (_monsterCount.size() > index)
	{
		return _monsterCount[index];
	}
	return 0;
}

const dialogueNode * encounter::dialogue(std::string key) const
{
	if (_dialogue.count(key)== 1)
	{
		return _dialogue.at(key);
	}
	return NULL;
}

void encounter::addNpc(std::string type, unsigned count)
{
	if (count > 0)
	{
		_monsterType.push_back(type);
		_monsterCount.push_back(count);
	}
}
void encounter::addDialogue(dialogueNode* dialogue)
{
	_dialogue[dialogue->id()] = dialogue;
}

encounter::encounter(std::string name) : _name(name)
{

}

encounter::~encounter()
{
	for (auto i : _dialogue)
	{
		delete i.second;
	}
}

