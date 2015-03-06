#pragma once
#include <string>
#include <vector>
#include <unordered_map>

//possibly move this to a different file at some point
class dialogueNode
{
public:
	std::string id() const;
	std::string trans() const;
	std::string text() const;
	bool ending() const;
	bool combat() const;
	std::string option(unsigned index) const;
	
	void addOption(std::string option);
	void setId(std::string id);
	void setTrans(std::string trans);
	void setText(std::string text);
	void setEnding(bool ending);
	void setCombat(bool combat);

	dialogueNode(std::string id, std::string trans, std::string text, bool ending, bool combat);
	dialogueNode();
private:
	std::string _id;
	std::string _trans;
	std::string _text;
	std::vector<std::string> _options;
	bool _ending;
	bool _combat;
};

class encounter
{
public:
	std::string name() const;
	std::string monsterType(unsigned index) const;
	unsigned monsterCount(unsigned index) const;
	const dialogueNode * dialogue(std::string key) const;

	void addNpc(std::string type, unsigned count);
	void addDialogue(dialogueNode* dialogue);

	encounter(std::string name);
	~encounter();
private:
	std::string _name;
	std::vector<std::string> _monsterType;
	std::vector<unsigned> _monsterCount;
	std::unordered_map<std::string,dialogueNode*> _dialogue;
};
