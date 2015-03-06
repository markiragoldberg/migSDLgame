#include "encounters.h"

//This is very temporary and shouldn't exist long!
#pragma warning(disable:4996)


std::vector<encounter*> encounters;

bool loadData()
{
	FILE* fp =	fopen("data/test2.json","r");
	fseek(fp, 0, SEEK_END);
	size_t filesize = (size_t)ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* buffer = (char*)malloc(filesize + 1);
	size_t readLength = fread(buffer, 1, filesize, fp);
	buffer[readLength] = '\0';
	fclose(fp);
	// In situ parsing the buffer into d, buffer will also be modified
	// Query/manipulate the DOM here...
	rapidjson::Document jsondata;
	jsondata.Parse(buffer);

	for (unsigned i = 0; i < jsondata.Size(); i++)
	{
		if (jsondata[i].HasMember("encounter"))
		{
			encounters.push_back(new encounter(jsondata[i]["encounter"].GetString()));
		}
		else
		{
			encounters.push_back(new encounter("Error: Unnamed Encounter"));
		}
		if (jsondata[i].HasMember("npcs") && jsondata[i]["npcs"].IsArray())
		{
			for (rapidjson::SizeType j = 0; j < jsondata[i]["npcs"].Size()-1; j+=2)
			{
				encounters[encounters.size() - 1]->addNpc(jsondata[i]["npcs"][j].GetString(), jsondata[i]["npcs"][j + 1].GetInt());
			}
		}

		const rapidjson::Value& d = jsondata[i]["dialogue"];
		for (rapidjson::SizeType i = 0; i < d.Size(); i++)
		{
			dialogueNode* diag = new dialogueNode();
			if (i == 0)
			{
				diag->setId("start");
				diag->setTrans("start");
			}
			else
			{
				if (d[i].HasMember("node"))
				{
					diag->setId(d[i]["node"].GetString());
					if (diag->id() == "wonCombat")
					{
						diag->setTrans("wonCombat");
					}
				}
				if (d[i].HasMember("trans"))
				{
					diag->setTrans(d[i]["trans"].GetString());
				}
			}
			if (!d[i].HasMember("ending"))
			{
				diag->setEnding(false);
			}
			else if (strcmp(d[i]["ending"].GetString(),"startCombat")==0)
			{
				diag->setCombat(true);
			}
			if (d[i].HasMember("text"))
			{
				diag->setText(d[i]["text"].GetString());
			}
			if (d[i].HasMember("options"))
			{
				const rapidjson::Value& o = d[i]["options"];
				for (rapidjson::SizeType k = 0; k < o.Size(); k++)
				{
					if (o[k].IsString())
					{
						diag->addOption(o[k].GetString());
					}
				}
			}
			encounters[encounters.size() - 1]->addDialogue(diag);
		}
	}
	free(buffer);
	return true;
}

const encounter * getEncounter(unsigned index)
{
	if (index < encounters.size())
	{
		return encounters[index];
	}
	return NULL;
}

void deleteEncounters()
{
	while (encounters.size() > 0)
	{
		delete encounters.back();
		encounters.pop_back();
	}
}
